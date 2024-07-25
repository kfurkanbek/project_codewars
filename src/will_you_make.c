#include "will_you_make.h"

/**
 * @brief A function that tells you
if it is possible to get to the pump or not.
 *
 * @param distance_to_pump
 * @param mpg
 * @param fuel_left
 * @return true
 * @return false
 */
bool zero_fuel(double distance_to_pump, double mpg, double fuel_left)
{
    return (distance_to_pump / mpg) <= fuel_left ? true : false;
}
