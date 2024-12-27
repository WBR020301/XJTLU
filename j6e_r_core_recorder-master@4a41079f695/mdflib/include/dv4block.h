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
#include <cstdio>

#include "datablock.h"
namespace mdf::detail {

class Dv4Block : public DataBlock {
 public:
  void GetBlockProperty(BlockPropertyList& dest) const override;
  size_t Read(std::FILE* file) override;
  [[nodiscard]] size_t DataSize() const override;
};

}  // namespace mdf::detail
