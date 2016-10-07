#include "ics3/ics3.hpp"

#include "core.hpp"
#include "ics3/angle.hpp"
#include "ics3/eeprom.hpp"
#include "ics3/parameter.hpp"
#include "ics3/id.hpp"

ics::ICS3::ICS3(const char* path, ICSBaudrate baudrate) throw(std::invalid_argument, std::runtime_error)
  : core(Core::getReference(path, static_cast<speed_t>(baudrate)))
{
}

ics::Angle ics::ICS3::move(const ID &id, Angle angle) const throw(std::runtime_error) {
  static std::vector<unsigned char> tx(3), rx(6);
  uint16_t send = angle.getRaw();
  tx[0] = 0x80 | id.get();
  tx[1] = 0x7F & (send >> 7);
  tx[2] = 0x7F & send;
  try {
    core.communicate(tx, rx);
  } catch (std::runtime_error e) {
    throw e;
  }
  uint16_t receive = (rx[4] << 7) | rx[5];
  try {
    angle.setRaw(receive);
  } catch (std::invalid_argument) {
    throw std::runtime_error("Receive angle error");
  }
  return angle;
}

ics::Parameter ics::ICS3::get(const ID &id, Parameter param) const throw(std::runtime_error) {
  static std::vector<unsigned char> tx(2), rx(5);
  tx[0] = 0xA0 | id.get();
  tx[1] = param.getSc();
  try {
    core.communicate(tx, rx);
  } catch (std::runtime_error e) {
    throw e;
  }
  param.set(rx[4]);
  return param;
}

void ics::ICS3::set(const ID &id, const Parameter &param) const throw(std::runtime_error) {
  static std::vector<unsigned char> tx(3), rx(6);
  tx[0] = 0xC0 | id.get();
  tx[1] = param.getSc();
  tx[2] = param.get();
  try {
    core.communicate(tx, rx);
  } catch (std::runtime_error e) {
    throw e;
  }
}

ics::Eeprom ics::ICS3::getRom(const ID &id) const throw(std::runtime_error) {
  static std::vector<unsigned char> tx(2), rx(68);
  tx[0] = 0xA0 | id.get();
  tx[1] = 0;
  try {
    core.communicate(tx, rx);
  } catch (std::runtime_error e) {
    throw e;
  }
  Eeprom rom;
  std::copy(rx.begin() + 2, rx.end(), rom.data.begin());
  return rom;
}

void ics::ICS3::setRom(const ID &id, const Eeprom &rom) const throw(std::runtime_error) {
  static std::vector<unsigned char> tx(66), rx(68);
  tx[0] = 0xC0 | id.get();
  tx[2] = 0;
  std::copy(rom.data.begin(), rom.data.end(), tx.begin() + 2);
  try {
    core.communicate(tx, rx);
  } catch (std::runtime_error e) {
    throw e;
  }
}
