#ifndef LIBICS3_ICS3_EEPROM_H_
#define LIBICS3_ICS3_EEPROM_H_

#include<array>
#include<algorithm>

#include"ics3/eepparam.hpp"

namespace ics {
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

  inline ics::EepParam ics::Eeprom::get(EepParam place) const {
    place.read(data);
    return place;
  }

  inline void Eeprom::set(const EepParam& param) noexcept {
    param.write(data);
  }

  template<typename Iter> inline void Eeprom::write(Iter&& dest) const noexcept {
    std::copy(data.begin(), data.end(), dest);
  }

  inline Eeprom::Eeprom(const std::array<unsigned char, 64>& src)
  : data {}
  {
    std::copy(src.begin(), src.end(), data.begin());
  }
}

#endif // LIBICS3_ICS3_EEPROM_H_
