#ifndef LIBICS3_ICS3_ID_H_
#define LIBICS3_ICS3_ID_H_

#include <stdexcept>

namespace ics {
  class ID {
  public:
    ID(unsigned char) throw(std::invalid_argument);
    double get() const noexcept;
    void set(unsigned char) throw(std::invalid_argument);
  private:
    double data;
  };
}

#endif // LIBICS3_ICS3_ID_H_
