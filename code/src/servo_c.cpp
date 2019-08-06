#include "servo_c.hpp"

int16_t r2d2::servo_interface::servo_c::get_angle() {
    return angle;
}

r2d2::servo_interface::pwm_s r2d2::servo_interface::servo_c::get_pwm() {
    return pwm;
}
