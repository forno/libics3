#ifndef LIBICS3_ICS3_CORE_H_
#define LIBICS3_ICS3_CORE_H_

#include <vector>

namespace ics {
  class Core {
  public:
    static const Core &getReference();
    std::vector<unsigned char> &communicate(std::vector<unsigned char>);
  private:
  };
}

#endif // LIBICS3_ICS3_CORE_H_
