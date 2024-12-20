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
#include "datablock.h"

namespace mdf::detail {

class Rd4Block : public DataBlock {
 public:
  size_t Read(std::FILE *file) override;

 protected:
  [[nodiscard]] size_t DataSize() const override;
};

}  // namespace mdf::detail
