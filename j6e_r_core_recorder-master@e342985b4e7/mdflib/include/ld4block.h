/**
 * *****************************************************************************
 * @brief       mdflib
 * @author      Ji Wei (BCSC/EPA4, XC-AS/ENG-PMT2-CN) (wei.ji2@cn.bosch.com)
 * @date        2024-11-1
 *
 * @Copyright (c) 2024-2030 Robert Bosch GmbH. All rights reserved.
 * *****************************************************************************
 */

#pragma once
#include "datalistblock.h"
namespace mdf::detail {

namespace Ld4Flags {

constexpr uint32_t EqualSampleCount = 0x01;
constexpr uint32_t TimeValues = 0x02;
constexpr uint32_t AngleValues = 0x04;
constexpr uint32_t DistanceValues = 0x08;
constexpr uint32_t InvalidData = 0x80000000;
}  // namespace Ld4Flags

class Ld4Block : public DataListBlock {
 public:
  void GetBlockProperty(BlockPropertyList& dest) const override;
  size_t Read(std::FILE* file) override;

 private:
  uint32_t flags_ = 0;
  uint32_t nof_blocks_ = 0;
  uint64_t equal_sample_count_ = 0;
  std::vector<uint64_t> offset_list_;
  std::vector<int64_t>
      time_values_;  // Note that this actually store an int64_t or a double.
  std::vector<int64_t>
      angle_values_;  // Note that this actually store an int64_t or a double.
  std::vector<int64_t> distance_values_;  // Note that this actually store an
                                          // int64_t or a double.
};
}  // namespace mdf::detail
