#include <core/init.hpp>
#include <core/quark.hpp>
#include <utils.hpp>

extern Quark pc_vesa;

bool ksinit::platform()
{
    quark_collection.add_quark(pc_vesa);
    return true;
}