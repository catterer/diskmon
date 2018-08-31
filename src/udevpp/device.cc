#include <udevpp/device.hh>

#include <sstream>

namespace udevpp {

Device::Device(udev_device* uptr):
    dev_(std::shared_ptr<udev_device>(uptr, udev_device_unref))
{
    if (!dev_)
        throw std::invalid_argument("trying to create empty device");
}

auto Device::parent() const
    -> optional<Device>
{
    auto p = udev_device_get_parent(dev_.get());
    if (!p)
        return {};
    return Device{p};
}

std::ostream& operator<<(std::ostream& out, optional<std::string> opts) {
    if (!opts)
        out << "(none)";
    else
        out << *opts;
    return out;
}

auto Device::fullinfo() const
    -> std::string
{
    std::stringstream out;
    out <<  "devpath   " << devpath   () << "\n";
    out <<  "subsystem " << subsystem () << "\n";
    out <<  "devtype   " << devtype   () << "\n";
    out <<  "syspath   " << syspath   () << "\n";
    out <<  "sysname   " << sysname   () << "\n";
    out <<  "sysnum    " << sysnum    () << "\n";
    out <<  "devnode   " << devnode   () << "\n";
    out <<  "driver    " << driver    () << "\n";

    return out.str();
}

}
