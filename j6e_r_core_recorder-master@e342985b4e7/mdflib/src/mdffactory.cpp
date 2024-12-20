

#include "mdf/mdffactory.h"

#include "mdf4file.h"
#include "mdf4writer.h"
#include "mdfbuslogger.h"
#include "mdfconverter.h"
#include "mdf/mdflogstream.h"
#include "cn4block.h"
#include "sr4block.h"

using namespace mdf::detail;

namespace mdf {

std::unique_ptr<MdfWriter> MdfFactory::CreateMdfWriter(MdfWriterType type) {
  std::unique_ptr<MdfWriter> writer;

  switch (type) {
    case MdfWriterType::Mdf3Basic: {
      //not support
      break;
    }

    case MdfWriterType::Mdf4Basic: {
      auto mdf4 = std::make_unique<Mdf4Writer>();
      writer = std::move(mdf4);
      break;
    }

    case MdfWriterType::MdfBusLogger: {
      auto mdf4 = std::make_unique<MdfBusLogger>();
      writer = std::move(mdf4);
      break;
    }

    case MdfWriterType::MdfConverter: {
      auto mdf4 = std::make_unique<MdfConverter>();
      writer = std::move(mdf4);
      break;
    }
    default:
      break;
  }
  return writer;
}

std::unique_ptr<MdfFile> MdfFactory::CreateMdfFile(MdfFileType type) {
  std::unique_ptr<MdfFile> file;

  switch (type) {
    case MdfFileType::Mdf3FileType: {
      //not support
      break;
    }
    case MdfFileType::Mdf4FileType: {
      auto mdf4 = std::make_unique<Mdf4File>();
      file = std::move(mdf4);
      break;
    }

    default:
      break;
  }
  return file;
}

MdfWriter* MdfFactory::CreateMdfWriterEx(MdfWriterType type) {
  MdfWriter* writer = nullptr;

  switch (type) {
    case MdfWriterType::Mdf3Basic: {
      //not support
      break;
    }

    case MdfWriterType::Mdf4Basic: {
      writer = new Mdf4Writer();
      break;
    }
    
    case MdfWriterType::MdfBusLogger: {
      writer = new MdfBusLogger();
      break;
    }

    case MdfWriterType::MdfConverter: {
      writer = new MdfConverter();
      break;
    }
    
    default:
      break;
  }
  return writer;
}

MdfFile* MdfFactory::CreateMdfFileEx(MdfFileType type) {
  MdfFile* file = nullptr;

  switch (type) {
    case MdfFileType::Mdf3FileType: {
      //not support
      break;
    }

    case MdfFileType::Mdf4FileType: {
      file = new Mdf4File();
      break;
    }

    default:
      break;
  }
  return file;
}

void MdfFactory::SetLogFunction2(const MdfLogFunction2& func) {
  MdfLogStream::SetLogFunction2(func);
}

}  // namespace mdf
