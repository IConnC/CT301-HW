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

    bool IsGov() const;
    
    bool operator<(const Event &rhs) const;
    bool operator<(const std::string &rhs) const;
    bool operator<(const Priority_Event &rhs) const;
    bool operator<(const Holiday &rhs) const;
};

std::ostream& operator<<(std::ostream &out, const Holiday &rhs);

#endif /* HOLIDAY_H_INCLUDED */
