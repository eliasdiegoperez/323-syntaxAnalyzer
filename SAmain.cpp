/*
Andrew Nguyen
Joshua Womack 
CPSC323
Assignment 1 - Lexical Analyzer
*/

#include "LA.h"

using namespace std;


int main() 
{
	bool				    wroteHeader = false;
	ifstream			    ifget;
	LA                      lex;
	string				    current = "";
	string				    infilepath = "";
	string				    outfilepath = "";
	vector<LA::tokenData>	tokens;
	

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
		lex.printTokens(tokens, outfilepath);
	}

	ifget.close();

    /*
     * New stuff goes here
     */

	system("pause");
	return 0;
}

