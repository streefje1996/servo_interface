#include <servo_logger_c.hpp>

namespace r2d2::servo_interface {

    void servo_logger_c::set_angle(const int16_t &new_angle) {
        this->servo_decorator_c::set_angle(new_angle);
        hwlib::cout << "the servo is at an angle of "
                    << this->servo_decorator_c::get_angle() << "\n";
    }

    void servo_logger_c::add_angle(const int16_t &adding_angle) {
        this->servo_decorator_c::add_angle(adding_angle);
        hwlib::cout << "servo is at an angle of "
                    << this->servo_decorator_c::get_angle() << "\n";
    }
} // namespace r2d2::servo_interface