#ifndef LIBICS3_ICS3_EEPROM_H_
#define LIBICS3_ICS3_EEPROM_H_

#include"ics3/eepparam.hpp"

#include<algorithm>

namespace ics {
  class ICS3;

  class EepRom {
    friend ICS3; // for ICS3::getRom()
  public:
    using size_type = std::size_t;
    static constexpr size_type length {64};
    using Container = std::array<uint8_t, length>;

    EepParam get(EepParam) const;
    void set(const EepParam&) noexcept;
    template<typename Iter>
    void write(Iter&&) const;
  private:
    EepRom(const Container&); // non explicit, user cannot touch this

    std::array<uint8_t, length> data;
  };

  inline ics::EepParam ics::EepRom::get(EepParam type) const {
    type.read(data); // throw std::out_of_range
    return type;
  }

  inline void EepRom::set(const EepParam& param) noexcept {
    param.write(data);
  }

  template<typename Iter>
  inline void EepRom::write(Iter&& dest) const {
    std::copy(data.cbegin(), data.cend(), dest);
  }

  inline EepRom::EepRom(const Container& src)
  : data(src) // for Ubuntu14.04 compiler
  {}
}

#endif // LIBICS3_ICS3_EEPROM_H_
