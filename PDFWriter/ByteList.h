#pragma once

#include "IOBasicTypes.h"

#include <string>

typedef std::basic_string<IOBasicTypes::Byte> ByteList;


ByteList stringToByteList(const std::string& inString);
ByteList substr(const ByteList& inList, IOBasicTypes::LongBufferSizeType inStart, IOBasicTypes::LongBufferSizeType inLength);
void append(ByteList& ioTargetList, const ByteList& inSource);
ByteList concat(const ByteList& inA, const ByteList& inB);
std::string ByteListToString(const ByteList& inByteList);

namespace std {
    template <>
    struct char_traits<IOBasicTypes::Byte> {
        using char_type = IOBasicTypes::Byte;
        using int_type = int;
        using off_type = std::streamoff;
        using pos_type = std::streampos;
        using state_type = std::mbstate_t;

        static constexpr void assign(char_type& r, const char_type& a) noexcept {
            r = a;
        }

        static constexpr bool eq(const char_type& c1, const char_type& c2) noexcept {
            return c1 == c2;
        }

        static constexpr bool lt(const char_type& c1, const char_type& c2) noexcept {
            return c1 < c2; // Example: compare based on underlying char
        }

        static constexpr int compare(const char_type* s1, const char_type* s2, size_t n) noexcept {
            for (size_t i = 0; i < n; ++i) {
                if (lt(s1[i], s2[i])) return -1;
                if (lt(s2[i], s1[i])) return 1;
            }
            return 0;
        }

        static constexpr size_t length(const char_type* s) noexcept {
            size_t len = 0;
            while (s[len] != '\0') { // Assuming null terminator for MyChar
                ++len;
            }
            return len;
        }

        static constexpr const char_type* find(const char_type* s, size_t n, const char_type& a) noexcept {
            for (size_t i = 0; i < n; ++i) {
                if (eq(s[i], a)) return s + i;
            }
            return nullptr;
        }

        static constexpr char_type* move(char_type* dest, const char_type* src, size_t count) noexcept {
            return static_cast<char_type*>(memmove(dest, src, count * sizeof(char_type)));
        }

        static constexpr char_type* copy(char_type* dest, const char_type* src, size_t count) noexcept {
            return static_cast<char_type*>(memcpy(dest, src, count * sizeof(char_type)));
        }

        static constexpr char_type* assign(char_type* s, size_t n, char_type a) noexcept {
            for (size_t i = 0; i < n; ++i) {
                s[i] = a;
            }
            return s;
        }

        static constexpr int_type eof() noexcept { return EOF; }
        static constexpr int_type not_eof(int_type c) noexcept { return c != eof() && c; }
        static constexpr int_type to_int_type(const char_type& c) noexcept { return static_cast<int_type>(c); }
        static constexpr char_type to_char_type(int_type c) noexcept { return IOBasicTypes::Byte{static_cast<char_type >(c)}; }
    };
} // namespace std

