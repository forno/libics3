#ifndef LIBICS3_ICS3_PARAMETER_H_
#define LIBICS3_ICS3_PARAMETER_H_

#include<stdexcept>

namespace ics {
  class Parameter {
  public:
    static constexpr Parameter stretch() noexcept;
    static constexpr Parameter speed() noexcept;
    static constexpr Parameter current() noexcept;
    static constexpr Parameter temperature() noexcept;

    constexpr unsigned char get() const noexcept;
    void set(unsigned char);
    constexpr unsigned char getSc() const noexcept;
  private:
    constexpr explicit Parameter(unsigned char, unsigned char, unsigned char, unsigned char) noexcept;

    const unsigned char sc;
    const unsigned char min;
    const unsigned char max;
    unsigned char data;
  };

  constexpr Parameter Parameter::stretch() noexcept {
    return Parameter {0x01, 1, 127, 30};
  }

  constexpr Parameter Parameter::speed() noexcept {
    return Parameter {0x02, 1, 127, 127};
  }

  constexpr Parameter Parameter::current() noexcept {
    return Parameter {0x03, 0, 63, 63};
  }

  constexpr Parameter Parameter::temperature() noexcept {
    return Parameter {0x04, 1, 127, 80};
  }

  constexpr unsigned char Parameter::get() const noexcept {
    return data;
  }

  inline void Parameter::set(unsigned char input) {
    data = input < min ? throw std::invalid_argument {"Too small value"} :
           max < input ? throw std::invalid_argument {"Too big value"} :
           input;
  }

  constexpr unsigned char Parameter::getSc() const noexcept {
    return sc;
  }

  constexpr Parameter::Parameter(unsigned char sc, unsigned char min, unsigned char max, unsigned char default_data) noexcept
  : sc {sc},
    min {min},
    max {max},
    data {default_data}
  {}
}

#endif // LIBICS3_ICS3_PARAMETER_H_
