/**
 * *****************************************************************************
 * @file        mtc_mcu_mf4_writer.hpp
 * @brief
 * @author      Ji Wei (BCSC/EPA4, XC-AS/ENG-PMT2-CN) (wei.ji2@cn.bosch.com)
 * @date        2024-11-1
 *
 * @Copyright (c) 2024-2030 Robert Bosch GmbH. All rights reserved.
 * *****************************************************************************
 */
#ifndef MF4WRITER_H
#define MF4WRITER_H

#include <algorithm>
#include <filesystem>
#include <string>
#include <thread>
#include <set>
#include <iostream>
#include <chrono>
#include <iomanip>
#include <sstream>

#include "utils/timestamp.h"
#include "utils/logconfig.h"
#include "utils/logstream.h"

#include "mdf/isourceinformation.h"
#include "mdf/iattachment.h"
#include "mdf/ichannelgroup.h"
#include "mdf/idatagroup.h"
#include "mdf/ievent.h"
#include "mdf/ifilehistory.h"


#include "mdf/mdffactory.h"
#include "mdf/mdfreader.h"
#include "mdf/mdfwriter.h"
#include "mdf/mdflogstream.h"
#include "mdf/itimestamp.h"
#if 0
namespace mtc {

class CMcuMF4Writer {
public:
    /**
     * @class CMcuMF4Writer
     * @brief used for mcu mf4 data write
     * */
    CMcuMF4Writer();

    // Destructor
    virtual ~CMcuMF4Writer();

    // Configuration function
    void config();

    // Initialization function
    void init(const std::string& a2lFilePath);

    // Start recording data
    void start();

    // Stop recording data
    void stop();
private:
    std::unique_ptr<MdfWriter> m_mf4WriterInstance;
    IHeader         *m_pMf4Header;
    IFileHistory    *m_pMf4FileHistory;
};

}// namespace mtc

#endif // MF4WRITER_H
#endif