
#include "dl4block.h"

namespace {

constexpr size_t kIndexNext = 0;
constexpr size_t kIndexData = 1;

std::string MakeFlagString(uint8_t flag) {
  std::ostringstream s;
  if (flag & 0x01) {
    s << "Equal";
  }
  return s.str();
}
}  // namespace
namespace mdf::detail {

void Dl4Block::GetBlockProperty(BlockPropertyList &dest) const {
  MdfBlock::GetBlockProperty(dest);

  dest.emplace_back("Links", "", "", BlockItemType::HeaderItem);
  dest.emplace_back("Next DL", ToHexString(Link(kIndexNext)),
                    "Link to next DL block", BlockItemType::LinkItem);
  for (size_t ii = 0; ii < nof_blocks_; ++ii) {
    dest.emplace_back("Data", ToHexString(Link(kIndexData + ii)),
                      "Link to data block", BlockItemType::LinkItem);
  }
  dest.emplace_back("", "", "", BlockItemType::BlankItem);

  dest.emplace_back("Information", "", "", BlockItemType::HeaderItem);

  dest.emplace_back("Flags", MakeFlagString(flags_));
  dest.emplace_back("Nof Data Blocks", std::to_string(nof_blocks_));
  dest.emplace_back("Equal Length", std::to_string(equal_length_));
  for (auto offset : offset_list_) {
    dest.emplace_back("Offset", std::to_string(offset), "Offset in data block");
  }
}

size_t Dl4Block::Read(std::FILE *file) {
  size_t bytes = ReadHeader4(file);
  bytes += ReadNumber(file, flags_);
  std::vector<uint8_t> reserved;
  bytes += ReadByte(file, reserved, 3);
  bytes += ReadNumber(file, nof_blocks_);
  if (flags_ & Dl4Flags::EqualLength) {
    bytes += ReadNumber(file, equal_length_);
  } else {
    for (uint32_t ii = 0; ii < nof_blocks_; ++ii) {
      uint64_t offset = 0;
      bytes += ReadNumber(file, offset);
      offset_list_.push_back(offset);
    }
  }
  ReadLinkList(file, kIndexData, nof_blocks_);
  return bytes;
}

size_t Dl4Block::Write(std::FILE *file) {
  const bool update = FilePosition() > 0;
  if (update) {
    // The DL block properties cannot be changed, but it
    // is possible to append DL blocks
    WriteBlockList(file, kIndexData);
    return block_length_;
  }
  const size_t nof = block_list_.size(); // Number of DZ/DT blocks
  block_type_ = "##DL";
  link_list_.resize(1 + nof);

  block_length_ = 24 + 8 + (nof*8) + 1 + 3 + 4;
  const bool equal = (flags_ & Dl4Flags::EqualLength) != 0;
  const bool time = (flags_ & Dl4Flags::TimeValues) != 0;
  const bool angle = (flags_ & Dl4Flags::AngleValues) != 0;
  const bool distance = (flags_ & Dl4Flags::DistanceValues) != 0;

  if (equal) {
    block_length_ += 8;
  } else {
    block_length_ += 8 * nof;
  }
  if (time) {
    block_length_ += 8 * nof;
  }
  if (angle) {
    block_length_ += 8 * nof;
  }
  if (distance) {
    block_length_ += 8 * nof;
  }

  auto bytes = MdfBlock::Write(file);
  bytes += WriteNumber(file,flags_);
  bytes += WriteBytes(file, 3);
  bytes += WriteNumber(file, static_cast<uint32_t>(nof));
  if (equal) {
    bytes += WriteNumber(file, equal_length_);
  } else {
    for (size_t index = 0; index < nof; ++index) {
      bytes += WriteNumber(file, Offset(index));
    }
  }

  if (time) {
    for (size_t index = 0; index < nof; ++index) {
      bytes += WriteNumber(file, TimeValue(index));
    }
  }

  if (angle) {
    for (size_t index = 0; index < nof; ++index) {
      bytes += WriteNumber(file, AngleValue(index));
    }
  }

  if (distance) {
    for (size_t index = 0; index < nof; ++index) {
      bytes += WriteNumber(file, DistanceValue(index));
    }
  }

  UpdateBlockSize(file, bytes);

  WriteBlockList(file, kIndexData);
  return bytes;
}

void Dl4Block::EqualLength(uint64_t length) {
  if (length > 0) {
    flags_ |= Dl4Flags::EqualLength;
  }
  equal_length_ = length;
}

uint64_t Dl4Block::EqualLength() const { return equal_length_;}

void Dl4Block::Offset(size_t index, uint64_t offset) {
  while (index >= offset_list_.size()) {
    offset_list_.push_back(0);
  }
  flags_ &= ~Dl4Flags::EqualLength;
  offset_list_[index] = offset;
}

uint64_t Dl4Block::Offset(size_t index) const {
  return index < offset_list_.size() ? offset_list_[index] : 0;
}

void Dl4Block::TimeValue(size_t index, uint64_t value) {
  while (index >= time_list_.size()) {
    time_list_.push_back(0);
  }
  flags_ |= Dl4Flags::TimeValues;
  time_list_[index] = value;
}

uint64_t Dl4Block::TimeValue(size_t index) const {
  return index < time_list_.size() ? time_list_[index] : 0;
}

void Dl4Block::AngleValue(size_t index, uint64_t value) {
  while (index >= angle_list_.size()) {
    angle_list_.push_back(0);
  }
  flags_ |= Dl4Flags::AngleValues;
  angle_list_[index] = value;
}

uint64_t Dl4Block::AngleValue(size_t index) const {
  return index < angle_list_.size() ? angle_list_[index] : 0;
}

void Dl4Block::DistanceValue(size_t index, uint64_t value) {
  while (index >= distance_list_.size()) {
    distance_list_.push_back(0);
  }
  flags_ |= Dl4Flags::DistanceValues;
  distance_list_[index] = value;
}

uint64_t Dl4Block::DistanceValue(size_t index) const {
  return index < distance_list_.size() ? distance_list_[index] : 0;
}

}  // namespace mdf::detail