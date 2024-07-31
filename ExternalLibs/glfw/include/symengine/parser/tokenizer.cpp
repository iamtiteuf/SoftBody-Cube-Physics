/* Generated by re2c 3.0 */
#line 1 "tokenizer.re"
#include "tokenizer.h"

#include "parser.tab.hh"

namespace SymEngine
{

void Tokenizer::set_string(const std::string &str)
{
    // The input string must be NULL terminated, otherwise the tokenizer will
    // not detect the end of string. After C++11, the std::string is guaranteed
    // to end with \0, but we check this here just in case.
    SYMENGINE_ASSERT(str[str.size()] == '\0');
    cur = (unsigned char *)(&str[0]);
}

int Tokenizer::lex(yy::parser::semantic_type *yylval)
{
    for (;;) {
        tok = cur;

#line 25 "tokenizer.cpp"
        {
            unsigned char yych;
            static const unsigned char yybm[] = {
                0,   0,   0,   0,   0,   0,   0,   0,   0,   32,  32,  32,  0,
                32,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
                0,   0,   0,   0,   0,   0,   32,  0,   0,   0,   0,   0,   0,
                0,   0,   0,   0,   0,   0,   0,   0,   0,   192, 192, 192, 192,
                192, 192, 192, 192, 192, 192, 0,   0,   0,   0,   0,   0,   0,
                128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128,
                128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128,
                0,   0,   0,   0,   128, 0,   128, 128, 128, 128, 128, 128, 128,
                128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128,
                128, 128, 128, 128, 128, 128, 0,   0,   0,   0,   0,   128, 128,
                128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128,
                128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128,
                128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128,
                128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128,
                128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128,
                128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128,
                128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128,
                128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128,
                128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128,
                128, 128, 128, 128, 128, 128, 128, 128, 128,
            };
            yych = *cur;
            if (yybm[0 + yych] & 32) {
                goto yy4;
            }
            if (yych <= '>') {
                if (yych <= '*') {
                    if (yych <= '%') {
                        if (yych <= 0x00)
                            goto yy1;
                        if (yych <= 0x1F)
                            goto yy2;
                        if (yych <= '!')
                            goto yy5;
                        goto yy2;
                    } else {
                        if (yych == '\'')
                            goto yy2;
                        if (yych <= ')')
                            goto yy6;
                        goto yy8;
                    }
                } else {
                    if (yych <= '9') {
                        if (yych == '.')
                            goto yy9;
                        if (yych <= '/')
                            goto yy6;
                        goto yy10;
                    } else {
                        if (yych <= ';')
                            goto yy2;
                        if (yych <= '<')
                            goto yy12;
                        if (yych <= '=')
                            goto yy13;
                        goto yy14;
                    }
                }
            } else {
                if (yych <= '_') {
                    if (yych <= 'P') {
                        if (yych <= '?')
                            goto yy2;
                        if (yych <= '@')
                            goto yy15;
                        if (yych <= 'O')
                            goto yy16;
                        goto yy18;
                    } else {
                        if (yych <= 'Z')
                            goto yy16;
                        if (yych <= ']')
                            goto yy2;
                        if (yych <= '^')
                            goto yy6;
                        goto yy16;
                    }
                } else {
                    if (yych <= '|') {
                        if (yych <= '`')
                            goto yy2;
                        if (yych <= 'z')
                            goto yy16;
                        if (yych <= '{')
                            goto yy2;
                        goto yy6;
                    } else {
                        if (yych == '~')
                            goto yy6;
                        if (yych <= 0x7F)
                            goto yy2;
                        goto yy16;
                    }
                }
            }
        yy1:
            ++cur;
#line 44 "tokenizer.re"
            {
                return yy::parser::token::yytokentype::END_OF_FILE;
            }
#line 120 "tokenizer.cpp"
        yy2:
            ++cur;
        yy3 :
#line 43 "tokenizer.re"
        {
            throw SymEngine::ParseError("Unknown token: '" + token() + "'");
        }
#line 126 "tokenizer.cpp"
        yy4:
            yych = *++cur;
            if (yybm[0 + yych] & 32) {
                goto yy4;
            }
#line 45 "tokenizer.re"
            {
                continue;
            }
#line 134 "tokenizer.cpp"
        yy5:
            yych = *++cur;
            if (yych == '=')
                goto yy19;
            goto yy3;
        yy6:
            ++cur;
        yy7 :
#line 48 "tokenizer.re"
        {
            return tok[0];
        }
#line 144 "tokenizer.cpp"
        yy8:
            yych = *++cur;
            if (yych == '*')
                goto yy15;
            goto yy7;
        yy9:
            yych = *++cur;
            if (yych <= '/')
                goto yy3;
            if (yych <= '9')
                goto yy20;
            goto yy3;
        yy10:
            yych = *++cur;
            if (yybm[0 + yych] & 64) {
                goto yy10;
            }
            if (yych <= '^') {
                if (yych <= '@') {
                    if (yych == '.')
                        goto yy22;
                } else {
                    if (yych == 'E')
                        goto yy26;
                    if (yych <= 'Z')
                        goto yy23;
                }
            } else {
                if (yych <= 'd') {
                    if (yych != '`')
                        goto yy23;
                } else {
                    if (yych <= 'e')
                        goto yy26;
                    if (yych <= 'z')
                        goto yy23;
                    if (yych >= 0x80)
                        goto yy23;
                }
            }
        yy11 :
#line 56 "tokenizer.re"
        {
            yylval->emplace<std::string>() = token();
            return yy::parser::token::yytokentype::NUMERIC;
        }
#line 178 "tokenizer.cpp"
        yy12:
            yych = *++cur;
            if (yych == '=')
                goto yy27;
            goto yy7;
        yy13:
            yych = *++cur;
            if (yych == '=')
                goto yy28;
            goto yy3;
        yy14:
            yych = *++cur;
            if (yych == '=')
                goto yy29;
            goto yy7;
        yy15:
            ++cur;
#line 49 "tokenizer.re"
            {
                return yy::parser::token::yytokentype::POW;
            }
#line 195 "tokenizer.cpp"
        yy16:
            yych = *++cur;
        yy17:
            if (yybm[0 + yych] & 128) {
                goto yy16;
            }
#line 55 "tokenizer.re"
            {
                yylval->emplace<std::string>() = token();
                return yy::parser::token::yytokentype::IDENTIFIER;
            }
#line 204 "tokenizer.cpp"
        yy18:
            yych = *++cur;
            if (yych == 'i')
                goto yy30;
            goto yy17;
        yy19:
            ++cur;
#line 52 "tokenizer.re"
            {
                return yy::parser::token::yytokentype::NE;
            }
#line 213 "tokenizer.cpp"
        yy20:
            yych = *++cur;
        yy21:
            if (yych <= '^') {
                if (yych <= '@') {
                    if (yych <= '/')
                        goto yy11;
                    if (yych <= '9')
                        goto yy20;
                    goto yy11;
                } else {
                    if (yych == 'E')
                        goto yy26;
                    if (yych <= 'Z')
                        goto yy23;
                    goto yy11;
                }
            } else {
                if (yych <= 'd') {
                    if (yych == '`')
                        goto yy11;
                    goto yy23;
                } else {
                    if (yych <= 'e')
                        goto yy26;
                    if (yych <= 'z')
                        goto yy23;
                    if (yych <= 0x7F)
                        goto yy11;
                    goto yy23;
                }
            }
        yy22:
            yych = *++cur;
            if (yych == 'E')
                goto yy23;
            if (yych != 'e')
                goto yy21;
        yy23:
            yych = *++cur;
        yy24:
            if (yych <= '^') {
                if (yych <= '9') {
                    if (yych >= '0')
                        goto yy23;
                } else {
                    if (yych <= '@')
                        goto yy25;
                    if (yych <= 'Z')
                        goto yy23;
                }
            } else {
                if (yych <= '`') {
                    if (yych <= '_')
                        goto yy23;
                } else {
                    if (yych <= 'z')
                        goto yy23;
                    if (yych >= 0x80)
                        goto yy23;
                }
            }
        yy25 :
#line 57 "tokenizer.re"
        {
            yylval->emplace<std::string>() = token();
            return yy::parser::token::yytokentype::IMPLICIT_MUL;
        }
#line 263 "tokenizer.cpp"
        yy26:
            yych = *(mar = ++cur);
            if (yych <= ',') {
                if (yych == '+')
                    goto yy31;
                goto yy24;
            } else {
                if (yych <= '-')
                    goto yy31;
                if (yych <= '/')
                    goto yy24;
                if (yych <= '9')
                    goto yy33;
                goto yy24;
            }
        yy27:
            ++cur;
#line 50 "tokenizer.re"
            {
                return yy::parser::token::yytokentype::LE;
            }
#line 279 "tokenizer.cpp"
        yy28:
            ++cur;
#line 53 "tokenizer.re"
            {
                return yy::parser::token::yytokentype::EQ;
            }
#line 284 "tokenizer.cpp"
        yy29:
            ++cur;
#line 51 "tokenizer.re"
            {
                return yy::parser::token::yytokentype::GE;
            }
#line 289 "tokenizer.cpp"
        yy30:
            yych = *++cur;
            if (yych == 'e')
                goto yy34;
            goto yy17;
        yy31:
            yych = *++cur;
            if (yych <= '/')
                goto yy32;
            if (yych <= '9')
                goto yy33;
        yy32:
            cur = mar;
            goto yy25;
        yy33:
            yych = *++cur;
            if (yych <= '^') {
                if (yych <= '9') {
                    if (yych <= '/')
                        goto yy11;
                    goto yy33;
                } else {
                    if (yych <= '@')
                        goto yy11;
                    if (yych <= 'Z')
                        goto yy23;
                    goto yy11;
                }
            } else {
                if (yych <= '`') {
                    if (yych <= '_')
                        goto yy23;
                    goto yy11;
                } else {
                    if (yych <= 'z')
                        goto yy23;
                    if (yych <= 0x7F)
                        goto yy11;
                    goto yy23;
                }
            }
        yy34:
            yych = *++cur;
            if (yych != 'c')
                goto yy17;
            yych = *++cur;
            if (yych != 'e')
                goto yy17;
            yych = *++cur;
            if (yych != 'w')
                goto yy17;
            yych = *++cur;
            if (yych != 'i')
                goto yy17;
            yych = *++cur;
            if (yych != 's')
                goto yy17;
            yych = *++cur;
            if (yych != 'e')
                goto yy17;
            yych = *++cur;
            if (yybm[0 + yych] & 128) {
                goto yy16;
            }
#line 54 "tokenizer.re"
            {
                yylval->emplace<std::string>() = token();
                return yy::parser::token::yytokentype::PIECEWISE;
            }
#line 341 "tokenizer.cpp"
        }
#line 58 "tokenizer.re"
    }
}

} // namespace SymEngine
