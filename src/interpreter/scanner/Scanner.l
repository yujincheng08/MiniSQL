%case-insensitive
%lex-source = "Scanner.cpp"
%%
[[:space:]]+
create			return CREATE;
table			return TABLE;
insert			return INSERT;
into			return INTO;
select			return SELECT;
from			return FROM;
where			return WHERE;
values			return VALUES;
int			return INT;
float			return FLOAT;
[[:digit:]]+		return DIGITAL;
;			return SEMICOLON;
char			return CHAR;
\(			return LBRACKER;
\)			return RBRACKER;
,			return COMMA;
unique			return UNIQUE;
primary			return PRIMARY;
key			return KEY;
drop			return DROP;
delete			return DELTE;
quit			return QUIT;
exec			return EXEC;
\<			return LOWER;
\>			return GREATER;
index			return INDEX;
on			return ON;
\*			return START;
!=			return NOTEQUAL;
=			return EQUAL;
and			return AND;
or			return OR;
'			return QUOTATION;
[^[:space:],;\(\)\<\>\*\=\!]+ return NAME;
%%
