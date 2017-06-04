/* Driver template for the LEMON parser generator.
** The author disclaims copyright to this source code.
*/
/* First off, code is included that follows the "include" declaration
** in the input grammar file. */
#include <stdio.h>
#line 32 "parser.y"

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
** various aspects of the generated parser.
**    YYCODETYPE         is the data type used for storing terminal
**                       and nonterminal numbers.  "unsigned char" is
**                       used if there are fewer than 250 terminals
**                       and nonterminals.  "int" is used otherwise.
**    YYNOCODE           is a number of type YYCODETYPE which corresponds
**                       to no legal terminal or nonterminal number.  This
**                       number is used to fill in empty slots of the hash 
**                       table.
**    YYFALLBACK         If defined, this indicates that one or more tokens
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
**    YYERRORSYMBOL      is the code number of the error symbol.  If not
**                       defined, then do no error processing.
*/
#define YYCODETYPE unsigned char
#define YYNOCODE 74
#define YYACTIONTYPE unsigned char
#define ParserTOKENTYPE const string *
typedef union {
  int yyinit;
  ParserTOKENTYPE yy0;
  Column::Type yy11;
  Constraint::Type yy112;
  Condition * yy116;
  Condition::Type yy130;
} YYMINORTYPE;
#ifndef YYSTACKDEPTH
#define YYSTACKDEPTH 100
#endif
#define ParserARG_SDECL Interpreter *interpreter;
#define ParserARG_PDECL ,Interpreter *interpreter
#define ParserARG_FETCH Interpreter *interpreter = yypParser->interpreter
#define ParserARG_STORE yypParser->interpreter = interpreter
#define YYNSTATE 138
#define YYNRULE 75
#define YY_NO_ACTION      (YYNSTATE+YYNRULE+2)
#define YY_ACCEPT_ACTION  (YYNSTATE+YYNRULE+1)
#define YY_ERROR_ACTION   (YYNSTATE+YYNRULE)

/* The yyzerominor constant is used to initialize instances of
** YYMINORTYPE objects to zero. */
static const YYMINORTYPE yyzerominor = { 0 };

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
**   0 <= N < YYNSTATE                  Shift N.  That is, push the lookahead
**                                      token onto the stack and goto state N.
**
**   YYNSTATE <= N < YYNSTATE+YYNRULE   Reduce by rule N-YYNSTATE.
**
**   N == YYNSTATE+YYNRULE              A syntax error has occurred.
**
**   N == YYNSTATE+YYNRULE+1            The parser accepts its input.
**
**   N == YYNSTATE+YYNRULE+2            No such action.  Denotes unused
**                                      slots in the yy_action[] table.
**
** The action table is constructed as a single large table named yy_action[].
** Given state S and lookahead X, the action is computed as
**
**      yy_action[ yy_shift_ofst[S] + X ]
**
** If the index value yy_shift_ofst[S]+X is out of range or if the value
** yy_lookahead[yy_shift_ofst[S]+X] is not equal to X or if yy_shift_ofst[S]
** is equal to YY_SHIFT_USE_DFLT, it means that the action is not in the table
** and that yy_default[S] should be used instead.  
**
** The formula above is for computing the action when the lookahead is
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
*/
#define YY_ACTTAB_COUNT (217)
static const YYACTIONTYPE yy_action[] = {
 /*     0 */   102,   13,   11,    9,    8,    7,    6,    5,    4,   13,
 /*    10 */    11,    9,    8,    7,    6,   13,   11,    9,    8,    7,
 /*    20 */     6,    5,    4,   13,   11,    9,    8,    7,    6,    5,
 /*    30 */   213,  213,  213,  213,  213,  213,  138,  134,   62,   12,
 /*    40 */   128,   79,   32,  126,  104,   96,   68,  133,   37,  125,
 /*    50 */    62,   60,   35,  103,   10,  136,   76,  118,  214,   15,
 /*    60 */    83,   82,   46,   60,    2,   97,   39,   45,  101,  117,
 /*    70 */    37,   64,   96,   68,   35,   43,    2,   89,   39,  121,
 /*    80 */    78,   63,  119,   64,  131,   59,   90,   98,   61,  111,
 /*    90 */   113,   80,   94,  130,   67,  115,  137,   82,   46,   67,
 /*   100 */    67,  101,   48,   67,  106,   77,   22,   50,   47,  106,
 /*   110 */   106,   51,   67,  106,   29,   67,   67,  120,   33,   67,
 /*   120 */    57,   16,  106,   56,   55,  106,  106,   54,   67,  106,
 /*   130 */    44,   67,   67,  112,   30,   75,   53,   72,  106,   52,
 /*   140 */    49,  106,  106,   75,   17,   72,  125,   42,   92,   21,
 /*   150 */   116,   58,  121,   20,   70,  122,  114,  113,  115,  110,
 /*   160 */    27,  109,  115,  100,   66,   65,   86,  115,   23,  115,
 /*   170 */    14,  115,  115,  125,  127,   74,  115,   36,  123,   84,
 /*   180 */   107,   99,  107,   19,   88,   31,   18,   28,   88,   41,
 /*   190 */    38,   91,   40,   95,    3,   87,   25,   24,   81,  135,
 /*   200 */     1,  125,   73,   26,   93,   71,   69,   34,   85,  108,
 /*   210 */   105,  132,   14,  215,  129,  215,  124,
};
static const YYCODETYPE yy_lookahead[] = {
 /*     0 */     5,   20,   21,   22,   23,   24,   25,   26,   27,   20,
 /*    10 */    21,   22,   23,   24,   25,   20,   21,   22,   23,   24,
 /*    20 */    25,   26,   27,   20,   21,   22,   23,   24,   25,   26,
 /*    30 */    20,   21,   22,   23,   24,   25,    0,    5,    2,    4,
 /*    40 */     7,    8,    3,   10,    9,   52,   53,   48,   49,   14,
 /*    50 */     2,   15,   53,   18,   19,    1,   57,   58,   39,   40,
 /*    60 */    41,   42,   43,   15,   28,   72,   30,   46,   33,   48,
 /*    70 */    49,   35,   52,   53,   53,   36,   28,    9,   30,   53,
 /*    80 */     4,   55,   56,   35,   12,   65,   18,   45,   51,   52,
 /*    90 */    53,   11,   72,   13,   53,   53,   41,   42,   43,   53,
 /*   100 */    53,   33,   61,   53,   63,    9,   64,   61,   61,   63,
 /*   110 */    63,   61,   53,   63,    3,   53,   53,    5,    6,   53,
 /*   120 */    61,    6,   63,   61,   61,   63,   63,   61,   53,   63,
 /*   130 */     4,   53,   53,    5,    6,   11,   61,   13,   63,   61,
 /*   140 */    61,   63,   63,   11,   29,   13,   14,   36,    5,    6,
 /*   150 */    45,   69,   53,   71,   45,   56,   52,   53,   53,   45,
 /*   160 */     6,   45,   53,   45,   45,   67,   68,   53,   45,   53,
 /*   170 */    16,   53,   53,   14,    5,   12,   53,    6,    5,   59,
 /*   180 */    60,   59,   60,    4,   63,   37,    4,   37,   63,   17,
 /*   190 */     6,   70,   17,   34,    4,   70,   31,   29,   47,   44,
 /*   200 */     6,   14,   53,   66,   68,   53,   53,    4,   32,   53,
 /*   210 */    53,   50,   16,   73,   54,   73,   58,
};
#define YY_SHIFT_USE_DFLT (-20)
#define YY_SHIFT_COUNT (82)
#define YY_SHIFT_MIN   (-19)
#define YY_SHIFT_MAX   (203)
static const short yy_shift_ofst[] = {
 /*     0 */    48,  132,  159,  187,   35,   35,   35,   35,   35,   35,
 /*    10 */    35,   35,   35,   35,   35,   36,  187,  187,  187,  187,
 /*    20 */    68,   68,  154,  196,  187,  203,  187,  187,  187,  187,
 /*    30 */   187,  187,  187,  187,  -20,   33,  124,   80,  203,  176,
 /*    40 */   187,  187,  187,  187,  187,  194,  190,   -5,  -19,    3,
 /*    50 */    10,   10,  -11,   10,   10,   10,   10,  -11,  143,  115,
 /*    60 */   111,  128,   39,  112,  168,  184,  165,  175,  172,  150,
 /*    70 */   182,  148,  179,  173,  126,  163,  171,  169,   96,   76,
 /*    80 */    72,   32,   54,
};
#define YY_REDUCE_USE_DFLT (-8)
#define YY_REDUCE_COUNT (46)
#define YY_REDUCE_MIN   (-7)
#define YY_REDUCE_MAX   (161)
static const short yy_reduce_ofst[] = {
 /*     0 */    19,   -1,   20,   21,   79,   78,   75,   66,   63,   62,
 /*    10 */    59,   50,   47,   46,   41,   55,   -7,   42,   37,   26,
 /*    20 */   125,  121,  122,  120,  123,   98,  119,  118,  116,  114,
 /*    30 */   104,  109,  105,   99,   82,  160,  158,  161,  136,  137,
 /*    40 */   157,  156,  153,  152,  149,  151,  155,
};
static const YYACTIONTYPE yy_default[] = {
 /*     0 */   142,  213,  213,  213,  213,  213,  213,  213,  213,  213,
 /*    10 */   213,  213,  213,  213,  213,  142,  213,  213,  213,  213,
 /*    20 */   213,  213,  170,  170,  213,  213,  213,  213,  213,  213,
 /*    30 */   213,  213,  213,  213,  204,  213,  213,  156,  213,  193,
 /*    40 */   213,  213,  213,  213,  213,  163,  213,  213,  172,  187,
 /*    50 */   180,  181,  186,  185,  184,  183,  182,  179,  213,  213,
 /*    60 */   213,  213,  213,  213,  213,  192,  213,  175,  151,  213,
 /*    70 */   213,  213,  213,  213,  213,  213,  164,  213,  213,  213,
 /*    80 */   213,  213,  213,  140,  210,  194,  197,  200,  203,  202,
 /*    90 */   201,  199,  198,  196,  207,  205,  209,  206,  190,  191,
 /*   100 */   189,  195,  178,  177,  176,  174,  173,  171,  208,  212,
 /*   110 */   169,  150,  211,  151,  149,  188,  144,  147,  166,  161,
 /*   120 */   168,  162,  160,  167,  165,  159,  155,  154,  153,  152,
 /*   130 */   158,  157,  148,  146,  145,  143,  141,  139,
};

/* The next table maps tokens into fallback tokens.  If a construct
** like the following:
** 
**      %fallback ID X Y Z.
**
** appears in the grammar, then ID becomes a fallback token for X, Y,
** and Z.  Whenever one of the tokens X, Y, or Z is input to the parser
** but it does not parse, the type of the token is changed to ID and
** the parse is retried before an error is thrown.
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
*/
struct yyStackEntry {
  YYACTIONTYPE stateno;  /* The state-number */
  YYCODETYPE major;      /* The major token value.  This is the code
                         ** number for the token at this stack level */
  YYMINORTYPE minor;     /* The user-supplied minor token value.  This
                         ** is the value of the token  */
};
typedef struct yyStackEntry yyStackEntry;

/* The state of the parser is completely contained in an instance of
** the following structure */
struct yyParser {
  int yyidx;                    /* Index of top element in stack */
#ifdef YYTRACKMAXSTACKDEPTH
  int yyidxMax;                 /* Maximum value of yyidx */
#endif
  int yyerrcnt;                 /* Shifts left before out of the error */
  ParserARG_SDECL                /* A place to hold %extra_argument */
#if YYSTACKDEPTH<=0
  int yystksz;                  /* Current side of the stack */
  yyStackEntry *yystack;        /* The parser's stack */
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
  "LEFTPARENTHESIS",  "RIGHTPARENTHESIS",  "COMMA",         "INT_TYPE",    
  "CHAR_TYPE",     "INTEGER",       "FLOAT_TYPE",    "PRIMARY",     
  "KEY",           "UNIQUE",        "NAME",          "DROP",        
  "WHERE",         "DOT",           "FLOAT",         "NOT",         
  "EQ",            "NE",            "LT",            "GT",          
  "LE",            "GE",            "AND",           "OR",          
  "SELECT",        "FROM",          "INSERT",        "VALUES",      
  "INTO",          "STRING",        "TIMES",         "DELETE",      
  "INDEX",         "ON",            "error",         "start",       
  "cmdList",       "cmdAndEnd",     "cmd",           "create_table",
  "create_table_args",  "table_name",    "columnlist",    "optional_constraint_list",
  "column_define",  "column",        "column_constraint",  "rawcolumnlist",
  "rawcolumn",     "name",          "type_token",    "unique_list", 
  "unique",        "constraint_list",  "table_constraint",  "opt_where_clause",
  "where_clause",  "expr",          "binary_op",     "stringvalue", 
  "table_list",    "select_column_list",  "into",          "valueslist",  
  "values",        "valuelist",     "value",         "beginValue",  
  "full_name",   
};
#endif /* NDEBUG */

#ifndef NDEBUG
/* For tracing reduce actions, the names of all rules are required.
*/
static const char *const yyRuleName[] = {
 /*   0 */ "start ::= cmdList",
 /*   1 */ "cmdList ::= cmdList cmdAndEnd",
 /*   2 */ "cmdList ::= cmdAndEnd",
 /*   3 */ "cmdAndEnd ::= cmd SEMICOLON",
 /*   4 */ "cmd ::=",
 /*   5 */ "cmd ::= create_table create_table_args",
 /*   6 */ "create_table ::= CREATE TABLE table_name",
 /*   7 */ "create_table_args ::= LEFTPARENTHESIS columnlist optional_constraint_list RIGHTPARENTHESIS",
 /*   8 */ "columnlist ::= columnlist COMMA column_define",
 /*   9 */ "columnlist ::= column_define",
 /*  10 */ "column_define ::= column column_constraint",
 /*  11 */ "rawcolumnlist ::= rawcolumnlist COMMA rawcolumn",
 /*  12 */ "rawcolumnlist ::= rawcolumn",
 /*  13 */ "rawcolumn ::= name",
 /*  14 */ "column ::= name type_token",
 /*  15 */ "type_token ::= INT_TYPE",
 /*  16 */ "type_token ::= CHAR_TYPE LEFTPARENTHESIS INTEGER RIGHTPARENTHESIS",
 /*  17 */ "type_token ::= FLOAT_TYPE",
 /*  18 */ "column_constraint ::=",
 /*  19 */ "column_constraint ::= PRIMARY KEY",
 /*  20 */ "column_constraint ::= UNIQUE",
 /*  21 */ "name ::= NAME",
 /*  22 */ "unique_list ::= unique_list COMMA unique",
 /*  23 */ "unique_list ::= unique",
 /*  24 */ "unique ::= name",
 /*  25 */ "optional_constraint_list ::=",
 /*  26 */ "optional_constraint_list ::= COMMA constraint_list",
 /*  27 */ "constraint_list ::= constraint_list COMMA table_constraint",
 /*  28 */ "constraint_list ::= table_constraint",
 /*  29 */ "table_constraint ::= PRIMARY KEY LEFTPARENTHESIS name RIGHTPARENTHESIS",
 /*  30 */ "table_constraint ::= UNIQUE LEFTPARENTHESIS unique_list RIGHTPARENTHESIS",
 /*  31 */ "cmd ::= DROP TABLE table_name",
 /*  32 */ "opt_where_clause ::=",
 /*  33 */ "opt_where_clause ::= where_clause",
 /*  34 */ "where_clause ::= WHERE expr",
 /*  35 */ "expr ::= stringvalue",
 /*  36 */ "expr ::= name DOT name",
 /*  37 */ "expr ::= name",
 /*  38 */ "expr ::= INTEGER",
 /*  39 */ "expr ::= FLOAT",
 /*  40 */ "expr ::= LEFTPARENTHESIS expr RIGHTPARENTHESIS",
 /*  41 */ "expr ::= NOT expr",
 /*  42 */ "expr ::= expr EQ expr",
 /*  43 */ "expr ::= expr NE expr",
 /*  44 */ "expr ::= expr LT expr",
 /*  45 */ "expr ::= expr GT expr",
 /*  46 */ "expr ::= expr LE expr",
 /*  47 */ "expr ::= expr GE expr",
 /*  48 */ "expr ::= expr AND expr",
 /*  49 */ "expr ::= expr OR expr",
 /*  50 */ "table_name ::= name",
 /*  51 */ "table_list ::= table_list COMMA table_name",
 /*  52 */ "table_list ::= table_name",
 /*  53 */ "cmd ::= SELECT select_column_list FROM table_list opt_where_clause",
 /*  54 */ "cmd ::= INSERT into table_name VALUES valueslist",
 /*  55 */ "into ::=",
 /*  56 */ "into ::= INTO",
 /*  57 */ "stringvalue ::= STRING",
 /*  58 */ "valueslist ::= valueslist COMMA values",
 /*  59 */ "valueslist ::= values",
 /*  60 */ "values ::= LEFTPARENTHESIS valuelist RIGHTPARENTHESIS",
 /*  61 */ "valuelist ::= valuelist COMMA value",
 /*  62 */ "valuelist ::= beginValue value",
 /*  63 */ "value ::= FLOAT",
 /*  64 */ "value ::= INTEGER",
 /*  65 */ "value ::= stringvalue",
 /*  66 */ "beginValue ::=",
 /*  67 */ "select_column_list ::= TIMES",
 /*  68 */ "select_column_list ::= select_column_list COMMA full_name",
 /*  69 */ "select_column_list ::= full_name",
 /*  70 */ "full_name ::= name DOT name",
 /*  71 */ "full_name ::= rawcolumn",
 /*  72 */ "cmd ::= DELETE FROM table_name opt_where_clause",
 /*  73 */ "cmd ::= CREATE INDEX name ON table_name LEFTPARENTHESIS rawcolumnlist RIGHTPARENTHESIS",
 /*  74 */ "cmd ::= DROP INDEX name ON table_name",
};
#endif /* NDEBUG */


#if YYSTACKDEPTH<=0
/*
** Try to increase the size of the parser stack.
*/
static void yyGrowStack(yyParser *p){
  int newSize;
  yyStackEntry *pNew;

  newSize = p->yystksz*2 + 100;
  pNew = realloc(p->yystack, newSize*sizeof(pNew[0]));
  if( pNew ){
    p->yystack = pNew;
    p->yystksz = newSize;
#ifndef NDEBUG
    if( yyTraceFILE ){
      fprintf(yyTraceFILE,"%sStack grows to %d entries!\n",
              yyTracePrompt, p->yystksz);
    }
#endif
  }
}
#endif

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
void *ParserAlloc(void *(*mallocProc)(size_t)){
  yyParser *pParser;
  pParser = (yyParser*)(*mallocProc)( (size_t)sizeof(yyParser) );
  if( pParser ){
    pParser->yyidx = -1;
#ifdef YYTRACKMAXSTACKDEPTH
    pParser->yyidxMax = 0;
#endif
#if YYSTACKDEPTH<=0
    pParser->yystack = NULL;
    pParser->yystksz = 0;
    yyGrowStack(pParser);
#endif
  }
  return pParser;
}

/* The following function deletes the value associated with a
** symbol.  The symbol can be either a terminal or nonterminal.
** "yymajor" is the symbol code, and "yypminor" is a pointer to
** the value.
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
    ** which appear on the RHS of the rule, but which are not used
    ** inside the C code.
    */
      /* TERMINAL Destructor */
    case 1: /* SEMICOLON */
    case 2: /* CREATE */
    case 3: /* TABLE */
    case 4: /* LEFTPARENTHESIS */
    case 5: /* RIGHTPARENTHESIS */
    case 6: /* COMMA */
    case 7: /* INT_TYPE */
    case 8: /* CHAR_TYPE */
    case 9: /* INTEGER */
    case 10: /* FLOAT_TYPE */
    case 11: /* PRIMARY */
    case 12: /* KEY */
    case 13: /* UNIQUE */
    case 14: /* NAME */
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
    case 33: /* STRING */
    case 34: /* TIMES */
    case 35: /* DELETE */
    case 36: /* INDEX */
    case 37: /* ON */
{
#line 3 "parser.y"
delete (yypminor->yy0);
#line 561 "parser.c"
}
      break;
    default:  break;   /* If no destructor action specified: do nothing */
  }
}

/*
** Pop the parser's stack once.
**
** If there is a destructor routine associated with the token which
** is popped from the stack, then call it.
**
** Return the major token number for the symbol popped.
*/
static int yy_pop_parser_stack(yyParser *pParser){
  YYCODETYPE yymajor;
  yyStackEntry *yytos = &pParser->yystack[pParser->yyidx];

  if( pParser->yyidx<0 ) return 0;
#ifndef NDEBUG
  if( yyTraceFILE && pParser->yyidx>=0 ){
    fprintf(yyTraceFILE,"%sPopping %s\n",
      yyTracePrompt,
      yyTokenName[yytos->major]);
  }
#endif
  yymajor = yytos->major;
  yy_destructor(pParser, yymajor, &yytos->minor);
  pParser->yyidx--;
  return yymajor;
}

/* 
** Deallocate and destroy a parser.  Destructors are all called for
** all stack elements before shutting the parser down.
**
** Inputs:
** <ul>
** <li>  A pointer to the parser.  This should be a pointer
**       obtained from ParserAlloc.
** <li>  A pointer to a function used to reclaim memory obtained
**       from malloc.
** </ul>
*/
void ParserFree(
  void *p,                    /* The parser to be deleted */
  void (*freeProc)(void*)     /* Function used to reclaim memory */
){
  yyParser *pParser = (yyParser*)p;
  if( pParser==0 ) return;
  while( pParser->yyidx>=0 ) yy_pop_parser_stack(pParser);
#if YYSTACKDEPTH<=0
  free(pParser->yystack);
#endif
  (*freeProc)((void*)pParser);
}

/*
** Return the peak depth of the stack for a parser.
*/
#ifdef YYTRACKMAXSTACKDEPTH
int ParserStackPeak(void *p){
  yyParser *pParser = (yyParser*)p;
  return pParser->yyidxMax;
}
#endif

/*
** Find the appropriate action for a parser given the terminal
** look-ahead token iLookAhead.
**
** If the look-ahead token is YYNOCODE, then check to see if the action is
** independent of the look-ahead.  If it is, return the action, otherwise
** return YY_NO_ACTION.
*/
static int yy_find_shift_action(
  yyParser *pParser,        /* The parser */
  YYCODETYPE iLookAhead     /* The look-ahead token */
){
  int i;
  int stateno = pParser->yystack[pParser->yyidx].stateno;
 
  if( stateno>YY_SHIFT_COUNT
   || (i = yy_shift_ofst[stateno])==YY_SHIFT_USE_DFLT ){
    return yy_default[stateno];
  }
  assert( iLookAhead!=YYNOCODE );
  i += iLookAhead;
  if( i<0 || i>=YY_ACTTAB_COUNT || yy_lookahead[i]!=iLookAhead ){
    if( iLookAhead>0 ){
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
        return yy_find_shift_action(pParser, iFallback);
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
          yy_lookahead[j]==YYWILDCARD
        ){
#ifndef NDEBUG
          if( yyTraceFILE ){
            fprintf(yyTraceFILE, "%sWILDCARD %s => %s\n",
               yyTracePrompt, yyTokenName[iLookAhead], yyTokenName[YYWILDCARD]);
          }
#endif /* NDEBUG */
          return yy_action[j];
        }
      }
#endif /* YYWILDCARD */
    }
    return yy_default[stateno];
  }else{
    return yy_action[i];
  }
}

/*
** Find the appropriate action for a parser given the non-terminal
** look-ahead token iLookAhead.
**
** If the look-ahead token is YYNOCODE, then check to see if the action is
** independent of the look-ahead.  If it is, return the action, otherwise
** return YY_NO_ACTION.
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
static void yyStackOverflow(yyParser *yypParser, YYMINORTYPE *yypMinor){
   ParserARG_FETCH;
   yypParser->yyidx--;
#ifndef NDEBUG
   if( yyTraceFILE ){
     fprintf(yyTraceFILE,"%sStack Overflow!\n",yyTracePrompt);
   }
#endif
   while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
   /* Here code is inserted which will execute if the parser
   ** stack every overflows */
#line 26 "parser.y"

    interpreter->error("Stack overflow.");
#line 746 "parser.c"
   ParserARG_STORE; /* Suppress warning about unused %extra_argument var */
}

/*
** Perform a shift action.
*/
static void yy_shift(
  yyParser *yypParser,          /* The parser to be shifted */
  int yyNewState,               /* The new state to shift in */
  int yyMajor,                  /* The major token to shift in */
  YYMINORTYPE *yypMinor         /* Pointer to the minor token to shift in */
){
  yyStackEntry *yytos;
  yypParser->yyidx++;
#ifdef YYTRACKMAXSTACKDEPTH
  if( yypParser->yyidx>yypParser->yyidxMax ){
    yypParser->yyidxMax = yypParser->yyidx;
  }
#endif
#if YYSTACKDEPTH>0 
  if( yypParser->yyidx>=YYSTACKDEPTH ){
    yyStackOverflow(yypParser, yypMinor);
    return;
  }
#else
  if( yypParser->yyidx>=yypParser->yystksz ){
    yyGrowStack(yypParser);
    if( yypParser->yyidx>=yypParser->yystksz ){
      yyStackOverflow(yypParser, yypMinor);
      return;
    }
  }
#endif
  yytos = &yypParser->yystack[yypParser->yyidx];
  yytos->stateno = (YYACTIONTYPE)yyNewState;
  yytos->major = (YYCODETYPE)yyMajor;
  yytos->minor = *yypMinor;
#ifndef NDEBUG
  if( yyTraceFILE && yypParser->yyidx>0 ){
    int i;
    fprintf(yyTraceFILE,"%sShift %d\n",yyTracePrompt,yyNewState);
    fprintf(yyTraceFILE,"%sStack:",yyTracePrompt);
    for(i=1; i<=yypParser->yyidx; i++)
      fprintf(yyTraceFILE," %s",yyTokenName[yypParser->yystack[i].major]);
    fprintf(yyTraceFILE,"\n");
  }
#endif
}

/* The following table contains information about every rule that
** is used during the reduce.
*/
static const struct {
  YYCODETYPE lhs;         /* Symbol on the left-hand side of the rule */
  unsigned char nrhs;     /* Number of right-hand side symbols in the rule */
} yyRuleInfo[] = {
  { 39, 1 },
  { 40, 2 },
  { 40, 1 },
  { 41, 2 },
  { 42, 0 },
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
  { 61, 1 },
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
  { 64, 3 },
  { 64, 1 },
  { 42, 5 },
  { 42, 5 },
  { 66, 0 },
  { 66, 1 },
  { 63, 1 },
  { 67, 3 },
  { 67, 1 },
  { 68, 3 },
  { 69, 3 },
  { 69, 2 },
  { 70, 1 },
  { 70, 1 },
  { 70, 1 },
  { 71, 0 },
  { 65, 1 },
  { 65, 3 },
  { 65, 1 },
  { 72, 3 },
  { 72, 1 },
  { 42, 4 },
  { 42, 8 },
  { 42, 5 },
};

static void yy_accept(yyParser*);  /* Forward Declaration */

/*
** Perform a reduce action and the shift that must immediately
** follow the reduce.
*/
static void yy_reduce(
  yyParser *yypParser,         /* The parser */
  int yyruleno                 /* Number of the rule by which to reduce */
){
  int yygoto;                     /* The next state */
  int yyact;                      /* The next action */
  YYMINORTYPE yygotominor;        /* The LHS of the rule reduced */
  yyStackEntry *yymsp;            /* The top of the parser's stack */
  int yysize;                     /* Amount to pop the stack */
  ParserARG_FETCH;
  yymsp = &yypParser->yystack[yypParser->yyidx];
#ifndef NDEBUG
  if( yyTraceFILE && yyruleno>=0 
        && yyruleno<(int)(sizeof(yyRuleName)/sizeof(yyRuleName[0])) ){
    fprintf(yyTraceFILE, "%sReduce [%s].\n", yyTracePrompt,
      yyRuleName[yyruleno]);
  }
#endif /* NDEBUG */

  /* Silence complaints from purify about yygotominor being uninitialized
  ** in some cases when it is copied into the stack after the following
  ** switch.  yygotominor is uninitialized when a rule reduces that does
  ** not set the value of its left-hand side nonterminal.  Leaving the
  ** value of the nonterminal uninitialized is utterly harmless as long
  ** as the value is never used.  So really the only thing this code
  ** accomplishes is to quieten purify.  
  **
  ** 2007-01-16:  The wireshark project (www.wireshark.org) reports that
  ** without this code, their parser segfaults.  I'm not sure what there
  ** parser is doing to make this happen.  This is the second bug report
  ** from wireshark this week.  Clearly they are stressing Lemon in ways
  ** that it has not been previously stressed...  (SQLite ticket #2172)
  */
  /*memset(&yygotominor, 0, sizeof(yygotominor));*/
  yygotominor = yyzerominor;


  switch( yyruleno ){
  /* Beginning here are the reduction cases.  A typical example
  ** follows:
  **   case 0:
  **  #line <lineno> <grammarfile>
  **     { ... }           // User supplied code
  **  #line <lineno> <thisfile>
  **     break;
  */
      case 3: /* cmdAndEnd ::= cmd SEMICOLON */
#line 53 "parser.y"
{
  yy_destructor(yypParser,1,&yymsp[0].minor);
}
#line 937 "parser.c"
        break;
      case 5: /* cmd ::= create_table create_table_args */
#line 57 "parser.y"
{
    interpreter->setActionType(Action::CreateTable);
}
#line 944 "parser.c"
        break;
      case 6: /* create_table ::= CREATE TABLE table_name */
#line 61 "parser.y"
{
  yy_destructor(yypParser,2,&yymsp[-2].minor);
  yy_destructor(yypParser,3,&yymsp[-1].minor);
}
#line 952 "parser.c"
        break;
      case 7: /* create_table_args ::= LEFTPARENTHESIS columnlist optional_constraint_list RIGHTPARENTHESIS */
#line 64 "parser.y"
{
  yy_destructor(yypParser,4,&yymsp[-3].minor);
  yy_destructor(yypParser,5,&yymsp[0].minor);
}
#line 960 "parser.c"
        break;
      case 8: /* columnlist ::= columnlist COMMA column_define */
      case 11: /* rawcolumnlist ::= rawcolumnlist COMMA rawcolumn */ yytestcase(yyruleno==11);
      case 22: /* unique_list ::= unique_list COMMA unique */ yytestcase(yyruleno==22);
      case 26: /* optional_constraint_list ::= COMMA constraint_list */ yytestcase(yyruleno==26);
      case 27: /* constraint_list ::= constraint_list COMMA table_constraint */ yytestcase(yyruleno==27);
      case 51: /* table_list ::= table_list COMMA table_name */ yytestcase(yyruleno==51);
      case 58: /* valueslist ::= valueslist COMMA values */ yytestcase(yyruleno==58);
      case 61: /* valuelist ::= valuelist COMMA value */ yytestcase(yyruleno==61);
      case 68: /* select_column_list ::= select_column_list COMMA full_name */ yytestcase(yyruleno==68);
#line 67 "parser.y"
{
  yy_destructor(yypParser,6,&yymsp[-1].minor);
}
#line 975 "parser.c"
        break;
      case 10: /* column_define ::= column column_constraint */
#line 69 "parser.y"
{
    interpreter->newConstraint(*yymsp[-1].minor.yy0,yymsp[0].minor.yy112);
}
#line 982 "parser.c"
        break;
      case 13: /* rawcolumn ::= name */
#line 75 "parser.y"
{
    interpreter->newColumn(*yymsp[0].minor.yy0,Column::Undefined);
}
#line 989 "parser.c"
        break;
      case 14: /* column ::= name type_token */
#line 79 "parser.y"
{
    interpreter->newColumn(*yymsp[-1].minor.yy0, yymsp[0].minor.yy11);
    yygotominor.yy0 = yymsp[-1].minor.yy0;
}
#line 997 "parser.c"
        break;
      case 15: /* type_token ::= INT_TYPE */
#line 86 "parser.y"
{ yygotominor.yy11 = Column::Int;   yy_destructor(yypParser,7,&yymsp[0].minor);
}
#line 1003 "parser.c"
        break;
      case 16: /* type_token ::= CHAR_TYPE LEFTPARENTHESIS INTEGER RIGHTPARENTHESIS */
#line 87 "parser.y"
{ yygotominor.yy11 = stoi(*yymsp[-1].minor.yy0);  yy_destructor(yypParser,8,&yymsp[-3].minor);
  yy_destructor(yypParser,4,&yymsp[-2].minor);
  yy_destructor(yypParser,5,&yymsp[0].minor);
}
#line 1011 "parser.c"
        break;
      case 17: /* type_token ::= FLOAT_TYPE */
#line 88 "parser.y"
{ yygotominor.yy11 = Column::Float;  yy_destructor(yypParser,10,&yymsp[0].minor);
}
#line 1017 "parser.c"
        break;
      case 18: /* column_constraint ::= */
#line 91 "parser.y"
{yygotominor.yy112 = Constraint::None;}
#line 1022 "parser.c"
        break;
      case 19: /* column_constraint ::= PRIMARY KEY */
#line 92 "parser.y"
{yygotominor.yy112 = Constraint::PrimaryKey;  yy_destructor(yypParser,11,&yymsp[-1].minor);
  yy_destructor(yypParser,12,&yymsp[0].minor);
}
#line 1029 "parser.c"
        break;
      case 20: /* column_constraint ::= UNIQUE */
#line 93 "parser.y"
{yygotominor.yy112 = Constraint::Unique;  yy_destructor(yypParser,13,&yymsp[0].minor);
}
#line 1035 "parser.c"
        break;
      case 21: /* name ::= NAME */
#line 95 "parser.y"
{yygotominor.yy0=yymsp[0].minor.yy0;}
#line 1040 "parser.c"
        break;
      case 24: /* unique ::= name */
#line 99 "parser.y"
{
    interpreter->newConstraint(*yymsp[0].minor.yy0,Constraint::Unique);
}
#line 1047 "parser.c"
        break;
      case 29: /* table_constraint ::= PRIMARY KEY LEFTPARENTHESIS name RIGHTPARENTHESIS */
#line 109 "parser.y"
{
    interpreter->newConstraint(*yymsp[-1].minor.yy0,Constraint::PrimaryKey);
  yy_destructor(yypParser,11,&yymsp[-4].minor);
  yy_destructor(yypParser,12,&yymsp[-3].minor);
  yy_destructor(yypParser,4,&yymsp[-2].minor);
  yy_destructor(yypParser,5,&yymsp[0].minor);
}
#line 1058 "parser.c"
        break;
      case 30: /* table_constraint ::= UNIQUE LEFTPARENTHESIS unique_list RIGHTPARENTHESIS */
#line 113 "parser.y"
{
  yy_destructor(yypParser,13,&yymsp[-3].minor);
  yy_destructor(yypParser,4,&yymsp[-2].minor);
  yy_destructor(yypParser,5,&yymsp[0].minor);
}
#line 1067 "parser.c"
        break;
      case 31: /* cmd ::= DROP TABLE table_name */
#line 117 "parser.y"
{
    interpreter->setActionType(Action::DropTable);
  yy_destructor(yypParser,15,&yymsp[-2].minor);
  yy_destructor(yypParser,3,&yymsp[-1].minor);
}
#line 1076 "parser.c"
        break;
      case 34: /* where_clause ::= WHERE expr */
#line 128 "parser.y"
{
    interpreter->newCondition(yymsp[0].minor.yy116);
  yy_destructor(yypParser,16,&yymsp[-1].minor);
}
#line 1084 "parser.c"
        break;
      case 35: /* expr ::= stringvalue */
#line 142 "parser.y"
{
    yygotominor.yy116 = interpreter->newCondition(*yymsp[0].minor.yy0,yymsp[0].minor.yy0->length());
}
#line 1091 "parser.c"
        break;
      case 36: /* expr ::= name DOT name */
#line 146 "parser.y"
{
    yygotominor.yy116 = interpreter->newCondition(*yymsp[0].minor.yy0,Column::Undefined, *yymsp[-2].minor.yy0);
  yy_destructor(yypParser,17,&yymsp[-1].minor);
}
#line 1099 "parser.c"
        break;
      case 37: /* expr ::= name */
#line 150 "parser.y"
{
    yygotominor.yy116 = interpreter->newCondition(*yymsp[0].minor.yy0,Column::Undefined);
}
#line 1106 "parser.c"
        break;
      case 38: /* expr ::= INTEGER */
#line 154 "parser.y"
{
    yygotominor.yy116 = interpreter->newCondition(*yymsp[0].minor.yy0,Column::Int);
}
#line 1113 "parser.c"
        break;
      case 39: /* expr ::= FLOAT */
#line 157 "parser.y"
{
    yygotominor.yy116 = interpreter->newCondition(*yymsp[0].minor.yy0,Column::Float);
}
#line 1120 "parser.c"
        break;
      case 40: /* expr ::= LEFTPARENTHESIS expr RIGHTPARENTHESIS */
#line 161 "parser.y"
{
    yygotominor.yy116 = yymsp[-1].minor.yy116;
  yy_destructor(yypParser,4,&yymsp[-2].minor);
  yy_destructor(yypParser,5,&yymsp[0].minor);
}
#line 1129 "parser.c"
        break;
      case 41: /* expr ::= NOT expr */
#line 165 "parser.y"
{
    yygotominor.yy116 = interpreter->newCondition(Condition::Not, yymsp[0].minor.yy116);
  yy_destructor(yypParser,19,&yymsp[-1].minor);
}
#line 1137 "parser.c"
        break;
      case 42: /* expr ::= expr EQ expr */
#line 169 "parser.y"
{
    yygotominor.yy116 = interpreter->newCondition(Condition::Equal,yymsp[-2].minor.yy116,yymsp[0].minor.yy116); 
  yy_destructor(yypParser,20,&yymsp[-1].minor);
}
#line 1145 "parser.c"
        break;
      case 43: /* expr ::= expr NE expr */
#line 172 "parser.y"
{
    yygotominor.yy116 = interpreter->newCondition(Condition::NotEqual,yymsp[-2].minor.yy116,yymsp[0].minor.yy116); 
  yy_destructor(yypParser,21,&yymsp[-1].minor);
}
#line 1153 "parser.c"
        break;
      case 44: /* expr ::= expr LT expr */
#line 175 "parser.y"
{
    yygotominor.yy116 = interpreter->newCondition(Condition::LessThan,yymsp[-2].minor.yy116,yymsp[0].minor.yy116); 
  yy_destructor(yypParser,22,&yymsp[-1].minor);
}
#line 1161 "parser.c"
        break;
      case 45: /* expr ::= expr GT expr */
#line 178 "parser.y"
{
    yygotominor.yy116 = interpreter->newCondition(Condition::GreaterThan,yymsp[-2].minor.yy116,yymsp[0].minor.yy116); 
  yy_destructor(yypParser,23,&yymsp[-1].minor);
}
#line 1169 "parser.c"
        break;
      case 46: /* expr ::= expr LE expr */
#line 181 "parser.y"
{
    yygotominor.yy116 = interpreter->newCondition(Condition::LessEqual,yymsp[-2].minor.yy116,yymsp[0].minor.yy116); 
  yy_destructor(yypParser,24,&yymsp[-1].minor);
}
#line 1177 "parser.c"
        break;
      case 47: /* expr ::= expr GE expr */
#line 184 "parser.y"
{
    yygotominor.yy116 = interpreter->newCondition(Condition::GreaterEqual,yymsp[-2].minor.yy116,yymsp[0].minor.yy116); 
  yy_destructor(yypParser,25,&yymsp[-1].minor);
}
#line 1185 "parser.c"
        break;
      case 48: /* expr ::= expr AND expr */
#line 188 "parser.y"
{
    yygotominor.yy116 = interpreter->newCondition(Condition::And,yymsp[-2].minor.yy116,yymsp[0].minor.yy116); 
  yy_destructor(yypParser,26,&yymsp[-1].minor);
}
#line 1193 "parser.c"
        break;
      case 49: /* expr ::= expr OR expr */
#line 192 "parser.y"
{
    yygotominor.yy116 = interpreter->newCondition(Condition::Or,yymsp[-2].minor.yy116,yymsp[0].minor.yy116); 
  yy_destructor(yypParser,27,&yymsp[-1].minor);
}
#line 1201 "parser.c"
        break;
      case 50: /* table_name ::= name */
#line 202 "parser.y"
{
    interpreter->addTableName(*yymsp[0].minor.yy0);
}
#line 1208 "parser.c"
        break;
      case 53: /* cmd ::= SELECT select_column_list FROM table_list opt_where_clause */
#line 210 "parser.y"
{
    interpreter->setActionType(Action::Select);
    
  yy_destructor(yypParser,28,&yymsp[-4].minor);
  yy_destructor(yypParser,29,&yymsp[-2].minor);
}
#line 1218 "parser.c"
        break;
      case 54: /* cmd ::= INSERT into table_name VALUES valueslist */
#line 216 "parser.y"
{
   interpreter->setActionType(Action::Insert);
  yy_destructor(yypParser,30,&yymsp[-4].minor);
  yy_destructor(yypParser,31,&yymsp[-1].minor);
}
#line 1227 "parser.c"
        break;
      case 56: /* into ::= INTO */
#line 221 "parser.y"
{
  yy_destructor(yypParser,32,&yymsp[0].minor);
}
#line 1234 "parser.c"
        break;
      case 57: /* stringvalue ::= STRING */
#line 223 "parser.y"
{
    yygotominor.yy0 = new string(yymsp[0].minor.yy0->substr(1,yymsp[0].minor.yy0->length()-2));
    delete yymsp[0].minor.yy0;
}
#line 1242 "parser.c"
        break;
      case 60: /* values ::= LEFTPARENTHESIS valuelist RIGHTPARENTHESIS */
#line 230 "parser.y"
{
  yy_destructor(yypParser,4,&yymsp[-2].minor);
  yy_destructor(yypParser,5,&yymsp[0].minor);
}
#line 1250 "parser.c"
        break;
      case 63: /* value ::= FLOAT */
#line 234 "parser.y"
{
    interpreter->addValue(*yymsp[0].minor.yy0, Column::Float);
}
#line 1257 "parser.c"
        break;
      case 64: /* value ::= INTEGER */
#line 237 "parser.y"
{
    interpreter->addValue(*yymsp[0].minor.yy0, Column::Int);
}
#line 1264 "parser.c"
        break;
      case 65: /* value ::= stringvalue */
#line 240 "parser.y"
{
    interpreter->addValue(*yymsp[0].minor.yy0, yymsp[0].minor.yy0->length());
}
#line 1271 "parser.c"
        break;
      case 66: /* beginValue ::= */
#line 243 "parser.y"
{
    interpreter->beginValue();
}
#line 1278 "parser.c"
        break;
      case 67: /* select_column_list ::= TIMES */
#line 246 "parser.y"
{  yy_destructor(yypParser,34,&yymsp[0].minor);
}
#line 1284 "parser.c"
        break;
      case 70: /* full_name ::= name DOT name */
#line 252 "parser.y"
{
    interpreter->newColumn(*yymsp[0].minor.yy0,Column::Undefined, *yymsp[-2].minor.yy0);
  yy_destructor(yypParser,17,&yymsp[-1].minor);
}
#line 1292 "parser.c"
        break;
      case 72: /* cmd ::= DELETE FROM table_name opt_where_clause */
#line 260 "parser.y"
{
    interpreter->setActionType(Action::Delete);
  yy_destructor(yypParser,35,&yymsp[-3].minor);
  yy_destructor(yypParser,29,&yymsp[-2].minor);
}
#line 1301 "parser.c"
        break;
      case 73: /* cmd ::= CREATE INDEX name ON table_name LEFTPARENTHESIS rawcolumnlist RIGHTPARENTHESIS */
#line 266 "parser.y"
{
    interpreter->setActionType(Action::CreateIndex);
    interpreter->addIndexName(*yymsp[-5].minor.yy0);
  yy_destructor(yypParser,2,&yymsp[-7].minor);
  yy_destructor(yypParser,36,&yymsp[-6].minor);
  yy_destructor(yypParser,37,&yymsp[-4].minor);
  yy_destructor(yypParser,4,&yymsp[-2].minor);
  yy_destructor(yypParser,5,&yymsp[0].minor);
}
#line 1314 "parser.c"
        break;
      case 74: /* cmd ::= DROP INDEX name ON table_name */
#line 273 "parser.y"
{
    interpreter->setActionType(Action::DropIndex);
    interpreter->addIndexName(*yymsp[-2].minor.yy0);
  yy_destructor(yypParser,15,&yymsp[-4].minor);
  yy_destructor(yypParser,36,&yymsp[-3].minor);
  yy_destructor(yypParser,37,&yymsp[-1].minor);
}
#line 1325 "parser.c"
        break;
      default:
      /* (0) start ::= cmdList */ yytestcase(yyruleno==0);
      /* (1) cmdList ::= cmdList cmdAndEnd */ yytestcase(yyruleno==1);
      /* (2) cmdList ::= cmdAndEnd */ yytestcase(yyruleno==2);
      /* (4) cmd ::= */ yytestcase(yyruleno==4);
      /* (9) columnlist ::= column_define */ yytestcase(yyruleno==9);
      /* (12) rawcolumnlist ::= rawcolumn */ yytestcase(yyruleno==12);
      /* (23) unique_list ::= unique */ yytestcase(yyruleno==23);
      /* (25) optional_constraint_list ::= */ yytestcase(yyruleno==25);
      /* (28) constraint_list ::= table_constraint */ yytestcase(yyruleno==28);
      /* (32) opt_where_clause ::= */ yytestcase(yyruleno==32);
      /* (33) opt_where_clause ::= where_clause */ yytestcase(yyruleno==33);
      /* (52) table_list ::= table_name */ yytestcase(yyruleno==52);
      /* (55) into ::= */ yytestcase(yyruleno==55);
      /* (59) valueslist ::= values */ yytestcase(yyruleno==59);
      /* (62) valuelist ::= beginValue value */ yytestcase(yyruleno==62);
      /* (69) select_column_list ::= full_name */ yytestcase(yyruleno==69);
      /* (71) full_name ::= rawcolumn */ yytestcase(yyruleno==71);
        break;
  };
  yygoto = yyRuleInfo[yyruleno].lhs;
  yysize = yyRuleInfo[yyruleno].nrhs;
  yypParser->yyidx -= yysize;
  yyact = yy_find_reduce_action(yymsp[-yysize].stateno,(YYCODETYPE)yygoto);
  if( yyact < YYNSTATE ){
#ifdef NDEBUG
    /* If we are not debugging and the reduce action popped at least
    ** one element off the stack, then we can push the new element back
    ** onto the stack here, and skip the stack overflow test in yy_shift().
    ** That gives a significant speed improvement. */
    if( yysize ){
      yypParser->yyidx++;
      yymsp -= yysize-1;
      yymsp->stateno = (YYACTIONTYPE)yyact;
      yymsp->major = (YYCODETYPE)yygoto;
      yymsp->minor = yygotominor;
    }else
#endif
    {
      yy_shift(yypParser,yyact,yygoto,&yygotominor);
    }
  }else{
    assert( yyact == YYNSTATE + YYNRULE + 1 );
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
  while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
  /* Here code is inserted which will be executed whenever the
  ** parser fails */
  ParserARG_STORE; /* Suppress warning about unused %extra_argument variable */
}
#endif /* YYNOERRORRECOVERY */

/*
** The following code executes when a syntax error first occurs.
*/
static void yy_syntax_error(
  yyParser *yypParser,           /* The parser */
  int yymajor,                   /* The major type of the error token */
  YYMINORTYPE yyminor            /* The minor type of the error token */
){
  ParserARG_FETCH;
#define TOKEN (yyminor.yy0)
#line 9 "parser.y"

    //cout<<"error"<<endl;
    int n = sizeof(yyTokenName) / sizeof(yyTokenName[0]);
    string expect = "Syntax error.\n";
    expect += "Expected token:\n";
    for (int i = 0; i < n; ++i) {
            int a = yy_find_shift_action(yypParser, (YYCODETYPE)i);
            if (a < YYNSTATE + YYNRULE) {
                    expect += '\t';
                    expect += yyTokenName[i];
                    expect += '\n';
            }
    }
    expect.pop_back();
    interpreter->error(expect);
#line 1420 "parser.c"
  ParserARG_STORE; /* Suppress warning about unused %extra_argument variable */
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
  while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
  /* Here code is inserted which will be executed whenever the
  ** parser accepts */
  ParserARG_STORE; /* Suppress warning about unused %extra_argument variable */
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
  int yyact;            /* The parser action. */
  int yyendofinput;     /* True if we are at the end of input */
#ifdef YYERRORSYMBOL
  int yyerrorhit = 0;   /* True if yymajor has invoked an error */
#endif
  yyParser *yypParser;  /* The parser */

  /* (re)initialize the parser, if necessary */
  yypParser = (yyParser*)yyp;
  if( yypParser->yyidx<0 ){
#if YYSTACKDEPTH<=0
    if( yypParser->yystksz <=0 ){
      /*memset(&yyminorunion, 0, sizeof(yyminorunion));*/
      yyminorunion = yyzerominor;
      yyStackOverflow(yypParser, &yyminorunion);
      return;
    }
#endif
    yypParser->yyidx = 0;
    yypParser->yyerrcnt = -1;
    yypParser->yystack[0].stateno = 0;
    yypParser->yystack[0].major = 0;
  }
  yyminorunion.yy0 = yyminor;
  yyendofinput = (yymajor==0);
  ParserARG_STORE;

#ifndef NDEBUG
  if( yyTraceFILE ){
    fprintf(yyTraceFILE,"%sInput %s\n",yyTracePrompt,yyTokenName[yymajor]);
  }
#endif

  do{
    yyact = yy_find_shift_action(yypParser,(YYCODETYPE)yymajor);
    if( yyact<YYNSTATE ){
      assert( !yyendofinput );  /* Impossible to shift the $ token */
      yy_shift(yypParser,yyact,yymajor,&yyminorunion);
      yypParser->yyerrcnt--;
      yymajor = YYNOCODE;
    }else if( yyact < YYNSTATE + YYNRULE ){
      yy_reduce(yypParser,yyact-YYNSTATE);
    }else{
      assert( yyact == YY_ERROR_ACTION );
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
        yy_syntax_error(yypParser,yymajor,yyminorunion);
      }
      yymx = yypParser->yystack[yypParser->yyidx].major;
      if( yymx==YYERRORSYMBOL || yyerrorhit ){
#ifndef NDEBUG
        if( yyTraceFILE ){
          fprintf(yyTraceFILE,"%sDiscard input token %s\n",
             yyTracePrompt,yyTokenName[yymajor]);
        }
#endif
        yy_destructor(yypParser, (YYCODETYPE)yymajor,&yyminorunion);
        yymajor = YYNOCODE;
      }else{
         while(
          yypParser->yyidx >= 0 &&
          yymx != YYERRORSYMBOL &&
          (yyact = yy_find_reduce_action(
                        yypParser->yystack[yypParser->yyidx].stateno,
                        YYERRORSYMBOL)) >= YYNSTATE
        ){
          yy_pop_parser_stack(yypParser);
        }
        if( yypParser->yyidx < 0 || yymajor==0 ){
          yy_destructor(yypParser,(YYCODETYPE)yymajor,&yyminorunion);
          yy_parse_failed(yypParser);
          yymajor = YYNOCODE;
        }else if( yymx!=YYERRORSYMBOL ){
          YYMINORTYPE u2;
          u2.YYERRSYMDT = 0;
          yy_shift(yypParser,yyact,YYERRORSYMBOL,&u2);
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
      yy_syntax_error(yypParser,yymajor,yyminorunion);
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
        yy_syntax_error(yypParser,yymajor,yyminorunion);
      }
      yypParser->yyerrcnt = 3;
      yy_destructor(yypParser,(YYCODETYPE)yymajor,&yyminorunion);
      if( yyendofinput ){
        yy_parse_failed(yypParser);
      }
      yymajor = YYNOCODE;
#endif
    }
  }while( yymajor!=YYNOCODE && yypParser->yyidx>=0 );
  return;
}
