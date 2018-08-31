#pragma once

#include <udevpp/util.hh>

#include <libudev.h>
#include <memory>
#include <string>

namespace udevpp {

class Device {
public:
    Device(udev_device* uptr);

    auto parent() const -> optional<Device>;

    auto devpath()    const -> optional<std::string> { return get_str<udev_device_get_devpath>(); }
    auto subsystem()  const -> optional<std::string> { return get_str<udev_device_get_subsystem>(); }
    auto devtype()    const -> optional<std::string> { return get_str<udev_device_get_devtype>(); }
    auto syspath()    const -> optional<std::string> { return get_str<udev_device_get_syspath>(); }
    auto sysname()    const -> optional<std::string> { return get_str<udev_device_get_sysname>(); }
    auto sysnum()     const -> optional<std::string> { return get_str<udev_device_get_sysnum>(); }
    auto devnode()    const -> optional<std::string> { return get_str<udev_device_get_devnode>(); }
    auto driver()     const -> optional<std::string> { return get_str<udev_device_get_driver>(); }

    auto fullinfo() const -> std::string;

private:
    template<const char* (*CB)(udev_device*)>
    auto get_str() const -> optional<std::string> {
        auto p = CB(raw_.get());
        if (!p)
            return {};
        return {std::string(p)};
    }

    std::shared_ptr<udev_device> raw_;
};

}

/*
struct udev *       udev_device_get_udev                (struct udev_device *udev_device);
struct udev_device * udev_device_new_from_syspath       (struct udev *udev, const char *syspath);
struct udev_device * udev_device_new_from_devnum        (struct udev *udev, char type, dev_t devnum);
struct udev_device * udev_device_new_from_subsystem_sysname (struct udev *udev, const char *subsystem, const char *sysname);
struct udev_device * udev_device_new_from_environment   (struct udev *udev);
struct udev_device * udev_device_get_parent_with_subsystem_devtype (struct udev_device *udev_device, const char *subsystem, const char *devtype);
int                 udev_device_get_is_initialized      (struct udev_device *udev_device);
struct udev_list_entry * udev_device_get_devlinks_list_entry (struct udev_device *udev_device);
struct udev_list_entry * udev_device_get_properties_list_entry (struct udev_device *udev_device);
struct udev_list_entry * udev_device_get_tags_list_entry (struct udev_device *udev_device);
dev_t               udev_device_get_devnum              (struct udev_device *udev_device);
const char *        udev_device_get_action              (struct udev_device *udev_device);
struct udev_list_entry * udev_device_get_sysattr_list_entry (struct udev_device *udev_device);
unsigned long long int udev_device_get_seqnum           (struct udev_device *udev_device);
unsigned long long int udev_device_get_usec_since_initialized (struct udev_device *udev_device);
int                 udev_device_has_tag                 (struct udev_device *udev_device, const char *tag);
const char *        udev_device_get_property_value      (struct udev_device *udev_device, const char *key);
const char *        udev_device_get_sysattr_value       (struct udev_device *udev_device, const char *sysattr);
*/
