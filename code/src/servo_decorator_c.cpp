#include <servo_decorator_c.hpp>

namespace r2d2::servo_interface {
    void servo_decorator_c::set_angle(const int16_t &new_angle) {
        component.set_angle(new_angle);
    }

    int16_t servo_decorator_c::get_angle() {
        return component.get_angle();
    }

    void servo_decorator_c::add_angle(const int16_t &adding_angle) {
        component.add_angle(adding_angle);
    }

    pwm_s servo_decorator_c::get_pwm() {
        return component.get_pwm();
    }

} // namespace r2d2::servo_interface