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

/*GetName*/
// returns the job name
const std::string& Workday::GetName() const {
    return job_name;
}

/*GetPay*/
// Returns the hourly pay for the job
double Workday::GetPay() const {
    return hourly_pay;
}

/*operator<*/
// Default Event operator< function called for comparison, result is returned
bool Workday::operator<(const Event &rhs) const {
    return Event::operator<(rhs);
}

/*operator<*/
// Default Event operator< function called for comparison, result is returned
bool Workday::operator<(const std::string &rhs) const {
    return Event::operator<(rhs);
}

/*operator<*/
// Default Event operator< function called for comparison, result is returned
bool Workday::operator<(const Priority_Event &rhs) const {
    return Event::operator<(rhs);
}

/*operator<*/
// Default Event operator< function called for comparison, result is returned
bool Workday::operator<(const Workday &rhs) const {
    return Event::operator<(rhs);
}

/*operator<<*/
// Concatenates the data required to be the string output desired, outputs to ostream operator with the concatenated string
std::ostream& operator<<(std::ostream &lhs, const Workday &rhs) {
	const auto save_fill = lhs.fill('0');
	return lhs << rhs.GetName() << ", Pay: $" << rhs.GetPay() << ", Date: "
			   << std::setw(4) << rhs.year() << '-'
			   << std::setw(2) << rhs.month() << '-'
			   << std::setw(2) << rhs.day() << std::setfill(save_fill);
}