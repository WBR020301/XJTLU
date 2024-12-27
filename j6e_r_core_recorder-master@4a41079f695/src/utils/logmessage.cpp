/**
 * *****************************************************************************
 * @brief       mdflib
 * @author      Ji Wei (BCSC/EPA4, XC-AS/ENG-PMT2-CN) (wei.ji2@cn.bosch.com)
 * @date        2024-11-1
 *
 * @Copyright (c) 2024-2030 Robert Bosch GmbH. All rights reserved.
 * *****************************************************************************
 */
#include "logmessage.h"

#include <string>

namespace util::log {
std::string GetSeverityString(LogSeverity severity) {
  switch (severity) {
    case LogSeverity::kTrace:
      return "[Trace]";
    case LogSeverity::kDebug:
      return "[Debug]";
    case LogSeverity::kInfo:
      return "[Info]";
    case LogSeverity::kNotice:
      return "[Notify]";
    case LogSeverity::kWarning:
      return "[Warning]";
    case LogSeverity::kError:
      return "[Error]";
    case LogSeverity::kCritical:
      return "[Critical]";
    case LogSeverity::kAlert:
      return "[Alert]";
    case LogSeverity::kEmergency:
      return "[Emergency]";
    default:
      break;
  }
  return "[Unknown]";
}
}  // namespace util::log