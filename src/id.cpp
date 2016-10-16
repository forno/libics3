#include "ics3/id.hpp"

ics::ID::ID(unsigned char id)
: data(id)
{
  if (id > 31) throw std::invalid_argument("Too big arguments");
}

unsigned char ics::ID::get() const noexcept {
  return data;
}
