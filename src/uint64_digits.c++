#include "uint64_digits.h++"


#include <cmath>
#include <cstdint>
#include <concepts>
#include <type_traits>
#include <typeindex>
#include <typeinfo>
#include <utility>
#include <array>
#include <iterator>
#include <algorithm>
#include <functional>
#include <numeric>
#include <ranges>


#include <cfenv>
#include <cerrno>


enum class err_nums {
    eperm  = EPERM,                        /* Operation not permitted */
    enoent = ENOENT,               /* No such file or directory */
    esrch  = ESRCH,                        /* No such process */
    eintr  = EINTR,                        /* Interrupted system call */
    eio    = EIO,                          /* I/O error */
    enxio  = ENXIO,                        /* No such device or address */
    e2big  = E2BIG,                        /* Argument list too long */
    enoexec = ENOEXEC,             /* Exec format error */
    ebadf  = EBADF,                        /* Bad file number */
    echild = ECHILD,               /* No child processes */
    edeadlk = EDEADLK,             /* Try again */
    enomem = ENOMEM,               /* Out of memory */
    eacces = EACCES,               /* Permission denied */
    efault = EFAULT,               /* Bad address */
    enotblk = ENOTBLK,             /* Block device required */
    ebusy  = EBUSY,                        /* Device or resource busy */
    eexist = EEXIST,               /* File exists */
    exdev  = EXDEV,                        /* Cross-device link */
    enodev = ENODEV,               /* No such device */
    enotdir = ENOTDIR,             /* Not a directory */
    eisdir = EISDIR,               /* Is a directory */
    einval = EINVAL,               /* Invalid argument */
    enfile = ENFILE,               /* File table overflow */
    emfile = EMFILE,               /* Too many open files */
    enotty = ENOTTY,               /* Not a typewriter */
    etxtbsy = ETXTBSY,             /* Text file busy */
    efbig  = EFBIG,                        /* File too large */
    enospc = ENOSPC,               /* No space left on device */
    espipe = ESPIPE,               /* Illegal seek */
    erofs  = EROFS,                        /* Read-only file system */
    emlink = EMLINK,               /* Too many links */
    epipe  = EPIPE,                        /* Broken pipe */
    edom   = EDOM,                         /* Math argument out of domain of func */
    erange = ERANGE,               /* Math result not representable */
    eagain = EAGAIN,               /* Resource temporarily unavailable */
    ewouldblock = EWOULDBLOCK,     /* Operation would block */
    einprogress = EINPROGRESS,             /* Operation now in progress */
    ealready = EALREADY,               /* Operation already in progress */
    enotsock = ENOTSOCK,             /* Socket operation on non-socket */
    edestaddrreq = EDESTADDRREQ,           /* Destination address required */
    emsgsize = EMSGSIZE,               /* Message too long */
    eprototype = EPROTOTYPE,           /* Protocol wrong type for socket */
    enoprotoopt = ENOPROTOOPT,         /* Protocol not available */
    eprotonosupport = EPROTONOSUPPORT,         /* Protocol not supported */
    esocktnosupport = ESOCKTNOSUPPORT,         /* Socket type not supported */





#define EAFNOSUPPORT    47              /* Address family not supported by protocol family */
#define EADDRINUSE      48              /* Address already in use */
#define EADDRNOTAVAIL   49              /* Can't assign requested address */

/* ipc/network software -- operational errors */
#define ENETDOWN        50              /* Network is down */
#define ENETUNREACH     51              /* Network is unreachable */
#define ENETRESET       52              /* Network dropped connection on reset */
#define ECONNABORTED    53              /* Software caused connection abort */
#define ECONNRESET      54              /* Connection reset by peer */
#define ENOBUFS         55              /* No buffer space available */
#define EISCONN         56              /* Socket is already connected */
#define ENOTCONN        57              /* Socket is not connected */
#if __DARWIN_C_LEVEL >= __DARWIN_C_FULL
#define ESHUTDOWN       58              /* Can't send after socket shutdown */
#define ETOOMANYREFS    59              /* Too many references: can't splice */
#endif
#define ETIMEDOUT       60              /* Operation timed out */
#define ECONNREFUSED    61              /* Connection refused */

#define ELOOP           62              /* Too many levels of symbolic links */
#define ENAMETOOLONG    63              /* File name too long */

/* should be rearranged */
#if __DARWIN_C_LEVEL >= __DARWIN_C_FULL
#define EHOSTDOWN       64              /* Host is down */
#endif
#define EHOSTUNREACH    65              /* No route to host */
#define ENOTEMPTY       66              /* Directory not empty */

/* quotas & mush */
#if __DARWIN_C_LEVEL >= __DARWIN_C_FULL
#define EPROCLIM        67              /* Too many processes */
#define EUSERS          68              /* Too many users */
#endif
#define EDQUOT          69              /* Disc quota exceeded */

/* Network File System */
#define ESTALE          70              /* Stale NFS file handle */
#if __DARWIN_C_LEVEL >= __DARWIN_C_FULL
#define EREMOTE         71              /* Too many levels of remote in path */
#define EBADRPC         72              /* RPC struct is bad */
#define ERPCMISMATCH    73              /* RPC version wrong */
#define EPROGUNAVAIL    74              /* RPC prog. not avail */
#define EPROGMISMATCH   75              /* Program version wrong */
#define EPROCUNAVAIL    76              /* Bad procedure for program */
#endif

#define ENOLCK          77              /* No locks available */
#define ENOSYS          78              /* Function not implemented */

#if __DARWIN_C_LEVEL >= __DARWIN_C_FULL
#define EFTYPE          79              /* Inappropriate file type or format */
#define EAUTH           80              /* Authentication error */
#define ENEEDAUTH       81              /* Need authenticator */

/* Intelligent device errors */
#define EPWROFF         82      /* Device power is off */
#define EDEVERR         83      /* Device error, e.g. paper out */
#endif

#define EOVERFLOW       84              /* Value too large to be stored in data type */

/* Program loading errors */
#if __DARWIN_C_LEVEL >= __DARWIN_C_FULL
#define EBADEXEC        85      /* Bad executable */
#define EBADARCH        86      /* Bad CPU type in executable */
#define ESHLIBVERS      87      /* Shared library version mismatch */
#define EBADMACHO       88      /* Malformed Macho file */
#endif

#define ECANCELED       89              /* Operation canceled */

#define EIDRM           90              /* Identifier removed */
#define ENOMSG          91              /* No message of desired type */
#define EILSEQ          92              /* Illegal byte sequence */
#if __DARWIN_C_LEVEL >= __DARWIN_C_FULL
#define ENOATTR         93              /* Attribute not found */
#endif

#define EBADMSG         94              /* Bad message */
#define EMULTIHOP       95              /* Reserved */
#define ENODATA         96              /* No message available on STREAM */
#define ENOLINK         97              /* Reserved */
#define ENOSR           98              /* No STREAM resources */
#define ENOSTR          99              /* Not a STREAM */
#define EPROTO          100             /* Protocol error */
#define ETIME           101             /* STREAM ioctl timeout */

#if __DARWIN_UNIX03 || defined(KERNEL)
/* This value is only discrete when compiling __DARWIN_UNIX03, or KERNEL */
#define EOPNOTSUPP      102             /* Operation not supported on socket */
#endif /* __DARWIN_UNIX03 || KERNEL */

#define ENOPOLICY       103             /* No such policy registered */

#if __DARWIN_C_LEVEL >= 200809L
#define ENOTRECOVERABLE 104             /* State not recoverable */
#define EOWNERDEAD      105             /* Previous owner died */
#endif

#if __DARWIN_C_LEVEL >= __DARWIN_C_FULL
#define EQFULL          106             /* Interface output queue is full */
#define ELAST           106             /* Must be equal largest errno */
#endif

};


enum class error_numbers {
    fe_div_by_zero      = FE_DIVBYZERO, fe_inexact = FE_INEXACT, fe_invalid = FE_INVALID, fe_overflow = FE_OVERFLOW,
    fe_underflow        = FE_UNDERFLOW, fe_all_exceptions = FE_ALL_EXCEPT, fe_div_by_zero_masked = FE_DIVBYZERO << 8,
    fe_inexact_masked   = FE_INEXACT << 8, fe_invalid_masked = FE_INVALID << 8, fe_overflow_masked = FE_OVERFLOW << 8,
    fe_underflow_masked = FE_UNDERFLOW << 8, fe_all_exceptions_masked = FE_ALL_EXCEPT << 8
};


struct math_clearexcept {
    auto operator () () const noexcept -> void {
        std::feclearexcept (static_cast< int > (error_numbers::fe_all_exceptions));
    }
};

struct math_getexceptflag {

    auto operator () (error_numbers flag) const noexcept -> bool {
        return std::fetestexcept (static_cast< int > (flag));
    }

    auto operator () (error_numbers flag, bool clear) const noexcept -> bool {
        return std::fetestexcept (static_cast< int > (flag)) != 0 &&
               (!clear || std::feclearexcept (static_cast< int > (flag)), true);
    }
};

struct math_raiseexcept {
    auto operator () (error_numbers flag) const noexcept -> void {
        std::feraiseexcept (static_cast< int > (flag));
    }
};


struct math_setexceptflag {
    auto operator () (error_numbers flag, bool value) const noexcept -> void {
        if (value) {
            std::fesetexceptflag (reinterpret_cast<const fexcept_t *>(& flag), static_cast< int > (flag));
        } else {
            std::feclearexcept (static_cast< int > (flag));
        }
    }
};

struct math_setexceptmask {
    auto operator () (error_numbers mask) const noexcept -> void {
        std::fesetexceptflag (reinterpret_cast<const fexcept_t *>(& mask), static_cast< int > (mask));
    }
};


struct math_getround {
    auto operator () () const noexcept -> std::float_round_style {
        return static_cast< std::float_round_style > (std::fegetround ());
    }
};


struct math_round_t {
    auto operator () (std::float_round_style style) const noexcept -> void {
        std::fesetround (static_cast< int > (style));
    }
};


struct math_getenv {

    auto operator () () const noexcept -> std::fenv_t {
        std::fenv_t env;
        std::fegetenv (& env);
        return env;
    }
};


struct math_setenv {
    auto operator () (std::fenv_t env) const noexcept -> void {
        std::fesetenv (& env);
    }
};


struct math_updateenv {

    auto operator () (std::fenv_t env) const noexcept -> void {
        std::feupdateenv (& env);
    }
};

struct math_holdexcept {
    auto operator () () const noexcept -> std::fenv_t {
        std::fenv_t env;
        std::feholdexcept (& env);
        return env;
    }
};


struct math_err_handle {

public:
    std::fenv_t env = math_getenv () ();

    std::float_round_style round_style     = std::float_round_style::round_to_nearest;
    error_numbers          except_mask     = error_numbers::fe_all_exceptions;
    error_numbers          except_flag     = error_numbers::fe_all_exceptions;
    bool                   except_flag_set = false;
    bool                   except_mask_set = false;
    bool                   round_style_set = false;
    bool                   env_set         = false;

public:
    math_clearexcept   clear_except    = math_clearexcept ();
    math_getexceptflag get_except_flag = math_getexceptflag ();
    math_raiseexcept   raise_except    = math_raiseexcept ();
    math_setexceptflag set_except_flag = math_setexceptflag ();
    math_setexceptmask set_except_mask = math_setexceptmask ();
    math_getround      get_round       = math_getround ();
    math_round_t       set_round       = math_round_t ();
    math_getenv        get_env         = math_getenv ();
    math_setenv        set_env         = math_setenv ();
    math_updateenv     update_env      = math_updateenv ();
    math_holdexcept    hold_except     = math_holdexcept ();

private:

    constexpr math_err_handle () noexcept = default;


    const std::function< bool () > ret_true = [] () -> bool { return true; };

    std::function< bool () > ret_false = [] () -> bool { return false; };

public:

    auto operator () (error_numbers flag) const noexcept -> void {
        std::feclearexcept (static_cast< int > (flag));
    }

    auto operator () (error_numbers flag, bool clear) const noexcept -> bool {

        switch (std::feclearexcept (static_cast<int>(flag))) {
            case 0: {
                return true;
            }
            case EDOM:
            case ERANGE:
            default:
                return false;
        };
    }

    auto operator () (error_numbers flag, bool clear, bool raise) const noexcept -> bool {
        return std::fetestexcept (static_cast< int > (flag)) ? (clear ? std::feclearexcept (static_cast< int > (flag))
                                                                      : true
        ), (raise ? std::feraiseexcept (static_cast< int > (flag)) : true), true : false;
    }

    auto operator () (error_numbers flag, bool clear, bool raise, bool set) const noexcept -> bool {
        return std::fetestexcept (static_cast< int > (flag)) ? (clear ? std::feclearexcept (static_cast< int > (flag))
                                                                      : true
        ), (raise ? std::feraiseexcept (static_cast< int > (flag)) : true), (set ? std::fesetexceptflag (
                reinterpret_cast<const fexcept_t *>(& flag),
                static_cast< int > (flag)) : true
        ), true : false;
    }

    auto operator () (error_numbers flag, bool clear, bool raise, bool set, bool update) const noexcept -> bool {
        return std::fetestexcept (static_cast< int > (flag)) ? (clear ? std::feclearexcept (static_cast< int > (flag))
                                                                      : true
        ), (raise ? std::feraiseexcept (static_cast< int > (flag)) : true), (set ? std::fesetexceptflag (
                reinterpret_cast<const fexcept_t *>(& flag),
                static_cast< int > (flag)) : true
        ), (update ? std::feupdateenv (reinterpret_cast<const fenv_t *>(& flag)) : true), true : false;
    }

    auto
    operator () (error_numbers flag, bool clear, bool raise, bool set, bool update, bool hold) const noexcept -> bool {
        return std::fetestexcept (static_cast< int > (flag)) ? (clear ?
    };
