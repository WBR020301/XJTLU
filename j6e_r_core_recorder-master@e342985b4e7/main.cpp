#include <algorithm>
#include <filesystem>
#include <string>
#include <thread>
#include <set>
#include <iostream>
#include <chrono>
#include <iomanip>
#include <sstream>
#include "include/utils/timestamp.h"
#include "include/utils/logconfig.h"
#include "include/utils/logstream.h"

#include "include/mdf/isourceinformation.h"
#include "include/mdf/iattachment.h"
#include "include/mdf/ichannelgroup.h"
#include "include/mdf/idatagroup.h"
#include "include/mdf/ievent.h"
#include "include/mdf/ifilehistory.h"


#include "include/mdf/mdffactory.h"
#include "include/mdf/mdfreader.h"
#include "include/mdf/mdfwriter.h"
#include "include/mdf/mdflogstream.h"
#include "include/mdf/itimestamp.h"
using namespace std::this_thread;
using namespace std::chrono_literals;
using namespace util::log;
using namespace util::time;
using namespace std::filesystem;
using namespace mdf;

void test_pre_time()
{
   auto writer = MdfFactory::CreateMdfWriter(MdfWriterType::Mdf4Basic);
  writer->Init("test_for_channel_name.mf4");
  //writer->CompressData(true);

  auto* header = writer->Header();
  auto* history = header->CreateFileHistory();
  auto tick_time1 = TimeStampToNs();
  header->Author("Ji.Wei");
	header->Department("XC-AS/ENG-PMT2-CN");
	header->Description("Testing Header");
	header->Project("J6E_Project");
	header->StartTime(tick_time1);
	header->Subject("R_Core");
	//header->Boss("Wang Tao");
  history->Description("Test");
  history->ToolName("MTCD");
  history->ToolVendor("Bosch Company");
  history->ToolVersion("1.0");
  history->Time(tick_time1);
  history->UserName("Ji.Wei");

  auto* data_group = header->CreateDataGroup();

  auto* group1 = data_group->CreateChannelGroup();
  group1->Name("FloatMaster");

  auto* master1 = group1->CreateChannel();
  master1->Name("Time");
  master1->Type(ChannelType::Master);
  master1->Sync(ChannelSyncType::Time);
  master1->DataType(ChannelDataType::FloatLe);
  master1->DataBytes(4);

  auto* ch1 = group1->CreateChannel();
  ch1->Name("Intel32_1");
  ch1->Type(ChannelType::FixedLength);
  ch1->Sync(ChannelSyncType::None);
  ch1->DataType(ChannelDataType::FloatLe);
  ch1->DataBytes(4);

  auto* group2 = data_group->CreateChannelGroup();
  group2->Name("DoubleMaster");

  auto* master2 = group2->CreateChannel();
  master2->Name("Time");
  master2->Type(ChannelType::Master);
  master2->Sync(ChannelSyncType::Time);
  master2->DataType(ChannelDataType::FloatBe);
  master1->DataBytes(8);

  auto* ch2 = group2->CreateChannel();
  ch2->Name("Intel32_2");
  ch2->Type(ChannelType::FixedLength);
  ch2->Sync(ChannelSyncType::None);
  ch2->DataType(ChannelDataType::FloatLe);
  ch2->DataBytes(4);

  auto* group3 = data_group->CreateChannelGroup();
  group3->Name("Signed32Master");

  //note: 32bit cannot convert ns.
  auto* master3 = group3->CreateChannel();
  master3->Name("Time");
  master3->Unit("s");
  master3->Type(ChannelType::Master);
  master3->Sync(ChannelSyncType::Time);
  master3->DataType(ChannelDataType::SignedIntegerLe);
  master3->DataBytes(8);

  auto cc3 = master3->CreateChannelConversion();
  cc3->Name("NsToS");
  cc3->Description("Nanoseconds to seconds conversion");
  cc3->Unit("s");
  cc3->Type(ConversionType::Linear);
  cc3->Parameter(0,0.0);
  cc3->Parameter(1, 1E-9);

  auto* ch3 = group3->CreateChannel();
  ch3->Name("Intel32_3");
  ch3->Type(ChannelType::FixedLength);
  ch3->Sync(ChannelSyncType::None);
  ch3->DataType(ChannelDataType::FloatLe);
  ch3->DataBytes(4);

  auto* group4 = data_group->CreateChannelGroup();
  group4->Name("Signed64Master");

  auto* master4 = group4->CreateChannel();
  master4->Name("Time");
  master4->Unit("s");
  master4->Type(ChannelType::Master);
  master4->Sync(ChannelSyncType::Time);
  master4->DataType(ChannelDataType::SignedIntegerLe);
  master4->DataBytes(8);

  auto cc4 = master4->CreateChannelConversion();
  cc4->Name("NsToS");
  cc4->Description("Nanoseconds to seconds conversion");
  cc4->Unit("s");
  cc4->Type(ConversionType::Linear);
  cc4->Parameter(0,0.0);
  cc4->Parameter(1, 1E-9);

  auto* ch4 = group4->CreateChannel();
  ch4->Name("Intel32_4");
  ch4->Type(ChannelType::FixedLength);
  ch4->Sync(ChannelSyncType::None);
  ch4->DataType(ChannelDataType::FloatLe);
  ch4->DataBytes(4);

  writer->PreTrigTime(1.0); // Store one seconds samples before start
  writer->InitMeasurement(); // Start the internal cache
  auto tick_time = TimeStampToNs();

  // Fill cache with 1 second data
  uint64_t sample = 0;
  for (; sample < 1000; ++sample) {
    const auto value = static_cast<uint32_t>(sample);
    ch1->SetChannelValue(1);//将数据根据不同的类型写入到缓冲区中
    ch2->SetChannelValue(2);
    ch3->SetChannelValue(3);
    ch4->SetChannelValue(4);
    writer->SaveSample(*group1, tick_time);//将group1的数据保存到文件
    writer->SaveSample(*group2, tick_time);
    writer->SaveSample(*group3, tick_time);
    writer->SaveSample(*group4, tick_time);
    tick_time += 1'000'000; // Stepping 1ms
  }

  writer->StartMeasurement(tick_time);

  // Fill with 1 seconds samples after start.
  for (; sample < 2000; ++sample) {
    const auto value = static_cast<uint32_t>(sample);
    ch1->SetChannelValue(5);
    ch2->SetChannelValue(6);
    ch3->SetChannelValue(7);
    ch4->SetChannelValue(8);
    writer->SaveSample(*group1, tick_time);
    writer->SaveSample(*group2, tick_time);
    writer->SaveSample(*group3, tick_time);
    writer->SaveSample(*group4, tick_time);
    tick_time += 1'000'000;
    writer->WriteSamples();
  }
  printf("write success\n");


  writer->StopMeasurement(tick_time);
  writer->FinalizeMeasurement();

}
int test2()
{

  auto writer = MdfFactory::CreateMdfWriter(MdfWriterType::Mdf4Basic);
  writer->Init("test_cccccc.mf4");
  writer->CompressData(true);

  auto* header = writer->Header();
  auto* history = header->CreateFileHistory();
  auto tick_time1 = TimeStampToNs();
  header->Author("Ji.Wei");
	header->Department("XC-AS/ENG-PMT2-CN");
	header->Description("Testing Header");
	header->Project("J6E_Project");
	header->StartTime(tick_time1);
	header->Subject("R_Core");
  history->Description("Test");
  history->ToolName("MTCD");
  history->ToolVendor("Bosch Company");
  history->ToolVersion("1.0");
  history->Time(tick_time1);
  history->UserName("Ji.Wei");

	// Data Group
	// Channel Group
	// Channel
  auto* data_group = header->CreateDataGroup();
  auto* group1 = data_group->CreateChannelGroup();
  group1->Name("Float");


  auto* ch1 = group1->CreateChannel();
  ch1->Name("Intel32");
  ch1->Type(ChannelType::FixedLength);
  ch1->Sync(ChannelSyncType::None);
  ch1->DataType(ChannelDataType::FloatLe);
  ch1->DataBytes(4);

  auto* ch2 = group1->CreateChannel();
  ch2->Name("Intel64");
  ch2->Type(ChannelType::FixedLength);
  ch2->Sync(ChannelSyncType::None);
  ch2->DataType(ChannelDataType::FloatLe);
  ch2->DataBytes(8);

  auto* ch3 = group1->CreateChannel();
  ch3->Name("Motorola32");
  ch3->Type(ChannelType::FixedLength);
  ch3->Sync(ChannelSyncType::None);
  ch3->DataType(ChannelDataType::FloatBe);
  ch3->DataBytes(4);

  auto* ch4 = group1->CreateChannel();
  ch4->Name("Motorola64");
  ch4->Type(ChannelType::FixedLength);
  ch4->Sync(ChannelSyncType::None);
  ch4->DataType(ChannelDataType::FloatBe);
  ch4->DataBytes(8);
  int test_offset = ch4->ByteOffset();
  printf("offset = %d\n", test_offset);


  writer->PreTrigTime(0);
  writer->InitMeasurement();
  //ch4->ByteOffset(8);
  int test_offset2 = ch4->ByteOffset();
  printf("offset2 = %d\n", test_offset2);

  auto tick_time = TimeStampToNs();
  writer->StartMeasurement(tick_time);
  int test_offset3 = ch4->ByteOffset();
  printf("offset = %d\n", test_offset3);

  for (size_t sample = 0; sample < 1'000'000; ++sample) {
    double value = static_cast<double>(sample) + 0.23;
    ch1->SetChannelValue(1.0);
    ch2->SetChannelValue(2.0);
    ch3->SetChannelValue(3.0);
    ch4->SetChannelValue(4.0);

    writer->SaveSample(*group1,tick_time);
    tick_time += 100'000'000;
  }
  writer->StopMeasurement(tick_time);
  writer->FinalizeMeasurement();

printf("success\n");
  return 0;
}

int main()
{
	test_pre_time();
  printf("test pre time done\n");
	return 0;
}
