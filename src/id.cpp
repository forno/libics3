#include "ics3/id.hpp"

ics::ID::ID(unsigned char data) throw(std::invalid_argument) {
  try {
    set(data);
  } catch (std::invalid_arument e) {
    return e;
  }
}

double ics::ID::get() const noexcept {
  return data;
}

void icd::ID::set(unsigned char) throw(std::invalid_argument) {
  if (id > 31) throw std::invalid_argument("Too big argument");
  data = id;
}
