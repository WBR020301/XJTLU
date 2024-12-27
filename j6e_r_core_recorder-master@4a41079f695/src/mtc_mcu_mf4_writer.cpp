//#include "mtc_mcu_mf4_writer.hpp"
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
#if 0
namespace mtc {
struct tMf4FileHistory {
    std::string description = "MTC_MF4_Data_Recording";
    std::string toolName    = "MTCD";
    std::string vendor      = "Robert Bosch Company";
    std::string version     = "1.0";
    std::string userName    = "Ji.Wei";
};

CMcuMF4Writer::CMcuMF4Writer()
{
    m_mf4WriterInstance = MdfFactory::CreateMdfWriter(MdfWriterType::Mdf4Basic);
    // default not compress.
    //m_mf4WriterInstance->CompressData(true);
    m_pMf4Header = m_mf4WriterInstance->Header();
    m_pMf4Header->Author("Ji.Wei");
    m_pMf4Header->Department("XC-AS/ENG-PMT2-CN");
    m_pMf4Header->Description("Header Description");
    m_pMf4Header->Project("J6E_Project");
    m_pMf4Header->StartTime(start_time1);
    m_pMf4Header->Subject("R_Core Data");
    
    m_pMf4FileHistory = m_mf4WriterInstance->CreateFileHistory();
    m_pMf4FileHistory->Description("MTC_MF4_Data_Recording");
    m_pMf4FileHistory->ToolName("MTC_Mf4Writer");
    m_pMf4FileHistory->ToolVendor("Robert Bosch Company");
    m_pMf4FileHistory->ToolVersion("1.0");
    m_pMf4FileHistory->UserName("Ji.Wei");
}

CMcuMF4Writer::~CMcuMF4Writer(){}

void CMcuMF4Writer::createMf4FileHistory()
{

}

void CMcuMF4Writer::config()
{

}

// Initialization function
void CMcuMF4Writer::init(const std::string& a2lFilePath)
{

}

// Start recording data
void CMcuMF4Writer::start()
{

}

// Stop recording data
void CMcuMF4Writer::stop()
{

}

}// namespace mtc
#endif