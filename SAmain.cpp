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


int tokenIndex = 0;
bool printSwitch =  true;
vector<tokenData>   tokens;
vector<tokenData>   tokenList;
tokenData           currentToken;

int main() 
{
	bool				    wroteHeader = false;
	ifstream			    ifget;
	LA                      lex;
	string				    current = "";
	string				    infilepath = "";
	string				    outfilepath = "";


	//Input file to read from
	cout << "Before you begin, make sure the input test file is in\nthe same folder as the .exe of this program.\n";
	cout << "----------------------------------------------------------------------\n";
	cout << "Please enter the file name and extension of the input file (input.txt).\n";
	cout << "Input: ";
	getline(cin, infilepath);
	cout << "You entered: " << infilepath << endl << endl;

	//Output file to write to
	cout << "Please enter the file and extension of the output file (output.txt).\n";
	cout << "Input: ";
	getline(cin, outfilepath);
	cout << "You entered: " << outfilepath << endl << endl;

	//Open file for reading
	ifget.open(infilepath);

	//Catch issue with opening file
	if (!ifget)
	{
		cout << "Error. Unable to read file." << endl;
		system("pause");
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
	lex.printTokens(tokenList, outfilepath);

    /*
     * New stuff goes here
     */

	system("pause");
	return 0;
}



void Rat16F()
{
	if (printSwitch == true)
		cout << "<Rat16F> ::= $$ <Opt Function Definitions>\n$$ <Opt Declaration List> <Statement List> $$\n";

	if (currentToken.lexeme == "$$")
	{
		lexAdv();
		OptFuncDef();
		if (currentToken.lexeme == "$$")
		{
			lexAdv();
			OptDecList();
			StatementList();
		}
	}
}

void OptFuncDef()
{

}

void funcdef()
{

}

void func()
{

}

void optparamlist()
{

}

void ParamList()
{

}

void Parameter()
{

}

void Qualifier()
{

}

void Body()
{

}

void OptDecList()
{

}

void DecList()
{

}

void Declaration()
{

}

void IDs()
{

}

void StatementList()
{
	if (printSwitch == true)
		cout << "<Statement List> ::= <Statement> | <Statement> <Statement List>\n";
}

void Statement()
{
	if (printSwitch == true)
		cout << "<Statement> ::= <Compound> | <Assign> | <If> | <Return> | <Write> | <Read> | <While>\n";
}

void Compound()
{
	if (printSwitch == true)
		cout << "<Compound> ::= {<Statement List>}\n";
}

void Assign()
{
	if (printSwitch == true)
		cout << "<Assign> ::= <Identifier> := <Expression>;\n";
}

void If()
{
	if (printSwitch == true)
		cout << "<If> ::= if (<Condition>) <Statement> endif | if (<Condition>) <Statement> else <Statement> endif\n";
}

void Return()
{
	if (printSwitch == true)
		cout << "<Return> ::= return; | return <Expression>;\n";
}

void Write()
{
	if (printSwitch == true)
		cout << "<Write> ::= print (<Expressions>);\n";
}

void Read()
{
	if (printSwitch == true)
		cout << "<Read> ::= read (<IDs>);\n";
}

void While()
{
	if (printSwitch == true)
		cout << "<While> ::= while (<Condition>) <Statement>\n";
}

void Condition()
{
	if (printSwitch == true)
		cout << "<Condition> ::= <Expression> <Relop> <Expression>\n";
}

void Relop()
{
	if (printSwitch == true)
		cout << "<Relop> ::= = | /= | > | < | => | <=\n";
}

void Expression()
{
	if (printSwitch == true)
		cout << "<Expression> ::= <Term> <Expression Prime>\n";
}

void ExpressionPrime()
{
	if (printSwitch == true)
		cout << "<Expression Prime> ::= + <Term> <Expression Prime> | - <Term> <Expression Prime> | <Empty>\n";
}

void Term()
{
	if (printSwitch == true)
		cout << "<Term> ::= <Factor> <Term Prime>\n";
}

void TermPrime()
{
	if (printSwitch == true)
		cout <<  "<Term Prime> ::= * <Factor> <Term Prime> | / <Factor> <Term Prime> | <Empty>\n";
}

void Factor()
{
	if (printSwitch == true)
		cout << "<Factor> ::= - <Primary> | <Primary>\n";
}

void Primary()
{
	if (printSwitch == true)
		cout << "<Primary> ::= <Identifier> | <Integer> | <Idetifier> [<IDs>] | (<Expression>) | <Real> | true | false\n";
}

void Empty()
{
	if (printSwitch == true)
		cout << "<Empty> ::= epsilon\n";

}

void lexAdv() {
	if (tokenIndex < tokenList.size())
	{
		currentToken = tokenList[tokenIndex];
	}
	tokenIndex++;
}


