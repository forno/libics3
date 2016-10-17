#ifndef LIBICS3_ICS3_EEPROM_H_
#define LIBICS3_ICS3_EEPROM_H_

#include<array>
#include<vector>
#include<algorithm>

namespace ics {
  class EepParam;
  class ICS3;

  class Eeprom {
  public:
    friend ICS3;
    EepParam get(EepParam) const;
    void set(const EepParam&) noexcept;
    template<typename Iter> void write(Iter&&) const noexcept;
  private:
    explicit Eeprom(const std::array<unsigned char, 64>&);
    std::array<unsigned char, 64> data;
  };

  template<typename Iter> inline void Eeprom::write(Iter&& dest) const noexcept {
    std::copy(data.begin(), data.end(), dest);
  }
}

#endif // LIBICS3_ICS3_EEPROM_H_
