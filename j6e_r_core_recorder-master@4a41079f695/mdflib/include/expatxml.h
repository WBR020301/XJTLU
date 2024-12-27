/**
 * *****************************************************************************
 * @brief       mdflib
 * @author      Ji Wei (BCSC/EPA4, XC-AS/ENG-PMT2-CN) (wei.ji2@cn.bosch.com)
 * @date        2024-11-1
 *
 * @Copyright (c) 2024-2030 Robert Bosch GmbH. All rights reserved.
 * *****************************************************************************
 */
/** \file expatxml.h
 * \brief Implement a wrapper around the EXPAT parser.
 */
#pragma once
#include <expat.h>

#include <memory>

#include "ixmlfile.h"
#include "ixmlnode.h"
#include "xmlnode.h"

namespace mdf {
/** \class ExpatXml expatxml.h "expatxml.h"
 * \brief Simple wrapper around the EXPAT parser.
 *
 * Implements an XML parser by using the EXPAT parser.
 */
class ExpatXml final : public IXmlFile {
 public:
  ExpatXml() = default;            ///< Constructor
  ~ExpatXml() override = default;  ///< Destructor

  bool ParseFile() override;  ///< Parses the input file.
  bool ParseString(
      const std::string &input) override;  ///< Parses an input string.
  void Reset() override;  ///< Reset the parser for a new round.

  void StartElement(const XML_Char *name,
                    const XML_Char **attributes);   ///< Parser callback
  void EndElement(const XML_Char *name);            ///< Parser callback
  void CharacterData(const char *buffer, int len);  ///< Parser callback
  void XmlDecl(const XML_Char *version, const XML_Char *encoding,
               int standalone);  ///< Parser callback
 protected:
 private:
  using NodeStack = std::stack<XmlNode *>;  ///< Temporary parser stack
  NodeStack node_stack_;
};
}  // namespace mdf