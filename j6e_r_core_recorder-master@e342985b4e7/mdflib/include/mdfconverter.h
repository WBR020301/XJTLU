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

class MdfConverter : public Mdf4Writer {
 public:
  MdfConverter() = default;
  ~MdfConverter() override;

  bool InitMeasurement() override;
  void SaveSample(const IChannelGroup& group, uint64_t time) override;
  bool FinalizeMeasurement() override;
 protected:
  void TrimQueue() override; ///< Trims the sample queue.
  void SaveQueue(std::unique_lock<std::mutex>& lock) override;
  void CleanQueue(std::unique_lock<std::mutex>& lock) override;

  void SaveQueueCompressed(std::unique_lock<std::mutex>& lock) override;

  /** \brief Save one DZ block from the sample queue. */
  void CleanQueueCompressed(std::unique_lock<std::mutex>& lock,
                            bool finalize) override;
 private:
  std::FILE* file_ = nullptr; ///< File pointer as the file is open between calls.
  void ConverterThread();
};

}  // namespace mdf::detail

