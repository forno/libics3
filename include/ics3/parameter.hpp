#ifndef LIBICS3_ICS3_PARAMETER_H_
#define LIBICS3_ICS3_PARAMETER_H_

#include"ics3/check_invalid.hpp"

namespace ics {
  class Parameter {
  public:
    using type = uint8_t;
    static constexpr Parameter stretch(type = 30);
    static constexpr Parameter speed(type = 127);
    static constexpr Parameter current(type = 63);
    static constexpr Parameter temperature(type = 80);
    static constexpr Parameter newParameter(const Parameter&, type);

    constexpr type get() const noexcept;
    constexpr operator type() const noexcept;
    void set(type);
    Parameter& operator=(type);
    constexpr type getSubcommand() const noexcept;
  private:
    constexpr Parameter(type, type, type, type); // non explicit, user cannot touch this

    const type sc;
    const type min;
    const type max;
    type data;
  };

  constexpr Parameter Parameter::stretch(type data) {
    return Parameter {0x01, 1, 127, data};
  }

  constexpr Parameter Parameter::speed(type data) {
    return Parameter {0x02, 1, 127, data};
  }

  constexpr Parameter Parameter::current(type data) {
    return Parameter {0x03, 0, 63, data};
  }

  constexpr Parameter Parameter::temperature(type data) {
    return Parameter {0x04, 1, 127, data};
  }

  constexpr Parameter Parameter::newParameter(const Parameter& base, type data) {
    return Parameter {base.sc, base.min, base.max, data};
  }

  constexpr Parameter::type Parameter::get() const noexcept {
    return data;
  }

  constexpr Parameter::operator type() const noexcept {
    return get();
  }

  inline void Parameter::set(type input) {
    data = checkInvalidRange(input, min, max);
  }

  inline Parameter& Parameter::operator=(type rhs) {
    set(rhs);
    return *this;
  }

  constexpr Parameter::type Parameter::getSubcommand() const noexcept {
    return sc;
  }

  constexpr Parameter::Parameter(type sc, type min, type max, type defaultData)
  : sc {sc},
    min {min},
    max {max},
    data {checkInvalidRange(defaultData, min, max)}
  {}
}

#endif // LIBICS3_ICS3_PARAMETER_H_
