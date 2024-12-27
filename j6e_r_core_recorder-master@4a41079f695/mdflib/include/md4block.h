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
#include <string>

#include "tx4block.h"

namespace mdf::detail {
class Md4Block : public Tx4Block, public IMetaData {
 public:

  Md4Block();
  explicit Md4Block(const std::string& text);

  [[nodiscard]] int64_t Index() const override {
    return MdfBlock::Index();
  }
  [[nodiscard]] std::string BlockType() const override {
    return MdfBlock::BlockType();
  }
  void GetBlockProperty(BlockPropertyList& dest) const override;

  void TxComment(const std::string& tx_comment);
  [[nodiscard]] std::string TxComment() const override;

  void XmlSnippet(const std::string& text) override;
  [[nodiscard]] const std::string& XmlSnippet() const override;
};
}  // namespace mdf::detail
