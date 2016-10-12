#include "ics3/id.hpp"

ics::ID::ID(unsigned char id) {
  try {
    set(id);
  } catch (std::invalid_argument& e) {
    throw;
  }
}

unsigned char ics::ID::get() const noexcept {
  return data;
}

void ics::ID::set(unsigned char id) {
  if (id > 31) throw std::invalid_argument("Too big argument");
  data = id;
}
