#include <sg90_c.hpp>

namespace r2d2::servo_interface {
    sg90_c::sg90_c() {
        pwm.frequency = pwm_frequency_hz;
        angle = min_rotation;
    }

    void sg90_c::set_angle(const int16_t &new_angle) {
        if (new_angle >= min_rotation && new_angle <= max_rotation) {
            angle = new_angle;

            pwm.time_on_us =
                (angle - min_rotation) * rotation_time_ratio + min_time_on_us;

            /*
            calculate the frequency in us
            by dividing 1 through the frequency results in seconds
            multiply by 1 000 000 to get to micro seconds
            multiply by number of steps 255
            */
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
