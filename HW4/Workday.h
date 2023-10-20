#ifndef WORKDAY_H_INCLUDED
#define WORKDAY_H_INCLUDED

#include "Holiday.h"
#include "Priority_Event.h"
#include "Event.h"
#include <iostream>
#include <string>

class Workday : public Event {
    std::string job_name;
    double hourly_pay = 15;
  public:
    Workday(const std::string &name);
    Workday(const std::string &name, double pay);
    Workday(const std::string &name, const std::string &date);
    Workday(const std::string &name, const std::string &date, double pay);
    Workday(const std::string &name, int y, int m, int d);
    
    Workday() = delete; // Remove default constructor
    Workday(const Workday &rhs) = default;
    Workday &operator=(const Workday &rhs) = default;
    Workday &operator=(Workday &&rhs) = default;
    Workday(Workday &&rhs) = default;
    virtual ~Workday() = default;

    const std::string& GetName() const;
    double GetPay() const;
    
    bool operator<(const Event &rhs) const;
    bool operator<(const std::string &rhs) const;
    bool operator<(const Priority_Event &rhs) const;
    bool operator<(const Workday &rhs) const;
};

std::ostream& operator<<(std::ostream &out, const Workday &rhs);

#endif /* WORKDAY_H_INCLUDED */
