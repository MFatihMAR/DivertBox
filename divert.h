#ifndef DIVERT_H
#define DIVERT_H

#include <stddef.h>
#include <stdint.h>

#if defined(_WIN32) || defined(WIN32)
    #define DIVERT_PLATFORM_WINDOWS
#elif __linux__
    #define DIVERT_PLATFORM_LINUX
#elif __APPLE__
    #include "TargetConditionals.h"
    #if TARGET_OS_MAC
        #define DIVERT_PLATFORM_MACOS
    #endif
#endif

#if !defined(DIVERT_PLATFORM_WINDOWS) &&\
    !defined(DIVERT_PLATFORM_LINUX) &&\
    !defined(DIVERT_PLATFORM_MACOS)
    #error "libdivert: unsupported platform"
#endif

// TODO:WIP: Filter Language Syntax

typedef enum
{
    DV_ERROR_NONE       = 0
} dv_error_t;

typedef enum
{
    DV_MODE_DIVERT      = 0xA,
    DV_MODE_SNIFF       = 0xB,
    DV_MODE_INFO        = 0xC
} dv_mode_t;

typedef enum
{
    DV_STATUS_IDLE      = 0x0,
    DV_STATUS_READY     = 0xA,
    DV_STATUS_ACTIVE    = 0xF
} dv_status_t;

typedef void (*dv_handler_t)(size_t filter_index, const uint8_t* buffer, size_t length);

dv_error_t divert_status(dv_status_t* status);

dv_error_t divert_open(dv_handler_t handler);
dv_error_t divert_close(void);

dv_error_t divert_filter_add(const uint8_t* buffer, size_t length);
dv_error_t divert_filter_get(size_t index, uint8_t* buffer, size_t* length);
dv_error_t divert_filter_remove(size_t index);
dv_error_t divert_filter_count(size_t* count);
dv_error_t divert_filter_clear(void);

dv_error_t divert_start(dv_mode_t mode);
dv_error_t divert_inject(const uint8_t* buffer, size_t length);
dv_error_t divert_stop(void);

#endif // DIVERT_H
