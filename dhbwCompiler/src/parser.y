/* 
 * parser.y - Parser utility for the DHBW compiler
 */

%{
	#include "include/utlist.h" 
	#include "table_dummy.h"
	#include "ir_code_generation.h"
	#include <stdio.h>
	
	void yyerror (char const *);
%}
 
%union{
	int num;
	char *id;
	struct Element *Elem;
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
%token <id>INT <id>VOID
%token RETURN
%token COLON COMMA SEMICOLON
%token BRACE_OPEN BRACE_CLOSE

%token <id>ID
%token <num>NUM

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

%type <Elem> function_call_parameters
%type <Elem> function_definition
%type <Elem> function_parameter_list
%type <Elem> function_declaration
%type <Elem> function_call
%type <num> type
%type <Elem> function_parameter
%type <Elem> identifier_declaration
%type <Elem> expression
%type <Elem> primary

%%

program
     : program_element_list			/*Nothing to be done here*/
     ;

program_element_list
     : program_element_list program_element 	
     | program_element {printf("--- DEBUG: "); debug_printAllElems();printf("---");} 				
     ;

program_element
     : variable_declaration SEMICOLON		/*Nothing to be done here*/
     | function_declaration SEMICOLON		/*Nothing to be done here*/
     | function_definition					/*Nothing to be done here*/
     | SEMICOLON							/*Nothing to be done here*/
     ;
     
type
     : INT  {$$=1}
     | VOID {$$=0}
     ;

variable_declaration
     : variable_declaration COMMA identifier_declaration	/*Nothing to be done here*/
     | type identifier_declaration { if($1==0) { printf("ERROR -- your variable needs a type\n"); } } 
     ;
	
identifier_declaration
     : identifier_declaration BRACKET_OPEN NUM BRACKET_CLOSE
     | ID {$$ = putElem($1)}
     ;

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
     : // empty: epsilon
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
     : expression ASSIGN expression			
     | expression LOGICAL_OR expression	
     | expression LOGICAL_AND expression
     | LOGICAL_NOT expression		
     | expression EQ expression		
     | expression NE expression		
     | expression LS expression 	
     | expression LSEQ expression 	
     | expression GTEQ expression 
     | expression GT expression	
     | expression PLUS expression				
     | expression MINUS expression				
     | expression MUL expression				
     | MINUS expression %prec UNARY_MINUS		
     | ID BRACKET_OPEN primary BRACKET_CLOSE	
     | PARA_OPEN expression PARA_CLOSE			
     | function_call							
     | primary									
     ;

primary
     : NUM 										{printf("DEBUG -- num");}
     | ID  										{printf("DEBUG -- id");}
     ;

function_call
      : ID PARA_OPEN PARA_CLOSE						
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