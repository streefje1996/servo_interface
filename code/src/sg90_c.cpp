#include "sg90_c.hpp"

namespace r2d2::servo_interface {
    void sg90_c::set_angle(const int16_t &new_angle) {
        if (new_angle >= min_rotation && new_angle <= max_rotation) {
            angle = new_angle;

            pwm.time_on_us =
                (angle - min_rotation) * rotation_time_ratio + min_time_on_us;

            pwm.duty_cycle =
                pwm.time_on_us / (1.f / pwm.frequency * 1'000'000) * 255;
        }
    }

    void sg90_c::add_angle(const int16_t &adding_angle) {
        if (((adding_angle + angle) <= max_rotation) &&
            ((adding_angle + angle) >= min_rotation)) {
            set_angle(adding_angle + angle);
        }
    }
} // namespace r2d2::servo_interface
