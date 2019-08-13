#include <servo_led_c.hpp>

namespace r2d2::servo_interface {
    void servo_led_c::set_angle(const int16_t &new_angle) {
        led.write(1);
        this->servo_decorator_c::set_angle(new_angle);
        led.write(0);
    }
} // namespace r2d2::servo_interface