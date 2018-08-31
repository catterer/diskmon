#pragma once
#include <udevpp/util.hh>
#include <udevpp/device.hh>

#include <libudev.h>

namespace udevpp {

struct Event {
    std::string action;
    Device device;
};

class Monitor: util::RawPointerWrapper<udev_monitor, udev_monitor_unref> {
public:
    Monitor(udev_monitor*);
    int fd() const;
    auto receive_event() const -> Event;
};

}
