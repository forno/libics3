#include"ics3/ics3.hpp"

#include"core.hpp"
#include"ics3/eeprom.hpp"
#include"ics3/parameter.hpp"
#include"ics3/id.hpp"

#include<stdexcept>
#include<array>
#include<cassert>

ics::Angle getReceiveAngle(std::vector<unsigned char>::iterator&& it, ics::Angle unit) {
  uint16_t receive {static_cast<uint16_t>((*it << 7) | *++it)};
  try {
    unit.setRaw(receive);
  } catch (...) {
    throw std::runtime_error {"Receive angle error"};
  }
  return unit;
}

ics::ICS3::ICS3(const char* path, const Baudrate& baudrate)
: core {Core::getReference(path, baudrate.get())}
{}

ics::Angle ics::ICS3::free(const ID& id, const Angle& unit) const {
  static std::vector<unsigned char> tx(3), rx(6);
  tx[0] = 0x80 | id.get();
  tx[1] = 0;
  tx[2] = 0;
  core.communicate(tx, rx); // throw std::runtime_error
  return getReceiveAngle(rx.begin() + 4, unit);
}

ics::Angle ics::ICS3::move(const ID& id, const Angle& angle) const {
  static std::vector<unsigned char> tx(3), rx(6);
  uint16_t send {angle.getRaw()};
  tx[0] = 0x80 | id.get();
  tx[1] = 0x7F & (send >> 7);
  tx[2] = 0x7F & send;
  core.communicate(tx, rx); // throw std::runtime_error
  return getReceiveAngle(rx.begin() + 4, angle);
}

ics::Parameter ics::ICS3::get(const ID& id, const Parameter& place) const {
  static std::vector<unsigned char> tx(2), rx(5);
  tx[0] = 0xA0 | id.get();
  tx[1] = place.getSubcommand();
  core.communicate(tx, rx); // throw std::runtime_error
  return Parameter::newParameter(place, rx[4]);
}

void ics::ICS3::set(const ID& id, const Parameter& param) const {
  static std::vector<unsigned char> tx(3), rx(6);
  tx[0] = 0xC0 | id.get();
  tx[1] = param.getSubcommand();
  tx[2] = param.get();
  core.communicate(tx, rx); // throw std::runtime_error
}

ics::Eeprom ics::ICS3::getRom(const ID& id) const {
  static std::vector<unsigned char> tx(2), rx(68);
  tx[0] = 0xA0 | id.get();
  tx[1] = 0;
  core.communicate(tx, rx); // throw std::runtime_error
  std::array<unsigned char, 64> rom;
  std::copy(rx.begin() + 2, rx.end(), rom.begin());
  return Eeprom {rom}; // need friend
}

void ics::ICS3::setRom(const ID& id, const Eeprom& rom) const {
  static std::vector<unsigned char> tx(66), rx(68);
  tx[0] = 0xC0 | id.get();
  tx[2] = 0;
  rom.write(tx.begin() + 2);
  core.communicate(tx, rx); // throw std::runtime_error
}
