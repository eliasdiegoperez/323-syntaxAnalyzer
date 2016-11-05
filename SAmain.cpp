/*
Andrew Nguyen
Joshua Womack 
CPSC323
Assignment 2 - Syntax Analyzer

*/

#include "LA.h"
using namespace std;


void Rat16F();
void OptFuncDef();
void FuncDef();
void Func();
void OptParamList();
void ParamList();
void Parameter();
void Qualifier();
void Body();
void OptDecList();
void DecList();
void Declaration();
void IDs();
void StatementList();
void Statement();
void Compound();
void Assign();
void If();
void Return();
void Write();
void Read();
void While();
void Condition();
void Relop();
void Expression();
void ExpressionPrime();
void Term();
void TermPrime();
void Factor();
void Primary();
void Empty();
void lexAdv();


int                     tokenIndex = 0;             //Index used to step through token vector
bool                    printSwitch = true;
vector<tokenData>       tokens;                     //vector to hold tokens as they are being inputted
vector<tokenData>       tokenList;                  //vector that holds all tokens once they have been read in initially
tokenData               currentToken;

int main() 
{
	bool				    wroteHeader = true;     //NOT NEEDED ANYMORE?
	ifstream			    ifget;
	LA                      lex;
	string				    current = "";
	string				    infilepath = "";
	string				    outfilepath = "";

	/*
	//Input file to read from
	cout << "Before you begin, make sure the input test file is in\nthe same folder as the .exe of this program.\n";
	cout << "----------------------------------------------------------------------\n";
	cout << "Please enter the file name and extension of the input file (input.txt).\n";
	cout << "Input: ";
	getline(cin, infilepath);
	cout << "You entered: " << infilepath << endl << endl;

	//Output file to write to
	//cout << "Please enter the file and extension of the output file (output.txt).\n";
	//cout << "Input: ";
	//getline(cin, outfilepath);
	//cout << "You entered: " << outfilepath << endl << endl;
	*/

	//Open file for reading
	//ifget.open(infilepath);

	infilepath = "/home/joshua/Git/323-syntaxAnalyzer/input.txt";
	outfilepath = "/home/joshua/Git/323-syntaxAnalyzer/output.txt";
	ifget.open(infilepath);


	//Catch issue with opening file
	if (!ifget)
	{
		cout << "Error. Unable to read file." << endl;
		//system("pause");
		return -1;
	}

	//While not end of file, read every line.
	while (getline(ifget, current))
	{
		if (!wroteHeader)
		{
			lex.printHeader(outfilepath);
			wroteHeader = true;
		}

		tokens = lex.lexer(current);
		tokenList.insert(tokenList.end(), tokens.begin(), tokens.end());
		tokens.clear();
	}

	ifget.close();
	//lex.printTokens(tokenList, outfilepath);

    /*
     * New stuff goes here
     */
	Rat16F();

	//system("pause");
	return 0;
}


void lexAdv() {
	if (tokenIndex < tokenList.size())
	{
		currentToken = tokenList[tokenIndex];
		if (printSwitch)
		{
			cout << left << setw(7) << "\nToken: " << left << setw(20) << currentToken.token
				 << left << setw(8) << "Lexeme: " << left << setw(20) << currentToken.lexeme << endl;
		}
		tokenIndex++;
	}
}


void Rat16F()
{
	lexAdv();
	if (printSwitch)
		cout << "\t<Rat16F> ::= $$ <Opt Function Definitions>\n\t\t\t\t $$ <Opt Declaration List> <Statement List> $$\n";

	if (currentToken.lexeme == "$$")
	{
		lexAdv();
		OptFuncDef();
		if (currentToken.lexeme == "$$")
		{
			lexAdv();
			OptDecList();
			StatementList();
			if (currentToken.lexeme == "$$")
				cout << "The End.\n";
		}
	}
	else
	{
		cout << "\n<><><> Syntax Error, expecting '$$'.";
		exit(1);
	}
}


void OptFuncDef()
{
	if (printSwitch)
		cout << "\t<Opt Function Definition> ::= <Function Definitions> | <Empty>\n";

	if (currentToken.lexeme == "function")
	{
		//lexAdv();
		FuncDef();
	}
	else
		Empty();
}


void FuncDef()
{
	if (printSwitch)
		cout << "\t<Function Definitions> ::= <Function> | <Function> <Function Definitions>\n";

	while (currentToken.lexeme == "function")
	{
		Func();
	}
}


void Func()
{
	if (printSwitch)
		cout << "\t<Function> ::= function <Identifier> [ <Opt Paramenter List> ] <Opt Declaration List> <Body>\n";

	lexAdv();

	if (currentToken.token == "IDENTIFIER")
	{
		lexAdv();
		if (currentToken.lexeme == "[")
		{
			lexAdv();
			OptParamList();
			if (currentToken.lexeme == "]")
			{
				lexAdv();
				OptDecList();
				Body();
			}
		}
	}
}


void OptParamList()
{
	if (printSwitch)
		cout << "\t<Opt Parameter List> ::= <Parameter List> | <Empty>\n";

	if (currentToken.token == "IDENTIFIER")
	{
		ParamList();
	}
	else
	{
		Empty();
	}
}


void ParamList()
{
	if (printSwitch)
		cout << "\t<Parameter List> ::= <Parameter> | <Parameter>, <Parameter List>\n";


	if (currentToken.token == "IDENTIFIER")
	{
		Parameter();
		if (currentToken.lexeme == ",")
		{
			lexAdv();
			ParamList();
		}
	}
}


void Parameter()
{
	if (printSwitch)
		cout << "\t<Parameter> ::= <IDs> : <Qualifier>\n";

	IDs();
	if (currentToken.lexeme == ":")
	{
		lexAdv();
		Qualifier();
	}
}


void Body()
{
	if (printSwitch)
		cout << "\t<Body> ::= { <Statement List> }\n";

	if (currentToken.lexeme == "{")
	{
		lexAdv();
		StatementList();
		if (currentToken.lexeme == "}")
			lexAdv();
		else
		{
			cout << "\n<><><> <Body> Syntax Error";
			exit(1);
		}
	}
	else
	{
		cout << "\n<><><> <Body> Syntax Error";
		exit(1);
	}
}


void OptDecList()
{
	if (printSwitch)
		cout << "\t<Opt Declaration List> ::= <Declaration List> | <Empty>\n";


	if (currentToken.lexeme == "{")
		Empty();
	else if (currentToken.lexeme == "integer" || currentToken.lexeme == "boolean" || currentToken.lexeme == "real")
		DecList();
	else
	{
		cout << "\n<><><> Syntax Error";
		exit(1);
	}
}


void DecList()
{
	if (printSwitch)
		cout << "\t<Declaration List> ::= <Declaration>; | <Declaration> ; <Declaration List>\n";

		Declaration();
		if (currentToken.lexeme == ";")
			lexAdv();
			if (currentToken.lexeme == "integer" || currentToken.lexeme == "boolean" || currentToken.lexeme == "real")
				DecList();
}


void Declaration()
{
	if (printSwitch)
		cout << "\t<Declaration> ::= <Qualifier> <IDs>\n";

	Qualifier();
	IDs();
}


void Qualifier()
{
	if (printSwitch)
		cout << "\t<Qualifier> ::= integer | boolean | real\n";

	if (currentToken.lexeme == "integer" || currentToken.lexeme == "true" 
		|| currentToken.lexeme == "false" || currentToken.lexeme == "real")
		lexAdv();
	else
	{
		cout << "\n<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>";
		cout << "Oops, you broke it. Expected 'integer', 'boolean', or 'real'.";
		exit(1);
	}
}


void IDs()
{
	if (printSwitch)
		cout << "\t<IDs> ::= <Identifier> | <Identifier>, <IDs>\n";

	if (currentToken.token == "IDENTIFIER")
	{
		lexAdv();
		if (currentToken.lexeme == ",")
		{
			lexAdv();
			IDs();
		}
	}
}

void StatementList()
{
	if (printSwitch)
		cout << "\t<Statement List> ::= <Statement> | <Statement> <Statement List>\n";

	while (currentToken.lexeme == "if" || currentToken.lexeme == "return" || currentToken.lexeme == "print"
			|| currentToken.lexeme == "read" || currentToken.lexeme == "while" || currentToken.token == "IDENTIFIER")
	{
		Statement();
	}
}


void Statement()
{
	if (printSwitch)
		cout << "\t<Statement> ::= <Compound> | <Assign> | <If> | <Return> | <Write> | <Read> | <While>\n";

	if (currentToken.lexeme == "{")
		Compound();
	else if (currentToken.token == "IDENTIFIER")
		Assign();
	else if (currentToken.lexeme == "if")
		If();
	else if (currentToken.lexeme == "return")
		Return();
	else if (currentToken.lexeme == "print")
		Write();
	else if (currentToken.lexeme == "read")
		Read();
	else if (currentToken.lexeme == "while")
		While();
	else
	{
		cout << "\n<><><><><><><><><><><><><><><><><><><>";
		cout << "<Statement> Error Unexpcted something.";
		exit(1);
	}
}


void Compound()
{
	if (printSwitch)
		cout << "\t<Compound> ::= {<Statement List>}\n";

	if (currentToken.lexeme == "{")
	{
		lexAdv();
		StatementList();
		if (currentToken.lexeme == "}")
		{
			lexAdv();
		}
	}
}


void Assign()
{
	if (printSwitch)
		cout << "\t<Assign> ::= <Identifier> := <Expression>;\n";

	if (currentToken.token == "IDENTIFIER")
	{
		lexAdv();
		if (currentToken.lexeme == ":=")
		{
			lexAdv();
			Expression();
			if (currentToken.lexeme == ";")
				lexAdv();
			else
			{
				cout << "\n<><><> <Assign> Syntax Error";
				exit(1);
			}
		}
	}
}


void If()
{
	if (printSwitch)
		cout << "\t<If> ::= if (<Condition>) <Statement> endif | if (<Condition>) <Statement> else <Statement> endif\n";
	if (currentToken.lexeme == "if")
	{
		lexAdv();
		if (currentToken.lexeme == "(")
		{
			lexAdv();
			Condition();
			if (currentToken.lexeme == ")")
			{
				lexAdv();
				Statement();
				if (currentToken.lexeme == "endif")
				{
					lexAdv();
				}
				else if (currentToken.lexeme == "else")
				{
					lexAdv();
					Statement();
					if (currentToken.lexeme == "endif")
					{
						lexAdv();
					}
					else
					{
						cout << "\n<><><><><><><><><><><><><><>";
						cout << "<If> error. Expecting 'endif'.";
						exit(1);
					}
				}
				else
				{
					cout << "\n<><><><><><><><><><><><><><><><><><><><>";
					cout << "<If> error. Expecting 'endif' or 'else'.";
					exit(1);
				}
			}
		}
	}
}


void Return()
{
	if (printSwitch)
		cout << "\t<Return> ::= return; | return <Expression>;\n";

	lexAdv();
	if (currentToken.lexeme == ";")
	{
		lexAdv();
	}
	else
	{
		Expression();
		if (currentToken.lexeme == ";")
			lexAdv();
		else
		{
			cout << "\n<><><> <Return> Syntax Error. Expecting ';'.";
			exit(1);
		}
	}
}


void Write()
{
	if (printSwitch)
		cout << "\t<Write> ::= print (<Expressions>);\n";

	lexAdv();
	if (currentToken.lexeme == "(")
	{
		lexAdv();
		Expression();
		if (currentToken.lexeme == ")")
		{
			lexAdv();
			if (currentToken.lexeme == ";")
				lexAdv();
			else
			{
				cout << "\n<><><> Syntax Error. Expecting ';'";
				exit(1);
			}
		}
		else
		{
			cout << "\n<><><> Syntax Error. Expecting ')'.";
			exit(1);
		}
	}
}


void Read()
{
	if (printSwitch)
		cout << "\t<Read> ::= read (<IDs>);\n";

	lexAdv();
	if (currentToken.lexeme == "(")
	{
		lexAdv();
		IDs();
		if (currentToken.lexeme == ")")
		{
			lexAdv();
			if (currentToken.lexeme == ";")
				lexAdv();
			else
			{
				cout << "\n<><><> Syntax Error. Expecting ';'";
				exit(1);
			}
		}
		else
		{
			cout << "\n<><><> Syntax Error. Expecting ')'.";
			exit(1);
		}
	}
}


void While()
{
	if (printSwitch)
		cout << "\t<While> ::= while (<Condition>) <Statement>\n";

	lexAdv();
	if (currentToken.lexeme == "(")
	{
		lexAdv();
		Condition();
		if (currentToken.lexeme == ")")
		{
			lexAdv();
			Statement();
		}
	}
}


void Condition()
{
	if (printSwitch)
		cout << "\t<Condition> ::= <Expression> <Relop> <Expression>\n";

	Expression();
	Relop();
	Expression();
}


void Relop()
{
	if (printSwitch)
		cout << "\t<Relop> ::= = | /= | > | < | => | <=\n";

	if (currentToken.lexeme == "=" || currentToken.lexeme == "/=" || currentToken.lexeme == ">"
		|| currentToken.lexeme == "<" || currentToken.lexeme == "=>" || currentToken.lexeme == "<=")
	{
		lexAdv();
	}
}


void Expression()
{
	if (printSwitch)
		cout << "\t<Expression> ::= <Term> <Expression Prime>\n";
	Term();
	ExpressionPrime();
}


void ExpressionPrime()
{
	if (printSwitch)
		cout << "\t<Expression Prime> ::= + <Term> <Expression Prime> | - <Term> <Expression Prime> | <Empty>\n";
	
	if (currentToken.lexeme == "+" || currentToken.lexeme == "-")
	{
		lexAdv();
		Term();
		ExpressionPrime();
	}
	else if (currentToken.token == "UNKNOWN")
	{
		cout << "<Expression Prime> Error. Expecting +, -, or nothing.\n";
	}
	else
	{
		Empty();
	}
}


void Term()
{
	if (printSwitch)
		cout << "\t<Term> ::= <Factor> <Term Prime>\n";
	
	Factor();
	TermPrime();
}


void TermPrime()
{
	if (printSwitch)
		cout <<  "\t<Term Prime> ::= * <Factor> <Term Prime> | / <Factor> <Term Prime> | <Empty>\n";

	if (currentToken.lexeme == "*" || currentToken.lexeme == "/")
	{
		lexAdv();
		Factor();
		TermPrime();
	}
	else if (currentToken.token == "UNKNOWN")
	{
		cout << "\n<><><><><><><><><><><><><><><><><><>";
		cout << "Error. Expecting '*', '/', or 'Empty'.";
		exit(1);
	}
	else
	{
		Empty();
	}
}


void Factor()
{
	if (printSwitch)
		cout << "\t<Factor> ::= - <Primary> | <Primary>\n";

	if (currentToken.lexeme == "-")
	{
		lexAdv();
		Primary();
	}
	
	if (currentToken.token != "UNKNOWN")
	{
		Primary();
	}
	
	else
	{
		cout << "\n<><><><><><><><>";
		cout << "<Factor> Error";
		exit(1);
	}
}


void Primary()
{
	if (printSwitch)
		cout << "\t<Primary> ::= <Identifier> | <Integer> | <Identifier> [<IDs>] | (<Expression>) | <Real> | true | false\n";

	if (currentToken.token == "IDENTIFIER")
	{
		lexAdv();
		if (currentToken.lexeme == "[")
		{
			lexAdv();
			IDs();
			if (currentToken.lexeme == "]")
			{
				lexAdv();
			}
			else
			{
				cout << "\n<><><><><><><><><><><><><><><>";
				cout << "<Primary> error.  Expecting ']'";
				exit(1);
			}
		}
	}
	
	else if (currentToken.token == "INTEGER" || currentToken.token == "REAL")
	{
		lexAdv();
	}
	
	else if (currentToken.lexeme == "(")
	{
		lexAdv();
		Expression();
		if (currentToken.lexeme == ")")
		{
			lexAdv();
		}
		else
		{
			cout << "\n<><><><><><><><><><><><><><><><>";
			cout << "<Primary> error.  Expecting ')'";
			exit(1);
		}
	}

	else if (currentToken.lexeme == "true" || currentToken.lexeme == "false")
	{
		lexAdv();
	}
	else
	{
		cout << "\n<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>";
		cout << "<Primary> error. '<Identifer>', '<Qualifier>', 'true', or 'false' expected.";
		exit(1);
	}
}


void Empty()
{
	if (printSwitch)
		cout << "\t<Empty> ::= epsilon\n";

}

