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

#include "mdf4writer.h"

namespace mdf::detail {

class MdfBusLogger : public Mdf4Writer {
 public:
  MdfBusLogger() = default;
  ~MdfBusLogger() override;

};

}  // namespace mdf::detail
