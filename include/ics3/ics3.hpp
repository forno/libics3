#ifndef LIBICS3_ICS3_ICS3_H_
#define LIBICS3_ICS3_ICS3_H_

#include"ics3/angle.hpp"
#include"ics3/baudrate.hpp"

#include<string>
#include<memory>

namespace ics {
  // Forward declaration
  class Core;
  class Parameter;
  class EepRom;
  class ID;

  class ICS3 {
  public:
    explicit ICS3(const std::string&, const Baudrate& = Baudrate::RATE115200());
    Angle move(const ID&, Angle);
    Angle free(const ID&, Angle = Angle::newRadian());
    Parameter get(const ID&, Parameter);
    void set(const ID&, const Parameter&);
    EepRom getRom(const ID&);
    void setRom(const ID&, const EepRom&);
  private:
    std::shared_ptr<Core> core;
  };
}

#endif // LIBICS3_ICS3_ICS3_H_
