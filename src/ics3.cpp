#include"ics3/ics3.hpp"

#include"core.hpp"
#include"ics3/eeprom.hpp"
#include"ics3/parameter.hpp"
#include"ics3/id.hpp"

static inline ics::Angle::rawType getReceiveAngle(const ics::Core::Container& rx) noexcept {
  return static_cast<ics::Angle::rawType>((rx[4] << 7) | rx[5]);
}

static inline ics::Core::value getCmd(const int head, const ics::ID& id) {
  return head | id.get();
}

ics::ICS3::ICS3(const std::string& path, const Baudrate& baudrate)
: core {Core::getCore(path, baudrate.getSpeed())}
{}

ics::Angle ics::ICS3::move(const ID& id, Angle angle) {
  static Core::Container tx(3), rx(6); // cache for runtime speed
  const uint16_t send {angle.getRaw()};
  tx[0] = getCmd(0x80, id);
  tx[1] = 0x7F & (send >> 7);
  tx[2] = 0x7F & send;
  core->communicate(tx, rx); // throw std::runtime_error
  angle.rawData = getReceiveAngle(rx); // avoid invalid check. need friend
  return angle;
}

ics::Angle ics::ICS3::free(const ID& id, Angle unit) {
  static Core::Container tx(3), rx(6); // cache for runtime speed
  tx[0] = getCmd(0x80, id); // tx[1] == tx[2] == 0
  core->communicate(tx, rx); // throw std::runtime_error
  unit.rawData = getReceiveAngle(rx); // avoid invalid check. need friend
  return unit;
}

ics::Parameter ics::ICS3::get(const ID& id, const Parameter& type) {
  const Core::Container tx {getCmd(0xA0, id), type.getSubcommand()};
  Core::Container rx(5);
  core->communicate(tx, rx); // throw std::runtime_error
  return Parameter::newParameter(type, rx[4]);
}

void ics::ICS3::set(const ID& id, const Parameter& param) {
  Core::Container tx(3), rx(6);
  tx[0] = getCmd(0xC0, id);
  tx[1] = param.getSubcommand();
  tx[2] = param.get();
  core->communicate(tx, rx); // throw std::runtime_error
}

ics::EepRom ics::ICS3::getRom(const ID& id) {
  Core::Container tx(2), rx(68);
  tx[0] = getCmd(0xA0, id); // tx[1] == 0
  core->communicate(tx, rx); // throw std::runtime_error
  std::array<uint8_t, 64> romData;
  std::copy(rx.cbegin() + 4, rx.cend(), romData.begin());
  return EepRom {romData}; // need friend
}

void ics::ICS3::setRom(const ID& id, const EepRom& rom) {
  Core::Container tx(66), rx(68);
  tx[0] = getCmd(0xC0, id); // tx[1] == 0
  rom.write(tx.begin() + 2);
  core->communicate(tx, rx); // throw std::runtime_error
}

ics::ID ics::ICS3::getID() {
  constexpr Core::IDContainerTx tx {0xFF, 0x00, 0x00, 0x00};
  Core::IDContainerRx rx;
  core->communicateID(tx, rx);
  return ID {static_cast<uint8_t>(0x1F & rx[4])};
}

void ics::ICS3::setID(const ID& id) {
  const Core::IDContainerTx tx {getCmd(0xE0, id), 1, 1, 1};
  Core::IDContainerRx rx;
  core->communicateID(tx, rx);
}
