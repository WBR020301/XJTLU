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
#include <map>
#include "datablock.h"
#include "vlsddata.h"

namespace mdf::detail {

class Sd4Block : public DataBlock {
 public:
  size_t Read(std::FILE *file) override;
  size_t Write(std::FILE *file) override;

  uint64_t AppendData(const std::string& text);
  uint64_t AppendData(const std::vector<uint8_t>& data);
 protected:
  [[nodiscard]] size_t DataSize() const override;
 private:
  uint64_t AppendData(const VlsdData& data);
  std::map<VlsdData, uint64_t> sorted_data_;
};
}  // namespace mdf::detail
