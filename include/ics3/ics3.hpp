#ifndef LIBICS3_ICS3_ICS3_H_
#define LIBICS3_ICS3_ICS3_H_

#include <stdexcept>
#include <vector>

namespace ics {
  // Forward declaration
  class Core;
  class Angle;
  class Parameter;
  class Eeprom;
  class ID;

  class ICS3 {
  public:
    ICS3() throw(std::runtime_error);
    Angle move(const ID &, Angle) const throw(std::runtime_error);
    Parameter get(const ID &, Parameter) const throw(std::rutime_error);
    void set(const ID &, const Parameter &) const throw(std::rutime_error);
    Eeprom getRom(const ID &) const throw(std::rutime_error);
    void setRom(const ID &, const Eeprom &) const throw(std::rutime_error);

  private:
    const Core &core;
  };
}

#endif // LIBICS3_ICS3_ICS3_H_
