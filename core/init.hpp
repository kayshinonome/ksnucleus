#pragma once

namespace ksinit
{
    /**
     * @brief Init the arch specific code
     *
     */
    void arch();

    /**
     * @brief Init the boot code
     *
     */
    void boot();

    /**
     * @brief Init the platform
     *
     */
    void platform();
} // namespace ksinit
