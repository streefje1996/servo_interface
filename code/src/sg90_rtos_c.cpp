#include <sg90_rtos_c.hpp>

namespace r2d2::servo_interface {
    void sg90_rtos_c::set_angle(const int16_t &new_angle) {
        angle_mutex.wait();
        angle_pool.write(new_angle);
        angle_mutex.signal();
    }

    void sg90_rtos_c::add_angle(const int16_t &adding_angle) {
        angle_mutex.wait();
        angle_pool.write(adding_angle + angle);
        angle_mutex.signal();
    }

    void sg90_rtos_c::main() {

        for (;;) {
            switch (state) {
            case states::low: {
                wait(pwm_period);
                angle_mutex.wait();
                this->sg90_c::set_angle(angle_pool.read());
                angle_mutex.signal();
                on_timer.set(pwm.time_on_us);
                state = states::high;
                break;
            }

            case states::high: {
                data_pin.write(1);
                wait(on_timer);
                data_pin.write(0);
                state = states::low;
            }

            default:
                break;
            }
        }
    }
} // namespace r2d2::servo_interface