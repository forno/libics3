#ifndef LIBICS3_ICS3_CORE_H_
#define LIBICS3_ICS3_CORE_H_

#include<vector>
#include<string>
#include<memory>
#include<termios.h>

namespace ics {
  class Core {
  public:
    explicit Core(const std::string&, speed_t); // touch by only libics3
    ~Core() noexcept;
    Core(const Core&) = delete;
    Core& operator=(const Core&) = delete;
    Core(Core&&) noexcept;
    Core& operator=(Core&&) noexcept;

    static std::shared_ptr<Core> getCore(const std::string&, speed_t);
    void communicate(const std::vector<uint8_t>&, std::vector<uint8_t>&);
    void communicateID(const std::vector<uint8_t>&, std::vector<uint8_t>&);
  private:
    static termios getTermios() noexcept;

    int fd;
    termios oldTio;
  };
}

#endif // LIBICS3_ICS3_CORE_H_
