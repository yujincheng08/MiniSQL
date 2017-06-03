%case-insensitive
%lex-source = "Scanner.cpp"
%%
[[:blank:]]+
\n          return Interpreter::NEWLINE;
;			return SEMICOLON;
create			return CREATE;
table			return TABLE;
insert			return INSERT;
into			return INTO;
select			return SELECT;
from			return FROM;
where			return WHERE;
values			return VALUES;
int			return INT_TYPE;
float			return FLOAT_TYPE;
char			return CHAR_TYPE;
-?[[:digit:]]+		return INTEGER;
\.                      return DOT;
-?[[:digit:]]?\.[[:digit:]]+ return FLOAT;
\(			return LP;
\)			return RP;
,			return COMMA;
'[^']*'           return SQMSTRING;
unique			return UNIQUE;
primary			return PRIMARY;
key			return KEY;
drop			return DROP;
delete			return DELETE;
quit			return Interpreter::QUIT;
exec			return Interpreter::EXEC;
\<			return LT;
\>			return GT;
index			return INDEX;
on			return ON;
\*			return TIMES;
=			return EQ;
!=			return NE;
and			return AND;
or			return OR;
not         return NOT;
[^[:space:]\.,;\(\)\<\>\*\=\!]+ return STRING;
<<EOF>>			return Interpreter::QUIT;
%%
