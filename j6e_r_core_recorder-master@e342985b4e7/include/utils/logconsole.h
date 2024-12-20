/**
 * *****************************************************************************
 * @brief       mdflib
 * @author      Ji Wei (BCSC/EPA4, XC-AS/ENG-PMT2-CN) (wei.ji2@cn.bosch.com)
 * @date        2024-11-1
 *
 * @Copyright (c) 2024-2030 Robert Bosch GmbH. All rights reserved.
 * *****************************************************************************
 */

/** \file logconsole.h
 * \brief Sends all log messages onto the console.
 */
#pragma once
#include <mutex>
#include <string>

#include "ilogger.h"

namespace util::log::detail {
/** \class LogConsole logconsole.h "logconsole.h"
 * \brief Implements a logger that sends the message to the console window.
 *
 * This class implements a logger that sends all log messages to the console.
 * This is useful for applications without GUI and where log files are annoying.
 *
 * Note that this implementations sends the message to the console directly thus
 * delaying the application.
 */
class LogConsole final : public ILogger {
 public:
  LogConsole() = default;
  ~LogConsole() override = default;

  LogConsole(const LogConsole &) = delete;
  LogConsole(LogConsole &&) = delete;
  LogConsole &operator=(const LogConsole &) = delete;
  LogConsole &operator=(const LogConsole &&) = delete;

  void AddLogMessage(
      const LogMessage &message) override;  ///< Mandatory message interface

 private:
  std::mutex locker_;
};
}  // namespace util::log::detail
