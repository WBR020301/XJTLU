/**
 * *****************************************************************************
 * @brief       mdflib
 * @author      Ji Wei (BCSC/EPA4, XC-AS/ENG-PMT2-CN) (wei.ji2@cn.bosch.com)
 * @date        2024-11-1
 *
 * @Copyright (c) 2024-2030 Robert Bosch GmbH. All rights reserved.
 * *****************************************************************************
 */
#include "logstream.h"

namespace util::log {
LogStream::LogStream(const Loc &location, LogSeverity severity)
    : location_(location), severity_(severity) {}

LogStream::~LogStream() { LogString(location_, severity_, str()); }
}  // namespace util::log
