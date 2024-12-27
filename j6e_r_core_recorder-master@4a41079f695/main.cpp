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
using namespace std::this_thread;
using namespace std::chrono_literals;
using namespace util::log;
using namespace util::time;
using namespace std::filesystem;
using namespace mdf;

void test_for_multi_dg()
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
  history->Description("Test");
  history->ToolName("MTCD");
  history->ToolVendor("Bosch Company");
  history->ToolVersion("1.0");
  history->Time(tick_time1);
  history->UserName("Ji.Wei");

  auto* data_group1 = header->CreateDataGroup();
  auto* group1 = data_group1->CreateChannelGroup();
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

  auto* data_group2 = header->CreateDataGroup();
  auto* group2 = data_group2->CreateChannelGroup();
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

  auto* data_group3 = header->CreateDataGroup();
  auto* group3 = data_group3->CreateChannelGroup();
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

  writer->InitMeasurement(); // Start the internal cache
  auto tick_time = TimeStampToNs();

  uint64_t sample = 0;

  writer->StartMeasurement(tick_time);

  ch1->SetChannelValue(5.0);
  ch2->SetChannelValue(6.0);
  ch3->SetChannelValue(7.0);
  tick_time += 1'000'000;
  writer->SaveSample(*group1, tick_time);
  printf("1\n");
   writer->SaveSample(*group2, tick_time);
   printf("2\n");
   writer->SaveSample(*group3, tick_time);
  writer->WriteSamples();
  printf("write success\n");


  // writer->StopMeasurement(tick_time);

  // writer->InitMeasurement(); // Start the internal cache
  // //auto tick_time = TimeStampToNs();

  // //uint64_t sample = 0;

  // writer->StartMeasurement(tick_time);

  // //ch1->SetChannelValue(5.0);
  // ch2->SetChannelValue(6.0);
  // //ch3->SetChannelValue(7.0);
  // tick_time += 1'000'000;
  // //writer->SaveSample(*group1, tick_time);
  // writer->SaveSample(*group2, tick_time);
  // // writer->SaveSample(*group3, tick_time);
  // writer->WriteSamples();
  // printf("write success\n");


  // writer->StopMeasurement(tick_time);

  // writer->InitMeasurement(); // Start the internal cache
  // //auto tick_time = TimeStampToNs();

  // //uint64_t sample = 0;

  // writer->StartMeasurement(tick_time);

  // //ch1->SetChannelValue(5.0);
  // //ch2->SetChannelValue(6.0);
  // ch3->SetChannelValue(7.0);
  // tick_time += 1'000'000;
  // //writer->SaveSample(*group1, tick_time);
  // // writer->SaveSample(*group2, tick_time);
  // writer->SaveSample(*group3, tick_time);
  // writer->WriteSamples();
  // printf("write success\n");


  writer->StopMeasurement(tick_time);
  writer->FinalizeMeasurement();
}

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

  //writer->PreTrigTime(1.0); // Store one seconds samples before start
  writer->InitMeasurement(); // Start the internal cache
  auto tick_time = TimeStampToNs();

  // Fill cache with 1 second data
  uint64_t sample = 0;
  // for (; sample < 1000; ++sample) {
  //   const auto value = static_cast<uint32_t>(sample);
  //   ch1->SetChannelValue(1);
  //   ch2->SetChannelValue(2);
  //   ch3->SetChannelValue(3);
  //   ch4->SetChannelValue(4);
  //   writer->SaveSample(*group1, tick_time);
  //   writer->SaveSample(*group2, tick_time);
  //   writer->SaveSample(*group3, tick_time);
  //   writer->SaveSample(*group4, tick_time);
  //   tick_time += 1'000'000; // Stepping 1ms
  // }

  writer->StartMeasurement(tick_time);

  // // Fill with 1 seconds samples after start.
  // for (; sample < 2000; ++sample) {
  //   const auto value = static_cast<uint32_t>(sample);
  //   ch1->SetChannelValue(5);
  //   ch2->SetChannelValue(6);
  //   ch3->SetChannelValue(7);
  //   ch4->SetChannelValue(8);
  //   writer->SaveSample(*group1, tick_time);
  //   writer->SaveSample(*group2, tick_time);
  //   writer->SaveSample(*group3, tick_time);
  //   writer->SaveSample(*group4, tick_time);
  //   tick_time += 1'000'000;
  //   writer->WriteSamples();
  // }

  ch1->SetChannelValue(5.0);
  ch2->SetChannelValue(6.0);
  ch3->SetChannelValue(7.0);
  ch4->SetChannelValue(8.0);
  tick_time += 1'000'000;
  writer->SaveSample(*group1, tick_time);
  writer->SaveSample(*group2, tick_time);
  writer->SaveSample(*group3, tick_time);
  writer->SaveSample(*group4, tick_time);
  writer->WriteSamples();
  printf("write success\n");


  writer->StopMeasurement(tick_time);
  writer->FinalizeMeasurement();

}
#if 0
void test_ca_struct()
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

  auto* data_group = header->CreateDataGroup();
  auto* group1 = data_group->CreateChannelGroup();
  group1->Name("test_array");


  auto* ch1     = group1->CreateChannel();
  auto* ca     = ch1->CreateChannelArray();
  // 设置通道数组的维度，比如存储 10 个结构体
  std::vector<uint64_t> dim_sizes = {10}; // 数组的尺寸是 10
  ca->Shape(dim_sizes);  // 设置通道数组的维度

// 创建存储结构体的数组
std::vector<MyStruct> structArray(10); // 假设有 10 个结构体需要存储

// 填充数据：
// 你可以从其他地方获取数据，然后填充到 structArray 中
for (int i = 0; i < 10; ++i) {
    structArray[i].field1 = i + 1;
    structArray[i].field2 = (i + 1) * 1.5f;
    structArray[i].field3 = (i + 1) * 2.5;
}

// 将结构体的数据写入通道数组
// AxisValues() 用于访问通道数组中的数据
std::vector<double>& values = ca->AxisValues();
values.resize(10 * 3); // 每个结构体有 3 个字段，所以需要 10 * 3 个位置

// 按顺序填入结构体字段
for (size_t i = 0; i < structArray.size(); ++i) {
    values[i * 3] = structArray[i].field1;       // 第一个字段
    values[i * 3 + 1] = structArray[i].field2;   // 第二个字段
    values[i * 3 + 2] = structArray[i].field3;   // 第三个字段
}

// 此时，通道数组已经包含了所有结构体字段

}
#endif
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
	test_for_multi_dg();

  return 0;
  MdfReader reader("Recorder_2024-11-19_11-23-02.mf4");
  if (reader.IsOk())
  {
    printf("read success\n");
  }
  else
  {
    printf("read failed\n");
    return -1;
  }

  if (reader.ReadHeader())
  {
    printf("read header success\n");
  }
  else
  {
    printf("read failed\n");
    return -1;
  }

  const auto* file1 = reader.GetFile();
  printf("get file success\n");
  const auto* header1 = file1->Header();
  printf("get header success\n");
  std::cout << "Author: " << header1->Author() << std::endl;
  std::string author = "wei";
  const auto *header2 = reader.GetHeader();
  std::cout << "Author: " << header1->Author() << std::endl;
  //header1->Author("Wei");
  printf("test pre time done\n");
	return 0;
}
