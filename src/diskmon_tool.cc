#include <udevpp/udevpp.hh>
#include <unistd.h>
#include <iostream>

int main(int argc, char** argv) try {
    struct udev *udev;
    struct udev_monitor *mon;
    int fd;

    /* create udev object */
    udev = udev_new();
    if (!udev)
        throw std::runtime_error("Failed to create udev");

    mon = udev_monitor_new_from_netlink(udev, "udev");
    udev_monitor_filter_add_match_subsystem_devtype(mon, "block", NULL);
    udev_monitor_enable_receiving(mon);
    fd = udev_monitor_get_fd(mon);

    while (1) {
        fd_set fds;
        struct timeval tv;
        int ret;

        FD_ZERO(&fds);
        FD_SET(fd, &fds);
        tv.tv_sec = 0;
        tv.tv_usec = 0;

        ret = select(fd+1, &fds, NULL, NULL, &tv);
        if (ret > 0 && FD_ISSET(fd, &fds)) {
            auto dev = udevpp::Device(udev_monitor_receive_device(mon));
            std::cout << "New device event:\n" << dev.fullinfo() << "---\n";
        }
        /* 500 milliseconds */
        usleep(500*1000);
    }
    /* free udev */
    udev_unref(udev);

    return EXIT_SUCCESS;
} catch (const std::exception& x) {
    std::cerr << x.what() << "\n";
    return EXIT_FAILURE;
}
