#pragma once
#include <array.hpp>
#include <atomic.hpp>
#include <future.hpp>
#include <types.hpp>

constexpr auto MAX_QUARK_ARG_COUNT = 1;

enum class Quark_Services : uint8_t
{
    COMMITFRAMEBUFFER,
    REBOOT,
    SHUTDOWN,
    RANDSEED
};

constexpr auto QUARK_SERVICE_COUNT = 4;

/**
 * @brief The base class that all quarks come from
 *
 * Default values are put here in order to ease the job on the quark_collection
 */
class Quark
{
  public:
    Atomic<bool> has_been_initialized = false;

    void (*init)() = nullptr;
    void (*fini)() = nullptr;

    /**
     * @brief These are the quark services
     * Every service returns false if it wasn't able to complete its job and another has to be found
     */
    bool (*commitframebuffer)(void *data) = nullptr;
    bool (*reboot)() = nullptr;
    bool (*shutdown)() = nullptr;
    bool (*randseed)() = nullptr;
};

class Quark_Collection : public Array<Quark *, 0xff>
{

  private:
    constexpr static Array<uint8_t, QUARK_SERVICE_COUNT> quark_arg_counts{1, 0, 0, 4};

  public:
    bool add_quark(Quark &quark);

    template <typename T, typename... Ts> bool add_quark(T &quark, Ts &...quarks)
    {
        return add_quark(quarks...) && add_quark(quark);
    }

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
