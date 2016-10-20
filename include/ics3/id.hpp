#ifndef LIBICS3_ICS3_ID_H_
#define LIBICS3_ICS3_ID_H_

#include<stdexcept>

namespace ics {
  class ID {
  public:
    constexpr ID(unsigned char); // ID is non explicit constructor because only do check limit
    constexpr unsigned char get() const noexcept;
    constexpr operator unsigned char() const noexcept;
  private:
    const unsigned char data;
  };

  constexpr ID::ID(unsigned char id)
  : data {id < 32 ? id : throw std::invalid_argument {"Too big arguments"}}
  {}

  constexpr unsigned char ID::get() const noexcept {
    return data;
  }

  constexpr ID::operator unsigned char() const noexcept {
    return get();
  }
}

#endif // LIBICS3_ICS3_ID_H_
