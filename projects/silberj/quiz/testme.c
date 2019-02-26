#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

int randomValue;
char characterSymbols[9] = {'[','(','{',' ','a','x','}',')',']'};
char* stringLetters[5] = {"r","e","s","e","t"};
char builtString[6];

int randomNumber(int min, int max)
{
	int range;
	range = max-min + 1;
	return rand()%range + min;
}

char inputChar()
{
	randomValue = randomNumber(0,8);
    return characterSymbols[randomValue];
}

char *inputString()
{
	int index;
    memset(builtString, '\0', 6);
	for(index = 0; index < 5; index++)
	{
		randomValue = randomNumber(0,4);

		if(index == 0)
		{
			strcpy(builtString, stringLetters[randomValue]);
		}
		else
        {
			strcat(builtString, stringLetters[randomValue]);
        }
	}

	return builtString;
}

void testme()
{
  int tcCount = 0;
  char *s;
  char c;
  int state = 0;
  while (1)
  {
    tcCount++;
    c = inputChar();
    s = inputString();
    printf("Iteration %d: c = %c, s = %s, state = %d\n", tcCount, c, s, state);

    if (c == '[' && state == 0) state = 1;
    if (c == '(' && state == 1) state = 2;
    if (c == '{' && state == 2) state = 3;
    if (c == ' '&& state == 3) state = 4;
    if (c == 'a' && state == 4) state = 5;
    if (c == 'x' && state == 5) state = 6;
    if (c == '}' && state == 6) state = 7;
    if (c == ')' && state == 7) state = 8;
    if (c == ']' && state == 8) state = 9;
    if (s[0] == 'r' && s[1] == 'e'
       && s[2] == 's' && s[3] == 'e'
       && s[4] == 't' && s[5] == '\0'
       && state == 9)
    {
      printf("error ");
      exit(200);
    }
  }
}


int main(int argc, char *argv[])
{
    srand(time(NULL));
    testme();
    return 0;
}
