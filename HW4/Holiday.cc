#include "Holiday.h"
#include <string.h>
#include <stdexcept>
#include <ctime>
#include <iomanip>

Holiday::Holiday(const std::string &name) {
    event_name = name;
    priority = 15;
}

Holiday::Holiday(const std::string &name, bool _is_gov) {
    event_name = name;
    is_gov = _is_gov;
    priority = _is_gov ? 0 : 15;

}

Holiday::Holiday(const std::string &name, const std::string &date) {
    event_name = name;
    priority = 15;

    int year, month, day;
    translate_date(date, year, month, day);
    Event::set(year, month, day);
}

Holiday::Holiday(const std::string &name, const std::string &date, bool _is_gov) {
    event_name = name;
    is_gov = _is_gov;
    priority = _is_gov ? 0 : 15;

    int year, month, day;
    translate_date(date, year, month, day);
    Event::set(year, month, day);
}

Holiday::Holiday(const std::string &name, int y, int m, int d) {
    event_name = name;
    priority = 15;

    Event::set(y, m, d);
}

Holiday::Holiday(const std::string &name, int y, int m, int d, bool _is_gov) {
    event_name = name;
    is_gov = _is_gov;
    priority = _is_gov ? 0 : 15;

    Event::set(y, m, d);
}

bool Holiday::IsGov() const {
    return is_gov;
}

bool Holiday::operator<(const Event &rhs) const {
    return false;
}

bool Holiday::operator<(const std::string &rhs) const {
    return false;
}

bool Holiday::operator<(const Priority_Event &rhs) const {
    return false;
}

bool Holiday::operator<(const Holiday &rhs) const {
    return false;
}

std::ostream& operator<<(std::ostream &out, const Holiday &rhs) {
    const auto save_fill = out.fill('0');
	return out << rhs.GetName() << ", " 
        << (rhs.IsGov() ? "Is a ": "Is Not a ") // Ternary operator to output "Is a" or "Is Not a" depending on if the holiday is a government holiday
        << "Government Holiday, Date: "
        << std::setw(4) << rhs.year() << '-'
        << std::setw(2) << rhs.month() << '-'
        << std::setw(2) << rhs.day() << std::setfill(save_fill);
}