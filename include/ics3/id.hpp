#ifndef LIBICS3_ICS3_ID_H_
#define LIBICS3_ICS3_ID_H_

#include <stdexcept>

namespace ics {
  class ID {
  public:
    explicit ID(unsigned char) throw(std::invalid_argument);
    unsigned char get() const noexcept;
    void set(unsigned char) throw(std::invalid_argument);
  private:
    double data;
  };
}

#endif // LIBICS3_ICS3_ID_H_
