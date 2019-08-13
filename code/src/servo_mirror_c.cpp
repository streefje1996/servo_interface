#include <servo_mirror_c.hpp>

namespace r2d2::servo_interface {

    void servo_mirror_c::set_angle(const int16_t &new_angle) {
        this->servo_decorator_c::set_angle(new_angle * -1);
    }

    void servo_mirror_c::add_angle(const int16_t &adding_angle) {
        this->servo_decorator_c::add_angle(adding_angle * -1);
    }
} // namespace r2d2::servo_interface