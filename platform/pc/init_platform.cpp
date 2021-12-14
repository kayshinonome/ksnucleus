#include <core/driver.hpp>
#include <core/init.hpp>
#include <core/registry.hpp>
#include <utils.hpp>

#if defined(CONFIG_KSNUCLEUS_VESA_SUPPORT)
extern Driver pc_vesa;
#endif

#if defined(CONFIG_KSNUCLEUS_8042_SUPPORT)
extern Driver pc_8042;
#endif

void ksinit::platform()
{
#if defined(CONFIG_KSNUCLEUS_VESA_SUPPORT)
    driver_collection.add_quark(pc_vesa);
#endif

#if defined(CONFIG_KSNUCLEUS_8042_SUPPORT)
    driver_collection.add_quark(pc_8042);
#endif
    // Reserve the IVT
    global_registry.memory_table[0] = {.memory = reinterpret_cast<void *>(0),
                                       .block_length = 0x3ff,
                                       .is_reserved = true,
                                       .permissions = {.system_read = true,
                                                       .system_write = true,
                                                       .system_execute = false,
                                                       .user_read = false,
                                                       .user_write = false,
                                                       .user_execute = false}};
}
