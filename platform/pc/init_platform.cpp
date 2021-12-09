#include <core/init.hpp>
#include <core/quark.hpp>
#include <utils.hpp>

#if defined(CONFIG_KSNUCLEUS_VESA_SUPPORT)
extern Quark pc_vesa;
#endif

#if defined(CONFIG_KSNUCLEUS_8042_SUPPORT)
extern Quark pc_8042;
#endif

void ksinit::platform()
{
#if defined(CONFIG_KSNUCLEUS_VESA_SUPPORT)
    quark_collection.add_quark(pc_vesa);
#endif

#if defined(CONFIG_KSNUCLEUS_8042_SUPPORT)
    quark_collection.add_quark(pc_8042);
#endif
}
