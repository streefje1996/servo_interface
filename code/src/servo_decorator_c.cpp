#include <servo_decorator_c.hpp>

namespace r2d2::servo_interface {
    void servo_decorator_c::set_angle(const int16_t &new_angle) {
        component.set_angle(new_angle);
    }

    void servo_decorator_c::add_angle(const int16_t &adding_angle) {
        component.add_angle(adding_angle);
    }

} // namespace r2d2::servo_interface