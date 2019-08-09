#include <pca9685_c.hpp>

namespace r2d2::servo_interface {

    void pca9685_c::set_angle(const uint8_t &id, const int16_t &new_angle) {
        if (id < servo_index) {
            servos[id]->set_angle(new_angle);

            double frequency_in_us =
                (1.f / servos[id]->get_pwm().frequency * 1'000'000);

            double ratio = counts / frequency_in_us;

            uint16_t counts_on =
                (servos[id]->get_pwm().time_on_us - frequency_in_us) * ratio +
                counts - 1;

            led_cmd[0] = id * 4 + reg_led0_off_l;

            led_cmd[1] = (counts_on & 0xFF);
            led_cmd[2] = (counts_on >> 8) & 0xF;

            i2c_bus.write(slave_address, led_cmd, 3);
        }
    }

    int16_t pca9685_c::get_angle(const uint8_t &id) {
        return servos[id]->get_angle();
    }

    void pca9685_c::add_angle(const uint8_t &id, const int16_t &added_angle) {
        servos[id]->add_angle(added_angle);
        set_angle(id, servos[id]->get_angle());
    }

} // namespace r2d2::servo_interface