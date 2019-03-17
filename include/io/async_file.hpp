/*
 * Copyright 2018 Justas Masiulis
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#pragma once
#include "traits/file.hpp"
#include "async_query.hpp"
#include "byte_span.hpp"

namespace ntw::io {

    /// \brief Asynchronous file API.
    template<class Handle, class Traits = traits::async_file_traits<Handle>>
    class basic_async_file : public detail::base_file<Traits> {
        using base_type = detail::base_file<Traits>;

        template<class Fn, class QueryData>
        NT_FN _control(Fn                  fn,
                       ulong_t             control_code,
                       cbyte_span<ulong_t> input,
                       byte_span<ulong_t>  output,
                       QueryData&          query) const noexcept;

    public:
        NTW_INLINE basic_async_file() = default;

        /// \brief Constructs basic_async_file using an object that stores a handle
        template<class ObjectHandle>
        NTW_INLINE basic_async_file(const ObjectHandle& handle)
            : base_type(unwrap_handle(handle))
        {}

        /// \brief Writes data to file using NtWriteFile API.
        /// \param data The data that will be written to the file.
        /// \param offset The offset from the beggining of file to write data to.
        /// \param query The query object containing optional event, callback, etc.
        template<class QueryData>
        NT_FN write(cbyte_span<ulong_t> data, std::int64_t offset, QueryData& query) const
            noexcept;

        /// \brief Reads data from file using NtReadFile API.
        /// \param buffer The buffer into which the data will be read.
        /// \param offset The offset from the beggining of file to read data from.
        /// \param query The query object containing optional event, callback, etc.
        template<class QueryData>
        NT_FN read(byte_span<ulong_t> buffer, std::int64_t offset, QueryData& query) const
            noexcept;

        /// \brief Sends a control code to a device driver using NtDeviceIoControl API.
        /// \param control_code The control code that will be sent.
        /// \param input The input buffer.
        /// \param output The output buffer.
        /// \param query The query data including completion callback etc.
        template<class QueryData>
        NT_FN device_io_control(ulong_t             control_code,
                                cbyte_span<ulong_t> input,
                                byte_span<ulong_t>  output,
                                QueryData&          query) const noexcept;

        /// \brief Sends a control code to a device driver using NtDeviceIoControl API.
        /// \param control_code The control code that will be sent.
        /// \param input The input buffer.
        /// \param output The output buffer.
        /// \param query The query data including completion callback etc.
        template<class Input, class Output, class QueryData>
        NT_FN device_io_control(ulong_t      control_code,
                                const Input& input,
                                Output&      output,
                                QueryData&   query) const noexcept;


        /// \brief Sends a control code to a file system or file system filter driver
        /// using NtFsControlFile API.
        /// \param control_code The control code that will be sent.
        /// \param input The input buffer.
        /// \param output The output buffer.
        /// \param query The query data including completion callback etc.
        template<class QueryData>
        NT_FN fs_control(ulong_t             control_code,
                         cbyte_span<ulong_t> input,
                         byte_span<ulong_t>  output,
                         QueryData&          query) const noexcept;

        /// \brief Sends a control code to a file system or file system filter driver
        /// using NtFsControlFile API.
        /// \param control_code The control code that will be sent.
        /// \param input The input buffer.
        /// \param output The output buffer.
        /// \param query The query data including completion callback etc.
        template<class Input, class Output, class QueryData>
        NT_FN fs_control(ulong_t      control_code,
                         const Input& input,
                         Output&      output,
                         QueryData&   query) const noexcept;
    };

    using unique_async_file = basic_async_file<unique_handle>;
    using async_file_ref    = basic_async_file<handle_ref>;

} // namespace ntw::io

#include "../impl/async_file.inl"