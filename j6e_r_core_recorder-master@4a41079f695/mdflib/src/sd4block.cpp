
#include "sd4block.h"
#include "littlebuffer.h"

namespace mdf::detail {
size_t Sd4Block::Read(std::FILE *file) {
  size_t bytes = ReadHeader4(file);
  data_position_ = GetFilePosition(file);
  return bytes;
}

size_t Sd4Block::DataSize() const {
  return block_length_ > 24 ? block_length_ - 24 : 0;
}

size_t Sd4Block::Write(std::FILE *file) {
  const auto update = FilePosition() > 0;
  if (update) {
    return block_length_;
  }
  block_type_ = "##SD";
  link_list_.clear();
  block_length_ = 24 + data_.size();

  auto bytes = MdfBlock::Write(file);
  bytes += WriteByte(file, data_);
  return bytes;
}

uint64_t Sd4Block::AppendData(const VlsdData& data) {
  // First check if the data block already exist
  auto itr = sorted_data_.find(data);
  if (itr != sorted_data_.cend()) {
    return itr->second;
  }
  const auto index = static_cast<uint64_t>(data_.size());
  LittleBuffer<uint32_t> length(data.Size());
  data_.insert(data_.end(), length.cbegin(), length.cend());
  data_.insert(data_.end(), data.Cbegin(), data.Cend());
  return index;
}

uint64_t Sd4Block::AppendData(const std::string &text) {
  VlsdData temp(text);
  return AppendData(temp);
}

}  // namespace mdf::detail