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
#include <vector>

#include "mdfblock.h"

namespace mdf::detail {
class DataBlock;
class DataListBlock : public MdfBlock {
 public:
  using BlockList = std::vector<std::unique_ptr<MdfBlock>>;
  BlockList& DataBlockList() { return block_list_; }
  [[nodiscard]] const BlockList& DataBlockList() const { return block_list_; }
  [[nodiscard]] virtual size_t DataSize() const;
  [[nodiscard]] MdfBlock* Find(int64_t index) const override;
  void ReadBlockList(std::FILE* file, size_t data_index);
  void WriteBlockList(std::FILE* file, size_t data_index);

  void ReadLinkList(std::FILE* file, size_t data_index, uint32_t nof_link);
  virtual void ClearData();
  void CopyDataToBuffer(FILE *from_file, std::vector<uint8_t> &buffer,
                                                   size_t &buffer_index) const;
  [[nodiscard]] bool IsRdBlock() const;
   void GetDataBlockList(std::vector<DataBlock*>& block_list) const;
 protected:
  BlockList block_list_;
};

}  // namespace mdf::detail
