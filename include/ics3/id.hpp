#ifndef LIBICS3_ICS3_ID_H_
#define LIBICS3_ICS3_ID_H_

#include <stdexcept>

namespace ics {
  class ID {
  public:
    ID(unsigned char);
    unsigned char get() const noexcept;
  private:
    const double data;
  };
}

#endif // LIBICS3_ICS3_ID_H_
