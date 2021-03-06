#include "mythical/walker.hpp"
#include <cassert>
#include <stdexcept>

using namespace std;

namespace mythical {

/****************************************************************************
 * External Methods
 ****************************************************************************/
Walker::Walker() {
  current_site_ = constants::unassignedId;
  potential_site_ = constants::unassignedId;
  dwell_time_ = -1.0;
}

int Walker::getIdOfSiteCurrentlyOccupying() const {
  if (current_site_ == constants::unassignedId) {
    std::string error_msg = std::string(__FILE__) + ":" + 
      to_string(__LINE__) + " Walker cannot get current site "
      "as it has not yet been assigned. You many need to first"
      " initialize the walker. You can do this by calling the "
      "occupySite method.";
    throw runtime_error(error_msg);
  }
  return current_site_;
}

int Walker::getPotentialSite() const {
  if (potential_site_ == constants::unassignedId) {
    throw runtime_error(
        "Cannot get potential site as it has not yet been "
        "assigned. You many need to first initialize the walker");
  }
  return potential_site_;
}
}
