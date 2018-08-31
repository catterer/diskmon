#include <udevpp/udevpp.hh>
#include <unistd.h>
#include <iostream>

int main(int argc, char** argv) try {
    udevpp::Udev udev;
    auto mon = udev.create_monitor();

    while (1) {
        fd_set fds;
        struct timeval tv;
        int ret;

        FD_ZERO(&fds);
        FD_SET(mon.fd(), &fds);
        tv.tv_sec = 0;
        tv.tv_usec = 0;

        ret = select(mon.fd()+1, &fds, NULL, NULL, &tv);
        if (ret > 0 && FD_ISSET(mon.fd(), &fds)) {
            auto ev = mon.receive_event();
            std::cout << "New device event '" << ev.action << "':\n" << ev.device.fullinfo() << "---\n";
        }
        /* 500 milliseconds */
        usleep(500*1000);
    }
    return EXIT_SUCCESS;
} catch (const std::exception& x) {
    std::cerr << x.what() << "\n";
    return EXIT_FAILURE;
}
