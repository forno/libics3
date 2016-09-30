#ifndef LIBICS3_ICS3_EEPPARAM_H_
#define LIBICS3_ICS3_EEPPARAM_H_

#include <array>
#include <stdexcept>

namespace ics {
  enum EepFlag : uint16_t {
    REVERSE =   000000001,
    FREE =      000000010,
    PWMINH =    000000100,
    ROLL_MODE = 000010000,
    SLAVE =     010000000
  };
  enum EepBaudrate : uint16_t {
    RATE115200 = 10
    RATE625000 = 1,
    RATE1250000 = 0,
  }

  class EepParam {
    public:
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
      void setRaw(std::array<unsigned char, 64> &) const noexcept;
      uint16_t get() const noexcept;
      void set(uint16_t) throw(std::invalid_argument);
    private:
      EepParam(int,
               uint16_t,
               uint16_t,
               void (EepParam::*)(std::array<unsigned char, 64> &) const noexcept,
               void (EepParam::*)(uint16_t) throw(std::invalid_argument),
               uint16_t
              ) noexcept;
      void setRaw2byte(std::array<unsigned char, 64> &) const noexcept;
      void setRaw4byte(std::array<unsigned char, 64> &) const noexcept;
      void setNormal(uint16_t) throw(std::invalid_argument);
      void setEven(uint16_t) throw(std::invalid_argument);
      void setFlag(uint16_t) throw(std::invalid_argument);
      void setBaudrate(uint16_t) throw(std::invalid_argument);
      void setOffset(uint16_t) throw(std::invalid_argument);

      const int offset;
      const uint16_t min;
      const uint16_t max;
      void (EepParam::*const setRawFunc)(std::array<unsigned char, 64> &) const noexcept;
      void (EepParam::*const setFunc)(uint16_t) throw(std::invalid_argument);
      uint16_t data;
  };
}

#endif // LIBICS3_ICS3_EEPPARAM_H_
