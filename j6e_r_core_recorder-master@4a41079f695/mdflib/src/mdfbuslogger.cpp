
#include "mdfbuslogger.h"

namespace mdf::detail {
MdfBusLogger::~MdfBusLogger() { StopWorkThread();}
}  // namespace mdf