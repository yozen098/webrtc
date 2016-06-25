/*
 *  Copyright 2004 The WebRTC Project Authors. All rights reserved.
 *
 *  Use of this source code is governed by a BSD-style license
 *  that can be found in the LICENSE file in the root of the source
 *  tree. An additional intellectual property rights grant can be found
 *  in the file PATENTS.  All contributing project authors may
 *  be found in the AUTHORS file in the root of the source tree.
 */

#ifndef WEBRTC_P2P_BASE_CANDIDATE_H_
#define WEBRTC_P2P_BASE_CANDIDATE_H_

#include <limits.h>
#include <math.h>

#include <algorithm>
#include <iomanip>
#include <sstream>
#include <string>

#include "webrtc/p2p/base/constants.h"
#include "webrtc/base/basictypes.h"
#include "webrtc/base/helpers.h"
#include "webrtc/base/network.h"
#include "webrtc/base/socketaddress.h"

namespace cricket {

// Candidate for ICE based connection discovery.

class Candidate {
 public:
  // TODO: Match the ordering and param list as per RFC 5245
  // candidate-attribute syntax. http://tools.ietf.org/html/rfc5245#section-15.1
  Candidate();

  Candidate(int component,
            const std::string& protocol,
            const rtc::SocketAddress& address,
            uint32 priority,
            const std::string& username,
            const std::string& password,
            const std::string& type,
            uint32 generation,
            const std::string& foundation);

  const std::string & id() const;
  void set_id(const std::string & id);

  int component() const;
  void set_component(int component);

  const std::string & protocol() const;
  void set_protocol(const std::string & protocol);

  // The protocol used to talk to relay.
  const std::string& relay_protocol() const;
  void set_relay_protocol(const std::string& protocol);

  const rtc::SocketAddress & address() const;
  void set_address(const rtc::SocketAddress & address);

  uint32 priority() const;
  void set_priority(const uint32 priority);

  // TODO(pthatcher): Remove once Chromium's jingle/glue/utils.cc
  // doesn't use it.
  // Maps old preference (which was 0.0-1.0) to match priority (which
  // is 0-2^32-1) to to match RFC 5245, section 4.1.2.1.  Also see
  // https://docs.google.com/a/google.com/document/d/
  // 1iNQDiwDKMh0NQOrCqbj3DKKRT0Dn5_5UJYhmZO-t7Uc/edit
  float preference() const;
    // The preference value is clamped to two decimal precision.


  // TODO(pthatcher): Remove once Chromium's jingle/glue/utils.cc
  // doesn't use it.
  void set_preference(float preference);
    // Limiting priority to UINT_MAX when value exceeds uint32 max.
    // This can happen for e.g. when preference = 3.


  const std::string & username() const;
  void set_username(const std::string & username);

  const std::string & password() const;
  void set_password(const std::string & password);

  const std::string & type() const;
  void set_type(const std::string & type);

  const std::string & network_name() const;
  void set_network_name(const std::string & network_name);

  rtc::AdapterType network_type() const;
  void set_network_type(rtc::AdapterType network_type);

  // Candidates in a new generation replace those in the old generation.
  uint32 generation() const;
  void set_generation(uint32 generation);
  const std::string generation_str() const;
  void set_generation_str(const std::string& str);

  const std::string& foundation() const;

  void set_foundation(const std::string& foundation);

  const rtc::SocketAddress & related_address() const;
  void set_related_address(
    const rtc::SocketAddress & related_address);
  const std::string& tcptype() const;
  void set_tcptype(const std::string& tcptype);

  // Determines whether this candidate is equivalent to the given one.
  bool IsEquivalent(const Candidate& c) const;
    // We ignore the network name, since that is just debug information, and
    // the priority, since that should be the same if the rest is (and it's
    // a float so equality checking is always worrisome).


  std::string ToString() const;

  std::string ToSensitiveString() const;

  uint32 GetPriority(uint32 type_preference,
                     int network_adapter_preference,
                     int relay_preference) const;
    // RFC 5245 - 4.1.2.1.
    // priority = (2^24)*(type preference) +
    //            (2^8)*(local preference) +
    //            (2^0)*(256 - component ID)

    // |local_preference| length is 2 bytes, 0-65535 inclusive.
    // In our implemenation we will partion local_preference into
    //              0                 1
    //       0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5
    //      +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    //      |  NIC Pref     |    Addr Pref  |
    //      +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    // NIC Type - Type of the network adapter e.g. 3G/Wifi/Wired.
    // Addr Pref - Address preference value as per RFC 3484.
    // local preference =  (NIC Type << 8 | Addr_Pref) - relay preference.



 private:
  std::string ToStringInternal(bool sensitive) const;

  std::string id_;
  int component_;
  std::string protocol_;
  std::string relay_protocol_;
  rtc::SocketAddress address_;
  uint32 priority_;
  std::string username_;
  std::string password_;
  std::string type_;
  std::string network_name_;
  rtc::AdapterType network_type_;
  uint32 generation_;
  std::string foundation_;
  rtc::SocketAddress related_address_;
  std::string tcptype_;
};

// Used during parsing and writing to map component to channel name
// and back.  This is primarily for converting old G-ICE candidate
// signalling to new ICE candidate classes.
class CandidateTranslator {
 public:
  virtual ~CandidateTranslator() {}
  virtual bool GetChannelNameFromComponent(
      int component, std::string* channel_name) const = 0;
  virtual bool GetComponentFromChannelName(
      const std::string& channel_name, int* component) const = 0;
};

}  // namespace cricket

#endif  // WEBRTC_P2P_BASE_CANDIDATE_H_
