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

#include "mdf/imetadata.h"
#include "mdfblock.h"

namespace mdf::detail {
std::string FixCommentToLine(const std::string& comment, size_t max);

class Tx4Block : public MdfBlock {
 public:
  Tx4Block() = default;
  explicit Tx4Block(const std::string& text);

  void GetBlockProperty(BlockPropertyList& dest) const override;
  [[nodiscard]] bool IsTxtBlock() const;
  size_t Read(std::FILE* file) override;
  size_t Write(std::FILE* file) override;

  void Text(const std::string& text) {text_ = text;}
  [[nodiscard]] std::string Text() const;
  [[nodiscard]] virtual std::string TxComment() const;

 protected:
  std::string text_;
};

}  // namespace mdf::detail
