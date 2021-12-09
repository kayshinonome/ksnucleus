# Options

These are all options set in the config.mk and match to

## General options

- CONFIG_KSNUCLEUS_ARCH
  - Controls the arch and cpu class that the nucleus will be built for

- CONFIG_KSNUCLEUS_PLATFORM
  - Controls the quarks built in and also runtime code for the platform. This may also further specify the cpu used.

- CONFIG_KSNUCLEUS_WORD_WIDTH
  - Controls the word width for the arch. Often times this controls the mode of the target cpu. Some targets will give a error if this is a incorrect value.

- CONFIG_KSNUCLEUS_ENDIAN
  - Controls the endian of the nucleus. Some targets require a value of `none` (8 bit platforms), and others only support one.

- CONFIG_KSNUCLEUS_DEBUG
  - Controls whether debug structures are built in and debug info is kept

## x86 Options

## PC Options

- CONFIG_KSNUCLEUS_8042_SUPPORT
  - Controls whether a quark to control the 8042 (has rebooting support) is added.

- CONFIG_KSNUCLEUS_VESA_SUPPORT
  - Controls whether a quark to control VESA operation is included (and by design general VGA and somewhat EGA support)

- CONFIG_KSNUCLEUS_MULTIBOOT_SUPPORT
  - Controls whether multiboot support is used.
