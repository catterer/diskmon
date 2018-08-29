#pragma once
#include <libudev.h>
#include <memory>

namespace udevpp {

template<typename T, void(*FREE)(T*)>
auto free_with(T* p)
    -> std::shared_ptr<T>
{
    return std::shared_ptr<T>(p, FREE);
}

class Device {
public:
    Device(struct udev_device* uptr):
        dev_{free_with<udev_device_unref>(uptr)}
    { }

private:
    std::shared_ptr<struct udev_device> dev_;
};

}
