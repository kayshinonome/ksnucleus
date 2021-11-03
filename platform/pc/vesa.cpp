#include <arch/x86/x86_32/v86.hpp>
#include <core/quark.hpp>
#include <platform/pc/bios.hpp>
#include <utils.hpp>
#include <video/rendering.hpp>

Quark pc_vesa{.is_viable = []() { return bios_data_area->CURRENT_VIDEO_MODE == 0; },
              .init = []() {},
              .fini = []() {},
              .commit_framebuffer =
                  [](void *data) {

                  }};