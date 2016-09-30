#ifndef LIBICS3_ICS3_EEPROM_H_
#define LIBICS3_ICS3_EEPROM_H_

#include <vector>
#include <stdexcept>

namespace ics {
  class EepParam {
    public:
      static EepParam strech();
      static EepParam speed();
      static EepParam punch();
      static EepParam deadBand();
      static EepParam dumping();
      static EepParam selfTimer();
      static EepParam pulseMaxLimit();
      static EepParam pulseMinLimit();
      static EepParam tmperatureLimit();
      static EepParam currentLimit();
      static EepParam response();
      static EepParam userOffset();
      static EepParam id();
      static EepParam strech1();
      static EepParam strech2();
      static EepParam strech3();
      void set(uint16_t) throw(std::range_error);
      uint16_t get() const noexcept;
      void setRaw(std::vector<unsigned char> &) const noexcept;
    private:
      EepParam(int, uint16_t, uint16_t, void *(std::vector<unsigned char> &), void *(uint16_t));
      void setRaw2byte(std::vector<unsigned char> &) const noexcept;
      void setRaw4byte(std::vector<unsigned char> &) const noexcept;
      void setNormal(uint16_t) throw(std::range_error);
      void setEven(uint16_t) throw(std::range_error);

      const int offset;
      const uint16_t min;
      const uint16_t max;
      void (*const rawFunc)(std::vector<unsigned char> &);
      void (*const setFunc)(uint16_t);
      uint16_t data;

      static const EepParam STRECH;
      static const EepParam SPEED;
      static const EepParam PUNCH;
      static const EepParam DEAD_BAND;
      static const EepParam DUMPING;
      static const EepParam SELF_TIMER;
      static const EepParam PULSE_MAX_LIMIT;
      static const EepParam PULSE_MIN_LIMIT;
      static const EepParam TMPERATURE_LIMIT;
      static const EepParam CURRENT_LIMIT;
      static const EepParam RESPONSE;
      static const EepParam USER_OFFSET;
      static const EepParam ID;
      static const EepParam STRECH1;
      static const EepParam STRECH2;
      static const EepParam STRECH3;
  };
  class Eeprom {
  public:
    Eeprom();
    void set(EepParam);
    EepParam get(const EepParam &);

  private:
  };
}

#endif // LIBICS3_ICS3_EEPROM_H_
