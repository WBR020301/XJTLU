/**
 * *****************************************************************************
 * @brief       mdflib
 * @author      Ji Wei (BCSC/EPA4, XC-AS/ENG-PMT2-CN) (wei.ji2@cn.bosch.com)
 * @date        2024-11-1
 *
 * @Copyright (c) 2024-2030 Robert Bosch GmbH. All rights reserved.
 * *****************************************************************************
 */

#include "ilogger.h"

namespace util::log {

bool ILogger::HasLogFile() const { return false; }

std::string ILogger::Filename() const { return {}; }

void ILogger::EnableSeverityLevel(LogSeverity severity, bool enable) {
  const auto level = static_cast<uint8_t>(severity);
  if (level < severity_filter_.size()) {
    severity_filter_[level] = enable;
  }
}

bool ILogger::IsSeverityLevelEnabled(LogSeverity severity) const {
  const auto level = static_cast<uint8_t>(severity);
  return level < severity_filter_.size() ? severity_filter_[level].load()
                                         : false;
}

void ILogger::Stop() {}

}  // namespace util::log