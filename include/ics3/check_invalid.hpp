#ifndef LIBICS3_ICS3_CHECK_INVALID_H_
#define LIBICS3_ICS3_CHECK_INVALID_H_

#include<stdexcept>

namespace ics {
  template<typename T>
  constexpr T checkInvalidRange(T input, T min, T max) {
    return input < min ? throw std::out_of_range {"Too small argument"} :
           max < input ? throw std::out_of_range {"Too big argument"} :
           input;
  }
}

#endif // LIBICS3_ICS3_CHECK_INVALID_H_
