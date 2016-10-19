#ifndef LIBICS3_ICS3_PARAMETER_H_
#define LIBICS3_ICS3_PARAMETER_H_

#include<stdexcept>

namespace ics {
  class Parameter {
  public:
    static constexpr Parameter stretch(unsigned char = 30);
    static constexpr Parameter speed(unsigned char = 127);
    static constexpr Parameter current(unsigned char = 63);
    static constexpr Parameter temperature(unsigned char = 80);

    constexpr unsigned char get() const noexcept;
    constexpr operator unsigned char() const noexcept;
    void set(unsigned char);
    constexpr unsigned char getSc() const noexcept;
  private:
    constexpr explicit Parameter(unsigned char, unsigned char, unsigned char, unsigned char);
    static constexpr unsigned char chackInvalid(unsigned char, unsigned char, unsigned char);

    const unsigned char sc;
    const unsigned char min;
    const unsigned char max;
    unsigned char data;
  };

  constexpr Parameter Parameter::stretch(unsigned char data) {
    return Parameter {0x01, 1, 127, data};
  }

  constexpr Parameter Parameter::speed(unsigned char data) {
    return Parameter {0x02, 1, 127, data};
  }

  constexpr Parameter Parameter::current(unsigned char data) {
    return Parameter {0x03, 0, 63, data};
  }

  constexpr Parameter Parameter::temperature(unsigned char data) {
    return Parameter {0x04, 1, 127, data};
  }

  constexpr unsigned char Parameter::get() const noexcept {
    return data;
  }

  constexpr Parameter::operator unsigned char() const noexcept {
    return get();
  }

  inline void Parameter::set(unsigned char input) {
    data = chackInvalid(input, min, max);
  }

  constexpr unsigned char Parameter::getSc() const noexcept {
    return sc;
  }

  constexpr Parameter::Parameter(unsigned char sc, unsigned char min, unsigned char max, unsigned char default_data)
  : sc {sc},
    min {min},
    max {max},
    data {chackInvalid(default_data, min, max)}
  {}

  constexpr unsigned char Parameter::chackInvalid(unsigned char input, unsigned char min, unsigned char max) {
    return input < min ? throw std::invalid_argument {"Too small value"} :
           max < input ? throw std::invalid_argument {"Too big value"} :
           input;
  }
}

#endif // LIBICS3_ICS3_PARAMETER_H_
