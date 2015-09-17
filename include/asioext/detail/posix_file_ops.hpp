/// @copyright Copyright (c) 2015 Tim Niederhausen (tim@rnc-ag.de)
/// Distributed under the Boost Software License, Version 1.0.
/// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef ASIOEXT_DETAIL_POSIXFILEOPS_HPP
#define ASIOEXT_DETAIL_POSIXFILEOPS_HPP

#include "asioext/detail/config.hpp"

#if ASIOEXT_HAS_PRAGMA_ONCE
#pragma once
#endif

#include "asioext/detail/cstdint.hpp"

#include <asio/error_code.hpp>

#define _FILE_OFFSET_BITS 64

#include <cstddef> // for size_t
#include <sys/uio.h> // for iovec

#undef _FILE_OFFSET_BITS

#include "asioext/detail/push_options.hpp"

ASIOEXT_NS_BEGIN

namespace detail {
namespace posix_file_ops {

typedef int handle_type;

ASIOEXT_DECL void set_error(asio::error_code& ec, int e);

ASIOEXT_DECL handle_type open(const char* path, uint32_t flags,
                              asio::error_code& ec);

ASIOEXT_DECL void close(handle_type fd, asio::error_code& ec);

ASIOEXT_DECL uint64_t size(handle_type fd, asio::error_code& ec);

ASIOEXT_DECL uint64_t seek(handle_type fd, int origin, int64_t offset,
                           asio::error_code& ec);

ASIOEXT_DECL std::size_t readv(handle_type fd, iovec* bufs, int count,
                               asio::error_code& ec);

ASIOEXT_DECL std::size_t writev(handle_type fd,
                                const iovec* bufs, int count,
                                asio::error_code& ec);

ASIOEXT_DECL std::size_t preadv(handle_type fd, iovec* bufs, int count,
                                uint64_t offset, asio::error_code& ec);

ASIOEXT_DECL std::size_t pwritev(handle_type fd,
                                 const iovec* bufs, int count,
                                 uint64_t offset, asio::error_code& ec);

}
}

ASIOEXT_NS_END

#include "asioext/detail/pop_options.hpp"

#if defined(ASIOEXT_HEADER_ONLY)
# include "asioext/detail/impl/posix_file_ops.cpp"
#endif

#endif
