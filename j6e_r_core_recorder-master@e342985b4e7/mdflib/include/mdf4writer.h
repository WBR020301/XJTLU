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

#include "mdf/mdfwriter.h"

namespace mdf::detail {
class Dg4Block;

class Mdf4Writer : public MdfWriter {
 public:
  Mdf4Writer() = default;
  ~Mdf4Writer() override;

  bool InitMeasurement() override;

  IChannelConversion* CreateChannelConversion(IChannel* parent) override;

 protected:
  uint64_t offset_ = 0;
  void CreateMdfFile() override;
  void SetLastPosition(std::FILE* file) override;
  bool PrepareForWriting() override;
  void SaveQueue(std::unique_lock<std::mutex>& lock) override;
  void CleanQueue(std::unique_lock<std::mutex>& lock) override;

  /** \brief Calculates number of DZ blocks in the sample queue */
  [[nodiscard]] size_t CalculateNofDzBlocks();
  virtual void SaveQueueCompressed(std::unique_lock<std::mutex>& lock);

  /** \brief Save one DZ block from the sample queue. */
  virtual void CleanQueueCompressed(std::unique_lock<std::mutex>& lock, bool finalize);

  void SetDataGroupDtEndPosition(IDataGroup* cur_dg, std::FILE* file);
  void SetDataPosition(std::FILE* file) override;
  bool WriteSignalData(std::FILE* file) override;

  Dg4Block* GetLastDg4();
 private:


};

}  // namespace mdf::detail
