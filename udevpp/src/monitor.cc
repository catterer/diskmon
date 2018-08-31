#include <udevpp/monitor.hh>

namespace udevpp {

Monitor::Monitor(udev_monitor* m):
    util::RawPointerWrapper<udev_monitor, udev_monitor_unref>::RawPointerWrapper(m)
{
    udev_monitor_filter_add_match_subsystem_devtype(raw_.get(), "block", NULL);
    udev_monitor_enable_receiving(raw_.get());
}

int Monitor::fd() const {
    return udev_monitor_get_fd(raw_.get());
}

auto Monitor::receive_event() const
    -> Event
{
    auto dev = udev_monitor_receive_device(raw_.get());
    if (!dev)
        throw std::runtime_error("monitor failed to receive event");

    auto act = udev_device_get_action(dev);

    if (!act)
        throw std::runtime_error("monitor failed to receive event action");

    return Event{act, Device(dev)};
}

}
