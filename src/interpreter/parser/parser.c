/*
** 2000-05-29
**
** The author disclaims copyright to this source code.  In place of
** a legal notice, here is a blessing:
**
**    May you do good and not evil.
**    May you find forgiveness for yourself and forgive others.
**    May you share freely, never taking more than you give.
**
*************************************************************************
** Driver template for the LEMON parser generator.
**
** The "lemon" program processes an LALR(1) input grammar file, then uses
** this template to construct a parser.  The "lemon" program inserts text
** at each "%%" line.  Also, any "P-a-r-s-e" identifer prefix (without the
** interstitial "-" characters) contained in this template is changed into
** the value of the %name directive from the grammar.  Otherwise, the content
** of this template is copied straight through into the generate parser
** source file.
**
** The following is the concatenation of all %include directives from the
** input grammar file:
*/
#include <stdio.h>
<<<<<<< HEAD:src/interpreter/parser/parser.c
#line 19 "parser.y"

#include "parser.h"
#include <iostream>
#include <string>
#include <list>
#include <assert.h>
#include "../Interpreter.h"
#include "../Column.h"
#include "../Action.h"
#include "../Condition.h"
using namespace std;
#line 20 "parser.c"
/* Next is all token values, in a form suitable for use by makeheaders.
** This section will be null unless lemon is run with the -m switch.
*/
/* 
** These constants (all generated automatically by the parser generator)
** specify the various kinds of tokens (terminals) that the parser
** understands. 
**
** Each symbol here is a terminal symbol in the grammar.
*/
/* Make sure the INTERFACE macro is defined.
*/
#ifndef INTERFACE
# define INTERFACE 1
#endif
/* The next thing included is series of defines which control
=======
/************ Begin %include sections from the grammar ************************/
#line 26 "parse.y"

#include "parse.h"
#include "miniSqlDef.h"
#include <assert.h>
#line 33 "parse.c"
/**************** End of %include directives **********************************/
/* These constants specify the various numeric values for terminal symbols
** in a format understandable to "makeheaders".  This section is blank unless
** "lemon" is run with the "-m" command-line option.
***************** Begin makeheaders token definitions *************************/
/**************** End makeheaders token definitions ***************************/

/* The next sections is a series of control #defines.
>>>>>>> c4ae7a9abd3ac49f353fba788979c4bffdb3825f:src/interpreter/parser/parse.c
** various aspects of the generated parser.
**    YYCODETYPE         is the data type used to store the integer codes
**                       that represent terminal and non-terminal symbols.
**                       "unsigned char" is used if there are fewer than
**                       256 symbols.  Larger types otherwise.
**    YYNOCODE           is a number of type YYCODETYPE that is not used for
**                       any terminal or nonterminal symbol.
**    YYFALLBACK         If defined, this indicates that one or more tokens
<<<<<<< HEAD:src/interpreter/parser/parser.c
**                       have fall-back values which should be used if the
**                       original value of the token will not parse.
**    YYACTIONTYPE       is the data type used for storing terminal
**                       and nonterminal numbers.  "unsigned char" is
**                       used if there are fewer than 250 rules and
**                       states combined.  "int" is used otherwise.
**    ParserTOKENTYPE     is the data type used for minor tokens given 
**                       directly to the parser from the tokenizer.
**    YYMINORTYPE        is the data type used for all minor tokens.
**                       This is typically a union of many types, one of
**                       which is ParserTOKENTYPE.  The entry in the union
**                       for base tokens is called "yy0".
**    YYSTACKDEPTH       is the maximum depth of the parser's stack.  If
**                       zero the stack is dynamically sized using realloc()
**    ParserARG_SDECL     A static variable declaration for the %extra_argument
**    ParserARG_PDECL     A parameter declaration for the %extra_argument
**    ParserARG_STORE     Code to store %extra_argument into yypParser
**    ParserARG_FETCH     Code to extract %extra_argument from yypParser
**    YYNSTATE           the combined number of states.
**    YYNRULE            the number of rules in the grammar
=======
**                       (also known as: "terminal symbols") have fall-back
**                       values which should be used if the original symbol
**                       would not parse.  This permits keywords to sometimes
**                       be used as identifiers, for example.
**    YYACTIONTYPE       is the data type used for "action codes" - numbers
**                       that indicate what to do in response to the next
**                       token.
**    miniSqlParserTOKENTYPE     is the data type used for minor type for terminal
**                       symbols.  Background: A "minor type" is a semantic
**                       value associated with a terminal or non-terminal
**                       symbols.  For example, for an "ID" terminal symbol,
**                       the minor type might be the name of the identifier.
**                       Each non-terminal can have a different minor type.
**                       Terminal symbols all have the same minor type, though.
**                       This macros defines the minor type for terminal 
**                       symbols.
**    YYMINORTYPE        is the data type used for all minor types.
**                       This is typically a union of many types, one of
**                       which is miniSqlParserTOKENTYPE.  The entry in the union
**                       for terminal symbols is called "yy0".
**    YYSTACKDEPTH       is the maximum depth of the parser's stack.  If
**                       zero the stack is dynamically sized using realloc()
**    miniSqlParserARG_SDECL     A static variable declaration for the %extra_argument
**    miniSqlParserARG_PDECL     A parameter declaration for the %extra_argument
**    miniSqlParserARG_STORE     Code to store %extra_argument into yypParser
**    miniSqlParserARG_FETCH     Code to extract %extra_argument from yypParser
>>>>>>> c4ae7a9abd3ac49f353fba788979c4bffdb3825f:src/interpreter/parser/parse.c
**    YYERRORSYMBOL      is the code number of the error symbol.  If not
**                       defined, then do no error processing.
**    YYNSTATE           the combined number of states.
**    YYNRULE            the number of rules in the grammar
**    YY_MAX_SHIFT       Maximum value for shift actions
**    YY_MIN_SHIFTREDUCE Minimum value for shift-reduce actions
**    YY_MAX_SHIFTREDUCE Maximum value for shift-reduce actions
**    YY_MIN_REDUCE      Maximum value for reduce actions
**    YY_ERROR_ACTION    The yy_action[] code for syntax error
**    YY_ACCEPT_ACTION   The yy_action[] code for accept
**    YY_NO_ACTION       The yy_action[] code for no-op
*/
#ifndef INTERFACE
# define INTERFACE 1
#endif
/************* Begin control #defines *****************************************/
#define YYCODETYPE unsigned char
<<<<<<< HEAD:src/interpreter/parser/parser.c
#define YYNOCODE 73
=======
#define YYNOCODE 72
>>>>>>> c4ae7a9abd3ac49f353fba788979c4bffdb3825f:src/interpreter/parser/parse.c
#define YYACTIONTYPE unsigned char
#define ParserTOKENTYPE const string *
typedef union {
  int yyinit;
<<<<<<< HEAD:src/interpreter/parser/parser.c
  ParserTOKENTYPE yy0;
  Constraint::Type yy12;
  Condition::Type yy46;
  Condition * yy82;
  Column::Type yy109;
=======
  miniSqlParserTOKENTYPE yy0;
  SrcList* yy5;
  NameList* yy52;
  int yy136;
>>>>>>> c4ae7a9abd3ac49f353fba788979c4bffdb3825f:src/interpreter/parser/parse.c
} YYMINORTYPE;
#ifndef YYSTACKDEPTH
#define YYSTACKDEPTH 100
#endif
<<<<<<< HEAD:src/interpreter/parser/parser.c
#define ParserARG_SDECL Interpreter *interpreter;
#define ParserARG_PDECL ,Interpreter *interpreter
#define ParserARG_FETCH Interpreter *interpreter = yypParser->interpreter
#define ParserARG_STORE yypParser->interpreter = interpreter
#define YYNSTATE 135
#define YYNRULE 73
#define YY_NO_ACTION      (YYNSTATE+YYNRULE+2)
#define YY_ACCEPT_ACTION  (YYNSTATE+YYNRULE+1)
#define YY_ERROR_ACTION   (YYNSTATE+YYNRULE)

/* The yyzerominor constant is used to initialize instances of
** YYMINORTYPE objects to zero. */
static const YYMINORTYPE yyzerominor = { 0 };
=======
#define miniSqlParserARG_SDECL Parser *pParser;
#define miniSqlParserARG_PDECL ,Parser *pParser
#define miniSqlParserARG_FETCH Parser *pParser = yypParser->pParser
#define miniSqlParserARG_STORE yypParser->pParser = pParser
#define YYNSTATE             121
#define YYNRULE              60
#define YY_MAX_SHIFT         120
#define YY_MIN_SHIFTREDUCE   121
#define YY_MAX_SHIFTREDUCE   180
#define YY_MIN_REDUCE        181
#define YY_MAX_REDUCE        240
#define YY_ERROR_ACTION      241
#define YY_ACCEPT_ACTION     242
#define YY_NO_ACTION         243
/************* End control #defines *******************************************/
>>>>>>> c4ae7a9abd3ac49f353fba788979c4bffdb3825f:src/interpreter/parser/parse.c

/* Define the yytestcase() macro to be a no-op if is not already defined
** otherwise.
**
** Applications can choose to define yytestcase() in the %include section
** to a macro that can assist in verifying code coverage.  For production
** code the yytestcase() macro should be turned off.  But it is useful
** for testing.
*/
#ifndef yytestcase
# define yytestcase(X)
#endif


/* Next are the tables used to determine what action to take based on the
** current state and lookahead token.  These tables are used to implement
** functions that take a state number and lookahead value and return an
** action integer.  
**
** Suppose the action integer is N.  Then the action is determined as
** follows
**
**   0 <= N <= YY_MAX_SHIFT             Shift N.  That is, push the lookahead
**                                      token onto the stack and goto state N.
**
**   N between YY_MIN_SHIFTREDUCE       Shift to an arbitrary state then
**     and YY_MAX_SHIFTREDUCE           reduce by rule N-YY_MIN_SHIFTREDUCE.
**
**   N between YY_MIN_REDUCE            Reduce by rule N-YY_MIN_REDUCE
**     and YY_MAX_REDUCE
**
**   N == YY_ERROR_ACTION               A syntax error has occurred.
**
**   N == YY_ACCEPT_ACTION              The parser accepts its input.
**
**   N == YY_NO_ACTION                  No such action.  Denotes unused
**                                      slots in the yy_action[] table.
**
** The action table is constructed as a single large table named yy_action[].
** Given state S and lookahead X, the action is computed as either:
**
**    (A)   N = yy_action[ yy_shift_ofst[S] + X ]
**    (B)   N = yy_default[S]
**
** The (A) formula is preferred.  The B formula is used instead if:
**    (1)  The yy_shift_ofst[S]+X value is out of range, or
**    (2)  yy_lookahead[yy_shift_ofst[S]+X] is not equal to X, or
**    (3)  yy_shift_ofst[S] equal YY_SHIFT_USE_DFLT.
** (Implementation note: YY_SHIFT_USE_DFLT is chosen so that
** YY_SHIFT_USE_DFLT+X will be out of range for all possible lookaheads X.
** Hence only tests (1) and (2) need to be evaluated.)
**
** The formulas above are for computing the action when the lookahead is
** a terminal symbol.  If the lookahead is a non-terminal (as occurs after
** a reduce action) then the yy_reduce_ofst[] array is used in place of
** the yy_shift_ofst[] array and YY_REDUCE_USE_DFLT is used in place of
** YY_SHIFT_USE_DFLT.
**
** The following are the tables generated in this section:
**
**  yy_action[]        A single table containing all actions.
**  yy_lookahead[]     A table containing the lookahead for each entry in
**                     yy_action.  Used to detect hash collisions.
**  yy_shift_ofst[]    For each state, the offset into yy_action for
**                     shifting terminals.
**  yy_reduce_ofst[]   For each state, the offset into yy_action for
**                     shifting non-terminals after a reduce.
**  yy_default[]       Default action for each state.
<<<<<<< HEAD:src/interpreter/parser/parser.c
*/
#define YY_ACTTAB_COUNT (217)
static const YYACTIONTYPE yy_action[] = {
 /*     0 */    99,   17,   15,   13,   12,   11,   10,    9,    8,   17,
 /*    10 */    15,   13,   12,   11,   10,   17,   15,   13,   12,   11,
 /*    20 */    10,    9,    8,   17,   15,   13,   12,   11,   10,    9,
 /*    30 */   208,  208,  208,  208,  208,  208,  135,  130,   61,  209,
 /*    40 */     2,   81,   80,  132,   45,   16,  127,  129,   30,   42,
 /*    50 */   101,   59,   28,   76,   61,  121,   74,  114,  133,  100,
 /*    60 */    14,   39,  124,   77,    3,  122,   34,   59,   75,   44,
 /*    70 */    63,  113,   30,   94,   67,  117,   28,   62,  115,   66,
 /*    80 */     3,   41,   34,   94,   67,   58,   63,   47,  134,   80,
 /*    90 */   132,   45,   92,   38,   29,   87,   60,  107,  109,    5,
 /*   100 */    86,   43,   95,   73,   88,   70,  121,   72,  116,   24,
 /*   110 */   108,   23,   90,   27,  123,   78,  117,  126,   57,  118,
 /*   120 */    26,   73,   22,   70,  110,  109,   96,   64,   84,   82,
 /*   130 */   103,   35,   97,  103,  119,   66,    7,   66,   66,    6,
 /*   140 */    66,   18,   66,   49,   19,   46,   50,   66,   56,   66,
 /*   150 */    55,   66,   66,   66,   40,   54,  121,   53,   37,   52,
 /*   160 */    51,   48,   36,   32,   21,   31,  131,    4,   79,   71,
 /*   170 */     1,  112,  121,  111,   25,   93,   69,  105,   33,   68,
 /*   180 */   104,  102,  106,   98,   83,   65,   91,   18,   20,  128,
 /*   190 */   210,  210,  210,  210,  210,  210,  210,  210,  210,   89,
 /*   200 */   125,  210,  120,  210,  210,  210,  210,  210,  210,  210,
 /*   210 */   210,  210,  210,  210,  210,  210,   85,
};
static const YYCODETYPE yy_lookahead[] = {
 /*     0 */     5,   20,   21,   22,   23,   24,   25,   26,   27,   20,
 /*    10 */    21,   22,   23,   24,   25,   20,   21,   22,   23,   24,
 /*    20 */    25,   26,   27,   20,   21,   22,   23,   24,   25,   26,
 /*    30 */    20,   21,   22,   23,   24,   25,    0,    5,    2,   38,
 /*    40 */    39,   40,   41,   42,   43,    4,   12,   48,   49,    3,
 /*    50 */     9,   15,   53,    4,    2,   14,   57,   58,    1,   18,
 /*    60 */    19,    3,    7,    8,   28,   10,   30,   15,    9,   46,
 /*    70 */    34,   48,   49,   52,   53,   53,   53,   55,   56,   53,
 /*    80 */    28,   35,   30,   52,   53,   64,   34,   61,   40,   41,
 /*    90 */    42,   43,   71,   35,    6,    9,   51,   52,   53,    6,
 /*   100 */    14,    4,   71,   11,   18,   13,   14,   12,    5,    6,
 /*   110 */     5,    6,    5,    6,    5,   11,   53,   13,   68,   56,
 /*   120 */    70,   11,   29,   13,   52,   53,   45,   66,   67,   59,
 /*   130 */    60,    6,   59,   60,    5,   53,    4,   53,   53,    4,
 /*   140 */    53,   16,   53,   61,   63,   61,   61,   53,   61,   53,
 /*   150 */    61,   53,   53,   53,   36,   61,   14,   61,   17,   61,
 /*   160 */    61,   61,   17,    6,   31,   29,   44,    4,   47,   53,
 /*   170 */     6,   45,   14,   14,    4,   33,   53,   53,   65,   45,
 /*   180 */    53,   53,   45,   45,   32,   45,   67,   16,   45,   50,
 /*   190 */    72,   72,   72,   72,   72,   72,   72,   72,   72,   69,
 /*   200 */    54,   72,   58,   72,   72,   72,   72,   72,   72,   72,
 /*   210 */    72,   72,   72,   72,   72,   72,   69,
};
#define YY_SHIFT_USE_DFLT (-20)
#define YY_SHIFT_COUNT (80)
#define YY_SHIFT_MIN   (-19)
#define YY_SHIFT_MAX   (171)
static const short yy_shift_ofst[] = {
 /*     0 */    52,   92,   36,  142,  158,  158,  158,  158,   41,   41,
 /*    10 */    41,   41,   41,   41,   41,   41,   41,   41,   41,  125,
 /*    20 */   171,  170,  159,  158,  158,  -20,   86,   86,   55,  110,
 /*    30 */   104,  159,  170,  159,  152,  159,  158,  158,  158,  159,
 /*    40 */   159,  158,  159,  158,  164,  163,   -5,  -19,    3,   10,
 /*    50 */    10,  -11,   10,   10,   10,   10,  -11,  107,   93,   58,
 /*    60 */   105,   46,  103,  136,  157,  133,  145,  141,  135,  118,
 /*    70 */   132,  129,   97,   95,   88,  109,   59,   49,   34,   32,
 /*    80 */    57,
};
#define YY_REDUCE_USE_DFLT (-2)
#define YY_REDUCE_COUNT (45)
#define YY_REDUCE_MIN   (-1)
#define YY_REDUCE_MAX   (147)
static const short yy_reduce_ofst[] = {
 /*     0 */     1,   -1,   48,   21,   23,   31,   45,   22,  100,   99,
 /*    10 */    98,   96,   94,   89,   87,   85,   84,   82,   26,   73,
 /*    20 */    70,   61,   81,   72,   63,   50,  147,  130,  146,  144,
 /*    30 */   139,  143,  119,  140,  113,  138,  128,  127,  124,  137,
 /*    40 */   134,  123,  126,  116,  121,  122,
};
static const YYACTIONTYPE yy_default[] = {
 /*     0 */   208,  208,  208,  208,  208,  208,  208,  208,  208,  208,
 /*    10 */   208,  208,  208,  208,  208,  208,  208,  208,  208,  167,
 /*    20 */   167,  208,  208,  208,  208,  199,  208,  208,  208,  208,
 /*    30 */   153,  208,  208,  208,  189,  208,  208,  208,  208,  208,
 /*    40 */   208,  208,  208,  208,  160,  208,  208,  169,  183,  176,
 /*    50 */   177,  182,  181,  180,  179,  178,  175,  208,  208,  208,
 /*    60 */   208,  208,  208,  208,  188,  208,  171,  148,  208,  208,
 /*    70 */   208,  208,  208,  208,  161,  208,  208,  208,  208,  208,
 /*    80 */   208,  137,  205,  190,  192,  195,  198,  197,  196,  194,
 /*    90 */   193,  191,  202,  200,  204,  201,  186,  187,  185,  174,
 /*   100 */   173,  172,  170,  168,  203,  207,  166,  147,  206,  148,
 /*   110 */   146,  184,  141,  144,  163,  158,  165,  159,  157,  164,
 /*   120 */   162,  156,  152,  151,  150,  149,  155,  154,  145,  143,
 /*   130 */   142,  140,  139,  138,  136,
=======
**
*********** Begin parsing tables **********************************************/
#define YY_ACTTAB_COUNT (491)
static const YYACTIONTYPE yy_action[] = {
 /*     0 */   208,  186,   52,  208,  208,   10,  208,   47,  208,   46,
 /*    10 */   208,  208,  208,  208,   46,  208,   89,  208,   88,  208,
 /*    20 */   208,  208,  208,  208,  208,  208,  208,  208,  208,   95,
 /*    30 */    85,   96,   68,  208,  111,  209,  108,   46,  209,  209,
 /*    40 */   208,  209,   99,    3,    7,    6,    6,    6,    6,    5,
 /*    50 */     5,   59,   42,  187,  209,  209,  209,  209,  209,  209,
 /*    60 */   209,  209,  209,  209,  224,  204,   67,   94,   96,  204,
 /*    70 */   224,   62,  114,   60,  204,  209,  204,  210,   69,   65,
 /*    80 */   210,  210,   67,  210,  224,  224,  224,  224,  224,  224,
 /*    90 */   224,  224,  224,    4,   73,   66,  210,  210,  210,  210,
 /*   100 */   210,  210,  210,  210,  210,  210,  225,   57,  120,  119,
 /*   110 */    45,   41,  225,   34,   63,   33,   51,  210,  111,  190,
 /*   120 */   108,   19,   75,   46,   64,  190,  225,  225,    6,    6,
 /*   130 */     6,    6,  225,  225,  225,   84,   53,   50,   49,  190,
 /*   140 */   190,    6,    6,    6,    6,  190,  190,  190,  230,   91,
 /*   150 */    52,   13,  230,   43,  230,   47,   47,  242,    1,   55,
 /*   160 */   120,  119,   45,   27,   54,   75,  219,   71,  230,  230,
 /*   170 */   230,  230,  230,  230,  230,  230,  230,  229,  106,   52,
 /*   180 */    75,  229,   78,  229,   47,    9,   92,  192,   20,  181,
 /*   190 */    97,   47,   32,   54,  192,   47,  235,  229,  229,  229,
 /*   200 */   229,  229,  229,  229,  229,  229,  228,  192,  192,  192,
 /*   210 */   228,   23,  228,   35,   24,   33,  191,  236,   81,   74,
 /*   220 */   102,  235,  234,  191,  117,   47,  228,  228,  228,  228,
 /*   230 */   228,  228,  228,  228,  228,  227,  191,  191,  191,  227,
 /*   240 */    52,  227,  236,  100,  103,   47,  107,  234,   47,   47,
 /*   250 */    80,   47,  233,   28,   54,  227,  227,  227,  227,  227,
 /*   260 */   227,  227,  227,  227,  226,  183,   72,   48,  226,  183,
 /*   270 */   226,  207,   77,  109,  115,  207,   82,  233,   12,   14,
 /*   280 */   207,  118,  207,   70,  226,  226,  226,  226,  226,  226,
 /*   290 */   226,  226,  226,  223,   37,  238,   16,   11,  206,   95,
 /*   300 */    93,  237,  206,   86,   15,   90,    2,  206,  101,  206,
 /*   310 */    87,   17,   43,    8,  223,    6,    6,    6,    6,    5,
 /*   320 */     5,   59,  222,  205,  231,   39,   18,  205,   95,  203,
 /*   330 */   232,   36,  205,  203,  205,  202,  189,  215,  203,  202,
 /*   340 */   203,  215,  222,  222,    6,    6,    6,    6,    5,    5,
 /*   350 */    59,  220,   58,   52,  240,  188,   52,   95,   47,  212,
 /*   360 */    98,   47,   38,  212,  217,  218,   26,   54,  217,   29,
 /*   370 */    54,    8,    7,    6,    6,    6,    6,    5,    5,   59,
 /*   380 */   221,  211,  239,   76,   21,  211,  221,   43,   22,  216,
 /*   390 */   182,  214,  213,  216,  199,  214,   40,  104,  105,   25,
 /*   400 */   221,  221,  221,  221,  221,  221,  221,  221,  221,  193,
 /*   410 */   195,   72,  195,  185,  110,  112,  184,  185,   79,   52,
 /*   420 */   184,   44,   52,   61,   47,  200,  201,   47,   70,  195,
 /*   430 */   201,  113,   30,   54,   83,   31,   54,  116,  198,  197,
 /*   440 */    56,  183,   11,  195,  183,   93,  195,  183,   86,  195,
 /*   450 */   196,  194,  196,  194,  183,  183,  183,  183,  183,  183,
 /*   460 */   183,  183,  183,  183,  183,  183,  183,  183,  183,  196,
 /*   470 */   194,  183,  183,  183,  183,  183,  183,  183,  183,  183,
 /*   480 */   183,  183,  183,  196,  194,  183,  196,  194,  183,  196,
 /*   490 */   194,
};
static const YYCODETYPE yy_lookahead[] = {
 /*     0 */     1,    5,   52,    4,    5,    9,    7,   57,    9,   17,
 /*    10 */    11,   12,   13,   14,   17,   16,   66,   18,   68,   20,
 /*    20 */    21,   22,   23,   24,   25,   26,   27,   28,   29,    7,
 /*    30 */    63,   64,   35,   34,   14,    1,   16,   17,    4,    5,
 /*    40 */    41,    7,    6,   21,   22,   23,   24,   25,   26,   27,
 /*    50 */    28,   29,   18,   17,   20,   21,   22,   23,   24,   25,
 /*    60 */    26,   27,   28,   29,    1,    5,   57,   63,   64,    9,
 /*    70 */     7,   11,   12,   13,   14,   41,   16,    1,   69,   70,
 /*    80 */     4,    5,   57,    7,   21,   22,   23,   24,   25,   26,
 /*    90 */    27,   28,   29,   67,   56,   70,   20,   21,   22,   23,
 /*   100 */    24,   25,   26,   27,   28,   29,    1,   46,   47,   48,
 /*   110 */    49,   53,    7,   55,   58,   57,   10,   41,   14,    1,
 /*   120 */    16,   62,   57,   17,   59,    7,   21,   22,   23,   24,
 /*   130 */    25,   26,   27,   28,   29,   56,   30,   31,   32,   21,
 /*   140 */    22,   23,   24,   25,   26,   27,   28,   29,    1,    5,
 /*   150 */    52,   52,    5,    9,    7,   57,   57,   44,   45,   46,
 /*   160 */    47,   48,   49,   65,   66,   57,    1,   59,   21,   22,
 /*   170 */    23,   24,   25,   26,   27,   28,   29,    1,    6,   52,
 /*   180 */    57,    5,   59,    7,   57,   20,   52,   10,   62,   17,
 /*   190 */    52,   57,   65,   66,   17,   57,    9,   21,   22,   23,
 /*   200 */    24,   25,   26,   27,   28,   29,    1,   30,   31,   32,
 /*   210 */     5,   51,    7,   55,   51,   57,   10,    9,   60,   61,
 /*   220 */    52,   34,    9,   17,   54,   57,   21,   22,   23,   24,
 /*   230 */    25,   26,   27,   28,   29,    1,   30,   31,   32,    5,
 /*   240 */    52,    7,   34,   52,   52,   57,   52,   34,   57,   57,
 /*   250 */    61,   57,    9,   65,   66,   21,   22,   23,   24,   25,
 /*   260 */    26,   27,   28,   29,    1,    5,    2,   57,    5,    9,
 /*   270 */     7,    5,   57,   57,   14,    9,   16,   34,    4,    9,
 /*   280 */    14,   50,   16,   19,   21,   22,   23,   24,   25,   26,
 /*   290 */    27,   28,   29,    1,    3,    1,   34,   33,    5,    7,
 /*   300 */    36,    1,    9,   39,   34,   38,    4,   14,    5,   16,
 /*   310 */     5,    4,    9,   21,   22,   23,   24,   25,   26,   27,
 /*   320 */    28,   29,    1,    5,    5,    3,   37,    9,    7,    5,
 /*   330 */     1,   40,   14,    9,   16,    5,    1,    5,   14,    9,
 /*   340 */    16,    9,   21,   22,   23,   24,   25,   26,   27,   28,
 /*   350 */    29,    1,   29,   52,    1,   17,   52,    7,   57,    5,
 /*   360 */     8,   57,   40,    9,    5,    1,   65,   66,    9,   65,
 /*   370 */    66,   21,   22,   23,   24,   25,   26,   27,   28,   29,
 /*   380 */     1,    5,    1,    5,    4,    9,    7,    9,   41,    5,
 /*   390 */    17,    5,    5,    9,    4,    9,    9,    8,    7,    4,
 /*   400 */    21,   22,   23,   24,   25,   26,   27,   28,   29,    0,
 /*   410 */     0,    2,    2,    5,   15,   10,    5,    9,    5,   52,
 /*   420 */     9,    4,   52,    5,   57,    1,    5,   57,   19,   19,
 /*   430 */     9,    4,   65,   66,   15,   65,   66,    5,    1,    1,
 /*   440 */     1,   71,   33,   33,   71,   36,   36,   71,   39,   39,
 /*   450 */     0,    0,    2,    2,   71,   71,   71,   71,   71,   71,
 /*   460 */    71,   71,   71,   71,   71,   71,   71,   71,   71,   19,
 /*   470 */    19,   71,   71,   71,   71,   71,   71,   71,   71,   71,
 /*   480 */    71,   71,   71,   33,   33,   71,   36,   36,   71,   39,
 /*   490 */    39,
};
#define YY_SHIFT_USE_DFLT (491)
#define YY_SHIFT_COUNT    (120)
#define YY_SHIFT_MIN      (-8)
#define YY_SHIFT_MAX      (451)
static const short yy_shift_ofst[] = {
 /*     0 */   264,  409,  106,  106,  106,  106,  106,  106,  106,  106,
 /*    10 */    20,   -3,   -8,  165,   -3,  165,   -8,   -8,   -8,   -8,
 /*    20 */    -8,   -8,   -8,   -8,   -8,   -8,   63,  105,  118,  292,
 /*    30 */   321,  350,   22,   60,  260,  260,   36,   36,  172,  172,
 /*    40 */   104,   -4,   -8,   -8,   -8,  274,   -1,   34,   76,  147,
 /*    50 */   176,  205,  234,  263,  379,  410,  450,  451,  177,  206,
 /*    60 */   266,  293,  318,  324,  144,  187,  208,  213,  243,  270,
 /*    70 */   291,  303,  322,  330,  332,  354,  359,  376,  378,  384,
 /*    80 */   386,  387,  408,  411,  421,  294,  262,  300,  305,  319,
 /*    90 */   302,  267,  307,  289,  329,  323,  335,  353,  338,  352,
 /*   100 */   364,  381,  380,  347,  373,  389,  391,  390,  395,  413,
 /*   110 */   417,  399,  418,  405,  427,  419,  424,  432,  437,  438,
 /*   120 */   439,
};
#define YY_REDUCE_USE_DFLT (-51)
#define YY_REDUCE_COUNT (45)
#define YY_REDUCE_MIN   (-50)
#define YY_REDUCE_MAX   (370)
static const short yy_reduce_ofst[] = {
 /*     0 */   113,   61,  -50,   98,  127,  188,  301,  304,  367,  370,
 /*    10 */   158,    9,   58,  -33,   25,    4,   99,   65,  134,  138,
 /*    20 */   191,  108,  168,  192,  194,  123,   26,   26,   26,   26,
 /*    30 */    26,   26,   26,   56,   38,   79,   59,  126,  160,  163,
 /*    40 */   189,  170,  210,  215,  216,  231,
};
static const YYACTIONTYPE yy_default[] = {
 /*     0 */   241,  241,  241,  241,  241,  241,  241,  241,  241,  241,
 /*    10 */   241,  241,  241,  241,  241,  241,  241,  241,  241,  241,
 /*    20 */   241,  241,  241,  241,  241,  241,  241,  241,  241,  241,
 /*    30 */   241,  241,  241,  241,  241,  241,  241,  241,  241,  241,
 /*    40 */   241,  241,  241,  241,  241,  241,  241,  241,  241,  241,
 /*    50 */   241,  241,  241,  241,  241,  241,  241,  241,  241,  241,
 /*    60 */   241,  241,  241,  241,  241,  241,  241,  241,  241,  241,
 /*    70 */   241,  241,  241,  241,  241,  241,  241,  241,  241,  241,
 /*    80 */   241,  241,  241,  241,  241,  241,  241,  241,  241,  241,
 /*    90 */   241,  241,  241,  241,  241,  241,  241,  241,  241,  241,
 /*   100 */   241,  241,  241,  241,  241,  241,  241,  241,  241,  241,
 /*   110 */   241,  241,  241,  241,  241,  241,  241,  241,  241,  241,
 /*   120 */   241,
>>>>>>> c4ae7a9abd3ac49f353fba788979c4bffdb3825f:src/interpreter/parser/parse.c
};
/********** End of lemon-generated parsing tables *****************************/

/* The next table maps tokens (terminal symbols) into fallback tokens.  
** If a construct like the following:
** 
**      %fallback ID X Y Z.
**
** appears in the grammar, then ID becomes a fallback token for X, Y,
** and Z.  Whenever one of the tokens X, Y, or Z is input to the parser
** but it does not parse, the type of the token is changed to ID and
** the parse is retried before an error is thrown.
**
** This feature can be used, for example, to cause some keywords in a language
** to revert to identifiers if they keyword does not apply in the context where
** it appears.
*/
#ifdef YYFALLBACK
static const YYCODETYPE yyFallback[] = {
};
#endif /* YYFALLBACK */

/* The following structure represents a single element of the
** parser's stack.  Information stored includes:
**
**   +  The state number for the parser at this level of the stack.
**
**   +  The value of the token stored at this level of the stack.
**      (In other words, the "major" token.)
**
**   +  The semantic value stored at this level of the stack.  This is
**      the information used by the action routines in the grammar.
**      It is sometimes called the "minor" token.
**
** After the "shift" half of a SHIFTREDUCE action, the stateno field
** actually contains the reduce action for the second half of the
** SHIFTREDUCE.
*/
struct yyStackEntry {
  YYACTIONTYPE stateno;  /* The state-number, or reduce action in SHIFTREDUCE */
  YYCODETYPE major;      /* The major token value.  This is the code
                         ** number for the token at this stack level */
  YYMINORTYPE minor;     /* The user-supplied minor token value.  This
                         ** is the value of the token  */
};
typedef struct yyStackEntry yyStackEntry;

/* The state of the parser is completely contained in an instance of
** the following structure */
struct yyParser {
  yyStackEntry *yytos;          /* Pointer to top element of the stack */
#ifdef YYTRACKMAXSTACKDEPTH
  int yyhwm;                    /* High-water mark of the stack */
#endif
#ifndef YYNOERRORRECOVERY
  int yyerrcnt;                 /* Shifts left before out of the error */
<<<<<<< HEAD:src/interpreter/parser/parser.c
  ParserARG_SDECL                /* A place to hold %extra_argument */
=======
#endif
  miniSqlParserARG_SDECL                /* A place to hold %extra_argument */
>>>>>>> c4ae7a9abd3ac49f353fba788979c4bffdb3825f:src/interpreter/parser/parse.c
#if YYSTACKDEPTH<=0
  int yystksz;                  /* Current side of the stack */
  yyStackEntry *yystack;        /* The parser's stack */
  yyStackEntry yystk0;          /* First stack entry */
#else
  yyStackEntry yystack[YYSTACKDEPTH];  /* The parser's stack */
#endif
};
typedef struct yyParser yyParser;

#ifndef NDEBUG
#include <stdio.h>
static FILE *yyTraceFILE = 0;
static char *yyTracePrompt = 0;
#endif /* NDEBUG */

#ifndef NDEBUG
/* 
** Turn parser tracing on by giving a stream to which to write the trace
** and a prompt to preface each trace message.  Tracing is turned off
** by making either argument NULL 
**
** Inputs:
** <ul>
** <li> A FILE* to which trace output should be written.
**      If NULL, then tracing is turned off.
** <li> A prefix string written at the beginning of every
**      line of trace output.  If NULL, then tracing is
**      turned off.
** </ul>
**
** Outputs:
** None.
*/
void ParserTrace(FILE *TraceFILE, char *zTracePrompt){
  yyTraceFILE = TraceFILE;
  yyTracePrompt = zTracePrompt;
  if( yyTraceFILE==0 ) yyTracePrompt = 0;
  else if( yyTracePrompt==0 ) yyTraceFILE = 0;
}
#endif /* NDEBUG */

#ifndef NDEBUG
/* For tracing shifts, the names of all terminals and nonterminals
** are required.  The following table supplies these names */
static const char *const yyTokenName[] = { 
  "$",             "SEMICOLON",     "CREATE",        "TABLE",       
<<<<<<< HEAD:src/interpreter/parser/parser.c
  "LP",            "RP",            "COMMA",         "INT_TYPE",    
  "CHAR_TYPE",     "INTEGER",       "FLOAT_TYPE",    "PRIMARY",     
  "KEY",           "UNIQUE",        "STRING",        "DROP",        
  "WHERE",         "DOT",           "FLOAT",         "NOT",         
  "EQ",            "NE",            "LT",            "GT",          
  "LE",            "GE",            "AND",           "OR",          
  "SELECT",        "FROM",          "INSERT",        "VALUES",      
  "INTO",          "TIMES",         "DELETE",        "INDEX",       
  "ON",            "error",         "start",         "cmdList",     
  "cmdAndEnd",     "singlcmd",      "cmd",           "create_table",
  "create_table_args",  "table_name",    "columnlist",    "optional_constraint_list",
  "column_define",  "column",        "column_constraint",  "rawcolumnlist",
  "rawcolumn",     "name",          "type_token",    "unique_list", 
  "unique",        "constraint_list",  "table_constraint",  "opt_where_clause",
  "where_clause",  "expr",          "binary_op",     "table_list",  
  "select_column_list",  "into",          "valueslist",    "values",      
  "valuelist",     "value",         "beginValue",    "full_name",   
=======
  "LP",            "RP",            "IF",            "NOT",         
  "EXISTS",        "COMMA",         "INTEGER",       "INT_TYPE",    
  "CHAR_TYPE",     "FLOAT_TYPE",    "PRIMARY",       "KEY",         
  "UNIQUE",        "ID",            "DOT",           "DROP",        
  "WHERE",         "AND",           "OR",            "LT",          
  "GT",            "GE",            "LE",            "EQ",          
  "NE",            "BETWEEN",       "NULL",          "FLOAT",       
  "STRING",        "SELECT",        "FROM",          "STAR",        
  "INSERT",        "INTO",          "VALUES",        "DELETE",      
  "INDEX",         "ON",            "IS",            "error",       
  "input",         "cmdlist",       "cmd_and_end",   "singlecmd",   
  "cmd",           "create_table",  "create_table_args",  "if_not_exists",
  "full_name",     "columnlist",    "optional_constraint_list",  "column_name", 
  "column_constraint",  "name",          "type_token",    "name_list",   
  "constraint_list",  "table_constraint",  "if_exists",     "opt_where_clause",
  "where_clause",  "expr",          "literal",       "between_op",  
  "literal_list",  "select_column_list",  "select_column",
>>>>>>> c4ae7a9abd3ac49f353fba788979c4bffdb3825f:src/interpreter/parser/parse.c
};
#endif /* NDEBUG */

#ifndef NDEBUG
/* For tracing reduce actions, the names of all rules are required.
*/
static const char *const yyRuleName[] = {
<<<<<<< HEAD:src/interpreter/parser/parser.c
 /*   0 */ "start ::= cmdList",
 /*   1 */ "cmdList ::= cmdList cmdAndEnd",
 /*   2 */ "cmdList ::= cmdAndEnd",
 /*   3 */ "cmdAndEnd ::= singlcmd SEMICOLON",
 /*   4 */ "singlcmd ::= cmd",
 /*   5 */ "cmd ::= create_table create_table_args",
 /*   6 */ "create_table ::= CREATE TABLE table_name",
 /*   7 */ "create_table_args ::= LP columnlist optional_constraint_list RP",
 /*   8 */ "columnlist ::= columnlist COMMA column_define",
 /*   9 */ "columnlist ::= column_define",
 /*  10 */ "column_define ::= column column_constraint",
 /*  11 */ "rawcolumnlist ::= rawcolumnlist COMMA rawcolumn",
 /*  12 */ "rawcolumnlist ::= rawcolumn",
 /*  13 */ "rawcolumn ::= name",
 /*  14 */ "column ::= name type_token",
 /*  15 */ "type_token ::= INT_TYPE",
 /*  16 */ "type_token ::= CHAR_TYPE LP INTEGER RP",
 /*  17 */ "type_token ::= FLOAT_TYPE",
 /*  18 */ "column_constraint ::=",
 /*  19 */ "column_constraint ::= PRIMARY KEY",
 /*  20 */ "column_constraint ::= UNIQUE",
 /*  21 */ "name ::= STRING",
 /*  22 */ "unique_list ::= unique_list COMMA unique",
 /*  23 */ "unique_list ::= unique",
 /*  24 */ "unique ::= name",
 /*  25 */ "optional_constraint_list ::=",
 /*  26 */ "optional_constraint_list ::= COMMA constraint_list",
 /*  27 */ "constraint_list ::= constraint_list COMMA table_constraint",
 /*  28 */ "constraint_list ::= table_constraint",
 /*  29 */ "table_constraint ::= PRIMARY KEY LP name RP",
 /*  30 */ "table_constraint ::= UNIQUE LP unique_list RP",
 /*  31 */ "cmd ::= DROP TABLE table_name",
 /*  32 */ "opt_where_clause ::=",
 /*  33 */ "opt_where_clause ::= where_clause",
 /*  34 */ "where_clause ::= WHERE expr",
 /*  35 */ "expr ::= name DOT name",
 /*  36 */ "expr ::= name",
 /*  37 */ "expr ::= INTEGER",
 /*  38 */ "expr ::= FLOAT",
 /*  39 */ "expr ::= LP expr RP",
 /*  40 */ "expr ::= NOT expr",
 /*  41 */ "expr ::= expr EQ expr",
 /*  42 */ "expr ::= expr NE expr",
 /*  43 */ "expr ::= expr LT expr",
 /*  44 */ "expr ::= expr GT expr",
 /*  45 */ "expr ::= expr LE expr",
 /*  46 */ "expr ::= expr GE expr",
 /*  47 */ "expr ::= expr AND expr",
 /*  48 */ "expr ::= expr OR expr",
 /*  49 */ "table_name ::= STRING",
 /*  50 */ "table_list ::= table_list COMMA table_name",
 /*  51 */ "table_list ::= table_name",
 /*  52 */ "cmd ::= SELECT select_column_list FROM table_list opt_where_clause",
 /*  53 */ "cmd ::= INSERT into table_name VALUES valueslist",
 /*  54 */ "into ::=",
 /*  55 */ "into ::= INTO",
 /*  56 */ "valueslist ::= valueslist COMMA values",
 /*  57 */ "valueslist ::= values",
 /*  58 */ "values ::= LP valuelist RP",
 /*  59 */ "valuelist ::= valuelist COMMA value",
 /*  60 */ "valuelist ::= beginValue value",
 /*  61 */ "value ::= FLOAT",
 /*  62 */ "value ::= INTEGER",
 /*  63 */ "value ::= STRING",
 /*  64 */ "beginValue ::=",
 /*  65 */ "select_column_list ::= TIMES",
 /*  66 */ "select_column_list ::= select_column_list COMMA full_name",
 /*  67 */ "select_column_list ::= full_name",
 /*  68 */ "full_name ::= name DOT name",
 /*  69 */ "full_name ::= rawcolumn",
 /*  70 */ "cmd ::= DELETE FROM table_name opt_where_clause",
 /*  71 */ "cmd ::= CREATE INDEX name ON table_name LP rawcolumnlist RP",
 /*  72 */ "cmd ::= DROP INDEX name",
=======
 /*   0 */ "if_not_exists ::=",
 /*   1 */ "if_not_exists ::= IF NOT EXISTS",
 /*   2 */ "column_constraint ::=",
 /*   3 */ "column_constraint ::= PRIMARY KEY",
 /*   4 */ "column_constraint ::= UNIQUE",
 /*   5 */ "optional_constraint_list ::=",
 /*   6 */ "if_exists ::=",
 /*   7 */ "if_exists ::= IF EXISTS",
 /*   8 */ "opt_where_clause ::= where_clause",
 /*   9 */ "expr ::= expr EQ|NE expr",
 /*  10 */ "between_op ::= BETWEEN",
 /*  11 */ "between_op ::= NOT BETWEEN",
 /*  12 */ "input ::= cmdlist",
 /*  13 */ "cmdlist ::= cmdlist cmd_and_end",
 /*  14 */ "cmdlist ::= cmd_and_end",
 /*  15 */ "cmd_and_end ::= singlecmd SEMICOLON",
 /*  16 */ "singlecmd ::= cmd",
 /*  17 */ "cmd ::= create_table create_table_args",
 /*  18 */ "create_table ::= CREATE TABLE if_not_exists full_name",
 /*  19 */ "create_table_args ::= LP columnlist optional_constraint_list RP",
 /*  20 */ "columnlist ::= columnlist COMMA column_name column_constraint",
 /*  21 */ "columnlist ::= column_name column_constraint",
 /*  22 */ "column_name ::= name type_token",
 /*  23 */ "type_token ::=",
 /*  24 */ "type_token ::= INT_TYPE",
 /*  25 */ "type_token ::= CHAR_TYPE LP INTEGER RP",
 /*  26 */ "type_token ::= FLOAT_TYPE",
 /*  27 */ "name ::= ID",
 /*  28 */ "full_name ::= name",
 /*  29 */ "full_name ::= name DOT name",
 /*  30 */ "name_list ::= name_list COMMA name",
 /*  31 */ "name_list ::= name",
 /*  32 */ "optional_constraint_list ::= COMMA constraint_list",
 /*  33 */ "constraint_list ::= constraint_list COMMA table_constraint",
 /*  34 */ "constraint_list ::= table_constraint",
 /*  35 */ "table_constraint ::= PRIMARY KEY LP name RP",
 /*  36 */ "table_constraint ::= UNIQUE LP name_list RP",
 /*  37 */ "cmd ::= DROP TABLE if_exists full_name",
 /*  38 */ "opt_where_clause ::=",
 /*  39 */ "where_clause ::= WHERE expr",
 /*  40 */ "expr ::= literal",
 /*  41 */ "expr ::= expr AND expr",
 /*  42 */ "expr ::= expr OR expr",
 /*  43 */ "expr ::= expr LT|GT|GE|LE expr",
 /*  44 */ "expr ::= expr between_op expr AND expr",
 /*  45 */ "literal ::= NULL",
 /*  46 */ "literal ::= full_name",
 /*  47 */ "literal ::= INTEGER",
 /*  48 */ "literal ::= FLOAT",
 /*  49 */ "literal ::= STRING",
 /*  50 */ "literal_list ::= literal",
 /*  51 */ "cmd ::= SELECT select_column_list FROM opt_where_clause",
 /*  52 */ "select_column ::= STAR",
 /*  53 */ "select_column ::= name",
 /*  54 */ "select_column_list ::= select_column",
 /*  55 */ "select_column_list ::= select_column_list COMMA select_column",
 /*  56 */ "cmd ::= INSERT INTO full_name LP name_list RP VALUES LP literal_list RP",
 /*  57 */ "cmd ::= DELETE FROM full_name opt_where_clause",
 /*  58 */ "cmd ::= CREATE INDEX if_not_exists full_name ON full_name LP name_list RP",
 /*  59 */ "cmd ::= DROP INDEX if_exists full_name",
>>>>>>> c4ae7a9abd3ac49f353fba788979c4bffdb3825f:src/interpreter/parser/parse.c
};
#endif /* NDEBUG */


#if YYSTACKDEPTH<=0
/*
** Try to increase the size of the parser stack.  Return the number
** of errors.  Return 0 on success.
*/
static int yyGrowStack(yyParser *p){
  int newSize;
  int idx;
  yyStackEntry *pNew;

  newSize = p->yystksz*2 + 100;
  idx = p->yytos ? (int)(p->yytos - p->yystack) : 0;
  if( p->yystack==&p->yystk0 ){
    pNew = malloc(newSize*sizeof(pNew[0]));
    if( pNew ) pNew[0] = p->yystk0;
  }else{
    pNew = realloc(p->yystack, newSize*sizeof(pNew[0]));
  }
  if( pNew ){
    p->yystack = pNew;
    p->yytos = &p->yystack[idx];
#ifndef NDEBUG
    if( yyTraceFILE ){
      fprintf(yyTraceFILE,"%sStack grows from %d to %d entries.\n",
              yyTracePrompt, p->yystksz, newSize);
    }
#endif
    p->yystksz = newSize;
  }
  return pNew==0; 
}
#endif

/* Datatype of the argument to the memory allocated passed as the
** second argument to miniSqlParserAlloc() below.  This can be changed by
** putting an appropriate #define in the %include section of the input
** grammar.
*/
#ifndef YYMALLOCARGTYPE
# define YYMALLOCARGTYPE size_t
#endif

/* Initialize a new parser that has already been allocated.
*/
void miniSqlParserInit(void *yypParser){
  yyParser *pParser = (yyParser*)yypParser;
#ifdef YYTRACKMAXSTACKDEPTH
  pParser->yyhwm = 0;
#endif
#if YYSTACKDEPTH<=0
  pParser->yytos = NULL;
  pParser->yystack = NULL;
  pParser->yystksz = 0;
  if( yyGrowStack(pParser) ){
    pParser->yystack = &pParser->yystk0;
    pParser->yystksz = 1;
  }
#endif
#ifndef YYNOERRORRECOVERY
  pParser->yyerrcnt = -1;
#endif
  pParser->yytos = pParser->yystack;
  pParser->yystack[0].stateno = 0;
  pParser->yystack[0].major = 0;
}

#ifndef miniSqlParser_ENGINEALWAYSONSTACK
/* 
** This function allocates a new parser.
** The only argument is a pointer to a function which works like
** malloc.
**
** Inputs:
** A pointer to the function used to allocate memory.
**
** Outputs:
** A pointer to a parser.  This pointer is used in subsequent calls
** to Parser and ParserFree.
*/
<<<<<<< HEAD:src/interpreter/parser/parser.c
void *ParserAlloc(void *(*mallocProc)(size_t)){
=======
void *miniSqlParserAlloc(void *(*mallocProc)(YYMALLOCARGTYPE)){
>>>>>>> c4ae7a9abd3ac49f353fba788979c4bffdb3825f:src/interpreter/parser/parse.c
  yyParser *pParser;
  pParser = (yyParser*)(*mallocProc)( (YYMALLOCARGTYPE)sizeof(yyParser) );
  if( pParser ) miniSqlParserInit(pParser);
  return pParser;
}
#endif /* miniSqlParser_ENGINEALWAYSONSTACK */


/* The following function deletes the "minor type" or semantic value
** associated with a symbol.  The symbol can be either a terminal
** or nonterminal. "yymajor" is the symbol code, and "yypminor" is
** a pointer to the value to be deleted.  The code used to do the 
** deletions is derived from the %destructor and/or %token_destructor
** directives of the input grammar.
*/
static void yy_destructor(
  yyParser *yypParser,    /* The parser */
  YYCODETYPE yymajor,     /* Type code for object to destroy */
  YYMINORTYPE *yypminor   /* The object to be destroyed */
){
  ParserARG_FETCH;
  switch( yymajor ){
    /* Here is inserted the actions which take place when a
    ** terminal or non-terminal is destroyed.  This can happen
    ** when the symbol is popped from the stack during a
    ** reduce or during error processing or when a parser is 
    ** being destroyed before it is finished parsing.
    **
    ** Note: during a reduce, the only symbols destroyed are those
    ** which appear on the RHS of the rule, but which are *not* used
    ** inside the C code.
    */
<<<<<<< HEAD:src/interpreter/parser/parser.c
      /* TERMINAL Destructor */
    case 1: /* SEMICOLON */
    case 2: /* CREATE */
    case 3: /* TABLE */
    case 4: /* LP */
    case 5: /* RP */
    case 6: /* COMMA */
    case 7: /* INT_TYPE */
    case 8: /* CHAR_TYPE */
    case 9: /* INTEGER */
    case 10: /* FLOAT_TYPE */
    case 11: /* PRIMARY */
    case 12: /* KEY */
    case 13: /* UNIQUE */
    case 14: /* STRING */
    case 15: /* DROP */
    case 16: /* WHERE */
    case 17: /* DOT */
    case 18: /* FLOAT */
    case 19: /* NOT */
    case 20: /* EQ */
    case 21: /* NE */
    case 22: /* LT */
    case 23: /* GT */
    case 24: /* LE */
    case 25: /* GE */
    case 26: /* AND */
    case 27: /* OR */
    case 28: /* SELECT */
    case 29: /* FROM */
    case 30: /* INSERT */
    case 31: /* VALUES */
    case 32: /* INTO */
    case 33: /* TIMES */
    case 34: /* DELETE */
    case 35: /* INDEX */
    case 36: /* ON */
{
#line 3 "parser.y"
delete (yypminor->yy0);
#line 557 "parser.c"
}
      break;
=======
/********* Begin destructor definitions ***************************************/
/********* End destructor definitions *****************************************/
>>>>>>> c4ae7a9abd3ac49f353fba788979c4bffdb3825f:src/interpreter/parser/parse.c
    default:  break;   /* If no destructor action specified: do nothing */
  }
}

/*
** Pop the parser's stack once.
**
** If there is a destructor routine associated with the token which
** is popped from the stack, then call it.
*/
static void yy_pop_parser_stack(yyParser *pParser){
  yyStackEntry *yytos;
  assert( pParser->yytos!=0 );
  assert( pParser->yytos > pParser->yystack );
  yytos = pParser->yytos--;
#ifndef NDEBUG
  if( yyTraceFILE ){
    fprintf(yyTraceFILE,"%sPopping %s\n",
      yyTracePrompt,
      yyTokenName[yytos->major]);
  }
#endif
  yy_destructor(pParser, yytos->major, &yytos->minor);
}

/*
** Clear all secondary memory allocations from the parser
*/
void miniSqlParserFinalize(void *p){
  yyParser *pParser = (yyParser*)p;
  while( pParser->yytos>pParser->yystack ) yy_pop_parser_stack(pParser);
#if YYSTACKDEPTH<=0
  if( pParser->yystack!=&pParser->yystk0 ) free(pParser->yystack);
#endif
}

#ifndef miniSqlParser_ENGINEALWAYSONSTACK
/* 
** Deallocate and destroy a parser.  Destructors are called for
** all stack elements before shutting the parser down.
**
<<<<<<< HEAD:src/interpreter/parser/parser.c
** Inputs:
** <ul>
** <li>  A pointer to the parser.  This should be a pointer
**       obtained from ParserAlloc.
** <li>  A pointer to a function used to reclaim memory obtained
**       from malloc.
** </ul>
=======
** If the YYPARSEFREENEVERNULL macro exists (for example because it
** is defined in a %include section of the input grammar) then it is
** assumed that the input pointer is never NULL.
>>>>>>> c4ae7a9abd3ac49f353fba788979c4bffdb3825f:src/interpreter/parser/parse.c
*/
void ParserFree(
  void *p,                    /* The parser to be deleted */
  void (*freeProc)(void*)     /* Function used to reclaim memory */
){
#ifndef YYPARSEFREENEVERNULL
  if( p==0 ) return;
#endif
  miniSqlParserFinalize(p);
  (*freeProc)(p);
}
#endif /* miniSqlParser_ENGINEALWAYSONSTACK */

/*
** Return the peak depth of the stack for a parser.
*/
#ifdef YYTRACKMAXSTACKDEPTH
int ParserStackPeak(void *p){
  yyParser *pParser = (yyParser*)p;
  return pParser->yyhwm;
}
#endif

/*
** Find the appropriate action for a parser given the terminal
** look-ahead token iLookAhead.
*/
static unsigned int yy_find_shift_action(
  yyParser *pParser,        /* The parser */
  YYCODETYPE iLookAhead     /* The look-ahead token */
){
  int i;
  int stateno = pParser->yytos->stateno;
 
  if( stateno>=YY_MIN_REDUCE ) return stateno;
  assert( stateno <= YY_SHIFT_COUNT );
  do{
    i = yy_shift_ofst[stateno];
    assert( iLookAhead!=YYNOCODE );
    i += iLookAhead;
    if( i<0 || i>=YY_ACTTAB_COUNT || yy_lookahead[i]!=iLookAhead ){
#ifdef YYFALLBACK
      YYCODETYPE iFallback;            /* Fallback token */
      if( iLookAhead<sizeof(yyFallback)/sizeof(yyFallback[0])
             && (iFallback = yyFallback[iLookAhead])!=0 ){
#ifndef NDEBUG
        if( yyTraceFILE ){
          fprintf(yyTraceFILE, "%sFALLBACK %s => %s\n",
             yyTracePrompt, yyTokenName[iLookAhead], yyTokenName[iFallback]);
        }
#endif
        assert( yyFallback[iFallback]==0 ); /* Fallback loop must terminate */
        iLookAhead = iFallback;
        continue;
      }
#endif
#ifdef YYWILDCARD
      {
        int j = i - iLookAhead + YYWILDCARD;
        if( 
#if YY_SHIFT_MIN+YYWILDCARD<0
          j>=0 &&
#endif
#if YY_SHIFT_MAX+YYWILDCARD>=YY_ACTTAB_COUNT
          j<YY_ACTTAB_COUNT &&
#endif
          yy_lookahead[j]==YYWILDCARD && iLookAhead>0
        ){
#ifndef NDEBUG
          if( yyTraceFILE ){
            fprintf(yyTraceFILE, "%sWILDCARD %s => %s\n",
               yyTracePrompt, yyTokenName[iLookAhead],
               yyTokenName[YYWILDCARD]);
          }
#endif /* NDEBUG */
          return yy_action[j];
        }
      }
#endif /* YYWILDCARD */
      return yy_default[stateno];
    }else{
      return yy_action[i];
    }
  }while(1);
}

/*
** Find the appropriate action for a parser given the non-terminal
** look-ahead token iLookAhead.
*/
static int yy_find_reduce_action(
  int stateno,              /* Current state number */
  YYCODETYPE iLookAhead     /* The look-ahead token */
){
  int i;
#ifdef YYERRORSYMBOL
  if( stateno>YY_REDUCE_COUNT ){
    return yy_default[stateno];
  }
#else
  assert( stateno<=YY_REDUCE_COUNT );
#endif
  i = yy_reduce_ofst[stateno];
  assert( i!=YY_REDUCE_USE_DFLT );
  assert( iLookAhead!=YYNOCODE );
  i += iLookAhead;
#ifdef YYERRORSYMBOL
  if( i<0 || i>=YY_ACTTAB_COUNT || yy_lookahead[i]!=iLookAhead ){
    return yy_default[stateno];
  }
#else
  assert( i>=0 && i<YY_ACTTAB_COUNT );
  assert( yy_lookahead[i]==iLookAhead );
#endif
  return yy_action[i];
}

/*
** The following routine is called if the stack overflows.
*/
<<<<<<< HEAD:src/interpreter/parser/parser.c
static void yyStackOverflow(yyParser *yypParser, YYMINORTYPE *yypMinor){
   ParserARG_FETCH;
   yypParser->yyidx--;
=======
static void yyStackOverflow(yyParser *yypParser){
   miniSqlParserARG_FETCH;
>>>>>>> c4ae7a9abd3ac49f353fba788979c4bffdb3825f:src/interpreter/parser/parse.c
#ifndef NDEBUG
   if( yyTraceFILE ){
     fprintf(yyTraceFILE,"%sStack Overflow!\n",yyTracePrompt);
   }
#endif
   while( yypParser->yytos>yypParser->yystack ) yy_pop_parser_stack(yypParser);
   /* Here code is inserted which will execute if the parser
   ** stack every overflows */
<<<<<<< HEAD:src/interpreter/parser/parser.c
#line 13 "parser.y"

    interpreter->error("Stack overflow");
#line 742 "parser.c"
   ParserARG_STORE; /* Suppress warning about unused %extra_argument var */
=======
/******** Begin %stack_overflow code ******************************************/
#line 20 "parse.y"

    miniSqlError(pParser, "parser stack overflow");
#line 825 "parse.c"
/******** End %stack_overflow code ********************************************/
   miniSqlParserARG_STORE; /* Suppress warning about unused %extra_argument var */
>>>>>>> c4ae7a9abd3ac49f353fba788979c4bffdb3825f:src/interpreter/parser/parse.c
}

/*
** Print tracing information for a SHIFT action
*/
#ifndef NDEBUG
static void yyTraceShift(yyParser *yypParser, int yyNewState){
  if( yyTraceFILE ){
    if( yyNewState<YYNSTATE ){
      fprintf(yyTraceFILE,"%sShift '%s', go to state %d\n",
         yyTracePrompt,yyTokenName[yypParser->yytos->major],
         yyNewState);
    }else{
      fprintf(yyTraceFILE,"%sShift '%s'\n",
         yyTracePrompt,yyTokenName[yypParser->yytos->major]);
    }
  }
}
#else
# define yyTraceShift(X,Y)
#endif

/*
** Perform a shift action.
*/
static void yy_shift(
  yyParser *yypParser,          /* The parser to be shifted */
  int yyNewState,               /* The new state to shift in */
  int yyMajor,                  /* The major token to shift in */
  miniSqlParserTOKENTYPE yyMinor        /* The minor token to shift in */
){
  yyStackEntry *yytos;
  yypParser->yytos++;
#ifdef YYTRACKMAXSTACKDEPTH
  if( (int)(yypParser->yytos - yypParser->yystack)>yypParser->yyhwm ){
    yypParser->yyhwm++;
    assert( yypParser->yyhwm == (int)(yypParser->yytos - yypParser->yystack) );
  }
#endif
#if YYSTACKDEPTH>0 
  if( yypParser->yytos>=&yypParser->yystack[YYSTACKDEPTH] ){
    yypParser->yytos--;
    yyStackOverflow(yypParser);
    return;
  }
#else
  if( yypParser->yytos>=&yypParser->yystack[yypParser->yystksz] ){
    if( yyGrowStack(yypParser) ){
      yypParser->yytos--;
      yyStackOverflow(yypParser);
      return;
    }
  }
#endif
  if( yyNewState > YY_MAX_SHIFT ){
    yyNewState += YY_MIN_REDUCE - YY_MIN_SHIFTREDUCE;
  }
  yytos = yypParser->yytos;
  yytos->stateno = (YYACTIONTYPE)yyNewState;
  yytos->major = (YYCODETYPE)yyMajor;
  yytos->minor.yy0 = yyMinor;
  yyTraceShift(yypParser, yyNewState);
}

/* The following table contains information about every rule that
** is used during the reduce.
*/
static const struct {
  YYCODETYPE lhs;         /* Symbol on the left-hand side of the rule */
  unsigned char nrhs;     /* Number of right-hand side symbols in the rule */
} yyRuleInfo[] = {
<<<<<<< HEAD:src/interpreter/parser/parser.c
  { 38, 1 },
  { 39, 2 },
  { 39, 1 },
  { 40, 2 },
  { 41, 1 },
  { 42, 2 },
  { 43, 3 },
  { 44, 4 },
  { 46, 3 },
  { 46, 1 },
  { 48, 2 },
  { 51, 3 },
  { 51, 1 },
  { 52, 1 },
  { 49, 2 },
  { 54, 1 },
  { 54, 4 },
  { 54, 1 },
  { 50, 0 },
  { 50, 2 },
  { 50, 1 },
  { 53, 1 },
  { 55, 3 },
  { 55, 1 },
  { 56, 1 },
  { 47, 0 },
  { 47, 2 },
  { 57, 3 },
  { 57, 1 },
  { 58, 5 },
  { 58, 4 },
  { 42, 3 },
  { 59, 0 },
  { 59, 1 },
  { 60, 2 },
  { 61, 3 },
  { 61, 1 },
  { 61, 1 },
  { 61, 1 },
  { 61, 3 },
  { 61, 2 },
  { 61, 3 },
  { 61, 3 },
  { 61, 3 },
  { 61, 3 },
  { 61, 3 },
  { 61, 3 },
  { 61, 3 },
  { 61, 3 },
  { 45, 1 },
  { 63, 3 },
  { 63, 1 },
  { 42, 5 },
  { 42, 5 },
  { 65, 0 },
  { 65, 1 },
  { 66, 3 },
  { 66, 1 },
  { 67, 3 },
  { 68, 3 },
  { 68, 2 },
  { 69, 1 },
  { 69, 1 },
  { 69, 1 },
  { 70, 0 },
  { 64, 1 },
  { 64, 3 },
  { 64, 1 },
  { 71, 3 },
  { 71, 1 },
  { 42, 4 },
  { 42, 8 },
  { 42, 3 },
=======
  { 51, 0 },
  { 51, 3 },
  { 56, 0 },
  { 56, 2 },
  { 56, 1 },
  { 54, 0 },
  { 62, 0 },
  { 62, 2 },
  { 63, 1 },
  { 65, 3 },
  { 67, 1 },
  { 67, 2 },
  { 44, 1 },
  { 45, 2 },
  { 45, 1 },
  { 46, 2 },
  { 47, 1 },
  { 48, 2 },
  { 49, 4 },
  { 50, 4 },
  { 53, 4 },
  { 53, 2 },
  { 55, 2 },
  { 58, 0 },
  { 58, 1 },
  { 58, 4 },
  { 58, 1 },
  { 57, 1 },
  { 52, 1 },
  { 52, 3 },
  { 59, 3 },
  { 59, 1 },
  { 54, 2 },
  { 60, 3 },
  { 60, 1 },
  { 61, 5 },
  { 61, 4 },
  { 48, 4 },
  { 63, 0 },
  { 64, 2 },
  { 65, 1 },
  { 65, 3 },
  { 65, 3 },
  { 65, 3 },
  { 65, 5 },
  { 66, 1 },
  { 66, 1 },
  { 66, 1 },
  { 66, 1 },
  { 66, 1 },
  { 68, 1 },
  { 48, 4 },
  { 70, 1 },
  { 70, 1 },
  { 69, 1 },
  { 69, 3 },
  { 48, 10 },
  { 48, 4 },
  { 48, 9 },
  { 48, 4 },
>>>>>>> c4ae7a9abd3ac49f353fba788979c4bffdb3825f:src/interpreter/parser/parse.c
};

static void yy_accept(yyParser*);  /* Forward Declaration */

/*
** Perform a reduce action and the shift that must immediately
** follow the reduce.
*/
static void yy_reduce(
  yyParser *yypParser,         /* The parser */
  unsigned int yyruleno        /* Number of the rule by which to reduce */
){
  int yygoto;                     /* The next state */
  int yyact;                      /* The next action */
  yyStackEntry *yymsp;            /* The top of the parser's stack */
  int yysize;                     /* Amount to pop the stack */
<<<<<<< HEAD:src/interpreter/parser/parser.c
  ParserARG_FETCH;
  yymsp = &yypParser->yystack[yypParser->yyidx];
=======
  miniSqlParserARG_FETCH;
  yymsp = yypParser->yytos;
>>>>>>> c4ae7a9abd3ac49f353fba788979c4bffdb3825f:src/interpreter/parser/parse.c
#ifndef NDEBUG
  if( yyTraceFILE && yyruleno<(int)(sizeof(yyRuleName)/sizeof(yyRuleName[0])) ){
    yysize = yyRuleInfo[yyruleno].nrhs;
    fprintf(yyTraceFILE, "%sReduce [%s], go to state %d.\n", yyTracePrompt,
      yyRuleName[yyruleno], yymsp[-yysize].stateno);
  }
#endif /* NDEBUG */

  /* Check that the stack is large enough to grow by a single entry
  ** if the RHS of the rule is empty.  This ensures that there is room
  ** enough on the stack to push the LHS value */
  if( yyRuleInfo[yyruleno].nrhs==0 ){
#ifdef YYTRACKMAXSTACKDEPTH
    if( (int)(yypParser->yytos - yypParser->yystack)>yypParser->yyhwm ){
      yypParser->yyhwm++;
      assert( yypParser->yyhwm == (int)(yypParser->yytos - yypParser->yystack));
    }
#endif
#if YYSTACKDEPTH>0 
    if( yypParser->yytos>=&yypParser->yystack[YYSTACKDEPTH-1] ){
      yyStackOverflow(yypParser);
      return;
    }
#else
    if( yypParser->yytos>=&yypParser->yystack[yypParser->yystksz-1] ){
      if( yyGrowStack(yypParser) ){
        yyStackOverflow(yypParser);
        return;
      }
      yymsp = yypParser->yytos;
    }
#endif
  }

  switch( yyruleno ){
  /* Beginning here are the reduction cases.  A typical example
  ** follows:
  **   case 0:
  **  #line <lineno> <grammarfile>
  **     { ... }           // User supplied code
  **  #line <lineno> <thisfile>
  **     break;
  */
<<<<<<< HEAD:src/interpreter/parser/parser.c
      case 3: /* cmdAndEnd ::= singlcmd SEMICOLON */
#line 40 "parser.y"
{
  yy_destructor(yypParser,1,&yymsp[0].minor);
}
#line 931 "parser.c"
        break;
      case 4: /* singlcmd ::= cmd */
#line 42 "parser.y"
{
    interpreter-> query();
}
#line 938 "parser.c"
        break;
      case 5: /* cmd ::= create_table create_table_args */
#line 46 "parser.y"
{
    interpreter->setActionType(Action::CreateTable);
}
#line 945 "parser.c"
        break;
      case 6: /* create_table ::= CREATE TABLE table_name */
#line 50 "parser.y"
{
  yy_destructor(yypParser,2,&yymsp[-2].minor);
  yy_destructor(yypParser,3,&yymsp[-1].minor);
}
#line 953 "parser.c"
        break;
      case 7: /* create_table_args ::= LP columnlist optional_constraint_list RP */
#line 53 "parser.y"
{
  yy_destructor(yypParser,4,&yymsp[-3].minor);
  yy_destructor(yypParser,5,&yymsp[0].minor);
}
#line 961 "parser.c"
        break;
      case 8: /* columnlist ::= columnlist COMMA column_define */
      case 11: /* rawcolumnlist ::= rawcolumnlist COMMA rawcolumn */ yytestcase(yyruleno==11);
      case 22: /* unique_list ::= unique_list COMMA unique */ yytestcase(yyruleno==22);
      case 26: /* optional_constraint_list ::= COMMA constraint_list */ yytestcase(yyruleno==26);
      case 27: /* constraint_list ::= constraint_list COMMA table_constraint */ yytestcase(yyruleno==27);
      case 50: /* table_list ::= table_list COMMA table_name */ yytestcase(yyruleno==50);
      case 56: /* valueslist ::= valueslist COMMA values */ yytestcase(yyruleno==56);
      case 59: /* valuelist ::= valuelist COMMA value */ yytestcase(yyruleno==59);
      case 66: /* select_column_list ::= select_column_list COMMA full_name */ yytestcase(yyruleno==66);
#line 56 "parser.y"
{
  yy_destructor(yypParser,6,&yymsp[-1].minor);
}
#line 976 "parser.c"
        break;
      case 10: /* column_define ::= column column_constraint */
#line 58 "parser.y"
{
    interpreter->newConstraint(*yymsp[-1].minor.yy0,yymsp[0].minor.yy12);
}
#line 983 "parser.c"
        break;
      case 13: /* rawcolumn ::= name */
#line 64 "parser.y"
{
    interpreter->newColumn(*yymsp[0].minor.yy0,Column::Undefined);
}
#line 990 "parser.c"
        break;
      case 14: /* column ::= name type_token */
#line 68 "parser.y"
{
    interpreter->newColumn(*yymsp[-1].minor.yy0, yymsp[0].minor.yy109);
    yygotominor.yy0 = yymsp[-1].minor.yy0;
}
#line 998 "parser.c"
        break;
      case 15: /* type_token ::= INT_TYPE */
#line 75 "parser.y"
{ yygotominor.yy109 = Column::Int;   yy_destructor(yypParser,7,&yymsp[0].minor);
}
#line 1004 "parser.c"
        break;
      case 16: /* type_token ::= CHAR_TYPE LP INTEGER RP */
#line 76 "parser.y"
{ yygotominor.yy109 = stoi(*yymsp[-1].minor.yy0);  yy_destructor(yypParser,8,&yymsp[-3].minor);
  yy_destructor(yypParser,4,&yymsp[-2].minor);
  yy_destructor(yypParser,5,&yymsp[0].minor);
}
#line 1012 "parser.c"
        break;
      case 17: /* type_token ::= FLOAT_TYPE */
#line 77 "parser.y"
{ yygotominor.yy109 = Column::Float;  yy_destructor(yypParser,10,&yymsp[0].minor);
}
#line 1018 "parser.c"
        break;
      case 18: /* column_constraint ::= */
#line 80 "parser.y"
{yygotominor.yy12 = Constraint::None;}
#line 1023 "parser.c"
        break;
      case 19: /* column_constraint ::= PRIMARY KEY */
#line 81 "parser.y"
{yygotominor.yy12 = Constraint::PrimaryKey;  yy_destructor(yypParser,11,&yymsp[-1].minor);
  yy_destructor(yypParser,12,&yymsp[0].minor);
}
#line 1030 "parser.c"
        break;
      case 20: /* column_constraint ::= UNIQUE */
#line 82 "parser.y"
{yygotominor.yy12 = Constraint::Unique;  yy_destructor(yypParser,13,&yymsp[0].minor);
}
#line 1036 "parser.c"
        break;
      case 21: /* name ::= STRING */
#line 84 "parser.y"
{yygotominor.yy0=yymsp[0].minor.yy0;}
#line 1041 "parser.c"
        break;
      case 24: /* unique ::= name */
#line 88 "parser.y"
{
    interpreter->newConstraint(*yymsp[0].minor.yy0,Constraint::Unique);
}
#line 1048 "parser.c"
        break;
      case 29: /* table_constraint ::= PRIMARY KEY LP name RP */
#line 98 "parser.y"
{
    interpreter->newConstraint(*yymsp[-1].minor.yy0,Constraint::PrimaryKey);
  yy_destructor(yypParser,11,&yymsp[-4].minor);
  yy_destructor(yypParser,12,&yymsp[-3].minor);
  yy_destructor(yypParser,4,&yymsp[-2].minor);
  yy_destructor(yypParser,5,&yymsp[0].minor);
}
#line 1059 "parser.c"
        break;
      case 30: /* table_constraint ::= UNIQUE LP unique_list RP */
#line 102 "parser.y"
{
  yy_destructor(yypParser,13,&yymsp[-3].minor);
  yy_destructor(yypParser,4,&yymsp[-2].minor);
  yy_destructor(yypParser,5,&yymsp[0].minor);
}
#line 1068 "parser.c"
        break;
      case 31: /* cmd ::= DROP TABLE table_name */
#line 106 "parser.y"
{
    interpreter->setActionType(Action::DropTable);
  yy_destructor(yypParser,15,&yymsp[-2].minor);
  yy_destructor(yypParser,3,&yymsp[-1].minor);
}
#line 1077 "parser.c"
        break;
      case 34: /* where_clause ::= WHERE expr */
#line 117 "parser.y"
{
    interpreter->newCondition(yymsp[0].minor.yy82);
  yy_destructor(yypParser,16,&yymsp[-1].minor);
}
#line 1085 "parser.c"
        break;
      case 35: /* expr ::= name DOT name */
#line 131 "parser.y"
{
    yygotominor.yy82 = interpreter->newCondition(*yymsp[0].minor.yy0,Column::Undefined, *yymsp[-2].minor.yy0);
  yy_destructor(yypParser,17,&yymsp[-1].minor);
}
#line 1093 "parser.c"
        break;
      case 36: /* expr ::= name */
#line 135 "parser.y"
{
    yygotominor.yy82 = interpreter->newCondition(*yymsp[0].minor.yy0,yymsp[0].minor.yy0->length());
}
#line 1100 "parser.c"
        break;
      case 37: /* expr ::= INTEGER */
#line 139 "parser.y"
{
    yygotominor.yy82 = interpreter->newCondition(*yymsp[0].minor.yy0,Column::Int);
}
#line 1107 "parser.c"
        break;
      case 38: /* expr ::= FLOAT */
#line 142 "parser.y"
{
    yygotominor.yy82 = interpreter->newCondition(*yymsp[0].minor.yy0,Column::Float);
}
#line 1114 "parser.c"
        break;
      case 39: /* expr ::= LP expr RP */
#line 146 "parser.y"
{
    yygotominor.yy82 = yymsp[-1].minor.yy82;
  yy_destructor(yypParser,4,&yymsp[-2].minor);
  yy_destructor(yypParser,5,&yymsp[0].minor);
}
#line 1123 "parser.c"
        break;
      case 40: /* expr ::= NOT expr */
#line 150 "parser.y"
{
    yygotominor.yy82 = interpreter->newCondition(Condition::Not, yymsp[0].minor.yy82);
  yy_destructor(yypParser,19,&yymsp[-1].minor);
}
#line 1131 "parser.c"
        break;
      case 41: /* expr ::= expr EQ expr */
#line 154 "parser.y"
{
    yygotominor.yy82 = interpreter->newCondition(Condition::Equal,yymsp[-2].minor.yy82,yymsp[0].minor.yy82); 
  yy_destructor(yypParser,20,&yymsp[-1].minor);
}
#line 1139 "parser.c"
        break;
      case 42: /* expr ::= expr NE expr */
#line 157 "parser.y"
{
    yygotominor.yy82 = interpreter->newCondition(Condition::NotEqual,yymsp[-2].minor.yy82,yymsp[0].minor.yy82); 
  yy_destructor(yypParser,21,&yymsp[-1].minor);
}
#line 1147 "parser.c"
        break;
      case 43: /* expr ::= expr LT expr */
#line 160 "parser.y"
{
    yygotominor.yy82 = interpreter->newCondition(Condition::LessThan,yymsp[-2].minor.yy82,yymsp[0].minor.yy82); 
  yy_destructor(yypParser,22,&yymsp[-1].minor);
}
#line 1155 "parser.c"
        break;
      case 44: /* expr ::= expr GT expr */
#line 163 "parser.y"
{
    yygotominor.yy82 = interpreter->newCondition(Condition::GreaterThan,yymsp[-2].minor.yy82,yymsp[0].minor.yy82); 
  yy_destructor(yypParser,23,&yymsp[-1].minor);
}
#line 1163 "parser.c"
        break;
      case 45: /* expr ::= expr LE expr */
#line 166 "parser.y"
{
    yygotominor.yy82 = interpreter->newCondition(Condition::LessEqual,yymsp[-2].minor.yy82,yymsp[0].minor.yy82); 
  yy_destructor(yypParser,24,&yymsp[-1].minor);
}
#line 1171 "parser.c"
        break;
      case 46: /* expr ::= expr GE expr */
#line 169 "parser.y"
{
    yygotominor.yy82 = interpreter->newCondition(Condition::GreaterEqual,yymsp[-2].minor.yy82,yymsp[0].minor.yy82); 
  yy_destructor(yypParser,25,&yymsp[-1].minor);
}
#line 1179 "parser.c"
        break;
      case 47: /* expr ::= expr AND expr */
#line 173 "parser.y"
{
    yygotominor.yy82 = interpreter->newCondition(Condition::And,yymsp[-2].minor.yy82,yymsp[0].minor.yy82); 
  yy_destructor(yypParser,26,&yymsp[-1].minor);
}
#line 1187 "parser.c"
        break;
      case 48: /* expr ::= expr OR expr */
#line 177 "parser.y"
{
    yygotominor.yy82 = interpreter->newCondition(Condition::Or,yymsp[-2].minor.yy82,yymsp[0].minor.yy82); 
  yy_destructor(yypParser,27,&yymsp[-1].minor);
}
#line 1195 "parser.c"
        break;
      case 49: /* table_name ::= STRING */
#line 187 "parser.y"
{
    interpreter->addTableName(*yymsp[0].minor.yy0);
}
#line 1202 "parser.c"
        break;
      case 52: /* cmd ::= SELECT select_column_list FROM table_list opt_where_clause */
#line 195 "parser.y"
{
    interpreter->setActionType(Action::Select);
    
  yy_destructor(yypParser,28,&yymsp[-4].minor);
  yy_destructor(yypParser,29,&yymsp[-2].minor);
}
#line 1212 "parser.c"
        break;
      case 53: /* cmd ::= INSERT into table_name VALUES valueslist */
#line 201 "parser.y"
{
   interpreter->setActionType(Action::Insert);
  yy_destructor(yypParser,30,&yymsp[-4].minor);
  yy_destructor(yypParser,31,&yymsp[-1].minor);
}
#line 1221 "parser.c"
        break;
      case 55: /* into ::= INTO */
#line 206 "parser.y"
{
  yy_destructor(yypParser,32,&yymsp[0].minor);
}
#line 1228 "parser.c"
        break;
      case 58: /* values ::= LP valuelist RP */
#line 210 "parser.y"
{
  yy_destructor(yypParser,4,&yymsp[-2].minor);
  yy_destructor(yypParser,5,&yymsp[0].minor);
}
#line 1236 "parser.c"
        break;
      case 61: /* value ::= FLOAT */
#line 214 "parser.y"
{
    interpreter->addValue(*yymsp[0].minor.yy0, Column::Float);
}
#line 1243 "parser.c"
        break;
      case 62: /* value ::= INTEGER */
#line 217 "parser.y"
{
    interpreter->addValue(*yymsp[0].minor.yy0, Column::Int);
}
#line 1250 "parser.c"
        break;
      case 63: /* value ::= STRING */
#line 220 "parser.y"
{
    interpreter->addValue(*yymsp[0].minor.yy0, yymsp[0].minor.yy0->length());
}
#line 1257 "parser.c"
        break;
      case 64: /* beginValue ::= */
#line 223 "parser.y"
{
    interpreter->beginValue();
}
#line 1264 "parser.c"
        break;
      case 65: /* select_column_list ::= TIMES */
#line 226 "parser.y"
{  yy_destructor(yypParser,33,&yymsp[0].minor);
}
#line 1270 "parser.c"
        break;
      case 68: /* full_name ::= name DOT name */
#line 232 "parser.y"
{
    interpreter->newColumn(*yymsp[0].minor.yy0,Column::Undefined, *yymsp[-2].minor.yy0);
  yy_destructor(yypParser,17,&yymsp[-1].minor);
}
#line 1278 "parser.c"
        break;
      case 70: /* cmd ::= DELETE FROM table_name opt_where_clause */
#line 240 "parser.y"
{
    interpreter->setActionType(Action::Delete);
  yy_destructor(yypParser,34,&yymsp[-3].minor);
  yy_destructor(yypParser,29,&yymsp[-2].minor);
}
#line 1287 "parser.c"
        break;
      case 71: /* cmd ::= CREATE INDEX name ON table_name LP rawcolumnlist RP */
#line 246 "parser.y"
{
    interpreter->setActionType(Action::CreateIndex);
    interpreter->addIndexName(*yymsp[-5].minor.yy0);
  yy_destructor(yypParser,2,&yymsp[-7].minor);
  yy_destructor(yypParser,35,&yymsp[-6].minor);
  yy_destructor(yypParser,36,&yymsp[-4].minor);
  yy_destructor(yypParser,4,&yymsp[-2].minor);
  yy_destructor(yypParser,5,&yymsp[0].minor);
}
#line 1300 "parser.c"
        break;
      case 72: /* cmd ::= DROP INDEX name */
#line 253 "parser.y"
{
    interpreter->setActionType(Action::DropIndex);
    interpreter->addIndexName(*yymsp[0].minor.yy0);
  yy_destructor(yypParser,15,&yymsp[-2].minor);
  yy_destructor(yypParser,35,&yymsp[-1].minor);
}
#line 1310 "parser.c"
        break;
      default:
      /* (0) start ::= cmdList */ yytestcase(yyruleno==0);
      /* (1) cmdList ::= cmdList cmdAndEnd */ yytestcase(yyruleno==1);
      /* (2) cmdList ::= cmdAndEnd */ yytestcase(yyruleno==2);
      /* (9) columnlist ::= column_define */ yytestcase(yyruleno==9);
      /* (12) rawcolumnlist ::= rawcolumn */ yytestcase(yyruleno==12);
      /* (23) unique_list ::= unique */ yytestcase(yyruleno==23);
      /* (25) optional_constraint_list ::= */ yytestcase(yyruleno==25);
      /* (28) constraint_list ::= table_constraint */ yytestcase(yyruleno==28);
      /* (32) opt_where_clause ::= */ yytestcase(yyruleno==32);
      /* (33) opt_where_clause ::= where_clause */ yytestcase(yyruleno==33);
      /* (51) table_list ::= table_name */ yytestcase(yyruleno==51);
      /* (54) into ::= */ yytestcase(yyruleno==54);
      /* (57) valueslist ::= values */ yytestcase(yyruleno==57);
      /* (60) valuelist ::= beginValue value */ yytestcase(yyruleno==60);
      /* (67) select_column_list ::= full_name */ yytestcase(yyruleno==67);
      /* (69) full_name ::= rawcolumn */ yytestcase(yyruleno==69);
=======
/********** Begin reduce actions **********************************************/
        YYMINORTYPE yylhsminor;
      case 0: /* if_not_exists ::= */
      case 2: /* column_constraint ::= */ yytestcase(yyruleno==2);
      case 6: /* if_exists ::= */ yytestcase(yyruleno==6);
#line 50 "parse.y"
{yymsp[1].minor.yy136 = 0;}
#line 1027 "parse.c"
        break;
      case 1: /* if_not_exists ::= IF NOT EXISTS */
#line 51 "parse.y"
{yymsp[-2].minor.yy136 = 1;}
#line 1032 "parse.c"
        break;
      case 3: /* column_constraint ::= PRIMARY KEY */
      case 7: /* if_exists ::= IF EXISTS */ yytestcase(yyruleno==7);
      case 11: /* between_op ::= NOT BETWEEN */ yytestcase(yyruleno==11);
#line 67 "parse.y"
{yymsp[-1].minor.yy136 = 1;}
#line 1039 "parse.c"
        break;
      case 4: /* column_constraint ::= UNIQUE */
#line 68 "parse.y"
{yymsp[0].minor.yy136 = 2;}
#line 1044 "parse.c"
        break;
      case 5: /* optional_constraint_list ::= */
#line 88 "parse.y"
{yymsp[1].minor.yy0.n = 0; yymsp[1].minor.yy0.text = 0;}
#line 1049 "parse.c"
        break;
      case 8: /* opt_where_clause ::= where_clause */
#line 106 "parse.y"
{yylhsminor.yy0 = yymsp[0].minor.yy0;}
#line 1054 "parse.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 9: /* expr ::= expr EQ|NE expr */
#line 114 "parse.y"
{}
#line 1060 "parse.c"
        break;
      case 10: /* between_op ::= BETWEEN */
#line 128 "parse.y"
{yymsp[0].minor.yy136 = 0;}
#line 1065 "parse.c"
        break;
      case 28: /* full_name ::= name */
#line 77 "parse.y"
{
}
#line 1071 "parse.c"
  yymsp[0].minor.yy5 = yylhsminor.yy5;
        break;
      case 29: /* full_name ::= name DOT name */
#line 78 "parse.y"
{
}
#line 1078 "parse.c"
  yymsp[-2].minor.yy5 = yylhsminor.yy5;
        break;
      case 45: /* literal ::= NULL */
      case 46: /* literal ::= full_name */ yytestcase(yyruleno==46);
      case 47: /* literal ::= INTEGER */ yytestcase(yyruleno==47);
      case 48: /* literal ::= FLOAT */ yytestcase(yyruleno==48);
      case 49: /* literal ::= STRING */ yytestcase(yyruleno==49);
      case 50: /* literal_list ::= literal */ yytestcase(yyruleno==50);
      case 53: /* select_column ::= name */ yytestcase(yyruleno==53);
      case 54: /* select_column_list ::= select_column */ yytestcase(yyruleno==54);
#line 117 "parse.y"
{
}
#line 1092 "parse.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      default:
      /* (12) input ::= cmdlist */ yytestcase(yyruleno==12);
      /* (13) cmdlist ::= cmdlist cmd_and_end */ yytestcase(yyruleno==13);
      /* (14) cmdlist ::= cmd_and_end */ yytestcase(yyruleno==14);
      /* (15) cmd_and_end ::= singlecmd SEMICOLON */ yytestcase(yyruleno==15);
      /* (16) singlecmd ::= cmd */ yytestcase(yyruleno==16);
      /* (17) cmd ::= create_table create_table_args */ yytestcase(yyruleno==17);
      /* (18) create_table ::= CREATE TABLE if_not_exists full_name */ yytestcase(yyruleno==18);
      /* (19) create_table_args ::= LP columnlist optional_constraint_list RP */ yytestcase(yyruleno==19);
      /* (20) columnlist ::= columnlist COMMA column_name column_constraint */ yytestcase(yyruleno==20);
      /* (21) columnlist ::= column_name column_constraint */ yytestcase(yyruleno==21);
      /* (22) column_name ::= name type_token */ yytestcase(yyruleno==22);
      /* (23) type_token ::= */ yytestcase(yyruleno==23);
      /* (24) type_token ::= INT_TYPE */ yytestcase(yyruleno==24);
      /* (25) type_token ::= CHAR_TYPE LP INTEGER RP */ yytestcase(yyruleno==25);
      /* (26) type_token ::= FLOAT_TYPE */ yytestcase(yyruleno==26);
      /* (27) name ::= ID */ yytestcase(yyruleno==27);
      /* (30) name_list ::= name_list COMMA name */ yytestcase(yyruleno==30);
      /* (31) name_list ::= name */ yytestcase(yyruleno==31);
      /* (32) optional_constraint_list ::= COMMA constraint_list */ yytestcase(yyruleno==32);
      /* (33) constraint_list ::= constraint_list COMMA table_constraint */ yytestcase(yyruleno==33);
      /* (34) constraint_list ::= table_constraint */ yytestcase(yyruleno==34);
      /* (35) table_constraint ::= PRIMARY KEY LP name RP */ yytestcase(yyruleno==35);
      /* (36) table_constraint ::= UNIQUE LP name_list RP */ yytestcase(yyruleno==36);
      /* (37) cmd ::= DROP TABLE if_exists full_name */ yytestcase(yyruleno==37);
      /* (38) opt_where_clause ::= */ yytestcase(yyruleno==38);
      /* (39) where_clause ::= WHERE expr */ yytestcase(yyruleno==39);
      /* (40) expr ::= literal */ yytestcase(yyruleno==40);
      /* (41) expr ::= expr AND expr */ yytestcase(yyruleno==41);
      /* (42) expr ::= expr OR expr */ yytestcase(yyruleno==42);
      /* (43) expr ::= expr LT|GT|GE|LE expr */ yytestcase(yyruleno==43);
      /* (44) expr ::= expr between_op expr AND expr */ yytestcase(yyruleno==44);
      /* (51) cmd ::= SELECT select_column_list FROM opt_where_clause */ yytestcase(yyruleno==51);
      /* (52) select_column ::= STAR */ yytestcase(yyruleno==52);
      /* (55) select_column_list ::= select_column_list COMMA select_column */ yytestcase(yyruleno==55);
      /* (56) cmd ::= INSERT INTO full_name LP name_list RP VALUES LP literal_list RP */ yytestcase(yyruleno==56);
      /* (57) cmd ::= DELETE FROM full_name opt_where_clause */ yytestcase(yyruleno==57);
      /* (58) cmd ::= CREATE INDEX if_not_exists full_name ON full_name LP name_list RP */ yytestcase(yyruleno==58);
      /* (59) cmd ::= DROP INDEX if_exists full_name */ yytestcase(yyruleno==59);
>>>>>>> c4ae7a9abd3ac49f353fba788979c4bffdb3825f:src/interpreter/parser/parse.c
        break;
/********** End reduce actions ************************************************/
  };
  assert( yyruleno<sizeof(yyRuleInfo)/sizeof(yyRuleInfo[0]) );
  yygoto = yyRuleInfo[yyruleno].lhs;
  yysize = yyRuleInfo[yyruleno].nrhs;
  yyact = yy_find_reduce_action(yymsp[-yysize].stateno,(YYCODETYPE)yygoto);
  if( yyact <= YY_MAX_SHIFTREDUCE ){
    if( yyact>YY_MAX_SHIFT ){
      yyact += YY_MIN_REDUCE - YY_MIN_SHIFTREDUCE;
    }
    yymsp -= yysize-1;
    yypParser->yytos = yymsp;
    yymsp->stateno = (YYACTIONTYPE)yyact;
    yymsp->major = (YYCODETYPE)yygoto;
    yyTraceShift(yypParser, yyact);
  }else{
    assert( yyact == YY_ACCEPT_ACTION );
    yypParser->yytos -= yysize;
    yy_accept(yypParser);
  }
}

/*
** The following code executes when the parse fails
*/
#ifndef YYNOERRORRECOVERY
static void yy_parse_failed(
  yyParser *yypParser           /* The parser */
){
  ParserARG_FETCH;
#ifndef NDEBUG
  if( yyTraceFILE ){
    fprintf(yyTraceFILE,"%sFail!\n",yyTracePrompt);
  }
#endif
  while( yypParser->yytos>yypParser->yystack ) yy_pop_parser_stack(yypParser);
  /* Here code is inserted which will be executed whenever the
  ** parser fails */
<<<<<<< HEAD:src/interpreter/parser/parser.c
  ParserARG_STORE; /* Suppress warning about unused %extra_argument variable */
=======
/************ Begin %parse_failure code ***************************************/
/************ End %parse_failure code *****************************************/
  miniSqlParserARG_STORE; /* Suppress warning about unused %extra_argument variable */
>>>>>>> c4ae7a9abd3ac49f353fba788979c4bffdb3825f:src/interpreter/parser/parse.c
}
#endif /* YYNOERRORRECOVERY */

/*
** The following code executes when a syntax error first occurs.
*/
static void yy_syntax_error(
  yyParser *yypParser,           /* The parser */
  int yymajor,                   /* The major type of the error token */
  miniSqlParserTOKENTYPE yyminor         /* The minor type of the error token */
){
<<<<<<< HEAD:src/interpreter/parser/parser.c
  ParserARG_FETCH;
#define TOKEN (yyminor.yy0)
#line 8 "parser.y"

    //cout<<"error"<<endl;
    interpreter->error("Syntax error");
#line 1392 "parser.c"
  ParserARG_STORE; /* Suppress warning about unused %extra_argument variable */
=======
  miniSqlParserARG_FETCH;
#define TOKEN yyminor
/************ Begin %syntax_error code ****************************************/
#line 10 "parse.y"

    // TODO: add location of error
    miniSqlError(pParser, "syntax error");
#line 1194 "parse.c"
/************ End %syntax_error code ******************************************/
  miniSqlParserARG_STORE; /* Suppress warning about unused %extra_argument variable */
>>>>>>> c4ae7a9abd3ac49f353fba788979c4bffdb3825f:src/interpreter/parser/parse.c
}

/*
** The following is executed when the parser accepts
*/
static void yy_accept(
  yyParser *yypParser           /* The parser */
){
  ParserARG_FETCH;
#ifndef NDEBUG
  if( yyTraceFILE ){
    fprintf(yyTraceFILE,"%sAccept!\n",yyTracePrompt);
  }
#endif
#ifndef YYNOERRORRECOVERY
  yypParser->yyerrcnt = -1;
#endif
  assert( yypParser->yytos==yypParser->yystack );
  /* Here code is inserted which will be executed whenever the
  ** parser accepts */
<<<<<<< HEAD:src/interpreter/parser/parser.c
  ParserARG_STORE; /* Suppress warning about unused %extra_argument variable */
=======
/*********** Begin %parse_accept code *****************************************/
#line 15 "parse.y"

miniSqlLog(pParser, "parsing complete");
#line 1221 "parse.c"
/*********** End %parse_accept code *******************************************/
  miniSqlParserARG_STORE; /* Suppress warning about unused %extra_argument variable */
>>>>>>> c4ae7a9abd3ac49f353fba788979c4bffdb3825f:src/interpreter/parser/parse.c
}

/* The main parser program.
** The first argument is a pointer to a structure obtained from
** "ParserAlloc" which describes the current state of the parser.
** The second argument is the major token number.  The third is
** the minor token.  The fourth optional argument is whatever the
** user wants (and specified in the grammar) and is available for
** use by the action routines.
**
** Inputs:
** <ul>
** <li> A pointer to the parser (an opaque structure.)
** <li> The major token number.
** <li> The minor token number.
** <li> An option argument of a grammar-specified type.
** </ul>
**
** Outputs:
** None.
*/
void Parser(
  void *yyp,                   /* The parser */
  int yymajor,                 /* The major token code number */
  ParserTOKENTYPE yyminor       /* The value for the token */
  ParserARG_PDECL               /* Optional %extra_argument parameter */
){
  YYMINORTYPE yyminorunion;
  unsigned int yyact;   /* The parser action. */
#if !defined(YYERRORSYMBOL) && !defined(YYNOERRORRECOVERY)
  int yyendofinput;     /* True if we are at the end of input */
#endif
#ifdef YYERRORSYMBOL
  int yyerrorhit = 0;   /* True if yymajor has invoked an error */
#endif
  yyParser *yypParser;  /* The parser */

  yypParser = (yyParser*)yyp;
  assert( yypParser->yytos!=0 );
#if !defined(YYERRORSYMBOL) && !defined(YYNOERRORRECOVERY)
  yyendofinput = (yymajor==0);
<<<<<<< HEAD:src/interpreter/parser/parser.c
  ParserARG_STORE;
=======
#endif
  miniSqlParserARG_STORE;
>>>>>>> c4ae7a9abd3ac49f353fba788979c4bffdb3825f:src/interpreter/parser/parse.c

#ifndef NDEBUG
  if( yyTraceFILE ){
    fprintf(yyTraceFILE,"%sInput '%s'\n",yyTracePrompt,yyTokenName[yymajor]);
  }
#endif

  do{
    yyact = yy_find_shift_action(yypParser,(YYCODETYPE)yymajor);
    if( yyact <= YY_MAX_SHIFTREDUCE ){
      yy_shift(yypParser,yyact,yymajor,yyminor);
#ifndef YYNOERRORRECOVERY
      yypParser->yyerrcnt--;
#endif
      yymajor = YYNOCODE;
    }else if( yyact <= YY_MAX_REDUCE ){
      yy_reduce(yypParser,yyact-YY_MIN_REDUCE);
    }else{
      assert( yyact == YY_ERROR_ACTION );
      yyminorunion.yy0 = yyminor;
#ifdef YYERRORSYMBOL
      int yymx;
#endif
#ifndef NDEBUG
      if( yyTraceFILE ){
        fprintf(yyTraceFILE,"%sSyntax Error!\n",yyTracePrompt);
      }
#endif
#ifdef YYERRORSYMBOL
      /* A syntax error has occurred.
      ** The response to an error depends upon whether or not the
      ** grammar defines an error token "ERROR".  
      **
      ** This is what we do if the grammar does define ERROR:
      **
      **  * Call the %syntax_error function.
      **
      **  * Begin popping the stack until we enter a state where
      **    it is legal to shift the error symbol, then shift
      **    the error symbol.
      **
      **  * Set the error count to three.
      **
      **  * Begin accepting and shifting new tokens.  No new error
      **    processing will occur until three tokens have been
      **    shifted successfully.
      **
      */
      if( yypParser->yyerrcnt<0 ){
        yy_syntax_error(yypParser,yymajor,yyminor);
      }
      yymx = yypParser->yytos->major;
      if( yymx==YYERRORSYMBOL || yyerrorhit ){
#ifndef NDEBUG
        if( yyTraceFILE ){
          fprintf(yyTraceFILE,"%sDiscard input token %s\n",
             yyTracePrompt,yyTokenName[yymajor]);
        }
#endif
        yy_destructor(yypParser, (YYCODETYPE)yymajor, &yyminorunion);
        yymajor = YYNOCODE;
      }else{
        while( yypParser->yytos >= yypParser->yystack
            && yymx != YYERRORSYMBOL
            && (yyact = yy_find_reduce_action(
                        yypParser->yytos->stateno,
                        YYERRORSYMBOL)) >= YY_MIN_REDUCE
        ){
          yy_pop_parser_stack(yypParser);
        }
        if( yypParser->yytos < yypParser->yystack || yymajor==0 ){
          yy_destructor(yypParser,(YYCODETYPE)yymajor,&yyminorunion);
          yy_parse_failed(yypParser);
#ifndef YYNOERRORRECOVERY
          yypParser->yyerrcnt = -1;
#endif
          yymajor = YYNOCODE;
        }else if( yymx!=YYERRORSYMBOL ){
          yy_shift(yypParser,yyact,YYERRORSYMBOL,yyminor);
        }
      }
      yypParser->yyerrcnt = 3;
      yyerrorhit = 1;
#elif defined(YYNOERRORRECOVERY)
      /* If the YYNOERRORRECOVERY macro is defined, then do not attempt to
      ** do any kind of error recovery.  Instead, simply invoke the syntax
      ** error routine and continue going as if nothing had happened.
      **
      ** Applications can set this macro (for example inside %include) if
      ** they intend to abandon the parse upon the first syntax error seen.
      */
      yy_syntax_error(yypParser,yymajor, yyminor);
      yy_destructor(yypParser,(YYCODETYPE)yymajor,&yyminorunion);
      yymajor = YYNOCODE;
      
#else  /* YYERRORSYMBOL is not defined */
      /* This is what we do if the grammar does not define ERROR:
      **
      **  * Report an error message, and throw away the input token.
      **
      **  * If the input token is $, then fail the parse.
      **
      ** As before, subsequent error messages are suppressed until
      ** three input tokens have been successfully shifted.
      */
      if( yypParser->yyerrcnt<=0 ){
        yy_syntax_error(yypParser,yymajor, yyminor);
      }
      yypParser->yyerrcnt = 3;
      yy_destructor(yypParser,(YYCODETYPE)yymajor,&yyminorunion);
      if( yyendofinput ){
        yy_parse_failed(yypParser);
#ifndef YYNOERRORRECOVERY
        yypParser->yyerrcnt = -1;
#endif
      }
      yymajor = YYNOCODE;
#endif
    }
  }while( yymajor!=YYNOCODE && yypParser->yytos>yypParser->yystack );
#ifndef NDEBUG
  if( yyTraceFILE ){
    yyStackEntry *i;
    char cDiv = '[';
    fprintf(yyTraceFILE,"%sReturn. Stack=",yyTracePrompt);
    for(i=&yypParser->yystack[1]; i<=yypParser->yytos; i++){
      fprintf(yyTraceFILE,"%c%s", cDiv, yyTokenName[i->major]);
      cDiv = ' ';
    }
    fprintf(yyTraceFILE,"]\n");
  }
#endif
  return;
}
