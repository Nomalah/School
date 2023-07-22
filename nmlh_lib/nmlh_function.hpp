#pragma once

#include <functional>

namespace nmlh{
    template <class>
    class function;

    template <class R, class... Args>
    class function <R(Args...)> final {

    };
}