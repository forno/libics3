#ifndef LIBICS3_ICS3_ID_H_
#define LIBICS3_ICS3_ID_H_

#include<stdexcept>

namespace ics {
  class ID {
  public:
    constexpr ID(uint8_t); // ID is non explicit constructor because only do check limit
    constexpr uint8_t get() const noexcept;
    constexpr operator uint8_t() const noexcept;
  private:
    const uint8_t data;
  };

  constexpr ID::ID(uint8_t id)
  : data {id < 32 ? id : throw std::out_of_range {"Too big arguments"}}
  {}

  constexpr uint8_t ID::get() const noexcept {
    return data;
  }

  constexpr ID::operator uint8_t() const noexcept {
    return get();
  }
}

#endif // LIBICS3_ICS3_ID_H_
