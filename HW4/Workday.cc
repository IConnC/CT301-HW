#include "Event.h"
#include "Workday.h"
#include <string.h>
#include <stdexcept>
#include <ctime>
#include <iomanip>


Workday::Workday(const std::string &name) {
    job_name = name;
    hourly_pay = 15.00;
}

Workday::Workday(const std::string &name, double pay) {
    job_name = name;
    hourly_pay = pay;
}

Workday::Workday(const std::string &name, const std::string &date) {
    job_name = name;
    hourly_pay = 15.00;
    
    int year, month, day;
    translate_date(date, year, month, day);
    Event::set(year, month, day);
}

Workday::Workday(const std::string &name, const std::string &date, double pay) {
    job_name = name;
    hourly_pay = pay;
    
    int year, month, day;
    translate_date(date, year, month, day);
    Event::set(year, month, day);
}

Workday::Workday(const std::string &name, int y, int m, int d) {
    job_name = name;
    hourly_pay = 15.00;
    
    Event::set(y, m, d);
}

const std::string& Workday::GetName() const {
    return job_name;
}

double Workday::GetPay() const {
    return hourly_pay;
}


bool Workday::operator<(const Event &rhs) const {
    return Event::operator<(rhs);
}

bool Workday::operator<(const std::string &rhs) const {
    return Event::operator<(rhs);
}

bool Workday::operator<(const Priority_Event &rhs) const {
    return Event::operator<(rhs);
}

bool Workday::operator<(const Workday &rhs) const {
    return Event::operator<(rhs);
}

std::ostream& operator<<(std::ostream &lhs, const Workday &rhs) {
	const auto save_fill = lhs.fill('0');
	return lhs << rhs.GetName() << ", Pay: $" << rhs.GetPay() << ", Date: "
			   << std::setw(4) << rhs.year() << '-'
			   << std::setw(2) << rhs.month() << '-'
			   << std::setw(2) << rhs.day() << std::setfill(save_fill);
}