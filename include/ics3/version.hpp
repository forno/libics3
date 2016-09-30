#ifndef LIBICS3_ICS3_VERSION_H_
#define LIBICS3_ICS3_VERSION_H_

namespace ics {
  class MinorVersion {
  public:
    enum struct Versions {
      DEFAULT,
      V0,
      V5,
      V6
    };

    static const Versions getVersion() noexcept;
    static void setVersion(const Versions) noexcept;
  private:
    static Versions version;
    MinorVersion();
  };
}

#endif // LIBICS3_ICS3_VERSION_H_
