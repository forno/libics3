#ifndef LIBICS3_ICS3_ID_H_
#define LIBICS3_ICS3_ID_H_

#include<stdexcept>

namespace ics {
  class ID {
  public:
    using type = uint8_t;
    constexpr ID(type); // ID is non explicit constructor because only do check limit
    constexpr type get() const noexcept;
    constexpr operator type() const noexcept;
  private:
    const type data;
  };

  constexpr ID::ID(type id)
  : data {id < 32 ? id : throw std::invalid_argument {"invalid ID: must be 0 <= id <= 31"}}
  {}

  constexpr ID::type ID::get() const noexcept {
    return data;
  }

  constexpr ID::operator type() const noexcept {
    return get();
  }
}

#endif // LIBICS3_ICS3_ID_H_
