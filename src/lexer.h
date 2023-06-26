#ifndef LEXER_H
#define LEXER_H

#include "source_location.h"
#include "token.h"

#include <cctype>
#include <sstream>


class InvalidTokenException {
public:
  InvalidTokenException(SourceLocation loc): loc_{loc} {}
  std::string what() {
    std::ostringstream msg;
    msg << "Invalid token: ";
    msg << *loc_.getLoc();
    return msg.str();
  }

private:
  SourceLocation loc_;
};


class Lexer {
public:
  Lexer(const char* buffer): buffer_{buffer}, cursor_{buffer}, curr_loc_{buffer_} {}
  Lexer(const Lexer&) = delete;
  Lexer& operator=(const Lexer&) = delete;

  const char* getBuffer() const;
  SourceLocation getSourceLocation() const;
  const char* getBufferLocation() const;

  /// Lex - Return the next token in the file by `result`.
  /// If this is the end of file, it returns false,
  /// and the kind of `result` will be kEOF.
  /// Will throw InvalidTokenException if parsing invalid token
  bool lex(Token& result);

private:
  const char* const buffer_;
  const char* cursor_;
  SourceLocation curr_loc_;
};

bool Lexer::lex(Token& result) {
  const char* p =cursor_;
  while (*p) {
    // Skip whitespace
    if (std::isspace(*p)) {
      p++;
      continue;
    }

    // Numeric literals
    if (std::isdigit(*p)) {
      char* q = const_cast<char*>(p);  // this is a flaw in C's strtol
      int val = std::strtol(q, &q, 10);
      result = Token(TokenKind::kNum, p, q - p);
      result.setValue(val);
      cursor_ = q;
      return true;
    }

    // Punctuators
    if (*p == '+' || *p == '-') {
      result = Token(TokenKind::kPunct, p, 1);
      p++;
      cursor_ = p;
      return true;
    }

    throw InvalidTokenException(curr_loc_);
  }

  cursor_ = p;
  result = Token(TokenKind::kEOF, p, 0);
  return false;
}

const char *Lexer::getBuffer() const { return buffer_; }

SourceLocation Lexer::getSourceLocation() const { return curr_loc_; }

const char *Lexer::getBufferLocation() const { return cursor_; }

#endif  // LEXER_H
