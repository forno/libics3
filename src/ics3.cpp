#include"ics3/ics3.hpp"

#include"core.hpp"
#include"ics3/eeprom.hpp"
#include"ics3/parameter.hpp"
#include"ics3/id.hpp"

static inline ics::Angle::rawType getReceiveAngle(const ics::Core::Container& rx) noexcept {
  return (rx[4] << 7) | rx[5];
}

static inline ics::Core::value getCmd(const ics::Core::value head, const ics::ID& id) {
  return head | id.get();
}

ics::ICS3::ICS3(const std::string& path, const Baudrate& baudrate)
: core {Core::getCore(path, baudrate.getSpeed())}
{}

ics::Angle ics::ICS3::move(const ID& id, Angle angle) {
  static Core::Container tx(3), rx(6); // cache for runtime speed
  const auto send = angle.getRaw();
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
  const Core::Container tx {getCmd(0xC0, id), param.getSubcommand(), param.get()};
  Core::Container rx(6);
  core->communicate(tx, rx); // throw std::runtime_error
}

ics::EepRom ics::ICS3::getRom(const ID& id) {
  const Core::Container tx {getCmd(0xA0, id), 0};
  Core::Container rx(68);
  core->communicate(tx, rx); // throw std::runtime_error
  EepRom::Container romData;
  std::copy(rx.cbegin() + 4, rx.cend(), romData.begin());
  return {romData}; // need friend
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
  return {static_cast<ID::type>(0x1F & rx[4])};
}

void ics::ICS3::setID(const ID& id) {
  const Core::IDContainerTx tx {getCmd(0xE0, id), 1, 1, 1};
  Core::IDContainerRx rx;
  core->communicateID(tx, rx);
}
