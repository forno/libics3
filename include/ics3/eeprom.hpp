#ifndef LIBICS3_ICS3_EEPROM_H_
#define LIBICS3_ICS3_EEPROM_H_

#include <array>
#include <vector>
#include <stdexcept>

namespace ics {
  enum struct EepFlag {
    REVERSE =   000000001,
    FREE =      000000010,
    PWMINH =    000000100,
    ROLL_MODE = 000010000,
    SLAVE =     010000000
  };

  class EepParam {
    public:
      static EepParam strech() noexcept;
      static EepParam speed() noexcept;
      static EepParam punch() noexcept;
      static EepParam deadBand() noexcept;
      static EepParam dumping() noexcept;
      static EepParam selfTimer() noexcept;
      static EepParam flag() noexcept;
      static EepParam pulseMaxLimit() noexcept;
      static EepParam pulseMinLimit() noexcept;
      static EepParam tmperatureLimit() noexcept;
      static EepParam currentLimit() noexcept;
      static EepParam response() noexcept;
      static EepParam userOffset() noexcept;
      static EepParam id() noexcept;
      static EepParam strech1() noexcept;
      static EepParam strech2() noexcept;
      static EepParam strech3() noexcept;
      void set(uint16_t) throw(std::range_error);
      uint16_t get() const noexcept;
      void setRaw(std::array<unsigned char, 64> &) const noexcept;
    private:
      EepParam(int,
               uint16_t,
               uint16_t,
               void (EepParam::*)(std::array<unsigned char, 64> &) const noexcept,
               void (EepParam::*)(uint16_t) throw(std::range_error)
              ) noexcept;
      void setRaw2byte(std::array<unsigned char, 64> &) const noexcept;
      void setRaw4byte(std::array<unsigned char, 64> &) const noexcept;
      void setNormal(uint16_t) throw(std::range_error);
      void setEven(uint16_t) throw(std::range_error);
      void setFlag(uint16_t) throw(std::range_error);

      const int offset;
      const uint16_t min;
      const uint16_t max;
      void (EepParam::*const setRawFunc)(std::array<unsigned char, 64> &) const noexcept;
      void (EepParam::*const setFunc)(uint16_t) throw(std::range_error);
      uint16_t data;
  };

  class Eeprom {
  public:
    Eeprom();
    void set(EepParam);
    EepParam get(const EepParam &);
    void copy(std::vector<unsigned char> &);

  private:
    std::array<unsigned char, 64> data;
  };
}

#endif // LIBICS3_ICS3_EEPROM_H_
