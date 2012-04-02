/* 
 * parser.y - Parser utility for the DHBW compiler
 */

%{
	#include "include/utlist.h" 
	#include "symboltable.h"
	#include "ir_code_generation.h"
	#include <stdio.h>
	
	void yyerror (char const *);
%}
 
%union{
	int num;
	char *id;
}

%debug
%locations
%start program

/*
 * One shift/reduce conflict is expected for the "dangling-else" problem. This
 * conflict however is solved by the default behavior of bison for shift/reduce 
 * conflicts (shift action). The default behavior of bison corresponds to what
 * we want bison to do: SHIFT if the lookahead is 'ELSE' in order to bind the 'ELSE' to
 * the last open if-clause. 
 */
%expect 1

%token DO WHILE
%token IF ELSE
%token INT VOID
%token RETURN
%token COLON COMMA SEMICOLON
%token BRACE_OPEN BRACE_CLOSE

%token ID
%token NUM

%right ASSIGN 
%left  LOGICAL_OR
%left  LOGICAL_AND
%left  EQ NE     
%left  LS LSEQ GTEQ GT 
%left  SHIFT_LEFT SHIFT_RIGHT
%left  PLUS MINUS     
%left  MUL
%right LOGICAL_NOT UNARY_MINUS UNARY_PLUS
%left  BRACKET_OPEN BRACKET_CLOSE PARA_OPEN PARA_CLOSE

%%

program
     : program_element_list	{printf("progelementlist");}			/*Nothing to be done here*/
     ;

program_element_list
     : program_element_list program_element 	
     | program_element 				
     ;

program_element
     : variable_declaration SEMICOLON		/*Nothing to be done here*/
     | function_declaration SEMICOLON		/*Nothing to be done here*/
     | function_definition					/*Nothing to be done here*/
     | SEMICOLON						/*Nothing to be done here*/
     ;
     
type
     : INT
     | VOID
     ;

variable_declaration
     : variable_declaration COMMA identifier_declaration	/*Nothing to be done here*/
     | type identifier_declaration 
     ;
	
identifier_declaration
     : identifier_declaration BRACKET_OPEN NUM BRACKET_CLOSE 
     | ID 
     ;
     
/*	Because of the new Grammar we don't have do delete the variable because functions are imediadly recongnised. Will stay here, if needed, for a few revesions..
function_signature
     : identifier_declaration PARA_OPEN {$$ = putFunc ($1->name, 1);deleteInt ($1->name)}
     ;*/

function_definition
     : type ID PARA_OPEN PARA_CLOSE BRACE_OPEN 	stmt_list BRACE_CLOSE 
     | type ID PARA_OPEN function_parameter_list PARA_CLOSE BRACE_OPEN stmt_list BRACE_CLOSE 
     ;

function_declaration
     : type ID PARA_OPEN PARA_CLOSE						
     | type ID PARA_OPEN function_parameter_list PARA_CLOSE		
     ;

function_parameter_list
     : function_parameter						
     | function_parameter_list COMMA function_parameter		
     ;
	
function_parameter
     : type identifier_declaration
     ;

stmt_list
     : /* empty: epsilon */
     | stmt_list stmt					/*Nothing to be done here*/
     ;

stmt
     : stmt_block
     | variable_declaration SEMICOLON
     | expression SEMICOLON
     | stmt_conditional
     | stmt_loop
     | RETURN expression SEMICOLON
     | RETURN SEMICOLON
     | SEMICOLON
     ;

stmt_block
     : BRACE_OPEN stmt_list BRACE_CLOSE
     ;
//the shift/reduce error which occurs here is expected. nothing to see here move along
//changed the grammar slightly to handle the goto statements easier.
stmt_conditional
     : IF PARA_OPEN expression PARA_CLOSE stmt_conditional_r //stmt
     //| IF PARA_OPEN expression {addif($3);addifgoto();} PARA_CLOSE stmt ELSE stmt	//{addif($3);addifgoto();}
     ;
     
stmt_conditional_r
     : stmt 
     | stmt ELSE stmt
     ;
     
stmt_loop
     : WHILE PARA_OPEN expression PARA_CLOSE stmt
     | DO stmt WHILE PARA_OPEN expression PARA_CLOSE SEMICOLON
     ;
     
/*
 * The non-terminal 'expression' is one of the core statements containing all arithmetic, logical, comparison and
 * assignment operators.expression
 */									
expression								// 0 = "false", nonzero = "true"
     : expression ASSIGN expression	{printf("equals");}			
     | expression LOGICAL_OR expression	
     | expression LOGICAL_AND expression
     | LOGICAL_NOT expression		
     | expression EQ expression		
     | expression NE expression		
     | expression LS expression 	
     | expression LSEQ expression 	
     | expression GTEQ expression 
     | expression GT expression	
     | expression PLUS expression				{printf("DEBUG -- function call");}
     | expression MINUS expression				{printf("DEBUG -- function call");}
     | expression MUL expression				{printf("DEBUG -- function call");}
     | MINUS expression %prec UNARY_MINUS		{printf("DEBUG -- function call");}
     | ID BRACKET_OPEN primary BRACKET_CLOSE	{printf("DEBUG -- function call");}
     | PARA_OPEN expression PARA_CLOSE			{printf("DEBUG -- para_open para_close");}
     | function_call							{printf("DEBUG -- function call");}
     | primary									
     ;

primary
     : NUM 										{printf("DEBUG -- num");}
     | ID  										{printf("DEBUG -- id");}
     ;

function_call
      : ID PARA_OPEN PARA_CLOSE					{printf("DEBUG -- para_open para_close");}	
      | ID PARA_OPEN function_call_parameters PARA_CLOSE	
      ;

function_call_parameters
     : function_call_parameters COMMA expression		
     | expression						
     ;

%%

void yyerror (const char *msg)
{
	printf("ERROR: %s\n", msg);
	//return 0;
}

int main()
{
	yyparse();
	return 0;
}

void print_debug(const char *msg)
{
	printf("ERROR: %s\n", msg);
}