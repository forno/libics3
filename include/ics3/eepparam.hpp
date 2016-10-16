#ifndef LIBICS3_ICS3_EEPPARAM_H_
#define LIBICS3_ICS3_EEPPARAM_H_

#include <array>

namespace ics {
  class EepParam {
  public:
    enum Flag : uint16_t {
      REVERSE =   0x1,
      FREE =      0x2,
      PWMINH =    0x8,
      ROLL_MODE = 0x10,
      SLAVE =     0x80
    };
    enum Baudrate : uint16_t {
      RATE115200 = 10,
      RATE625000 = 1,
      RATE1250000 = 0
    };

    static EepParam strech() noexcept;
    static EepParam speed() noexcept;
    static EepParam punch() noexcept;
    static EepParam deadBand() noexcept;
    static EepParam dumping() noexcept;
    static EepParam selfTimer() noexcept;
    static EepParam flag() noexcept;
    static EepParam pulseMax() noexcept;
    static EepParam pulseMin() noexcept;
    static EepParam baudrate() noexcept;
    static EepParam temperature() noexcept;
    static EepParam current() noexcept;
    static EepParam response() noexcept;
    static EepParam userOffset() noexcept;
    static EepParam id() noexcept;
    static EepParam strech1() noexcept;
    static EepParam strech2() noexcept;
    static EepParam strech3() noexcept;

    uint16_t get() const noexcept;
    void set(uint16_t);
    void write(std::array<unsigned char, 64>&) const noexcept;
    void read(const std::array<unsigned char, 64>&);
  private:
    explicit EepParam(
        size_t,
        size_t,
        uint16_t,
        uint16_t,
        void (EepParam::*)(uint16_t),
        uint16_t
    ) noexcept;
    void setNormal(uint16_t);
    void setEven(uint16_t);
    void setFlag(uint16_t);
    void setBaudrate(uint16_t);
    void setOffset(uint16_t);

    const size_t offset;
    const size_t length;
    const uint16_t min;
    const uint16_t max;
    void (EepParam::*const setFunc)(uint16_t);
    uint16_t data;
  };
}

#endif // LIBICS3_ICS3_EEPPARAM_H_
