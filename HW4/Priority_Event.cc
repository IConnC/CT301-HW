#include "Priority_Event.h"
#include <string.h>
#include <stdexcept>
#include <ctime>
#include <iomanip>


Priority_Event::Priority_Event() : event_name("New Event"), priority(10) {}

Priority_Event::Priority_Event(const std::string &name) {
    event_name = name;
    priority = 10;
}

Priority_Event::Priority_Event(const std::string &name, short _priority) {
    event_name = name;

    if (_priority < 0) throw std::runtime_error("Priority_Event - Error cannot set a priority less than 0. Given Priority: " + std::to_string(_priority) + "\n");
    priority = _priority;
}

Priority_Event::Priority_Event(const std::string &name, const std::string &date) {
    event_name = name;
    priority = 10;

    int year, month, day;
    translate_date(date, year, month, day);
    Event::set(year, month, day);
}

Priority_Event::Priority_Event(const std::string &name, const std::string &date, short _priority) {
    event_name = name;

    if (_priority < 0) throw std::runtime_error("Priority_Event - Error cannot set a priority less than 0. Given Priority: " + std::to_string(_priority) + "\n");

    priority = _priority;

    int year, month, day;
    translate_date(date, year, month, day);
    Event::set(year, month, day);
}

Priority_Event::Priority_Event(const std::string &name, int y, int m, int d) {
    event_name = name;
    priority = 10;

    Event::set(y, m, d);
}

Priority_Event::Priority_Event(const std::string &name, int y, int m, int d, short _priority) {
    event_name = name;

    if (_priority < 0) throw std::runtime_error("Priority_Event - Error cannot set a priority less than 0. Given Priority: " + std::to_string(_priority) + "\n");

    priority = _priority;

    Event::set(y, m, d);
}

const std::string& Priority_Event::GetName() const {
    return event_name;
}

ushort Priority_Event::GetPriority() const {
    return priority;
}


    // P1 = New Event, Priority: 10, Date: 2023-10-20
    // P2 = Simple, Priority: 10, Date: 2023-10-20
    // P3 = Low Prio, Priority: 200, Date: 2023-10-20
    // P4 = Simple, Priority: 7, Date: 2025-12-25
    // (p1 < p2) = false
    // (p2 < p3) = false
    // (p3 < p1) = true
bool Priority_Event::operator<(const Event &rhs) const {
    // rhs priority = 10

    // If date is earlier return true
    // Else return true if events are both the same date and priority of current event is less than priority of rhs event
    // Else return false
    if (Event::operator<(rhs)) {
        return true;
    } else {
        return (year() == rhs.year() && month() == rhs.month() && day() == rhs.day() && priority > 10);
    }
}

bool Priority_Event::operator<(const std::string &rhs) const {
    // rhs priority = 10
    Event temp(rhs);
    // If date is earlier return true
    // Else return true if events are both the same date and priority of current event is less than priority of rhs event
    // Else return false
    if (Event::operator<(temp)) {
        return true;
    } else {
        return (year() == temp.year() && month() == temp.month() && day() == temp.day() && priority > 10);
    }
}

bool Priority_Event::operator<(const Priority_Event &rhs) const {
    // If date is earlier return true
    // Else return true if events are both the same date and priority of current event is less than priority of rhs event
    // Else return false
    if (Event::operator<(rhs)) {
        return true;
    } else {
        return (year() == rhs.year() && month() == rhs.month() && day() == rhs.day() && priority > rhs.GetPriority());
    }
}


std::ostream& operator<<(std::ostream &out, const Priority_Event &rhs) {
    const auto save_fill = out.fill('0');
	return out << rhs.GetName() << ", Priority: "
            << rhs.GetPriority() << ", Date: "
            << std::setw(4) << rhs.year() << '-'
            << std::setw(2) << rhs.month() << '-'
            << std::setw(2) << rhs.day() << std::setfill(save_fill);
}