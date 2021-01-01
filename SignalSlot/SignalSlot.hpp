#ifndef _SIGNAL_SLOT_HPP_
#define _SIGNAL_SLOT_HPP_

#if defined SIGNAL_SLOT_MULTI_THREADS_SINGLE_MUTEX
#define SIGSLOT_DEFAULT_MT_POLICY multi_threaded_global
#elif defined SIGNAL_SLOT_MULTI_THREADS_MULTI_MUTEXS
#define SIGSLOT_DEFAULT_MT_POLICY multi_threaded_local
#else
#define SIGSLOT_DEFAULT_MT_POLICY single_threaded
#endif
#include "sigslot-1-0-0/sigslot/sigslot.h"
// --------------- !!!! NB !!!! ---------------
// Thread safety is not guaranteed between slots,
// but you can use:
//   "SIGNAL_SLOT_LOCK;/SIGNAL_SLOT_UNLOCK;" or
//   "SIGNAL_SLOT_LOCK_BLOCK;"(RAII)
// in slot function to ensure multi-thread safety.
#define SIGNAL_SLOT_LOCK       lock()
#define SIGNAL_SLOT_UNLOCK     unlock()
#define SIGNAL_SLOT_LOCK_BLOCK lock_block<SIGSLOT_DEFAULT_MT_POLICY> lock(this)

class Object : public sigslot::has_slots<> {
public:
    Object() = default;
    ~Object() override = default;
    // COPY & MOVE construction are not allowed.
    Object(Object const&) = delete;
    Object(Object &&) = delete;
    Object& operator=(Object const&) = delete;
    Object& operator=(Object &&) = delete;
};

template<const unsigned int argsCount, class ...Args>
class SignalTemplate {
    static_assert(sizeof...(Args) <= 8,
        "SignalTemplate: only <= 8 args are supported.");
};

#define _SIGNAL_TEMPLATE_FUNCTION_IMPLEMENT_                        \
inline void Emit(const Args& ...args)                               \
{                                                                   \
    signal.emit(args...);                                           \
}                                                                   \
template<typename DestObj>                                          \
inline void Connect(DestObj* object, void(DestObj::*slot)(Args...)) \
{                                                                   \
    signal.connect(object, slot);                                   \
}                                                                   \
template<typename DestObj>                                          \
inline void Disconnect(DestObj* object)                             \
{                                                                   \
    signal.disconnect(object);                                      \
}
#define _SIGNAL_TEMPLATE_VARIABLE_IMPLEMENT_(argsCount)             \
sigslot::signal##argsCount<Args...> signal;

#define _SIGNAL_TEMPLATE_IMPLEMENT_(n)      \
template<class ...Args>                     \
class SignalTemplate<n, Args...> {          \
public:                                     \
    _SIGNAL_TEMPLATE_FUNCTION_IMPLEMENT_    \
private:                                    \
    _SIGNAL_TEMPLATE_VARIABLE_IMPLEMENT_(n) \
};

_SIGNAL_TEMPLATE_IMPLEMENT_(0)
_SIGNAL_TEMPLATE_IMPLEMENT_(1)
_SIGNAL_TEMPLATE_IMPLEMENT_(2)
_SIGNAL_TEMPLATE_IMPLEMENT_(3)
_SIGNAL_TEMPLATE_IMPLEMENT_(4)
_SIGNAL_TEMPLATE_IMPLEMENT_(5)
_SIGNAL_TEMPLATE_IMPLEMENT_(6)
_SIGNAL_TEMPLATE_IMPLEMENT_(7)
_SIGNAL_TEMPLATE_IMPLEMENT_(8)

template<class ...Args>
class Signal {
public:
    Signal() = default;
    virtual ~Signal() = default;
    // COPY & MOVE construction are not allowed.
    Signal(Signal const&) = delete;
    Signal(Signal &&) = delete;
    Signal& operator=(Signal const&) = delete;
    Signal& operator=(Signal &&) = delete;

private:
    template<class ...Args> friend void Emit(
        Signal<Args...>& signal, const Args& ...args);
    template<typename DestObj, class ...Args> friend void Connect(
        Signal<Args...>& signal, DestObj* object, void(DestObj::*slot)(Args...));
    template<typename DestObj, class ...Args> friend void Disconnect(
        Signal<Args...>& signal, DestObj* object);

    inline void Emit(const Args& ...args)
    {
        st.Emit(args...);
    }

    template<typename DestObj>
    inline void Connect(DestObj* object, void(DestObj::*slot)(Args...))
    {
        static_assert(std::is_base_of<Object, DestObj>(),
            "Template is not base of Object");
        st.Connect(object, slot);
    }

    template<typename DestObj>
    inline void Disconnect(DestObj* object)
    {
        static_assert(std::is_base_of<Object, DestObj>(),
            "Template is not base of Object");
        st.Disconnect(object);
    }

    SignalTemplate<sizeof...(Args), Args...> st;
};

template<class ...Args> void Emit(
    Signal<Args...>& signal, const Args& ...args)
{
    signal.Emit(args...);
}

template<typename DestObj, class ...Args> void Connect(
    Signal<Args...>& signal, DestObj* object, void(DestObj::*slot)(Args...))
{
    signal.Connect(object, slot);
}

template<typename DestObj, class ...Args> void Disconnect(
    Signal<Args...>& signal, DestObj* object)
{
    signal.Disconnect(object);
}

#endif
