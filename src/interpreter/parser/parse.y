%token_prefix TOKEN_

%token_type {Token}
%default_type {Token}

// the parser context
// 4 th arg of Parse
%extra_argument {Parser *pParser}

%syntax_error {
    // TODO: add location of error
    miniSqlError(pParser, "syntax error");
}

%stack_overflow {
    miniSqlError(pParser, "parser stack overflow");
}

%name miniSqlParser

%include {
#include "parse.h"
#include "miniSqlDef.h"
#include <assert.h>
}

// every input starts here
input ::= cmdlist.
// cmd list is a list of one or more singlecmd
// always use left recursion
cmdlist ::= cmdlist cmd_and_end.
cmdlist ::= cmd_and_end.
cmd_and_end ::= singlecmd SEMICOLON.
// singlecmd is the wrapper for all kind of cmd
// use this to log some info
singlecmd ::= cmd. {
    // reach here doesn't mean there is no mistake in the statement
    miniSqlLog(pParser, "finish a command");
}

// create table

cmd ::= create_table create_table_args.
create_table ::= CREATE TABLE if_not_exists(E) full_name(N). {
    //
}

create_table_args ::= LP columnlist optional_constraint_list(X) RP(E). {

}

%type if_not_exists {int}
if_not_exists(A) ::= . {A = 0;}
if_not_exists(A) ::= IF NOT EXISTS. {A = 1;}

// column_arg_list
columnlist ::= columnlist COMMA column_name column_constraint.
columnlist ::= column_name column_constraint.
column_name(A) ::= name(A) type_token(Y). {

}
// default type is int
%token_class int INTEGER.

type_token(A) ::= . {}
type_token(A) ::= INT_TYPE(A). {}
type_token(A) ::= CHAR_TYPE(A) LP INTEGER RP. {}
type_token(A) ::= FLOAT_TYPE(A). {}

%type column_constraint {int}
column_constraint(A) ::= . {A = 0;}
column_constraint(A) ::= PRIMARY KEY. {A = 1;}
column_constraint(A) ::= UNIQUE. {A = 2;}

%type name {Token}
name(A) ::= STRING(A).
name(A) ::= ID(A).

%type full_name {SrcList*}
%destructor full_name {
//TODO: add destructor
}
full_name(A) ::= name(X). {
// TODO: alloc for SrcList
// transform Token to Src
}
full_name(B) ::= name(A) DOT name(B). {
// TODO: alloc for SrcList
}

%type name_list {NameList*}
%destructor name_list {}

name_list ::= name_list(A) COMMA name(N).{
}

name_list ::= name(N). {

}

// can be empty/optional
optional_constraint_list(A) ::= . {A.n = 0; A.text = 0;}
optional_constraint_list(A) ::= COMMA(A) constraint_list.
// constraint_list is one or more table_constraints
constraint_list ::= constraint_list COMMA table_constraint.
constraint_list ::= table_constraint.
// primary key is for single column
table_constraint ::= PRIMARY KEY LP name(N) RP. {

}
// unique may apply to multiple column
table_constraint ::= UNIQUE LP name_list(X) RP. {

}

// drop table
cmd ::= DROP TABLE if_exists(E) full_name(N). {

}

%type if_exists {int}
if_exists(A) ::= . {A = 0;}
if_exists(A) ::= IF EXISTS. {A = 1;}
// where clause
opt_where_clause ::= . {
// delete all
}
opt_where_clause(A) ::= where_clause(X). {A = X;}

where_clause ::= WHERE expr(X). {

}

expr(A) ::= literal(A). {}
expr(A) ::= expr(A) AND(OP) expr(Y). {}
expr(A) ::= expr(A) OR(OP) expr(Y). {}
expr(A) ::= expr(A) LT|GT|GE|LE(OP) expr(Y). {}
expr(A) ::= expr(A) EQ|NE(OP) expr(Y). {}
expr(A) ::= expr(A) between_op(N) expr(X) AND expr(Y). {

}

literal(A) ::= NULL(X). {}
// column name
literal(A) ::= full_name(B). {}
literal(A) ::= STRING(X). {}
literal(A) ::= INTEGER(X). {}

%type between_op {int}
between_op(A) ::= BETWEEN. {A = 0;}
between_op(A) ::= NOT BETWEEN. {A = 1;}

// select
cmd ::= SELECT select_column_list(L) FROM opt_where_clause(W). {

}

select_column(A) ::= STAR.
select_column(A) ::= name(X).

select_column_list(A) ::= select_column.
select_column_list(A) ::= select_column_list COMMA select_column.

// insert

cmd ::= INSERT INTO full_name(F) LP RP. {

}

// delete

cmd ::= DELETE FROM full_name(N) opt_where_clause. {

}

// create index

cmd ::= CREATE INDEX if_not_exists(E) full_name(N) ON full_name(T) LP name_list(C) RP. {

}

// drop index

cmd ::= DROP INDEX if_exists(E) full_name(N). {

}

// operators
%left OR.
%left AND.
%right NOT.
%left IS NE EQ BETWEEN.
%left GT LE LT GE.