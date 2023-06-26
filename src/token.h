#ifndef TOKEN_H
#define TOKEN_H

#include "source_location.h"

enum class TokenKind {
  kPunct, // Punctuators
  kNum,   // Numeric literals
  kEOF,   // EOF
  kUnknown
};


class Token {
public:
  Token() = default;
  Token(TokenKind kind, SourceLocation start_loc, int length);

  SourceLocation getStart() const;
  SourceLocation getEnd() const;
  int getLength() const;
  TokenKind getKind() const;
  int getValue() const;
  void setValue(int val);

private:
  TokenKind kind_ = TokenKind::kUnknown;
  SourceLocation start_ = nullptr;
  SourceLocation end_ = nullptr;
  int length_ = 0; // token length

  int value_ = 0; // hold the value if token kind is kNum
};


Token::Token(TokenKind kind, SourceLocation start_loc, int length) :
  kind_{ kind }, start_{ start_loc }, length_{ length }, end_{ start_loc.getLoc() + length } {}

SourceLocation Token::getStart() const { return start_; }

SourceLocation Token::getEnd() const { return end_; }

int Token::getLength() const { return length_; }

TokenKind Token::getKind() const {
  return kind_;
}

int Token::getValue() const {
  return value_;
}

void Token::setValue(int val) {
  value_ = val;
}

#endif  // TOKEN_H