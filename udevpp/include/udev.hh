#pragma once

#include <udevpp/util.hh>
#include <udevpp/monitor.hh>
#include <udevpp/entry.hh>

#include <libudev.h>

namespace udevpp {

class Udev: public util::RawPointerWrapper<udev, udev_unref> {
public:
    Udev();

    auto create_monitor() const -> Monitor;
    auto enumerate_devices() const -> EntryList;
    auto find_device(const std::string& path) const -> optional<Device>;
};

}
