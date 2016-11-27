/* BSD 2-Clause License

Copyright (c) 2016, Doi Yusuke
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

* Redistributions of source code must retain the above copyright notice, this
  list of conditions and the following disclaimer.

* Redistributions in binary form must reproduce the above copyright notice,
  this list of conditions and the following disclaimer in the documentation
  and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/
#ifndef LIBICS3_ICS3_ANGLE_H_
#define LIBICS3_ICS3_ANGLE_H_

#include"ics3/check_invalid.hpp"

namespace ics {
class ICS3;
class Angle {
  friend ICS3; // for touch rawData
public:
  using rawType = uint16_t;
  using type = double;
  static constexpr Angle newDegree(type = 0.0);
  static constexpr Angle newRadian(type = 0.0);
  static constexpr Angle newSameUnit(const Angle&, type = 0.0);
  static constexpr Angle newCalibration(type, type = 0.0);
  static constexpr rawType MIN {3500};
  static constexpr rawType MID {7500};
  static constexpr rawType MAX {11500};
  static constexpr type PI {3.141592653589793};

  Angle(const Angle&) noexcept = default;
  Angle& operator=(const Angle&) noexcept;
  constexpr type get() const noexcept;
  constexpr operator type() const noexcept;
  void set(type);
  Angle& operator=(type);
  constexpr rawType getRaw() const noexcept;
  void setRaw(rawType);
private:
  constexpr Angle(type, type); // non explicit, user cannot touch this
  static constexpr rawType castToRaw(type, type) noexcept;
  static constexpr rawType checkValidAngle(rawType);

  rawType rawData;
  const type rawCalibration;
};

constexpr Angle Angle::newDegree(type angle) {
  return {800.0 / 27.0, angle};
}

constexpr Angle Angle::newRadian(type angle) {
  return {16000.0 / 3.0 / PI, angle};
}

constexpr Angle Angle::newSameUnit(const Angle& unit, type angle) {
  return {unit.rawCalibration, angle};
}

constexpr Angle Angle::newCalibration(type calibration, type angle) {
  return {calibration, angle};
}

inline Angle& Angle::operator=(const Angle& rhs) noexcept {
  rawData = rhs.rawData;
  return *this;
}

constexpr Angle::type Angle::get() const noexcept {
  return (rawData - MID) / rawCalibration;
}

constexpr Angle::operator type() const noexcept {
  return get();
}

inline void Angle::set(type angle) {
  setRaw(castToRaw(rawCalibration, angle)); // throw std::out_of_range
}

inline Angle& Angle::operator=(type angle) {
  set(angle);
  return *this;
}

constexpr Angle::rawType Angle::getRaw() const noexcept {
  return rawData;
}

inline void Angle::setRaw(rawType raw) {
  rawData = checkValidAngle(raw); // throw std::out_of_range
}

constexpr Angle::Angle(type calibration, type angle)
: rawData {checkValidAngle(castToRaw(calibration, angle))}, // throw std::out_of_range
  rawCalibration {calibration}
{}

constexpr Angle::rawType Angle::castToRaw(type calibration, type angle) noexcept {
  return (calibration * angle) + MID;
}

constexpr Angle::rawType Angle::checkValidAngle(rawType raw) {
  return checkValidRange(raw, MIN, MAX);
}
}

#endif // LIBICS3_ICS3_ANGLE_H_
