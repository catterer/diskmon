#include <udevpp/device.hh>

#include <sstream>

namespace udevpp {

Device::Device(udev_device* d):
     util::RawPointerWrapper<udev_device, udev_device_unref>::RawPointerWrapper(d)
{ }

auto Device::parent() const
    -> optional<Device>
{
    auto p = udev_device_get_parent(raw_.get());
    if (!p)
        return {};
    return Device(p);
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
