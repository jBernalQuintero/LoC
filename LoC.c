//////////////////////////////////////////////////////////////
//Name: Loc.c 												//
//Author: Juan Bernal										//
//Inputs: filename, operators								//
//Description:												//
//		This program is a line counter for code projects.	//
//	This line counter opens the file and then counts the 	//
//	number of lines of code in the file by counting what	//
//	are considered 'legal' semicolons.  Legal semicolons 	//
//	are semicolons outside of the context of strings or 	//
//	or comments.  For example, ;;;;;; these should not be 	//
//	counted.												//
//	Note: As of now, operators don't exist yet				//
//															//
//////////////////////////////////////////////////////////////

#include <stdio.h>

struct lineTypes
{
	int totalCount;				//total number of lines
	int totalSemicolons;		//total number of semicolons
	int legalSemicolons;		//total number of legal semicolons
};

int LineCount(FILE *pointer);

int main(int argc, char **argv)
{
	FILE *filePoint;

	//check for command accuracy
	if(argc < 2)
	{
		printf("Too few arguments.\n");
		return 0;
	}

	//open file
	filePoint = fopen(argv[1], "r");
	if(filePoint == NULL)
	{
		printf("File could not be opened.\n");
		return 0;
	}

	//process file
	

	//output results
	printf("Total number of lines: %i\n", LineCount(filePoint));
	//close file
	fclose(filePoint);

	return 0; //stop... hammertime
}

int LineCount(FILE *pointer)
{	
	int count = 0;
	int semicolons = 0;
	int comment = 0;

	if(pointer != NULL)
	{
		count = 1;
	}
	char testChar;
	char nextChar;	//used in the case of closing /* comments
/* old code
	do
	{
		char testChar;	//character checked
		testChar = fgetc(pointer);
		if(testChar == ';')
		{
			count++;
		}	
	}while(!feof(pointer));

	return count;
	*/
	while(!feof(pointer))
	{
		testChar = fgetc(pointer);
		switch (testChar)
		{
			//if we see a new line
			case '\n':
				count++;
				if(comment == 1)
				{
					comment = 0;	//reset single line comments
				}
				break;
			case ';':
				if(comment == 0)
				{
					semicolons+= 1;
				}
				break;
			//comment cases
			/**/
			case '/':
				testChar = fgetc(pointer);
				//case 1: single line comments
				if(testChar == '/')
				{
					comment = 1;
				}
				//case 2: multi-line comments
				else if(testChar =='*' && comment == 0)
				{
					comment = 2;
				}
				// next character is a new line
				else if(testChar == '\n')
				{
					count++;
				}
				break;
				/**/
			case '\'':
				if(comment == 3)
				{
					comment = 0;
				}
				else if(comment == 0)
				{
					comment = 3;
				}
				break;
				/**/
			case '\"':
				//reset quote marker
				if(comment == 4)
				{
					comment = 0;
				}
				//set quote marker
				else if (comment == 0)	//if we are not in a comment OR a quote
				{
					comment = 4;	//set us in quote
				}
				break;
				/**/
			case '*':
				testChar = fgetc(pointer);
				if(testChar == '/')
				{
					comment = 0;	//reset multi-line comments
				}
				else if(testChar == '\n')
				{
					count++;
				}
				break;
		}
	}
	return semicolons;
}