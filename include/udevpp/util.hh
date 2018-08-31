#pragma once
#include <memory>

#if __has_include(<optional>)

#   include <optional>
namespace udevpp { using std::optional; }
#elif __has_include(<experimental/optional>)
#   include <experimental/optional>
namespace udevpp { using std::experimental::optional; }
#else
#   error <experimental/optional> and <optional> not found
#endif

namespace udevpp {
namespace util {

template<typename T, T* (*FREE_CB)(T*)>
class RawPointerWrapper {
public:
    RawPointerWrapper(T* raw):
        raw_{std::shared_ptr<T>(raw, [] (auto* p) { FREE_CB(p); })}
    {
        if (!raw_)
            throw std::invalid_argument("tried to create RawPointerWrapper with NULL pointer");
    }

protected:
    std::shared_ptr<T> raw_;
};

}
}
