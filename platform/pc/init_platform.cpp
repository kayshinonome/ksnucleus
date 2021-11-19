#include <core/init.hpp>
#include <core/quark.hpp>
#include <utils.hpp>

extern Quark pc_vesa;

bool ksinit::platform()
{
    // pc_vesa.commit_framebuffer(nullptr);
    return true;
}
