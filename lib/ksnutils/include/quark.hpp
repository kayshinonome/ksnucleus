#pragma once
#include <array.hpp>
#include <atomic.hpp>
#include <future.hpp>
#include <types.hpp>

constexpr auto MAX_QUARK_ARG_COUNT = 1;

class GenericQuark
{
  public:
    Atomic<bool> has_been_initialized = false;
    void (*init)() = nullptr;
    void (*fini)() = nullptr;
};

template <typename QUARK_TYPE, typename ID_TYPE, uint16_t QUARK_COUNT>
class Quark_Collection : protected Array<QUARK_TYPE *, QUARK_COUNT>
{
  protected:
    /**
     * @brief A function to verify a arg array
     *
     * @param args
     * @return true
     * @return false
     */
    bool is_arg_array_good(Array<void *, MAX_QUARK_ARG_COUNT> args, uint16_t arg_count) const
    {
        auto answer = args.search([](auto search_term) { return search_term == nullptr; });
        if (!answer.valid)
        {
            return true;
        }
        return answer.data < MAX_QUARK_ARG_COUNT;
    }

    void init_quark_if_needed(GenericQuark *quark)
    {
        if ((quark->init != nullptr) && !quark->has_been_initialized)
        {
            quark->init();
        }
    }

  public:
    bool add_quark(QUARK_TYPE &quark)
    {
        for (size_t x = 0, len = this->size(); x < len; x++)
        {
            if ((*this)[x] == nullptr)
            {
                (*this)[x] = &quark;
                return true;
            }
        }
        return false;
    }

    template <typename T, typename... Ts> bool add_quark(T &quark, Ts &...quarks)
    {
        return add_quark(quarks...) && add_quark(quark);
    }

    virtual bool call_quark_service(ID_TYPE quark_service, Array<void *, MAX_QUARK_ARG_COUNT> args) = 0;
};
