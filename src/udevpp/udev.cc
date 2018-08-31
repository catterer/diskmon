#include <udevpp/udev.hh>

namespace udevpp {

Udev::Udev():
    util::RawPointerWrapper<udev, udev_unref>::RawPointerWrapper(udev_new())
{ }

auto Udev::create_monitor() const
    -> Monitor
{
    return Monitor(udev_monitor_new_from_netlink(raw_.get(), "udev"));
}

}
