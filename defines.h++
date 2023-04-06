#ifndef DEFINES_H
#define DEFINES_H

#define ND [[nodiscard]]

#define NS [[maybe_unused]]

#define NR [[noreturn]]

#define NOD [[nodiscard]] [[maybe_unused]]

#define NRS [[maybe_unused]] [[noreturn]]

#define NOEXCEPT(arg) noexcept((arg))

#define SHARED_LIB_EXPORT __attribute__((visibility("default")))
#define SHARED_LIB_IMPORT __attribute__((visibility("default")))
#define SHARED_LIB_LOCAL __attribute__((visibility("hidden")))
#define SHARED_LIB_HIDDEN __attribute__((visibility("hidden")))

// setting the default visibility to internal will cause the compiler to treat the symbols as if they were static
// this is useful for symbols that are not intended to be exported
#define SHARED_LIB_INTERNAL __attribute__((visibility("internal")))
#define SHARED_LIB_PROTECTED __attribute__((visibility("protected")))
#define SHARED_LIB_DEFAULT __attribute__((visibility("default")))

// we can use this to make sure that a function is only called from a specific
// thread
#define SHARED_LIB_WEAK __attribute__((weak))

#endif
