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


class Dt4Block : public DataBlock {
 public:
  Dt4Block();
  void Init(const MdfBlock &id_block) override;
  void GetBlockProperty(BlockPropertyList& dest) const override;
  size_t Read(std::FILE* file) override;
  size_t Write(std::FILE *file) override;
  [[nodiscard]] size_t DataSize() const override;
  void UpdateDataSize(std::FILE* file);

};

}  // namespace mdf::detail
