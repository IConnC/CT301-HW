#ifndef HOLIDAY_H_INCLUDED
#define HOLIDAY_H_INCLUDED


#include "Event.h"
#include "Priority_Event.h"
#include <iostream>
#include <string>

class Holiday : public Priority_Event {
    bool is_gov = false;
  public:
    Holiday(const std::string &name);
    Holiday(const std::string &name, bool is_gov);
    Holiday(const std::string &name, const std::string &date);
    Holiday(const std::string &name, const std::string &date, bool is_gov);
    Holiday(const std::string &name, int y, int m, int d);
    Holiday(const std::string &name, int y, int m, int d, bool is_gov);

    Holiday() = delete;
    Holiday(const Holiday &rhs) = default;
    Holiday &operator=(const Holiday &rhs) = default;
    Holiday &operator=(Holiday &&rhs) = default;
    Holiday(Holiday &&rhs) = default;
    virtual ~Holiday() = default;

    /*IsGov*/
    //Input: None
    //Output: Boolean on whether it is a government holiday or not
    bool IsGov() const;

    /*operator<*/
    //Input: Event object
    //Output: boolean if the current Holiday object is higher priority than the event passed
    bool operator<(const Event &rhs) const;

    /*operator<*/
    //Input: string containing the date
    //Output: Boolean on whether it is a government holiday or not
    bool operator<(const std::string &rhs) const;
    
    /*operator<*/
    //Input: Priority_Event object on how
    //Output: Boolean on whether it is a government holiday or not
    bool operator<(const Priority_Event &rhs) const;
    
    /*operator<*/
    //Input: None
    //Output: Boolean on whether it is a government holiday or not
    bool operator<(const Holiday &rhs) const;
};

std::ostream& operator<<(std::ostream &out, const Holiday &rhs);

#endif /* HOLIDAY_H_INCLUDED */
