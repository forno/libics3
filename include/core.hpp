#ifndef LIBICS3_ICS3_CORE_H_
#define LIBICS3_ICS3_CORE_H_

#include<vector>
#include<array>
#include<string>
#include<memory>
#include<termios.h>

namespace ics {
  class Core {
  public:
    using value = uint8_t;
    using Container = std::vector<value>;
    using IDContainerTx = std::array<value, 4>;
    using IDContainerRx = std::array<value, 5>;
    explicit Core(const std::string&, speed_t); // touch by only libics3
    ~Core() noexcept;
    Core(const Core&) = delete;
    Core& operator=(const Core&) = delete;
    Core(Core&&) noexcept;
    Core& operator=(Core&&) noexcept;

    static std::shared_ptr<Core> getCore(const std::string&, speed_t);
    void communicate(const Container&, Container&);
    void communicateID(const IDContainerTx&, IDContainerRx&);
  private:
    static termios getTermios() noexcept;

    int fd;
    termios oldTio;
  };
}

#endif // LIBICS3_ICS3_CORE_H_
