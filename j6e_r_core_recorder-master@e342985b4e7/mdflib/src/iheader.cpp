
#include "mdf/iheader.h"

namespace mdf {

void IHeader::MeasurementId(const std::string &uuid) {}

std::string IHeader::MeasurementId() const { return {}; }

void IHeader::RecorderId(const std::string &uuid) {}

std::string IHeader::RecorderId() const { return {}; }

void IHeader::RecorderIndex(int64_t index) {}

int64_t IHeader::RecorderIndex() const { return 0; }

void IHeader::StartAngle(double angle) {}

std::optional<double> IHeader::StartAngle() const { return {}; }

void IHeader::StartDistance(double distance) {}

std::optional<double> IHeader::StartDistance() const { return {}; }

IMetaData *IHeader::CreateMetaData() { return nullptr; }

IMetaData *IHeader::MetaData() const { return nullptr; }

IAttachment *IHeader::CreateAttachment() { return nullptr; }

std::vector<IAttachment *> IHeader::Attachments() const { return {}; }

IFileHistory *IHeader::CreateFileHistory() { return nullptr; }

std::vector<IFileHistory *> IHeader::FileHistories() const { return {}; }

IEvent *IHeader::CreateEvent() { return nullptr; }

std::vector<IEvent *> IHeader::Events() const { return {}; }

IChannelHierarchy *IHeader::CreateChannelHierarchy() { return nullptr; }

std::vector<IChannelHierarchy *> IHeader::ChannelHierarchies() const {
  return {};
}

}  // namespace mdf