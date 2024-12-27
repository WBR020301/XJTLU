/**
 * *****************************************************************************
 * @brief       mdflib
 * @author      Ji Wei (BCSC/EPA4, XC-AS/ENG-PMT2-CN) (wei.ji2@cn.bosch.com)
 * @date        2024-11-1
 *
 * @Copyright (c) 2024-2030 Robert Bosch GmbH. All rights reserved.
 * *****************************************************************************
 */
/** \file
 * This file define the channel group range support class.
 */

#include "mdf/ichannelgroup.h"

namespace mdf {

class CgRange final {
 public:
  CgRange() = delete;
  explicit CgRange(const IChannelGroup& channel_group);
  [[nodiscard]] uint64_t RecordId() const;

  void IsUsed(bool used) { is_used_ = used;}
  [[nodiscard]] bool IsUsed() const { return is_used_;}

  [[nodiscard]] const IChannelGroup& ChannelGroup() const {
    return channel_group_;
  }

 private:
  const IChannelGroup& channel_group_;
  bool is_used_ = false;
};

}  // namespace mdf


