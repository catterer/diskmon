#pragma once

#include <udevpp/util.hh>
#include <udevpp/monitor.hh>

#include <libudev.h>

namespace udevpp {

class Udev: public util::RawPointerWrapper<udev, udev_unref> {
public:
    Udev();

    auto create_monitor() const -> Monitor;
};

}
