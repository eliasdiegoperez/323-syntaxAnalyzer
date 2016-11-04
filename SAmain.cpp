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
bool printSwitch = true;
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
	if (currentToken.lexeme == "$$")
	{
		lexAdv();
		OptFuncDef();
		if (currentToken.lexeme == "$$")
		{
			OptDecList();
			StatementList();
		}
	}
}

void OptFuncDef()
{
	if (printSwitch == true)
	{
		cout << "<Opt Function Definition> ::= <Function Definitions> | <Empty>\n";
	}
}

void FuncDef()
{
	if (printSwitch == true)
	{
		cout << "<Function Definitions> ::= <Function> | <Function> <Function Definitions>\n";
	}
}

void Func()
{
	if (printSwitch == true)
	{
		cout << "<Function> ::= function <Identifier> [ <Opt Paramenter List> ] <Opt Declaration List> <Body>\n";
	}
}

void OptParamList()
{
	if (printSwitch == true)
	{
		cout << "<Opt Parameter List> ::= <Parameter List> | <Empty>\n";
	}
}

void ParamList()
{
	if (printSwitch == true)
	{
		cout << "<Parameter List> ::= <Parameter> | <Parameter>, <Parameter List>\n";
	}
}

void Parameter()
{
	if (printSwitch == true)
	{
		cout << "<Parameter> ::= <IDs> : <Qualifier>\n";
	}
}

void Qualifier()
{
	if (printSwitch == true)
	{
		cout << "<Qualifier> ::= integer | boolean | real\n";
	}
}

void Body()
{
	if (printSwitch == true)
	{
		cout << "<Body> ::= { <Statement List> }\n";
	}
}

void OptDecList()
{
	if (printSwitch == true)
	{
		cout << "<Opt Declaration List> ::= <Declaration List> | <Empty>\n";
	}
}

void DecList()
{
	if (printSwitch == true)
	{
		cout << "<Declaration List> ::= <Declaration>; | <Declaration> ; <Declaration List>\n";
	}
}

void Declaration()
{
	if (printSwitch == true)
	{
		cout << "<Declaration> ::= <Qualifier> <IDs>\n";
	}
}

void IDs()
{
	if (printSwitch == true)
	{
		cout << "<IDs> ::= <Identifier> | <Identifier>, <IDs>\n";
	}
}

void StatementList()
{

}

void Statement()
{

}

void Compound()
{

}

void Assign()
{

}

void If()
{

}

void Return()
{

}

void Write()
{

}

void Read()
{

}

void While()
{

}

void Condition()
{

}

void Relop()
{

}

void Expression()
{

}

void ExpressionPrime()
{

}

void Term()
{

}

void TermPrime()
{

}

void Factor()
{

}

void Primary()
{

}

void Empty()
{

}

void lexAdv()
{
	if (tokenIndex < tokenList.size())
	{
		currentToken = tokenList[tokenIndex];
	}
	tokenIndex++;
}

