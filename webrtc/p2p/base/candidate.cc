#include "candidate.h"

namespace cricket {

  // TODO: Match the ordering and param list as per RFC 5245
  // candidate-attribute syntax. http://tools.ietf.org/html/rfc5245#section-15.1
Candidate::Candidate()
      : id_(rtc::CreateRandomString(8)),
        component_(0),
        priority_(0),
        network_type_(rtc::ADAPTER_TYPE_UNKNOWN),
        generation_(0) {}

Candidate:: Candidate(int component,
            const std::string& protocol,
            const rtc::SocketAddress& address,
            uint32 priority,
            const std::string& username,
            const std::string& password,
            const std::string& type,
            uint32 generation,
            const std::string& foundation)
      : id_(rtc::CreateRandomString(8)),
        component_(component),
        protocol_(protocol),
        address_(address),
        priority_(priority),
        username_(username),
        password_(password),
        type_(type),
        network_type_(rtc::ADAPTER_TYPE_UNKNOWN),
        generation_(generation),
        foundation_(foundation) {}

const std::string & Candidate::id() const
{
    return id_;
}
void Candidate::set_id(const std::string & id) { id_ = id; }

int Candidate::component() const { return component_; }
void Candidate::set_component(int component) { component_ = component; }

const std::string & Candidate::protocol() const { return protocol_; }
void Candidate::set_protocol(const std::string & protocol) { protocol_ = protocol; }

  // The protocol used to talk to relay.
const std::string& Candidate::relay_protocol() const { return relay_protocol_; }
    void Candidate::set_relay_protocol(const std::string& protocol) {
    relay_protocol_ = protocol;
}

const rtc::SocketAddress & Candidate::address() const { return address_; }
    void Candidate::set_address(const rtc::SocketAddress & address) {
    address_ = address;
}

    uint32 Candidate::priority() const { return priority_; }
    void Candidate::set_priority(const uint32 priority) { priority_ = priority; }

  // TODO(pthatcher): Remove once Chromium's jingle/glue/utils.cc
  // doesn't use it.
  // Maps old preference (which was 0.0-1.0) to match priority (which
  // is 0-2^32-1) to to match RFC 5245, section 4.1.2.1.  Also see
  // https://docs.google.com/a/google.com/document/d/
  // 1iNQDiwDKMh0NQOrCqbj3DKKRT0Dn5_5UJYhmZO-t7Uc/edit
    float Candidate::preference() const {
    // The preference value is clamped to two decimal precision.
    return static_cast<float>(((priority_ >> 24) * 100 / 127) / 100.0);
  }

  // TODO(pthatcher): Remove once Chromium's jingle/glue/utils.cc
  // doesn't use it.
    void Candidate::set_preference(float preference) {
    // Limiting priority to UINT_MAX when value exceeds uint32 max.
    // This can happen for e.g. when preference = 3.
    uint64 prio_val = static_cast<uint64>(preference * 127) << 24;
    priority_ =
        static_cast<uint32>(std::min(prio_val, static_cast<uint64>(UINT_MAX)));
  }

    const std::string & Candidate::username() const { return username_; }
    void Candidate::set_username(const std::string & username) { username_ = username; }

    const std::string & Candidate::password() const { return password_; }
    void Candidate::set_password(const std::string & password) { password_ = password; }

    const std::string & Candidate::type() const { return type_; }
    void Candidate::set_type(const std::string & type) { type_ = type; }

    const std::string & Candidate::network_name() const { return network_name_; }
    void Candidate::set_network_name(const std::string & network_name) {
    network_name_ = network_name;
  }

    rtc::AdapterType Candidate::network_type() const { return network_type_; }
    void Candidate::set_network_type(rtc::AdapterType network_type) {
    network_type_ = network_type;
  }

  // Candidates in a new generation replace those in the old generation.
    uint32 Candidate::generation() const { return generation_; }
    void Candidate::set_generation(uint32 generation) { generation_ = generation; }
    const std::string Candidate::generation_str() const {
    std::ostringstream ost;
    ost << generation_;
    return ost.str();
  }
    void Candidate::set_generation_str(const std::string& str) {
    std::istringstream ist(str);
    ist >> generation_;
  }

    const std::string& Candidate::foundation() const {
    return foundation_;
  }

    void Candidate::set_foundation(const std::string& foundation) {
    foundation_ = foundation;
  }

    const rtc::SocketAddress & Candidate::related_address() const {
    return related_address_;
  }
    void Candidate::set_related_address(
      const rtc::SocketAddress & related_address) {
    related_address_ = related_address;
  }
    const std::string& Candidate::tcptype() const { return tcptype_; }
    void Candidate::set_tcptype(const std::string& tcptype){
    tcptype_ = tcptype;
  }

  // Determines whether this candidate is equivalent to the given one.
    bool Candidate::IsEquivalent(const Candidate& c) const {
    // We ignore the network name, since that is just debug information, and
    // the priority, since that should be the same if the rest is (and it's
    // a float so equality checking is always worrisome).
    return (component_ == c.component_) && (protocol_ == c.protocol_) &&
           (address_ == c.address_) && (username_ == c.username_) &&
           (password_ == c.password_) && (type_ == c.type_) &&
           (generation_ == c.generation_) && (foundation_ == c.foundation_) &&
           (related_address_ == c.related_address_);
  }

    std::string Candidate::ToString() const {
    return ToStringInternal(false);
  }

    std::string Candidate::ToSensitiveString() const {
    return ToStringInternal(true);
  }

    uint32 Candidate::GetPriority(uint32 type_preference,
                     int network_adapter_preference,
                     int relay_preference) const {
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

    int addr_pref = IPAddressPrecedence(address_.ipaddr());
    int local_preference = ((network_adapter_preference << 8) | addr_pref) +
        relay_preference;

    return (type_preference << 24) |
           (local_preference << 8) |
           (256 - component_);
  }
////////////////////////////////////private///////////////////////////
    std::string Candidate::ToStringInternal(bool sensitive) const {
    std::ostringstream ost;
    std::string address = sensitive ? address_.ToSensitiveString() :
                                      address_.ToString();
    ost << "Cand[" << foundation_ << ":" << component_ << ":"
        << protocol_ << ":" << priority_ << ":"
        << address << ":" << type_ << ":" << related_address_ << ":"
        << username_ << ":" << password_ << "]";
    return ost.str();
  }



}  // namespace cricket
