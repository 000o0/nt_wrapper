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
#include "handle.hpp"
#include "../util.hpp"

namespace ntw::obj {

    namespace detail {

        template<class>
        class base_file;

        class file_attributes_builder {
            unsigned long _attributes = 0;

            template<class Derived>
            friend class base_file;

        protected:
            ~file_attributes_builder() = default;

        public:
            // clang-format off
			// FileAttributes; multiple allowed
			NTW_INLINE constexpr file_attributes_builder& reset_attributes();

			NTW_INLINE constexpr file_attributes_builder& archive(); // FILE_ATTRIBUTE_ARCHIVE
			NTW_INLINE constexpr file_attributes_builder& encrypted(); // FILE_ATTRIBUTE_ENCRYPTED
			NTW_INLINE constexpr file_attributes_builder& hidden(); // FILE_ATTRIBUTE_HIDDEN
			NTW_INLINE constexpr file_attributes_builder& normal(); // FILE_ATTRIBUTE_NORMAL
			NTW_INLINE constexpr file_attributes_builder& offline(); // FILE_ATTRIBUTE_OFFLINE
			NTW_INLINE constexpr file_attributes_builder& readonly(); // FILE_ATTRIBUTE_READONLY
			NTW_INLINE constexpr file_attributes_builder& system(); // FILE_ATTRIBUTE_SYSTEM
			NTW_INLINE constexpr file_attributes_builder& temporary(); // FILE_ATTRIBUTE_TEMPORARY
            // clang-format on
        };

        class pipe_options_builder {
            unsigned long _inbound_qouta; // uninitialized
            unsigned long _outbound_qouta; // uninitialized
            unsigned long _completion_mode; // uninitialized
            unsigned long _type            = 0;
            unsigned long _instances_limit = -1;
            std::int64_t  _timeout         = -500000;

            template<class Derived>
            friend class base_file;

        protected:
            ~pipe_options_builder() = default;

        public:
            // clang-format off
			// must be specified
			NTW_INLINE constexpr pipe_options_builder& qouta(unsigned long inbound,
															 unsigned long outbound);
			NTW_INLINE constexpr pipe_options_builder& inbound_qouta(unsigned long qouta);
			NTW_INLINE constexpr pipe_options_builder& outbound_qouta(unsigned long qouta);

			// CompletionMode; ; must be specified; 1 allowed
			NTW_INLINE constexpr pipe_options_builder& async(); // FILE_PIPE_COMPLETE_OPERATION
			NTW_INLINE constexpr pipe_options_builder& sync(); // FILE_PIPE_QUEUE_OPERATION

			// NamedPipeType; byte stream is default; 1 allowed
			// resets NamedPipeType back to byte stream and clears other flags
			NTW_INLINE constexpr pipe_options_builder& reset_type();

			// also sets ReadMode to the same values
			NTW_INLINE constexpr pipe_options_builder& byte_stream(); // FILE_PIPE_BYTE_STREAM_TYPE
			NTW_INLINE constexpr pipe_options_builder& message_stream(); // FILE_PIPE_MESSAGE_TYPE

			// NamedPipeType; may be specified
			NTW_INLINE constexpr pipe_options_builder& accept_remote_clients(); // FILE_PIPE_ACCEPT_REMOTE_CLIENTS
			NTW_INLINE constexpr pipe_options_builder& reject_remote_clients(); // FILE_PIPE_REJECT_REMOTE_CLIENTS

			// default = unlimited
			NTW_INLINE constexpr pipe_options_builder& instances_limit(unsigned long limit);

			// default = 5 seconds
			NTW_INLINE constexpr pipe_options_builder& timeout(std::int64_t& nanoseconds);
            // clang-format on
        };

        template<class Base>
        class file_options_builder : Base {
            ACCESS_MASK   _access       = 0;
            unsigned long _share_access = 0;
            unsigned long _options      = 0;
            unsigned long _disposition; // uninitialized
            // NOTE: if a need arises for extended attributes support please open a ticket
            // and I'll add a function and data members for it

            template<class Derived>
            friend class base_file;

        public:
            // clang-format off
			// ShareAccess; multiple allowed
			NTW_INLINE constexpr file_options_builder& reset_share_access();

			NTW_INLINE constexpr file_options_builder& share_all(); 
			NTW_INLINE constexpr file_options_builder& share_read(); // FILE_SHARE_READ
			NTW_INLINE constexpr file_options_builder& share_write(); // FILE_SHARE_WRITE
			NTW_INLINE constexpr file_options_builder& share_delete(); // FILE_SHARE_DELETE

			// CreateDisposition; 1 allowed
			NTW_INLINE constexpr file_options_builder& reset_disposition();

			NTW_INLINE constexpr file_options_builder& open(); // FILE_OPEN
			NTW_INLINE constexpr file_options_builder& create(); // FILE_CREATE
			NTW_INLINE constexpr file_options_builder& supersede(); // FILE_SUPERSEDE
			NTW_INLINE constexpr file_options_builder& overwrite(); // FILE_OVERWRITE
			NTW_INLINE constexpr file_options_builder& open_or_create(); // FILE_OPEN_IF
			NTW_INLINE constexpr file_options_builder& overwrite_or_create(); // FILE_OVERWRITE_IF

			// CreateOptions; multiple allowed
			NTW_INLINE constexpr file_options_builder& reset_create_options();

			NTW_INLINE constexpr file_options_builder& directory(); // FILE_DIRECTORY_FILE
			NTW_INLINE constexpr file_options_builder& non_directory(); // FILE_NON_DIRECTORY_FILE
			NTW_INLINE constexpr file_options_builder& write_trough(); // FILE_WRITE_THROUGH
			NTW_INLINE constexpr file_options_builder& sequential_access(); // FILE_SEQUENTIAL_ONLY
			NTW_INLINE constexpr file_options_builder& random_access(); // FILE_RANDOM_ACCESS
			NTW_INLINE constexpr file_options_builder& sync_io_alert(); // FILE_SYNCHRONOUS_IO_ALERT
			NTW_INLINE constexpr file_options_builder& sync_io_nonalert(); // FILE_SYNCHRONOUS_IO_NONALERT
			NTW_INLINE constexpr file_options_builder& create_tree_connection(); // FILE_CREATE_TREE_CONNECTION
			NTW_INLINE constexpr file_options_builder& no_ea_knownledge(); // FILE_NO_EA_KNOWLEDGE
			NTW_INLINE constexpr file_options_builder& open_reparse_point(); // FILE_OPEN_REPARSE_POINT
			NTW_INLINE constexpr file_options_builder& delete_on_close(); // FILE_DELETE_ON_CLOSE
			NTW_INLINE constexpr file_options_builder& open_by_file_id(); // FILE_OPEN_BY_FILE_ID
			NTW_INLINE constexpr file_options_builder& open_for_backup(); // FILE_OPEN_FOR_BACKUP_INTENT
			NTW_INLINE constexpr file_options_builder& reserve_opfilter(); // FILE_RESERVE_OPFILTER
			NTW_INLINE constexpr file_options_builder& requires_oplock(); // FILE_OPEN_REQUIRING_OPLOCK
			NTW_INLINE constexpr file_options_builder& complete_if_oplocked(); // FILE_COMPLETE_IF_OPLOCKED

			// DesiredAccess; multiple allowed
			NTW_INLINE constexpr file_options_builder& reset_access();

			NTW_INLINE constexpr file_options_builder& full_access();

			NTW_INLINE constexpr file_options_builder& deleteable(); // DELETE
			NTW_INLINE constexpr file_options_builder& synchronizable(); // SYNCHRONIZE
			NTW_INLINE constexpr file_options_builder& executeable(); // FILE_EXECUTE
			NTW_INLINE constexpr file_options_builder& traversible(); // FILE_TRAVERSE
			NTW_INLINE constexpr file_options_builder& listable_directory(); // FILE_LIST_DIRECTORY

			NTW_INLINE constexpr file_options_builder& generic_readable(); // FILE_GENERIC_READ
			NTW_INLINE constexpr file_options_builder& generic_writeable(); // FILE_GENERIC_WRITE
			NTW_INLINE constexpr file_options_builder& generic_executeable(); // FILE_GENERIC_EXECUTE

			NTW_INLINE constexpr file_options_builder& readable_data(); // FILE_READ_DATA
			NTW_INLINE constexpr file_options_builder& readable_attributes(); // FILE_READ_ATTRIBUTES
			NTW_INLINE constexpr file_options_builder& readable_extended_attributes(); // FILE_READ_EA
			NTW_INLINE constexpr file_options_builder& readable_access_control(); // READ_CONTROL

			NTW_INLINE constexpr file_options_builder& writeable_data(); // FILE_WRITE_DATA
			NTW_INLINE constexpr file_options_builder& writeable_attributes(); // FILE_WRITE_ATTRIBUTES
			NTW_INLINE constexpr file_options_builder& writeable_extended_attributes(); // FILE_WRITE_EA
			NTW_INLINE constexpr file_options_builder& writeable_access_control(); // WRITE_DAC
			NTW_INLINE constexpr file_options_builder& writeable_ownership(); // WRITE_OWNER
			NTW_INLINE constexpr file_options_builder& appendable_data(); // FILE_APPEND_DATA
            // clang-format on
        };

    } // namespace detail

    using file_options = detail::file_options_builder<detail::file_attributes_builder>;
    using pipe_options = detail::file_options_builder<detail::pipe_options_builder>;

    namespace detail {

        template<class Derived>
        class base_file {
            using handle_type = typename Derived::handle_type;
            handle_type _handle;

        protected:
            NTW_INLINE ~base_file() = default;

        public:
            NTW_INLINE base_file() = default;
            NTW_INLINE base_file(void* handle) noexcept : _handle(handle) {}

            NTW_INLINE handle_type& handle() noexcept { return _handle; }
            NTW_INLINE const handle_type& handle() const noexcept { return _handle; }

            template<class StringRef /* wstring_view or UNICODE_STRING */>
            NT_FN open(const StringRef&    path,
                       const file_options& options = Derived::options) noexcept;

            template<class StringRef /* wstring_view or UNICODE_STRING */>
            NT_FN open_as_pipe(const StringRef&    path,
                               const pipe_options& options = Derived::pipe_options) noexcept;

            NT_FN size(std::uint64_t& size_out) const noexcept;

            template<class StringRef /* wstring_view or UNICODE_STRING */>
            NT_FN static destroy(const StringRef& path, bool case_sensitive = false) noexcept;
        };

    } // namespace detail

} // namespace ntw::obj

#include "../impl/base_file.inl"
