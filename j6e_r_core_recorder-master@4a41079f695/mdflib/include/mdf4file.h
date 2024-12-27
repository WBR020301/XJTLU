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
#include <memory>

#include "hd4block.h"
#include "idblock.h"
#include "mdf/mdffile.h"

namespace mdf::detail {

class Mdf4File : public MdfFile {
 public:
  Mdf4File();
  explicit Mdf4File(std::unique_ptr<IdBlock> id_block);
  ~Mdf4File() override = default;

  Mdf4File(const Mdf4File&) = delete;
  Mdf4File(Mdf4File&&) = delete;
  Mdf4File& operator=(const Mdf4File&) = delete;
  Mdf4File& operator=(Mdf4File&&) = delete;

  void Attachments(AttachmentList& dest) const override;
  void DataGroups(DataGroupList& dest) const override;
  [[nodiscard]] std::string Version() const override;
  void MinorVersion(int minor) override;

  void ProgramId(const std::string& program_id) override;
  [[nodiscard]] std::string ProgramId() const override;

  [[nodiscard]] IHeader* Header() const override;

  [[nodiscard]] IAttachment* CreateAttachment() override;

  [[nodiscard]] IDataGroup* CreateDataGroup() override;

  [[nodiscard]] MdfBlock* Find(int64_t id) const;

  [[nodiscard]] bool IsMdf4() const override;

  void IsFinalized(bool finalized, std::FILE* file, uint16_t standard_flags,
                   uint16_t custom_flags) override;
  [[nodiscard]] bool IsFinalized(uint16_t& standard_flags,
                                 uint16_t& custom_flags) const override;

  void ReadHeader(std::FILE* file) override;
  void ReadMeasurementInfo(std::FILE* file) override;
  void ReadEverythingButData(std::FILE* file) override;

  [[nodiscard]] const IdBlock& Id() const;
  [[nodiscard]] const Hd4Block& Hd() const;

  bool Write(std::FILE* file) override;

  [[nodiscard]] IDataGroup* FindParentDataGroup(
      const IChannel& channel) const  override;

 private:
  std::unique_ptr<IdBlock> id_block_;
  std::unique_ptr<Hd4Block> hd_block_;

  bool finalized_done_ = false;
  bool FinalizeFile(std::FILE* file);
  void FindAllReferences(std::FILE* file);
};
}  // namespace mdf::detail
