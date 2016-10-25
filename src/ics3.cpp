#include"ics3/ics3.hpp"

#include"core.hpp"
#include"ics3/eeprom.hpp"
#include"ics3/parameter.hpp"
#include"ics3/id.hpp"

inline uint16_t getReceiveAngle(const std::vector<uint8_t>& rx) noexcept {
  return static_cast<uint16_t>((rx[4] << 7) | rx[5]);
}

ics::ICS3::ICS3(const std::string& path, const Baudrate& baudrate)
: core {Core::getReference(path, baudrate.get())}
{}

ics::Angle ics::ICS3::move(const ID& id, Angle angle) const {
  static std::vector<uint8_t> tx(3), rx(6);
  uint16_t send {angle.getRaw()};
  tx[0] = 0x80 | id.get();
  tx[1] = 0x7F & (send >> 7);
  tx[2] = 0x7F & send;
  core.communicate(tx, rx); // throw std::runtime_error
  angle.rawData = getReceiveAngle(rx);
  return angle;
}

ics::Angle ics::ICS3::free(const ID& id, Angle unit) const {
  static std::vector<uint8_t> tx(3), rx(6);
  tx[0] = 0x80 | id.get(); // tx[1] == tx[2] == 0
  core.communicate(tx, rx); // throw std::runtime_error
  unit.rawData = getReceiveAngle(rx);
  return unit;
}

ics::Parameter ics::ICS3::get(const ID& id, Parameter place) const {
  static std::vector<uint8_t> tx(2), rx(5);
  tx[0] = 0xA0 | id.get();
  tx[1] = place.getSubcommand();
  core.communicate(tx, rx); // throw std::runtime_error
  return place = rx[4];
}

void ics::ICS3::set(const ID& id, const Parameter& param) const {
  static std::vector<uint8_t> tx(3), rx(6);
  tx[0] = 0xC0 | id.get();
  tx[1] = param.getSubcommand();
  tx[2] = param.get();
  core.communicate(tx, rx); // throw std::runtime_error
}

ics::EepRom ics::ICS3::getRom(const ID& id) const {
  static std::vector<uint8_t> tx(2), rx(68);
  tx[0] = 0xA0 | id.get(); // tx[1] == 0
  core.communicate(tx, rx); // throw std::runtime_error
  std::array<uint8_t, 64> romData;
  std::copy(rx.begin() + 4, rx.end(), romData.begin());
  return EepRom {romData}; // need friend
}

void ics::ICS3::setRom(const ID& id, const EepRom& rom) const {
  static std::vector<uint8_t> tx(66), rx(68);
  tx[0] = 0xC0 | id.get(); // tx[1] == 0
  rom.write(tx.begin() + 2);
  core.communicate(tx, rx); // throw std::runtime_error
}
