#include "token.h"
#include "source_location.h"
#include "lexer.h"

#include <sstream>
#include <iomanip>
#include <iostream>
#include <charconv>
#include <string_view>
#include <iterator>


void syntax_error() {
  std::cerr << "Invalid syntex" << std::endl;
  exit(1);
}

int main(int argc, char **argv) {

  if (argc != 2) {
    std::cerr << argv[0] << ": invalid number of arguments" << std::endl;
    return 1;
  }

  const char* buffer{ argv[1] };
  Lexer lexer{ buffer };
  std::ostringstream code;
  size_t counter = 0;  // used for register 

  code << "define i32 @main(i32 %argc, i8** %argv) {\n";
  code << "entry:\n";
  Token token;
  // parse the first token
  lexer.lex(token);
  if (token.getKind() != TokenKind::kNum) {
    syntax_error();
  }
  code << "%" << counter << " = add i32 0, " << token.getValue() << "\n";
  while (lexer.lex(token)) {
    if (token.getKind() != TokenKind::kPunct) {
      syntax_error();
    }
    std::string op_inst{(*token.getStart().getLoc() == '+') ? "add" : "sub"};
    if (!lexer.lex(token) || token.getKind() != TokenKind::kNum) {
      syntax_error();
    }
    int operand{ token.getValue() };
    code << "%" << (counter + 1) << " = " << op_inst << " i32 %" << counter << ", " << operand << "\n";
    counter++;
  }
  code << "ret i32 %" << counter << "\n";
  code << "}\n";
  std::cout << code.str();

  return 0;
}