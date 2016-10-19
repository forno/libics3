#ifndef LIBICS3_ICS3_PARAMETER_H_
#define LIBICS3_ICS3_PARAMETER_H_

#include<stdexcept>

namespace ics {
  class Parameter {
  public:
    static constexpr Parameter stretch(uint8_t = 30);
    static constexpr Parameter speed(uint8_t = 127);
    static constexpr Parameter current(uint8_t = 63);
    static constexpr Parameter temperature(uint8_t = 80);

    constexpr uint8_t get() const noexcept;
    constexpr operator uint8_t() const noexcept;
    void set(uint8_t);
    Parameter& operator=(uint8_t);
    constexpr uint8_t getSc() const noexcept;
  private:
    explicit constexpr Parameter(uint8_t, uint8_t, uint8_t, uint8_t);
    static constexpr uint8_t checkInvalid(uint8_t, uint8_t, uint8_t);

    const uint8_t sc;
    const uint8_t min;
    const uint8_t max;
    uint8_t data;
  };

  constexpr Parameter Parameter::stretch(uint8_t data) {
    return Parameter {0x01, 1, 127, data};
  }

  constexpr Parameter Parameter::speed(uint8_t data) {
    return Parameter {0x02, 1, 127, data};
  }

  constexpr Parameter Parameter::current(uint8_t data) {
    return Parameter {0x03, 0, 63, data};
  }

  constexpr Parameter Parameter::temperature(uint8_t data) {
    return Parameter {0x04, 1, 127, data};
  }

  constexpr uint8_t Parameter::get() const noexcept {
    return data;
  }

  constexpr Parameter::operator uint8_t() const noexcept {
    return get();
  }

  inline void Parameter::set(uint8_t input) {
    data = checkInvalid(input, min, max);
  }

  inline Parameter& Parameter::operator=(uint8_t rhs) {
    set(rhs);
    return *this;
  }

  constexpr uint8_t Parameter::getSc() const noexcept {
    return sc;
  }

  constexpr Parameter::Parameter(uint8_t sc, uint8_t min, uint8_t max, uint8_t default_data)
  : sc {sc},
    min {min},
    max {max},
    data {checkInvalid(default_data, min, max)}
  {}

  constexpr uint8_t Parameter::checkInvalid(uint8_t input, uint8_t min, uint8_t max) {
    return input < min ? throw std::invalid_argument {"Too small value"} :
           max < input ? throw std::invalid_argument {"Too big value"} :
           input;
  }
}

#endif // LIBICS3_ICS3_PARAMETER_H_
