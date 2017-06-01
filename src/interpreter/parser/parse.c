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
/************ Begin %include sections from the grammar ************************/
#line 21 "parse.y"

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
** various aspects of the generated parser.
**    YYCODETYPE         is the data type used to store the integer codes
**                       that represent terminal and non-terminal symbols.
**                       "unsigned char" is used if there are fewer than
**                       256 symbols.  Larger types otherwise.
**    YYNOCODE           is a number of type YYCODETYPE that is not used for
**                       any terminal or nonterminal symbol.
**    YYFALLBACK         If defined, this indicates that one or more tokens
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
#define YYNOCODE 53
#define YYACTIONTYPE unsigned char
#define miniSqlParserTOKENTYPE Token
typedef union {
  int yyinit;
  miniSqlParserTOKENTYPE yy0;
  int yy20;
  SrcList* yy35;
  NameList* yy92;
} YYMINORTYPE;
#ifndef YYSTACKDEPTH
#define YYSTACKDEPTH 100
#endif
#define miniSqlParserARG_SDECL Parser *pParser;
#define miniSqlParserARG_PDECL ,Parser *pParser
#define miniSqlParserARG_FETCH Parser *pParser = yypParser->pParser
#define miniSqlParserARG_STORE yypParser->pParser = pParser
#define YYNSTATE             66
#define YYNRULE              36
#define YY_MAX_SHIFT         65
#define YY_MIN_SHIFTREDUCE   66
#define YY_MAX_SHIFTREDUCE   101
#define YY_MIN_REDUCE        102
#define YY_MAX_REDUCE        137
#define YY_ERROR_ACTION      138
#define YY_ACCEPT_ACTION     139
#define YY_NO_ACTION         140
/************* End control #defines *******************************************/

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
**
*********** Begin parsing tables **********************************************/
#define YY_ACTTAB_COUNT (170)
static const YYACTIONTYPE yy_action[] = {
 /*     0 */   134,   21,   20,  134,  134,  112,  124,  124,  134,  112,
 /*    10 */   134,  134,  134,  134,   60,  134,   43,  133,  134,  119,
 /*    20 */   133,  133,   18,    1,    9,  133,    8,  133,  133,  133,
 /*    30 */   133,   46,  133,  108,   25,  133,   27,  108,   48,   24,
 /*    40 */    59,   22,  108,   27,  108,  139,    2,   26,   65,   64,
 /*    50 */    19,  126,   56,   52,   53,   21,   20,   10,  115,    8,
 /*    60 */    34,  115,   42,   35,   29,   65,   64,   19,  111,  110,
 /*    70 */    45,   31,  111,  110,   47,    4,   14,  111,  110,  111,
 /*    80 */   110,    5,   52,  109,  107,  123,  123,  109,  107,  128,
 /*    90 */    50,  128,  109,  107,  109,  107,  129,  127,  129,  127,
 /*   100 */    31,  105,  105,   51,   36,   56,   39,   53,   27,  128,
 /*   110 */    12,  106,  106,    6,   62,  132,  129,  127,  116,  132,
 /*   120 */    33,  116,   38,  137,   63,  118,    3,  137,   11,  118,
 /*   130 */    49,  121,   54,  117,   37,  121,  103,  117,   15,  120,
 /*   140 */   136,  135,   41,  120,  136,   17,  114,  113,  125,  131,
 /*   150 */   114,  113,  122,  131,   30,   13,   32,    7,   55,   40,
 /*   160 */    16,  104,   23,   58,   44,   57,   61,  130,  102,   28,
};
static const YYCODETYPE yy_lookahead[] = {
 /*     0 */     1,   17,   18,    4,    5,    5,   17,   18,    9,    9,
 /*    10 */    11,   12,   13,   14,   14,   16,   16,    1,   19,    5,
 /*    20 */     4,    5,   42,    9,   44,    9,   46,   11,   12,   13,
 /*    30 */    14,   41,   16,    5,   47,   19,   46,    9,   41,   11,
 /*    40 */    12,   13,   14,   46,   16,   33,   34,   35,   36,   37,
 /*    50 */    38,    0,   14,    2,   16,   17,   18,   44,    1,   46,
 /*    60 */    45,    4,   49,   50,   35,   36,   37,   38,    5,    5,
 /*    70 */    45,   20,    9,    9,    6,   51,   19,   14,   14,   16,
 /*    80 */    16,   51,    2,    5,    5,   17,   18,    9,    9,    0,
 /*    90 */     6,    2,   14,   14,   16,   16,    0,    0,    2,    2,
 /*   100 */    20,   17,   18,   41,   46,   14,   48,   16,   46,   20,
 /*   110 */     3,   17,   18,   40,   43,    5,   20,   20,    1,    9,
 /*   120 */    46,    4,   46,    5,   39,    5,    4,    9,   21,    9,
 /*   130 */     7,    5,   46,    5,    5,    9,    4,    9,    9,    5,
 /*   140 */     5,    5,   50,    9,    9,    9,    5,    5,    1,    5,
 /*   150 */     9,    9,    1,    9,    8,    3,    8,    4,   15,    5,
 /*   160 */     4,    1,    5,    4,   15,   10,    5,    1,    1,    1,
};
#define YY_SHIFT_USE_DFLT (170)
#define YY_SHIFT_COUNT    (65)
#define YY_SHIFT_MIN      (-16)
#define YY_SHIFT_MAX      (168)
static const short yy_shift_ofst[] = {
 /*     0 */    80,   38,   51,  -16,  -16,  -16,  -16,  -16,   28,    0,
 /*    10 */     0,   68,   68,   84,  -16,  -16,  -16,   91,   14,  122,
 /*    20 */    -1,   16,   63,   64,   78,   79,   89,   57,   96,   97,
 /*    30 */   -11,  107,   94,  117,  110,  118,  120,  126,  128,  129,
 /*    40 */   134,  135,  136,  141,  142,  144,  147,  146,  151,  148,
 /*    50 */   123,  132,  152,  153,  154,  156,  143,  157,  155,  159,
 /*    60 */   149,  160,  161,  166,  167,  168,
};
#define YY_REDUCE_USE_DFLT (-21)
#define YY_REDUCE_COUNT (19)
#define YY_REDUCE_MIN   (-20)
#define YY_REDUCE_MAX   (92)
static const signed char yy_reduce_ofst[] = {
 /*     0 */    12,   13,   29,  -20,  -10,   -3,   62,   58,  -13,   15,
 /*    10 */    25,   24,   30,   73,   74,   76,   86,   92,   71,   85,
};
static const YYACTIONTYPE yy_default[] = {
 /*     0 */   138,  138,  138,  138,  138,  138,  138,  138,  138,  138,
 /*    10 */   138,  138,  138,  138,  138,  138,  138,  138,  138,  138,
 /*    20 */   138,  138,  138,  138,  138,  138,  138,  138,  138,  138,
 /*    30 */   138,  138,  138,  138,  138,  138,  138,  138,  138,  138,
 /*    40 */   138,  138,  138,  138,  138,  138,  138,  138,  138,  138,
 /*    50 */   138,  138,  138,  138,  138,  138,  138,  138,  138,  138,
 /*    60 */   138,  138,  138,  138,  138,  138,
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
#endif
  miniSqlParserARG_SDECL                /* A place to hold %extra_argument */
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
void miniSqlParserTrace(FILE *TraceFILE, char *zTracePrompt){
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
  "LP",            "RP",            "IF",            "NOT",         
  "EXISTS",        "COMMA",         "INTEGER",       "INT_TYPE",    
  "CHAR_TYPE",     "FLOAT_TYPE",    "PRIMARY",       "KEY",         
  "UNIQUE",        "STRING",        "ID",            "DOT",         
  "DROP",          "INDEX",         "OR",            "AND",         
  "IS",            "NE",            "EQ",            "BETWEEN",     
  "GT",            "LE",            "LT",            "GE",          
  "error",         "input",         "cmdlist",       "cmd_and_end", 
  "singlecmd",     "cmd",           "create_table",  "create_table_args",
  "if_not_exists",  "full_name",     "columnlist",    "optional_constraint_list",
  "column_name",   "column_constraint",  "name",          "type_token",  
  "name_list",     "constraint_list",  "table_constraint",  "if_exists",   
};
#endif /* NDEBUG */

#ifndef NDEBUG
/* For tracing reduce actions, the names of all rules are required.
*/
static const char *const yyRuleName[] = {
 /*   0 */ "singlecmd ::= cmd",
 /*   1 */ "create_table ::= CREATE TABLE if_not_exists full_name",
 /*   2 */ "create_table_args ::= LP columnlist optional_constraint_list RP",
 /*   3 */ "if_not_exists ::=",
 /*   4 */ "if_not_exists ::= IF NOT EXISTS",
 /*   5 */ "column_name ::= name type_token",
 /*   6 */ "type_token ::=",
 /*   7 */ "type_token ::= INT_TYPE",
 /*   8 */ "type_token ::= CHAR_TYPE LP INTEGER RP",
 /*   9 */ "type_token ::= FLOAT_TYPE",
 /*  10 */ "column_constraint ::=",
 /*  11 */ "column_constraint ::= PRIMARY KEY",
 /*  12 */ "column_constraint ::= UNIQUE",
 /*  13 */ "full_name ::= name",
 /*  14 */ "full_name ::= name DOT name",
 /*  15 */ "name_list ::= name_list COMMA name",
 /*  16 */ "name_list ::= name",
 /*  17 */ "optional_constraint_list ::=",
 /*  18 */ "table_constraint ::= PRIMARY KEY LP name RP",
 /*  19 */ "table_constraint ::= UNIQUE LP name_list RP",
 /*  20 */ "cmd ::= DROP TABLE if_exists full_name",
 /*  21 */ "if_exists ::=",
 /*  22 */ "if_exists ::= IF EXISTS",
 /*  23 */ "cmd ::= DROP INDEX if_exists full_name",
 /*  24 */ "input ::= cmdlist",
 /*  25 */ "cmdlist ::= cmdlist cmd_and_end",
 /*  26 */ "cmdlist ::= cmd_and_end",
 /*  27 */ "cmd_and_end ::= singlecmd SEMICOLON",
 /*  28 */ "cmd ::= create_table create_table_args",
 /*  29 */ "columnlist ::= columnlist COMMA column_name column_constraint",
 /*  30 */ "columnlist ::= column_name column_constraint",
 /*  31 */ "name ::= STRING",
 /*  32 */ "name ::= ID",
 /*  33 */ "optional_constraint_list ::= COMMA constraint_list",
 /*  34 */ "constraint_list ::= constraint_list COMMA table_constraint",
 /*  35 */ "constraint_list ::= table_constraint",
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
** to miniSqlParser and miniSqlParserFree.
*/
void *miniSqlParserAlloc(void *(*mallocProc)(YYMALLOCARGTYPE)){
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
  miniSqlParserARG_FETCH;
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
/********* Begin destructor definitions ***************************************/
    case 41: /* full_name */
{
#line 80 "parse.y"

//TODO: add destructor

#line 542 "parse.c"
}
      break;
    case 48: /* name_list */
{
#line 87 "parse.y"

#line 549 "parse.c"
}
      break;
/********* End destructor definitions *****************************************/
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
** If the YYPARSEFREENEVERNULL macro exists (for example because it
** is defined in a %include section of the input grammar) then it is
** assumed that the input pointer is never NULL.
*/
void miniSqlParserFree(
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
int miniSqlParserStackPeak(void *p){
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
static void yyStackOverflow(yyParser *yypParser){
   miniSqlParserARG_FETCH;
#ifndef NDEBUG
   if( yyTraceFILE ){
     fprintf(yyTraceFILE,"%sStack Overflow!\n",yyTracePrompt);
   }
#endif
   while( yypParser->yytos>yypParser->yystack ) yy_pop_parser_stack(yypParser);
   /* Here code is inserted which will execute if the parser
   ** stack every overflows */
/******** Begin %stack_overflow code ******************************************/
#line 15 "parse.y"

    miniSqlError(pParser, "parser stack overflow");
#line 731 "parse.c"
/******** End %stack_overflow code ********************************************/
   miniSqlParserARG_STORE; /* Suppress warning about unused %extra_argument var */
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
  { 36, 1 },
  { 38, 4 },
  { 39, 4 },
  { 40, 0 },
  { 40, 3 },
  { 44, 2 },
  { 47, 0 },
  { 47, 1 },
  { 47, 4 },
  { 47, 1 },
  { 45, 0 },
  { 45, 2 },
  { 45, 1 },
  { 41, 1 },
  { 41, 3 },
  { 48, 3 },
  { 48, 1 },
  { 43, 0 },
  { 50, 5 },
  { 50, 4 },
  { 37, 4 },
  { 51, 0 },
  { 51, 2 },
  { 37, 4 },
  { 33, 1 },
  { 34, 2 },
  { 34, 1 },
  { 35, 2 },
  { 37, 2 },
  { 42, 4 },
  { 42, 2 },
  { 46, 1 },
  { 46, 1 },
  { 43, 2 },
  { 49, 3 },
  { 49, 1 },
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
  miniSqlParserARG_FETCH;
  yymsp = yypParser->yytos;
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
/********** Begin reduce actions **********************************************/
        YYMINORTYPE yylhsminor;
      case 0: /* singlecmd ::= cmd */
#line 36 "parse.y"
{
    // reach here doesn't mean there is no mistake in the statement
    miniSqlLog(pParser, "finish a command");
}
#line 910 "parse.c"
        break;
      case 1: /* create_table ::= CREATE TABLE if_not_exists full_name */
#line 44 "parse.y"
{
    //
}
#line 917 "parse.c"
        break;
      case 2: /* create_table_args ::= LP columnlist optional_constraint_list RP */
      case 5: /* column_name ::= name type_token */ yytestcase(yyruleno==5);
      case 15: /* name_list ::= name_list COMMA name */ yytestcase(yyruleno==15);
      case 16: /* name_list ::= name */ yytestcase(yyruleno==16);
      case 18: /* table_constraint ::= PRIMARY KEY LP name RP */ yytestcase(yyruleno==18);
      case 19: /* table_constraint ::= UNIQUE LP name_list RP */ yytestcase(yyruleno==19);
      case 20: /* cmd ::= DROP TABLE if_exists full_name */ yytestcase(yyruleno==20);
      case 23: /* cmd ::= DROP INDEX if_exists full_name */ yytestcase(yyruleno==23);
#line 48 "parse.y"
{

}
#line 931 "parse.c"
        break;
      case 3: /* if_not_exists ::= */
      case 10: /* column_constraint ::= */ yytestcase(yyruleno==10);
      case 21: /* if_exists ::= */ yytestcase(yyruleno==21);
#line 53 "parse.y"
{yymsp[1].minor.yy20 = 0;}
#line 938 "parse.c"
        break;
      case 4: /* if_not_exists ::= IF NOT EXISTS */
#line 54 "parse.y"
{yymsp[-2].minor.yy20 = 1;}
#line 943 "parse.c"
        break;
      case 6: /* type_token ::= */
      case 7: /* type_token ::= INT_TYPE */ yytestcase(yyruleno==7);
      case 8: /* type_token ::= CHAR_TYPE LP INTEGER RP */ yytestcase(yyruleno==8);
      case 9: /* type_token ::= FLOAT_TYPE */ yytestcase(yyruleno==9);
#line 65 "parse.y"
{}
#line 951 "parse.c"
        break;
      case 11: /* column_constraint ::= PRIMARY KEY */
      case 22: /* if_exists ::= IF EXISTS */ yytestcase(yyruleno==22);
#line 72 "parse.y"
{yymsp[-1].minor.yy20 = 1;}
#line 957 "parse.c"
        break;
      case 12: /* column_constraint ::= UNIQUE */
#line 73 "parse.y"
{yymsp[0].minor.yy20 = 2;}
#line 962 "parse.c"
        break;
      case 13: /* full_name ::= name */
#line 83 "parse.y"
{yylhsminor.yy35 = yymsp[0].minor.yy0;}
#line 967 "parse.c"
  yymsp[0].minor.yy35 = yylhsminor.yy35;
        break;
      case 14: /* full_name ::= name DOT name */
#line 84 "parse.y"
{}
#line 973 "parse.c"
  yymsp[-2].minor.yy35 = yylhsminor.yy35;
        break;
      case 17: /* optional_constraint_list ::= */
#line 98 "parse.y"
{yymsp[1].minor.yy0.n = 0; yymsp[1].minor.yy0.text = 0;}
#line 979 "parse.c"
        break;
      default:
      /* (24) input ::= cmdlist */ yytestcase(yyruleno==24);
      /* (25) cmdlist ::= cmdlist cmd_and_end */ yytestcase(yyruleno==25);
      /* (26) cmdlist ::= cmd_and_end */ yytestcase(yyruleno==26);
      /* (27) cmd_and_end ::= singlecmd SEMICOLON */ yytestcase(yyruleno==27);
      /* (28) cmd ::= create_table create_table_args */ yytestcase(yyruleno==28);
      /* (29) columnlist ::= columnlist COMMA column_name column_constraint */ yytestcase(yyruleno==29);
      /* (30) columnlist ::= column_name column_constraint */ yytestcase(yyruleno==30);
      /* (31) name ::= STRING */ yytestcase(yyruleno==31);
      /* (32) name ::= ID */ yytestcase(yyruleno==32);
      /* (33) optional_constraint_list ::= COMMA constraint_list */ yytestcase(yyruleno==33);
      /* (34) constraint_list ::= constraint_list COMMA table_constraint */ yytestcase(yyruleno==34);
      /* (35) constraint_list ::= table_constraint */ yytestcase(yyruleno==35);
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
  miniSqlParserARG_FETCH;
#ifndef NDEBUG
  if( yyTraceFILE ){
    fprintf(yyTraceFILE,"%sFail!\n",yyTracePrompt);
  }
#endif
  while( yypParser->yytos>yypParser->yystack ) yy_pop_parser_stack(yypParser);
  /* Here code is inserted which will be executed whenever the
  ** parser fails */
/************ Begin %parse_failure code ***************************************/
/************ End %parse_failure code *****************************************/
  miniSqlParserARG_STORE; /* Suppress warning about unused %extra_argument variable */
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
  miniSqlParserARG_FETCH;
#define TOKEN yyminor
/************ Begin %syntax_error code ****************************************/
#line 10 "parse.y"

    // TODO: add location of error
    miniSqlError(pParser, "syntax error");
#line 1054 "parse.c"
/************ End %syntax_error code ******************************************/
  miniSqlParserARG_STORE; /* Suppress warning about unused %extra_argument variable */
}

/*
** The following is executed when the parser accepts
*/
static void yy_accept(
  yyParser *yypParser           /* The parser */
){
  miniSqlParserARG_FETCH;
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
/*********** Begin %parse_accept code *****************************************/
/*********** End %parse_accept code *******************************************/
  miniSqlParserARG_STORE; /* Suppress warning about unused %extra_argument variable */
}

/* The main parser program.
** The first argument is a pointer to a structure obtained from
** "miniSqlParserAlloc" which describes the current state of the parser.
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
void miniSqlParser(
  void *yyp,                   /* The parser */
  int yymajor,                 /* The major token code number */
  miniSqlParserTOKENTYPE yyminor       /* The value for the token */
  miniSqlParserARG_PDECL               /* Optional %extra_argument parameter */
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
#endif
  miniSqlParserARG_STORE;

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
