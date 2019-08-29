#include <servo_c.hpp>

namespace r2d2::servo_interface {
    int16_t servo_c::get_angle() {
        return angle;
    }

    pwm_s servo_c::get_pwm() {
        return pwm;
    }
} // namespace r2d2::servo_interface
