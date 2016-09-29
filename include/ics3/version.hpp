#ifndef LIBICS3_ICS3_VERSION_H_
#define LIBICS3_ICS3_VERSION_H_

namespace ics {
  class MinorVersion {
  public:
    enum struct Versions {
      V0,
      V5,
      V6
    };

    static const Versions getVersion();
    static void setVersion(const Versions);
  private:
    static Versions version;
    MinorVersion();
  };
}

#endif // LIBICS3_ICS3_VERSION_H_
