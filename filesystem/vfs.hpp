#pragma once
#include <array.hpp>
#include <permission.hpp>
#include <string.hpp>
#include <types.hpp>

enum class FilesystemTypes : uint8_t
{
    UNKNOWN,
    DEVICE
};

class FilesystemEntryInfo
{
  public:
    Permissions permissions;
    bool is_file;
};

enum class Filesystem_Services : uint8_t
{
    OPEN,
    INFO
};

class FilesystemHandler
{
  public:
    void (*open)(String path) = nullptr;
    void (*info)(String path, FilesystemEntryInfo *info) = nullptr;
};

class VFS
{
  public:
    bool call_filesystem_handler_service(Filesystem_Services quark_service, Array<void *, 3> args);
};

inline VFS vfs;