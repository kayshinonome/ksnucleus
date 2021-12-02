#pragma once
#include <array.hpp>
#include <atomic.hpp>
#include <types.hpp>

constexpr auto MAX_QUARK_ARG_COUNT = 1;
constexpr auto QUARK_SERVICE_COUNT = 5;

enum class Quark_Services : uint8_t
{
    COMMIT_FRAMEBUFFER,
    REBOOT,
    SHUTDOWN
};

class Quark
{
  public:
    Atomic<bool> has_been_initialized = false;

    bool (*is_viable)(Quark_Services quark_service) = nullptr;
    void (*init)() = nullptr;
    void (*fini)() = nullptr;

    /**
     * @brief These are the quark services
     *
     */
    void (*commit_framebuffer)(void *data) = nullptr;
    void (*reboot)() = nullptr;
    void (*shutdown)() = nullptr;
    void (*randseed)() = nullptr;
};

class Quark_Collection : public Array<Quark *, 0xff>
{

  private:
    constexpr static Array<uint8_t, QUARK_SERVICE_COUNT> quark_arg_counts{1, 0, 0};

  public:
    bool add_quark(Quark &quark);

    /**
     * @brief This is a bit like mk_syscall, except to call drivers
     *
     * @param quark_service
     * @param args
     * @return true
     * @return false
     */
    bool call_quark_service(Quark_Services quark_service, Array<void *, MAX_QUARK_ARG_COUNT> args);
};

inline Quark_Collection quark_collection{};