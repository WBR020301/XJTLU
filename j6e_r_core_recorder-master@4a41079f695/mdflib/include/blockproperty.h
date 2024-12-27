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
namespace mdf::detail {
enum class BlockItemType {
  NormalItem = 0,
  LinkItem = 1,
  HeaderItem = 2,
  BlankItem = 3
};

class BlockProperty final {
 public:
  explicit BlockProperty(const std::string& label, const std::string& value,
                         const std::string& desc = {},
                         BlockItemType type = BlockItemType::NormalItem);

  [[nodiscard]] const std::string& Label() const { return label_; }

  [[nodiscard]] const std::string& Value() const { return value_; }

  [[nodiscard]] const std::string& Description() const { return description_; }

  [[nodiscard]] BlockItemType Type() const { return type_; }

  [[nodiscard]] int64_t Link() const;

 private:
  std::string label_;
  std::string value_;
  std::string description_;
  BlockItemType type_ = BlockItemType::NormalItem;
};

}  // Namespace mdf::detail
