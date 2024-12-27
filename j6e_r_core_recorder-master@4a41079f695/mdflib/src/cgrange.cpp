

#include "cgrange.h"

namespace mdf {

CgRange::CgRange(const IChannelGroup& channel_group)
: channel_group_(channel_group) {

}
uint64_t CgRange::RecordId() const {
  return channel_group_.RecordId();
}

}  // namespace mdf