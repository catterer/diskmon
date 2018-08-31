#pragma once

#include <libudev.h>
#include <string>
#include <map>

namespace udevpp {

struct Entry {
    std::string key;
    std::string value;
    friend std::ostream& operator<<(std::ostream&, const Entry&);
};

class EntryList: public std::multimap<std::string, Entry> {
public:
    EntryList(udev_list_entry*);
};

}
