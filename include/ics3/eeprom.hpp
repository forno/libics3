#ifndef LIBICS3_ICS3_EEPROM_H_
#define LIBICS3_ICS3_EEPROM_H_

#include <array>
#include <vector>

namespace ics {
  class Eeprom {
  public:
    Eeprom() noexcept;
    void set(EepParam) noexcept;
    EepParam get(const EepParam &) const noexcept;
    void copy(std::vector<unsigned char> &) const noexcept;

  private:
    std::array<unsigned char, 64> data;
  };
}

#endif // LIBICS3_ICS3_EEPROM_H_
