#ifndef PRIORITY_EVENT_H_INCLUDED
#define PRIORITY_EVENT_H_INCLUDED

#include "Event.h"
#include <ostream>
#include <iostream>
#include <string>


class Priority_Event : public Event {
  protected:
    std::string event_name;
    ushort priority;

  public:
    Priority_Event();
    Priority_Event(const std::string &name);
    Priority_Event(const std::string &name, short priority);
    Priority_Event(const std::string &name, const std::string &date);
    Priority_Event(const std::string &name, const std::string &date, short priority);
    Priority_Event(const std::string &name, int y, int m, int d);
    Priority_Event(const std::string &name, int y, int m, int d, short priority);

    Priority_Event(const Priority_Event &rhs) = default;
    Priority_Event &operator=(const Priority_Event &rhs) = default;
    Priority_Event &operator=(Priority_Event &&rhs) = default;
    Priority_Event(Priority_Event &&rhs) = default;
    virtual ~Priority_Event() = default;
    
    const std::string& GetName() const;
    ushort GetPriority() const;
    
    virtual bool operator<(const Event &rhs) const;
    virtual bool operator<(const std::string &rhs) const;
    virtual bool operator<(const Priority_Event &rhs) const;
};

std::ostream& operator<<(std::ostream &out, const Priority_Event &rhs);

#endif /* PRIORITY_EVENT_H_INCLUDED */
