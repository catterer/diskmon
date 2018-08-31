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

auto Udev::enumerate_devices() const
    -> EntryList
{
    auto enm = udev_enumerate_new(raw_.get());
    if (!enm)
        throw std::runtime_error("Cannot create enumerate context.\n");
    auto remover = std::shared_ptr<void>(nullptr, [enm] (void*) { udev_enumerate_unref(enm); });

    udev_enumerate_add_match_subsystem(enm, "block");
    udev_enumerate_scan_devices(enm);
    auto devices = udev_enumerate_get_list_entry(enm);
    if (!devices)
        throw std::runtime_error("Failed to get device list.\n");

    return EntryList{devices};
}

auto Udev::find_device(const std::string& path) const
    -> optional<Device>
{
    auto d = udev_device_new_from_syspath(raw_.get(), path.c_str());
    if (!d)
        return {};
    return Device(d);
}

}
