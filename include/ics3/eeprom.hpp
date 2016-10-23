#ifndef LIBICS3_ICS3_EEPROM_H_
#define LIBICS3_ICS3_EEPROM_H_

#include<array>
#include<algorithm>

#include"ics3/eepparam.hpp"

namespace ics {
  class ICS3;

  class EepRom {
  public:
    friend ICS3; // for ICS3::getRom()
    EepParam get(EepParam) const;
    void set(const EepParam&) noexcept;
    template<typename Iter> void write(Iter&&) const noexcept;
  private:
    explicit EepRom(const std::array<uint8_t, 64>&);

    std::array<uint8_t, 64> data;
  };

  inline ics::EepParam ics::EepRom::get(EepParam place) const {
    place.read(data);
    return place;
  }

  inline void EepRom::set(const EepParam& param) noexcept {
    param.write(data);
  }

  template<typename Iter> inline void EepRom::write(Iter&& dest) const noexcept {
    std::copy(data.begin(), data.end(), dest);
  }

  inline EepRom::EepRom(const std::array<uint8_t, 64>& src)
  : data {}
  {
    std::copy(src.begin(), src.end(), data.begin());
  }
}

#endif // LIBICS3_ICS3_EEPROM_H_
