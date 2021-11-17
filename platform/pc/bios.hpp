/**
 * @file bios.hpp
 * @author Kay Shinonome (kayshinonome@protonmail.com)
 * @brief Bios tools set, derived from http://www.bioscentral.com/misc/bda.htm and
 * https://stanislavs.org/helppc/bios_data_area.html
 *
 * @copyright Copyright (c) 2021
 *
 */
#include <utils.hpp>

constexpr auto BIOS_DATA_AREA_BASE = 0x00000400;

/**
 * @brief Class to represent the entire BIOS BDA
 *
 */
class BiosDataArea
{
  public:
    /**
     *
     * @brief Base address for serial port 1
     *
     */
    uint16_t COM1_BASE_IO_ADDRESS;

    /**
     * @brief Base address for serial port 2
     *
     */
    uint16_t COM2_BASE_IO_ADDRESS;

    /**
     * @brief Base address for serial port 3
     *
     */
    uint16_t COM3_BASE_IO_ADDRESS;

    /**
     * @brief Base address for serial port 4
     *
     */
    uint16_t COM4_BASE_IO_ADDRESS;

    /**
     * @brief Base address for parallel port 1
     *
     */
    uint16_t LPT1_BASE_IO_ADDRESS;

    /**
     * @brief Base address for parallel port 2
     *
     */
    uint16_t LPT2_BASE_IO_ADDRESS;

    /**
     * @brief Base address for parallel port 3
     *
     */
    uint16_t LPT3_BASE_IO_ADDRESS;

    /**
     * @brief Base address for parallel port 4 (PC/XT only)
     *
     */
    uint16_t LPT4_BASE_IO_ADDRESS;

    /**
     * @brief Number of parallel ports installed, - 1
     *
     */
    uint8_t PARALLEL_PORT_COUNT : 2;

  private:
    uint8_t UNUSED_1 : 2;

  public:
    /**
     * @brief Number of serial ports installed
     *
     */
    uint8_t SERIAL_PORT_COUNT : 3;

  private:
    uint8_t UNUSED_2 : 1;

  public:
    /**
     * @brief Number of floppy drives installed - 1 (Max 2)
     *
     */
    uint8_t FLOPPY_DRIVE_COUNT : 2;

    /**
     * @brief Current video mode
     * 0    =   EGA or later
     * 1    =   color 40x25
     * 2    =   color 80x25
     * 3    =   monochrome 80x25
     */
    uint8_t CURRENT_VIDEO_MODE : 2;

  private:
    uint8_t UNUSED_3 : 1;

  public:
    /**
     * @brief 1 if a ps/2 mouse is installed, 0 if it isn't
     *
     */
    uint8_t IS_PS2_MOUSE_INSTALLED : 1;

  private:
    uint8_t UNUSED_4 : 1;

  public:
    /**
     * @brief 1 if a math coprocessor is installed, 0 if it isn't
     *
     */
    uint8_t IS_MATH_COPROCESSOR_INSTALLED : 1;

    /**
     * @brief 1 if a boot floppy is installed, 0 if it isn't
     *
     */
    uint8_t IS_BOOT_FLOPPY_INSTALLED : 1;

    /**
     * @brief Manufacturing test of sorts
     *
     */
    uint8_t INTERRUPT_FLAG_TEST;

    /**
     * @brief Memory size in kilobytes
     *
     */
    uint16_t MEMORY_SIZE_KB;

    /**
     * @brief Adaptor memory size on PC or PC/XT. On PC/AT plus this is error codes
     *
     */
    uint16_t ADAPTOR_MEMORY_SIZE;

    /**
     * @brief Keyboard shift flags
     *
     */
    uint8_t IS_INSERT_ON_1 : 1;
    uint8_t IS_CAPSLOCK_ON_1 : 1;
    uint8_t IS_NUMLOCK_ON_1 : 1;
    uint8_t IS_SCROLLLOCK_ON_1 : 1;
    uint8_t IS_ALT_PRESSED_1 : 1;
    uint8_t IS_CTRL_PRESSED_1 : 1;
    uint8_t IS_LEFT_SHIFT_PRESSED_1 : 1;
    uint8_t IS_RIGHT_SHIFT_PRESSED_1 : 1;
    uint8_t IS_INSERT_PRESSED_1 : 1;
    uint8_t IS_CAPSLOCK_PRESSED_1 : 1;
    uint8_t IS_NUMLOCK_PRESSED_1 : 1;
    uint8_t IS_SCROLLLOCK_PRESSED_1 : 1;
    uint8_t IS_PAUSE_ACTIVE_1 : 1;
    uint8_t IS_SYSREQ_PRESSED_1 : 1;
    uint8_t IS_LEFT_ALT_PRESSED_1 : 1;
    uint8_t IS_RIGHT_ALT_PRESSED_1 : 1;

    /**
     * @brief Alt numpad work area, probably reserved
     *
     */
    uint8_t ALT_NUMPAD_WORK_AREA;

    /**
     * @brief Pointer to the address of the head of the keyboard buffer
     *
     */
    uint16_t KEYBOARD_BUFFER_HEAD;

    /**
     * @brief Pointer to the address of the tail of the keyboard buffer
     *
     */
    uint16_t KEYBOARD_BUFFER_TAIL;

    /**
     * @brief The keyboard buffer
     *
     */
    uint8_t KEYBOARD_BUFFER[32];

  private:
    uint8_t UNUSED_5 : 3;

  public:
    /**
     * @brief Calibration status of the floppy disk
     *
     */

    /**
     * @brief Floppy 3 calibration status. (PC and PC/XT only)
     *
     */
    uint8_t IS_FLOPPY_3_CALIBRATED : 1;

    /**
     * @brief Floppy 2 calibration status. (PC and PC/XT only)
     *
     */
    uint8_t IS_FLOPPY_2_CALIBRATED : 1;

    /**
     * @brief Floppy 1 calibration status.
     */
    uint8_t IS_FLOPPY_1_CALIBRATED : 1;

    /**
     * @brief Floppy 3 calibration status. (PC and PC/XT only)
     *
     */
    uint8_t IS_FLOPPY_0_CALIBRATED : 1;

    /**
     * @brief Floppy drive motor status
     *
     */

    /**
     * @brief What operation the floppy motor is currently doing
     * 0    =   Read or verify operation
     * 1    =   Write or format operation
     */
    uint8_t FLOPPY_MOTOR_CURRENT_OPERATION : 1;

  private:
    uint8_t UNUSED_6 : 1;

  public:
    /**
     * @brief The selected drive
     *
     *
     */
    uint8_t FLOPPY_MOTOR_DRIVE_SELECT : 2;

} __attribute__((packed));

// NOLINTNEXTLINE(performance-no-int-to-ptr)
const volatile inline BiosDataArea *bios_data_area = reinterpret_cast<volatile BiosDataArea *>(BIOS_DATA_AREA_BASE);
