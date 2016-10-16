#ifndef LIBICS3_ICS3_EEPROM_H_
#define LIBICS3_ICS3_EEPROM_H_

#include <array>
#include <vector>

namespace ics {
  class EepParam;
  class ICS3;

  class Eeprom {
  public:
    friend ICS3;
    EepParam get(EepParam) const;
    void set(const EepParam&) noexcept;
    void copyTo(std::vector<unsigned char>&) const noexcept;
    void copyTo(std::array<unsigned char, 64>&) const noexcept;
  private:
    explicit Eeprom(const std::array<unsigned char, 64>&);
    std::array<unsigned char, 64> data;
  };
}

#endif // LIBICS3_ICS3_EEPROM_H_
