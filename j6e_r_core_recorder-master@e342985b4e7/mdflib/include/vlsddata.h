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
#include <cstdint>
#include <vector>
#include <string>
namespace mdf::detail {

class VlsdData {
 public:
  explicit VlsdData(const std::vector<uint8_t>& data);
  explicit VlsdData(const std::string& text);

  [[nodiscard]] bool operator < (const VlsdData&  item) const;
  [[nodiscard]] bool operator == (const VlsdData&  item) const;

  [[nodiscard]] uint32_t Size() const {
    return static_cast<uint32_t>(data_.size());
  }

  [[nodiscard]] auto Cbegin() const {
    return data_.cbegin();
  }

  [[nodiscard]] auto Cend() const {
    return data_.cend();
  }
 private:
  std::vector<uint8_t> data_;
};

}  // namespace mdf
