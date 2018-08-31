#include <udevpp/entry.hh>
#include <iostream>

namespace udevpp {

std::ostream& operator<<(std::ostream& out, const Entry& e) {
    out << e.key;
    if (e.value.size()) out << ": " << e.value;
    return out;
}

EntryList::EntryList(udev_list_entry* l) {
    for (; l; l = udev_list_entry_get_next(l)) {
        auto k = udev_list_entry_get_name(l);
        auto v = udev_list_entry_get_value(l);
        Entry e{std::string(k ?: ""), std::string(v ?: "")};
        emplace(e.key, e);
    }
}

}
