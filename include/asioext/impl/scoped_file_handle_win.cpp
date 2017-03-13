/// @copyright Copyright (c) 2015 Tim Niederhausen (tim@rnc-ag.de)
/// Distributed under the Boost Software License, Version 1.0.
/// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include "asioext/scoped_file_handle.hpp"
#include "asioext/open.hpp"

#include "asioext/detail/win_file_ops.hpp"
#include "asioext/detail/throw_error.hpp"

ASIOEXT_NS_BEGIN

scoped_file_handle::scoped_file_handle(const char* filename,
                                       open_flags flags,
                                       file_perms perms, file_attrs attrs,
                                       error_code& ec) ASIOEXT_NOEXCEPT
  : handle_(asioext::open(filename, flags, perms, attrs, ec))
{
  // ctor
}

scoped_file_handle::scoped_file_handle(const wchar_t* filename, open_flags flags,
                                       file_perms perms, file_attrs attrs)
  : handle_(asioext::open(filename, flags, perms, attrs))
{
  // ctor
}

scoped_file_handle::scoped_file_handle(const wchar_t* filename,
                                       open_flags flags,
                                       file_perms perms, file_attrs attrs,
                                       error_code& ec) ASIOEXT_NOEXCEPT
  : handle_(detail::win_file_ops::open(filename, flags, perms, attrs, ec))
{
  // ctor
}

#if defined(ASIOEXT_HAS_BOOST_FILESYSTEM)

scoped_file_handle::scoped_file_handle(const boost::filesystem::path& filename,
                                       open_flags flags,
                                       file_perms perms, file_attrs attrs,
                                       error_code& ec) ASIOEXT_NOEXCEPT
  : handle_(detail::win_file_ops::open(filename.c_str(), flags,
                                       perms, attrs, ec))
{
  // ctor
}

#endif

void scoped_file_handle::open(const wchar_t* filename, open_flags flags,
                              file_perms perms, file_attrs attrs)
{
  error_code ec;
  open(filename, flags, perms, attrs, ec);
  detail::throw_error(ec);
}

void scoped_file_handle::open(const wchar_t* filename,
                              open_flags flags,
                              file_perms perms, file_attrs attrs,
                              error_code& ec) ASIOEXT_NOEXCEPT
{
  if (handle_.is_open()) {
    handle_.close(ec);
    if (ec) return;
  }

  handle_ = asioext::open(filename, flags, perms, attrs, ec);
}

ASIOEXT_NS_END
