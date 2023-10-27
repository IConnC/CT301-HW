#include "Holiday.h"
#include <string.h>
#include <stdexcept>
#include <ctime>
#include <iomanip>

/*Holiday*/
// Constructor which sets the event_name to the name passed, also sets default priority to 15 and is_gov to false
Holiday::Holiday(const std::string &name) {
    event_name = name;
    priority = 15;
}

/*Holiday*/
// Constructor sets event_name and is_gov to given variables and sets the priority to 15 if it is not a government holiday
Holiday::Holiday(const std::string &name, bool _is_gov) {
    event_name = name;
    is_gov = _is_gov;
    priority = _is_gov ? 0 : 15;

}

/*Holiday*/
// Constructor sets event_name and the date while setting default priority to 15
Holiday::Holiday(const std::string &name, const std::string &date) {
    event_name = name;
    priority = 15;

    int year, month, day;
    translate_date(date, year, month, day);
    Event::set(year, month, day);
}

/*Holiday*/
// Constructor sets event_name, the date, and is_gov to provided inputs, also sets priority to 0 if government holiday and 15 if not
Holiday::Holiday(const std::string &name, const std::string &date, bool _is_gov) {
    event_name = name;
    is_gov = _is_gov;
    priority = _is_gov ? 0 : 15;

    int year, month, day;
    translate_date(date, year, month, day);
    Event::set(year, month, day);
}

/*Holiday*/
// Constructor sets event_name and date with a default priority of 15
Holiday::Holiday(const std::string &name, int y, int m, int d) {
    event_name = name;
    priority = 15;

    Event::set(y, m, d);
}

/*Holiday*/
// Constructor sets event_name, the date, and is_gov and sets priority to 0 if government holiday else 15
Holiday::Holiday(const std::string &name, int y, int m, int d, bool _is_gov) {
    event_name = name;
    is_gov = _is_gov;
    priority = _is_gov ? 0 : 15;

    Event::set(y, m, d);
}

/*IsGov*/
// Returns true if the holiday is a government holiday, else false
bool Holiday::IsGov() const {
    return is_gov;
}

/*operator<*/
// Outputs true if the holiday is equal in date to the compared event and is_gov is true, else return the default Event operator< method call to compare
bool Holiday::operator<(const Event &rhs) const {
    if (year() == rhs.year() && month() == rhs.month() && day() == rhs.day()) {
        return is_gov;
    }
    return Event::operator<(rhs);
}

/*operator<*/
// Converts the date string provided to an event
// then calls the operator< method for this current object with the parameters of Event (Polymorphic)
bool Holiday::operator<(const std::string &rhs) const {
    Event temp(rhs);
    return this->operator<(temp);
}

/*operator<*/
// 
bool Holiday::operator<(const Priority_Event &rhs) const {
    return false;
}

/*operator<*/
// 
bool Holiday::operator<(const Holiday &rhs) const {
    return false;
}

/*operator<<*/
// Concatenates the data required to be the string output desired, outputs to ostream operator with the concatenated string
std::ostream& operator<<(std::ostream &out, const Holiday &rhs) {
    const auto save_fill = out.fill('0');
	return out << rhs.GetName() << ", " 
        << (rhs.IsGov() ? "Is a ": "Is Not a ") // Ternary operator to output "Is a" or "Is Not a" depending on if the holiday is a government holiday
        << "Government Holiday, Date: "
        << std::setw(4) << rhs.year() << '-'
        << std::setw(2) << rhs.month() << '-'
        << std::setw(2) << rhs.day() << std::setfill(save_fill);
}