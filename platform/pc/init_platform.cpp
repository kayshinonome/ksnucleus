#include <core/init.hpp>
#include <core/quark.hpp>
#include <utils.hpp>

extern Quark pc_vesa;
extern Quark pc_8042;

void ksinit::platform()
{
    quark_collection.add_quark(pc_vesa, pc_8042);
}
