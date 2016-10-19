#ifndef LIBICS3_ICS3_CHECK_INVALID_H_
#define LIBICS3_ICS3_CHECK_INVALID_H_

#include<stdexcept>

template<typename T> constexpr T checkInvalid(T input, T min, T max) {
  return input < min ? throw std::invalid_argument {"Too small argument"} :
         max < input ? throw std::invalid_argument {"Too big argument"} :
         input;
}

#endif // LIBICS3_ICS3_CHECK_INVALID_H_
