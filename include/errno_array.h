/*
** EPITECH PROJECT, 2022
** strace
** File description:
** errno_array
*/

#pragma once

static const char *errno_values[] = {"EPERM", "ENOENT", "ESRCH", "EINTR",
    "EIO", "ENXIO", "E2BIG", "ENOEXEC", "EBADF", "ECHILD", "EAGAIN", "ENOMEM",
    "EACCES", "EFAULT", "ENOTBLK", "EBUSY", "EEXIST", "EXDEV", "ENODEV",
    "ENOTDIR", "EISDIR", "EINVAL", "ENFILE", "EMFILE", "ENOTTY", "ETXTBSY",
    "EFBIG", "ENOSPC", "ESPIPE", "EROFS", "EMLINK", "EPIPE", "EDOM", "ERANGE",
    "EDEADLK", "ENAMETOOLONG", "ENOLCK", "ENOSYS", "ENOTEMPTY", "ELOOP",
    "ERROR", "ENOMSG", "EIDRM", "ECHRNG", "EL2NSYNC", "EL3HLT", "EL3RST",
    "ELNRNG", "EUNATCH", "ENOCSI", "EL2HLT", "EBADE", "EBADR", "EXFULL",
    "ENOANO", "EBADRQC", "EBADSLT", "ERROR", "EBFONT", "ENOSTR", "ENODATA",
    "ETIME", "ENOSR", "ENONET", "ENOPKG", "EREMOTE", "ENOLINK", "EADV",
    "ESRMNT", "ECOMM", "EPROTO", "EMULTIHOP", "EDOTDOT", "EBADMSG",
    "EOVERFLOW", "ENOTUNIQ", "EBADFD", "EREMCHG", "ELIBACC", "ELIBBAD",
    "ELIBSCN", "ELIBMAX", "ELIBEXEC", "EILSEQ", "ERESTART", "ESTRPIPE",
    "EUSERS", "ENOTSOCK", "EDESTADDRREQ", "EMSGSIZE", "EPROTOTYPE",
    "ENOPROTOOPT", "EPROTONOSUPPORT", "ESOCKTNOSUPPORT", "EOPNOTSUPP",
    "EPFNOSUPPORT", "EAFNOSUPPORT", "EADDRINUSE", "EADDRNOTAVAIL", "ENETDOWN",
    "ENETUNREACH", "ENETRESET", "ECONNABORTED", "ECONNRESET", "ENOBUFS",
    "EISCONN", "ENOTCONN", "ESHUTDOWN", "ETOOMANYREFS", "ETIMEDOUT",
    "ECONNREFUSED", "EHOSTDOWN", "EHOSTUNREACH", "EALREADY", "EINPROGRESS",
    "ESTALE", "EUCLEAN", "ENOTNAM", "ENAVAIL", "EISNAM", "EREMOTEIO", "EDQUOT",
    "ENOMEDIUM", "EMEDIUMTYPE", "ECANCELED", "ENOKEY", "EKEYEXPIRED",
    "EKEYREVOKED", "EKEYREJECTED", "EOWNERDEAD", "ENOTRECOVERABLE"};
