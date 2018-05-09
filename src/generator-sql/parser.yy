%skeleton "lalr1.cc"
%require  "3.0"
%debug 
%defines 
%define api.namespace {apidb}
%define parser_class_name {Parser}

%code requires
{
	namespace apidb 
	{
      class Driver;
      class Scanner;
	}

// The following definitions is missing when %locations isn't used
# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

}

%parse-param { Scanner  &scanner  }
%parse-param { Driver  &driver  }

%code{
   #include <iostream>
   #include <cstdlib>
   #include <fstream>
   
   /* include for all driver functions */
   #include "driver.hpp"

#undef yylex
#define yylex scanner.yylex
}

%define api.value.type variant
%define parse.assert

%token			TINYINT
%token			SMALLINT
%token			MEDIUMINT
%token			INT
%token			INTEGER
%token			BIGINT
%token			BIT
%token			DECIMAL
%token			NUMERIC
%token			REAL
%token			FLOAT
%token			DOUBLE
%token			DATE
%token			DATETIME
%token			TIMESTAMP
%token			TIME
%token			YEAR
%token			CHAR
%token			VARCHAR
%token			BINARY
%token			VARBINARY
%token			BLOB
%token			TEXT
%token			ENUM
%token			SET


%token			COMA
%token			PARENTHESIS_OPEN
%token			PARENTHESIS_CLOSE
%token			SPACE
%token               END    0     "end of file"
%token               NEWLINE
%token               UNKNOW

%locations

%%

declare_type :
	TEXT declare_end 	{
							if(driver.getOutputLenguaje().compare("C++"))
							{
								std::cout<<"std::string";
							}
							else if(driver.getOutputLenguaje().compare("C"))
							{
								std::cout<<"const char*";
							}
						}
	|
	INTEGER declare_end {std::cout<<"int";}|	
	INT declare_end {std::cout<<"int";}|
	stringVarible declare_end 		{
										if(driver.getOutputLenguaje().compare("C++"))
										{
											std::cout<<"std::string";
										}
										else if(driver.getOutputLenguaje().compare("C"))
										{
											std::cout<<"const char*";
										}
									}
	|
	integerVariable declare_end {std::cout<<"double";};

stringVarible: stringVariableTypes PARENTHESIS_OPEN INTEGER PARENTHESIS_CLOSE;

stringVariableTypes : VARCHAR | CHAR | TEXT;

integerVariable : integerVariableTypes PARENTHESIS_OPEN INTEGER COMA INTEGER PARENTHESIS_CLOSE;
	
integerVariableTypes : DECIMAL | NUMERIC | REAL | FLOAT | DOUBLE;

declare_end : END | NEWLINE;





%%


void 
apidb::Parser::error( const location_type &l, const std::string &err_message )
{
   std::cerr << "Error: " << err_message << " at " << l << "\n";
}
