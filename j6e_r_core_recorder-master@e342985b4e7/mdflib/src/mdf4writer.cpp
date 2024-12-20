
#include "mdf4writer.h"
#include <ctime>
#include "mdf/mdflogstream.h"
#include "mdf4file.h"
#include "platform.h"
#include "dt4block.h"
#include "hl4block.h"
#include "dl4block.h"
#include "dz4block.h"
#include "dg4block.h"
#include "cn4block.h"
#include "sr4block.h"

namespace mdf::detail {

Mdf4Writer::~Mdf4Writer() { StopWorkThread(); }

IChannelConversion* Mdf4Writer::CreateChannelConversion(IChannel* parent) {
  auto* cn4 = dynamic_cast<Cn4Block*>(parent);
  IChannelConversion* cc = nullptr;
  if (cn4 != nullptr) {
    auto cc4 = std::make_unique<Cc4Block>();
    cc4->Init(*cn4);
    cn4->AddCc4(cc4);
    cc = const_cast<Cc4Block*>(cn4->Cc());
  }
  return cc;
}

void Mdf4Writer::CreateMdfFile() {
  auto mdf4 = std::make_unique<Mdf4File>();
  mdf_file_ = std::move(mdf4);
}

void Mdf4Writer::SetDataGroupDtEndPosition(IDataGroup* cur_dg, std::FILE* file) {
  Platform::fseek64(file, 0, SEEK_END);
  if (cur_dg == nullptr) {
    printf("err:cur_dg is nullptr\n");
    return;
  }

  auto* dg4 = dynamic_cast<Dg4Block*>(cur_dg);
  if (dg4 == nullptr) {
    printf("err:dg4 is nullptr\n");
    return;
  }

  // if (dg4->Link(2) > 0) {
  //   printf("LInk2 > 0\n");
  //   return;
  // }

  dg4->SetLastFilePosition(file);
  auto position = GetFilePosition(file);
  dg4->UpdateLink(file, 2, position);
  dg4->SetLastFilePosition(file);

  // 获取写入后的文件偏移量
  long endOffset = ftell(file);
  if (endOffset == -1L) {
      //
      printf("get offset error\n");
  }
  printf("after set offset:%ld\n", endOffset);

}

void Mdf4Writer::SetLastPosition(std::FILE* file) {
  Platform::fseek64(file, 0, SEEK_END);

  auto* header = Header();
  if (header == nullptr) {
    return;
  }
  auto* last_dg = header->LastDataGroup();
  if (last_dg == nullptr) {
    return;
  }
  auto* dg4 = dynamic_cast<Dg4Block*>(last_dg);
  if (dg4 == nullptr) {
    return;
  }

  if (dg4->Link(2) > 0) {
    return;
  }

  dg4->SetLastFilePosition(file);
  auto position = GetFilePosition(file);
  dg4->UpdateLink(file, 2, position);
  dg4->SetLastFilePosition(file);
}

bool Mdf4Writer::PrepareForWriting() {

  auto *header = Header();
  if (header == nullptr) {
    MDF_ERROR() << "No header  found. Invalid use of the function.";
    return false;
  }

  // Retrieve all DataGroups from the header
  auto data_groups = header->DataGroups();
  if (data_groups.empty()) {
    return true;
  }

  // Iterate through all DataGroups and initialize them
  for (auto* dg : data_groups) {
    auto* dg4 = dynamic_cast<Dg4Block*>(dg);
    if (dg4 == nullptr) {
      MDF_ERROR() << "Invalid DG block type detected.";
      continue; // Skip invalid DataGroups
    }

    if (CompressData()) {
      // Create and initialize a compressed HL block
      auto hl4 = std::make_unique<Hl4Block>();
      hl4->Init(*dg4);
    } else {
      // Add an uncompressed DT block to the data block list
      auto& block_list = dg4->DataBlockList();
      auto dt4 = std::make_unique<Dt4Block>();
      dt4->Init(*dg4);
      block_list.push_back(std::move(dt4));
    }

    // Initialize all associated ChannelGroups
    auto cg_list = dg4->ChannelGroups();
    for (auto& cg4 : dg4->Cg4()) {
      if (!cg4) {
        continue; // Skip invalid ChannelGroups
      }
      cg4->PrepareForWriting(); // Prepare the ChannelGroup for writing
    }
  }


  return true;
}

void Mdf4Writer::SaveQueue(std::unique_lock<std::mutex>& lock) {
  if (CompressData()) {
    SaveQueueCompressed(lock);
    return;
  }

  // Save uncompressed data in last DG/DT block
  auto *header = Header();
  if (header == nullptr) {
    return;
  }

  // Retrieve all DataGroups from the header
  auto data_groups = header->DataGroups();
  if (data_groups.empty()) {
    //return;
  }
  if (sample_queue_.empty()) {
    return;
  }
  // Iterate through all DataGroups and initialize them
  for (auto* dg : data_groups) {
    auto* dg4 = dynamic_cast<Dg4Block*>(dg);
    if (dg4 == nullptr) {
      MDF_ERROR() << "Invalid DG block type detected.";
      continue; // Skip invalid DataGroups
    }

    auto& block_list = dg4->DataBlockList();
    if (block_list.empty()) {
      return;
    }
    auto* dt4 = dynamic_cast<Dt4Block*>(block_list.back().get());
    if (dt4 == nullptr) {
      return;
    }

    const auto data_position = dt4->DataPosition();
    if (data_position <= 0) {
      return;
    }

    lock.unlock();

    std::FILE* file = nullptr;
    Platform::fileopen(&file, filename_.c_str(), "r+b");
    if (file == nullptr) {
      lock.lock();
      return;
    }

    SetDataGroupDtEndPosition(dg4, file);

    lock.lock();

    //TrimQueue();

    const auto id_size = dg4->RecordIdSize();

    auto sample = sample_queue_.front();
    sample_queue_.pop_front();

    if (stop_time_ > 0 && sample.timestamp > stop_time_) {
      break;
    }
    auto* cg4 = dg4->FindCgRecordId(sample.record_id);
    if (cg4 == nullptr) {
      continue;
    }
    lock.unlock();
    printf("id_size = %d\n", id_size);
    cg4->WriteSample(file, id_size, sample.record_buffer);
    printf("data: \n");
    for (auto tmp_data : sample.record_buffer)
    {
      printf("0x%x ", tmp_data);
    }
    printf("\n");
    lock.lock();
    lock.unlock();
    printf("size = %d\n", sample.SampleSize());
    //const auto last_position = GetFilePosition(file);
    uint64_t block_length = 24 + sample.SampleSize();
    printf("block length = %d\n", block_length);
    dt4->UpdateBlockSize(file, block_length);
    printf("begin to write\n");
    dg4->Write(file); // Flush out data
    printf("write done\n");
    fclose(file);
    lock.lock();
  }
  return;

  // Only the last DT block is updated. So go to the last DT
  auto *last_dg = header->LastDataGroup();
  if (last_dg == nullptr) {
    return;
  }
  auto* dg4 = dynamic_cast<Dg4Block*>(last_dg);
  if (dg4 == nullptr) {
    return;
  }
  auto& block_list = dg4->DataBlockList();
  if (block_list.empty()) {
    return;
  }
  auto* dt4 = dynamic_cast<Dt4Block*>(block_list.back().get());
  if (dt4 == nullptr) {
    return;
  }
  const auto data_position = dt4->DataPosition();
  if (data_position <= 0) {
    return;
  }
  lock.unlock();

  std::FILE* file = nullptr;
  Platform::fileopen(&file, filename_.c_str(), "r+b");
  if (file == nullptr) {
    lock.lock();
    return;
  }

  SetLastPosition(file);

  lock.lock();

  TrimQueue();

  const auto id_size = dg4->RecordIdSize();

  while (!sample_queue_.empty()) {
    // Write a sample last to file
    auto sample = sample_queue_.front();
    sample_queue_.pop_front();

    if (stop_time_ > 0 && sample.timestamp > stop_time_) {
      break;
    }
    auto* cg4 = dg4->FindCgRecordId(sample.record_id);
    if (cg4 == nullptr) {
      continue;
    }
    lock.unlock();


    auto* vlsd_group = sample.vlsd_data ?
                       dg4->FindCgRecordId(sample.record_id + 1) : nullptr;
    // The next group must have the VLSD flag set otherwise it's not a VLSD group.
    if (vlsd_group != nullptr && (vlsd_group->Flags() & CgFlag::VlsdChannel) == 0) {
      vlsd_group = nullptr;
    }
    auto* cn4 = sample.vlsd_data && vlsd_group == nullptr ?
                  cg4->FindSdChannel() : nullptr;
    // If the sample holds VLSD data, save this data first and then update
    // the data index. VLSD data is stored in SD or CG. A dirty trick is that
    // the VLSD CG must have the next record_id
    if (vlsd_group != nullptr) {
      // Store as a VLSD record
      const auto vlsd_index = vlsd_group->WriteVlsdSample(file, id_size,
                                                    sample.vlsd_buffer);
      // Update the sample buffer with the new vlsd_index. Index is always
      // last 8 bytes in sample buffer
      const LittleBuffer buff(vlsd_index);
      if (sample.record_buffer.size() >= 8) {
        const auto index_pos =
            static_cast<int>(sample.record_buffer.size() - 8);
        std::copy(buff.cbegin(), buff.cend(),
                  std::next(sample.record_buffer.begin(), index_pos) );
      }
    } else if (cn4 != nullptr) {
      // Store as SD data on VLSD channel
      const auto vlsd_index = cn4->WriteSdSample(sample.vlsd_buffer);
      // Update the sample buffer with the new vlsd_index. Index is always
      // last 8 bytes in sample buffer
      const LittleBuffer buff(vlsd_index);
      if (sample.record_buffer.size() >= 8) {
        const auto index_pos =
            static_cast<int>(sample.record_buffer.size() - 8);
        std::copy(buff.cbegin(), buff.cend(),
                  std::next(sample.record_buffer.begin(), index_pos) );
      }
    }

    cg4->WriteSample(file, id_size, sample.record_buffer);
    lock.lock();
  }

  lock.unlock();
  const auto last_position = GetFilePosition(file);
  uint64_t block_length = 24 + (last_position - data_position);
  dt4->UpdateBlockSize(file, block_length);
  dg4->Write(file); // Flush out data
  fclose(file);
  lock.lock();

}

void Mdf4Writer::CleanQueue(std::unique_lock<std::mutex>& lock) {
  if (CompressData()) {
    CleanQueueCompressed(lock, true);
    return;
  }
  printf("Mdf4Writer::begin to clean\n");
  SaveQueue(lock);
  printf("clean done mdf4Writer\n");
}

void Mdf4Writer::SaveQueueCompressed(std::unique_lock<std::mutex>& lock) {
  TrimQueue();

  const auto nof_dz = CalculateNofDzBlocks();
  if (nof_dz < 2) {
    // Only save full 4MB DZ blocks
    return;
  }
  CleanQueueCompressed(lock, false); // Saves one DZ block only
}

void Mdf4Writer::CleanQueueCompressed(std::unique_lock<std::mutex>& lock,
                                      bool finalize) {
  // Save compressed data in last DG block by appending HL/DL and DZ/DT blocks
  constexpr size_t buffer_max = 4'000'000;
  if (sample_queue_.empty()) {
    // Nothing to save to the file.
    return;
  }

  auto *header = Header();
  if (header == nullptr) {
    return;
  }

  // Only the last DT block is updated. So go to the last DT
  auto *last_dg = header->LastDataGroup();
  if (last_dg == nullptr) {
    return;
  }
  auto* dg4 = dynamic_cast<Dg4Block*>(last_dg);
  if (dg4 == nullptr) {
    return;
  }


  if (dg4->DataBlockList().empty()) {
    auto& hl4_list = dg4->DataBlockList();
    // Add a HL4 block
    auto hl_block = std::make_unique<Hl4Block>();
    hl_block->Flags(0);
    hl_block->Type(Hl4ZipType::Deflate);
    hl4_list.push_back(std::move(hl_block));
  }
  auto* hl4 = dynamic_cast<Hl4Block*>(dg4->DataBlockList().back().get());
  if (hl4 == nullptr) {
    return;
  }

  // Open the file for writing
  lock.unlock();

  std::FILE* file = nullptr;
  Platform::fileopen(&file, filename_.c_str(), "r+b");
  if (file == nullptr) {
    lock.lock();
    return;
  }

  SetLastPosition(file);

  std::vector<uint8_t> buffer;
  buffer.reserve(4'000'000);

  // Create DL block
  auto dl4 = std::make_unique<Dl4Block>();
  dl4->Flags(0);
  size_t dz_count = 0;
  dl4->Offset(dz_count, offset_);

  const auto id_size = dg4->RecordIdSize();

  lock.lock();
  TrimQueue();

  while (!sample_queue_.empty()) {
    auto sample = sample_queue_.front();
    sample_queue_.pop_front();

    if (stop_time_ > 0 && sample.timestamp > stop_time_) {
      // No more data.
      break;
    }
    lock.unlock(); // Need to unlock the sample queue while file operation
    sample_queue_size_ -= sample.SampleSize();

    size_t max_index = sample.record_buffer.size()
                             + dg4->RecordIdSize()
                             + buffer.size();
    if (sample.vlsd_data ) {
      max_index += sample.vlsd_buffer.size() + 4 + id_size;
    }

    // Check if this DZ block is full (4MB). If break out.
    if (max_index >= buffer_max) {
      // If the measurement should be finalized, we need to create a new
      // DZ block and put the remaining samples there. If not we can break
      // here and assume that the next cyclic call will handle the next DZ
      // block.
      if (finalize || sample_queue_size_ > buffer_max) {
        // Purge the buffer to a DZ block and add it to the last DL block
        auto dz4 = std::make_unique<Dz4Block>();
        dz4->OrigBlockType("DT");
        dz4->Type(Dz4ZipType::Deflate);
        dz4->Data(buffer);
        dl4->Offset(dz_count, offset_);
        ++dz_count;
        offset_ += buffer.size();
        dl4->DataBlockList().push_back(std::move(dz4));


        buffer.clear();
        buffer.reserve(buffer_max);
      } else {
        sample_queue_size_ += sample.SampleSize();
        lock.lock(); // Lock the sample queue when leaving the while loop.
        sample_queue_.push_front(sample);
        break;
      }
    }
    // The following handling is similar as with uncompressed data but instead
    // of saving to file, we need to save it to a temporary buffer.
    auto* cg4 = dg4->FindCgRecordId(sample.record_id);
    if (cg4 == nullptr) {
      // Should not happen but lost sample is
      lock.lock();
      continue;
    }

    // If the sample have vlsd data, it could be stored in the next VLSD CG or
    // in a SD block.
    auto* vlsd_group = sample.vlsd_data ?
                       dg4->FindCgRecordId(sample.record_id + 1) : nullptr;
    // The next group must have the VLSD flag set otherwise it's not a VLSD group.
    if (vlsd_group != nullptr &&
        (vlsd_group->Flags() & CgFlag::VlsdChannel) == 0) {
      vlsd_group = nullptr;
    }
    // Needs a pointer to the channel in case of VLSD SD storage
    auto* cn4 = sample.vlsd_data && vlsd_group == nullptr ?
                        cg4->FindSdChannel() : nullptr;
    // If the sample holds VLSD data, save this data first and then update
    // the data index. VLSD data is stored in SD or CG. A dirty trick is that
    // the VLSD CG must have the next record_id

    if (vlsd_group != nullptr) {
      // Store as a VLSD record
      const auto vlsd_index = vlsd_group->WriteCompressedVlsdSample(buffer,
                                                                    id_size,
                                                          sample.vlsd_buffer);
      // Update the sample buffer with the new vlsd_index. Index is always
      // last 8 bytes in sample buffer
      const LittleBuffer buff(vlsd_index);
      if (sample.record_buffer.size() >= 8) {
        const auto index_pos =
            static_cast<int>(sample.record_buffer.size() - 8);
        std::copy(buff.cbegin(), buff.cend(),
                  std::next(sample.record_buffer.begin(), index_pos) );
      }
    } else if (cn4 != nullptr) {
      // Store as SD data on VLSD channel
      const auto vlsd_index = cn4->WriteSdSample(sample.vlsd_buffer);
      // Update the sample buffer with the new vlsd_index. Index is always
      // last 8 bytes in sample buffer
      const LittleBuffer buff(vlsd_index);
      if (sample.record_buffer.size() >= 8) {
        const auto index_pos =
            static_cast<int>(sample.record_buffer.size() - 8);
        std::copy(buff.cbegin(), buff.cend(),
                  std::next(sample.record_buffer.begin(), index_pos) );
      }
    }
    cg4->WriteCompressedSample(buffer, id_size, sample.record_buffer);
    lock.lock();
  }

  lock.unlock();

  if (!buffer.empty()) {
    if (buffer.size() > 100) {
      auto dz4 = std::make_unique<Dz4Block>();
      dz4->OrigBlockType("DT");
      dz4->Type(Dz4ZipType::Deflate);
      dz4->Data(buffer);
      auto& block_list = dl4->DataBlockList();
      block_list.push_back(std::move(dz4));
    } else {
      auto dt4 = std::make_unique<Dt4Block>();
      dt4->Data(buffer);
      auto& block_list = dl4->DataBlockList();
      block_list.push_back(std::move(dt4));
    }
    dl4->Offset(dz_count, offset_);
    ++dz_count;
    offset_ += buffer.size();
  }
  hl4->DataBlockList().push_back(std::move(dl4));


  dg4->Write(file); // Flush out data
  fclose(file);
  lock.lock();

  hl4->ClearData(); // Remove temp data
}

void Mdf4Writer::SetDataPosition(std::FILE* file) {
  if (CompressData()) {
    return;
  }
  auto *header = Header();
  if (header == nullptr) {
    return;
  }

  // Only the last DT block is updated. So go to the last DT
  auto *last_dg = header->LastDataGroup();
  if (last_dg == nullptr) {
    return;
  }
  auto* dg4 = dynamic_cast<Dg4Block*>(last_dg);
  if (dg4 == nullptr) {
    return;
  }
  auto& block_list = dg4->DataBlockList();
  if (block_list.empty()) {
    return;
  }
  auto* dt4 = dynamic_cast<Dt4Block*>(block_list.back().get());
  if (dt4 == nullptr) {
    return;
  }
  SetLastPosition(file);
  const auto data_position = GetFilePosition(file);
  dt4->DataPosition(data_position);
}

size_t Mdf4Writer::CalculateNofDzBlocks() {
  // The sample queue is locked but the queue is trimmed
  // First make a list record ID -> record size

  const auto *header = Header();
  if (header == nullptr) {
    return 0;
  }

  // Only the last DG block is updated. So go to the last DT
  const auto *last_dg = header->LastDataGroup();
  if (last_dg == nullptr) {
    return 0;
  }
  const auto* dg4 = dynamic_cast<const Dg4Block*>(last_dg);
  if (dg4 == nullptr) {
    return 0;
  }

  bool vlsd = false;
  const auto id_size = dg4->RecordIdSize();
  std::map<uint64_t, size_t> id_size_list;
  const auto& cg4_list = dg4->Cg4();
  for (const auto& cg4 : cg4_list) {
    if (!cg4) {
      continue;
    }
    // Ignore any VLSD CG group. There size is calculated later.
    if (cg4->Flags() & CgFlag::VlsdChannel) {
      // Indicate if the samples extra bytes should be counted
      vlsd = true;
      id_size_list.emplace(cg4->RecordId(), 0);
      continue;
    }
    const auto& sample_buffer = cg4->SampleBuffer();
    const auto record_size = id_size + sample_buffer.size();
    id_size_list.emplace(cg4->RecordId(), record_size);
  }
  uint64_t nof_bytes = 0; // Total
  for(const auto& sample : sample_queue_) {
    const auto itr = id_size_list.find(sample.record_id);
    if (itr == id_size_list.cend()) {
      continue;
    }
    nof_bytes += itr->second;
    if (vlsd) {
      nof_bytes += id_size + 4 + sample.vlsd_buffer.size();
    }
  }
  return (nof_bytes / 4'000'000) + 1;
}

bool Mdf4Writer::InitMeasurement() {
  offset_ = 0;
  return MdfWriter::InitMeasurement();
}

bool Mdf4Writer::WriteSignalData(std::FILE* file) {
  if (file == nullptr) {
    MDF_ERROR() << "File is not opened. File: " << Name();
    return false;
  }

  const auto *header = Header();
  if (header == nullptr) {
    MDF_ERROR() << "No header block found. File: " << Name();
    return false;
  }

  // Only the last DG block is updated. So go to the last DT
  const auto *last_dg = header->LastDataGroup();
  if (last_dg == nullptr) {
    return true;
  }

  auto cg_list = last_dg->ChannelGroups();
  for (auto* group : cg_list) {
    if (group == nullptr) {
      continue;
    }
    auto cn_list = group->Channels();
    for (auto* channel : cn_list) {
      if (channel == nullptr) {
        continue;
      }
      auto* cn4 = dynamic_cast<Cn4Block*>(channel);
      if (cn4 == nullptr) {
        continue;
      }
      cn4->WriteSignalData(file, CompressData());
      cn4->ClearData();
    }
  }
  return true;
}

Dg4Block* Mdf4Writer::GetLastDg4() {
  auto *header = Header();
  if (header == nullptr) {
    return nullptr;
  }

  // Only the last DT block is updated. So go to the last DT
  auto *last_dg = header->LastDataGroup();
  if (last_dg == nullptr) {
    return nullptr;
  }
  return dynamic_cast<Dg4Block*>(last_dg);
}

}  // namespace mdf::detail