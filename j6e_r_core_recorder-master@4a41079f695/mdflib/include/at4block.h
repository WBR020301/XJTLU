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
#include <memory>
#include <vector>

#include "md4block.h"
#include "mdf/iattachment.h"
#include "mdfblock.h"

namespace mdf::detail {
namespace At4Flags {
constexpr uint16_t kEmbeddedData = 0x01;
constexpr uint16_t kCompressedData = 0x02;
constexpr uint16_t kUsingMd5 = 0x04;
}  // namespace At4Flags
class At4Block : public MdfBlock, public IAttachment {
 public:
  At4Block();
  [[nodiscard]] int64_t Index() const override {
      return MdfBlock::Index();
  };

  [[nodiscard]] std::string BlockType() const override {
    return MdfBlock::BlockType();
  };

  [[nodiscard]] IMetaData* CreateMetaData() override {
    return MdfBlock::CreateMetaData();
  };

  [[nodiscard]] IMetaData* MetaData() const override {
    return MdfBlock::MetaData();
  };

  void FileName(const std::string& filename) override;
  [[nodiscard]] const std::string& FileName() const override;

  void FileType(const std::string& file_type) override;
  [[nodiscard]] const std::string& FileType() const override;

  void CreatorIndex(uint16_t creator) override;
  [[nodiscard]] uint16_t CreatorIndex() const override;

  void IsEmbedded(bool embed) override;
  [[nodiscard]] bool IsEmbedded() const override;

  void IsCompressed(bool compress) override;
  [[nodiscard]] bool IsCompressed() const override;

  void GetBlockProperty(BlockPropertyList& dest) const override;
  size_t Read(std::FILE* file) override;

  void ReadData(std::FILE* file, const std::string& dest_file) const;

  size_t Write(std::FILE* file) override;
  [[nodiscard]] std::optional<std::string> Md5() const override;

 private:
  uint16_t flags_ = 0;
  uint16_t creator_index_ = 0;
  // 4 byte reserved
  std::vector<uint8_t> md5_;  ///< 16 byte MD5 checksum
  uint64_t original_size_ = 0;
  uint64_t nof_bytes_ = 0;

  int64_t data_position_ = 0;  ///< File position of the data BLOB
  std::string filename_;
  std::string file_type_;
};
}  // namespace mdf::detail
