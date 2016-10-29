#ifndef LIBICS3_ICS3_EEPROM_H_
#define LIBICS3_ICS3_EEPROM_H_

#include"ics3/eepparam.hpp"

#include<algorithm>

namespace ics {
  class ICS3;

  class EepRom {
  public:
    friend ICS3; // for ICS3::getRom()
    EepParam get(EepParam) const;
    void set(const EepParam&) noexcept;
    template<typename Iter> void write(Iter&&) const;
  private:
    explicit EepRom(const std::array<uint8_t, 64>&);

    std::array<uint8_t, 64> data;
  };

  inline ics::EepParam ics::EepRom::get(EepParam type) const {
    type.read(data); // throw std::out_of_range
    return type;
  }

  inline void EepRom::set(const EepParam& param) noexcept {
    param.write(data);
  }

  template<typename Iter> inline void EepRom::write(Iter&& dest) const {
    std::copy(data.begin(), data.end(), dest);
  }

  inline EepRom::EepRom(const std::array<uint8_t, 64>& src)
  : data {}
  {
    std::copy(src.begin(), src.end(), data.begin());
  }
}

#endif // LIBICS3_ICS3_EEPROM_H_
