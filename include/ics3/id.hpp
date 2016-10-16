#ifndef LIBICS3_ICS3_ID_H_
#define LIBICS3_ICS3_ID_H_

#include<stdexcept>

namespace ics {
  class ID {
  public:
    constexpr ID(unsigned char);
    constexpr operator unsigned char() const noexcept;
    constexpr unsigned char get() const noexcept;
  private:
    const unsigned char data;
  };

  constexpr ID::ID(unsigned char id)
  : data {id < 32 ? id : throw std::invalid_argument {"Too big arguments"}}
  {}

  constexpr ID::operator unsigned char() const noexcept {
    return data;
  }

  constexpr unsigned char ID::get() const noexcept {
    return data;
  }
}

#endif // LIBICS3_ICS3_ID_H_
