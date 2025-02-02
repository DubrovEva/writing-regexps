// wr22
#include <wr22/regex_parser/parser/errors.hpp>
#include <wr22/unicode/conversion.hpp>

// fmt
#include <fmt/core.h>
#include <fmt/ostream.h>

namespace wr22::regex_parser::parser::errors {

UnexpectedEnd::UnexpectedEnd(size_t position, std::string expected)
    : ParseError(
        fmt::format("Unexpected end of input at position {}: expected {}", position, expected)),
      m_position(position), m_expected(std::move(expected)) {}

size_t UnexpectedEnd::position() const {
    return m_position;
}

const std::string& UnexpectedEnd::expected() const {
    return m_expected;
}

ExpectedEnd::ExpectedEnd(size_t position, char32_t char_got)
    : ParseError(fmt::format(
        "Expected the input to end at position {}, but got the character `{}` (U+{:x})",
        position,
        wr22::unicode::to_utf8(char_got),
        static_cast<uint32_t>(char_got))),
      m_position(position), m_char_got(char_got) {}

size_t ExpectedEnd::position() const {
    return m_position;
}

char32_t ExpectedEnd::char_got() const {
    return m_char_got;
}

UnexpectedChar::UnexpectedChar(size_t position, char32_t char_got, std::string expected)
    : ParseError(fmt::format(
        "Expected {}, but got the character `{}` (U+{:x}) at position {}",
        expected,
        wr22::unicode::to_utf8(char_got),
        static_cast<uint32_t>(char_got),
        position)),
      m_position(position), m_char_got(char_got), m_expected(std::move(expected)) {}

size_t UnexpectedChar::position() const {
    return m_position;
}

char32_t UnexpectedChar::char_got() const {
    return m_char_got;
}

const std::string& UnexpectedChar::expected() const {
    return m_expected;
}

InvalidRange::InvalidRange(span::Span span, char32_t first, char32_t last)
    : ParseError(fmt::format(
        FMT_STRING("Invalid character range `{}..{}` at {}"),
        wr22::unicode::to_utf8(first),
        wr22::unicode::to_utf8(last),
        span)),
      m_span(span), m_first(first), m_last(last) {}

span::Span InvalidRange::span() const {
    return m_span;
}

char32_t InvalidRange::first() const {
    return m_first;
}

char32_t InvalidRange::last() const {
    return m_last;
}

}  // namespace wr22::regex_parser::parser::errors
