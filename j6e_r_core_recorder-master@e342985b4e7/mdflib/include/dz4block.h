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
#include "datablock.h"

namespace mdf::detail {
enum class Dz4ZipType : uint8_t { Deflate = 0, TransposeAndDeflate = 1 };

class Dz4Block : public DataBlock {
 public:
  void OrigBlockType(const std::string& block_type) {
    orig_block_type_ = block_type;
  }
  [[nodiscard]] std::string OrigBlockType() const { return orig_block_type_; }

  void Type(Dz4ZipType type) { type_ = static_cast<uint8_t>(type); }
  [[nodiscard]] Dz4ZipType Type() const {
    return static_cast<Dz4ZipType>(type_);
  }

  void Parameter(uint32_t parameter) {parameter_ = parameter; }
  [[nodiscard]] uint32_t Parameter() const { return parameter_; }


  [[nodiscard]] size_t DataSize() const override { return orig_data_length_; }
  [[nodiscard]] size_t CompressedDataSize() const { return data_length_; }

  void GetBlockProperty(BlockPropertyList& dest) const override;
  size_t Read(std::FILE* file) override;
  size_t Write(std::FILE* file) override;

  size_t CopyDataToFile(std::FILE* from_file,
                        std::FILE* to_file) const override;
  size_t CopyDataToBuffer(std::FILE* from_file, std::vector<uint8_t>& buffer,
                          size_t& buffer_index) const override;

  bool Data(const std::vector<uint8_t>& uncompressed_data) override;

 private:
  std::string orig_block_type_ = "DT";
  uint8_t type_ = 0; ///< Default is Deflate
  /* 1 byte reserved */
  uint32_t parameter_ = 0;
  uint64_t orig_data_length_ = 0;
  uint64_t data_length_ = 0;



};
}  // namespace mdf::detail
