#include <windows.h>
#include <stdint.h>
#include <stdio.h>


typedef struct _foreststructure //12 bytes
{
	struct _foreststructure *first; 		//0			//index 0
	struct _foreststructure *second;		//4			//index 1
	int32_t third;					//8			//index 2
} foreststructure;

foreststructure * nest(foreststructure * pforest, char n)
{
	if (pforest)
	{
		if (pforest->third >= n)
		{
			pforest->first = nest(pforest->first, n);
			return pforest;
		}
		else
		{
			pforest->second = nest(pforest->second, n);
			return pforest;
		}
	}
	else
	{
		foreststructure *result = (foreststructure *)malloc(sizeof(foreststructure)); //12
		result->first = 0;
		result->second = 0;
		result->third = n;
		return result;
	}
}

foreststructure *get_third_argument(char *string)  // "yuoteavpxqgrlsdhwfjkzi_cmbn"
{
	foreststructure *pforeststruct = 0;

	for (int32_t i = 0; string[i] != 0; ++i)
	{
		pforeststruct = nest(pforeststruct, string[i]);
	}
	
	return pforeststruct;
}

int check2(foreststructure *pforest, char *string1, char n)
{
	int result = 0;

	if (pforest && *string1)
	{
		if (pforest->third == n)
		{
			if (*string1 == 'D')
				result = pforest->third == n;
			else
				result = 0;
		}
		else if (pforest->third <= n)
		{
			if (*string1 == 'R')
				result = check2(pforest->second, string1 + 1, n);
			else
				result = 0;
		}
		else if (*string1 == 'L')
		{
			result = check2(pforest->first, string1 + 1, n);
		}
		else
		{
			result = 0;
		}
	}

	//printf("%c", *string1);			//added code
	
	return result;
}

int check(foreststructure *pforest, char *string1, char *string2)
{
	if (pforest && string1 && string2)
	{
		int n = 1;
		while (*string1 && *string2)				
		{
			//n &= check2(pforest, string1, *string2++);
			//check2 has to continuously return 1 for it to be true
			int m = check2(pforest, string1, *string2++);
			n &= m;
			while (*string1 == 'L' || *string1 == 'R')
			{
				++string1;
			}
			++string1;

			printf("%d", m);
		}
		return (*string1 == 0 && *string2 == 0) & (byte)n;
	}
	

	return 0;
}



int main(int argc, char **argv)
{
	foreststructure *forest = get_third_argument("yuoteavpxqgrlsdhwfjkzi_cmbn");

	/*if (argc != 3)
	{
		puts("You have the wrong number of arguments for this forest.");
		//printf("%s [password] [string]\n", *argv);
		exit(1);
	}*/
	printf("\n"); //added code
	//if (check(forest, argv[2], argv[1]))
	if (check(forest, 
		"DLLDLDLLLLLDLLLLRLDLLDLDLLLRRDLLLLRDLLLLLDLLRLRRRDLLLDLLLDLLLLLDLLRDLLLRRLDLLLDLLLLLDLLLRLDLLDLLRLRRDLLLDLLRLRRRDLLRDLLLLLDLLLRLDLLDLLRLRRDLLLLLDLLRDLLLRRLDLLLDLLLLLDLLRDLLRLRRDLLLDLLLDLLRLRRRDLLLLLDLLLLRLDLLLRRLRRDDLLLRRDLLLRRLRDLLLRLDLRRDDLLLRLDLLLRRRDLLRLRRRDLRRLD",
		argv[1]))
	{
		printf("\n"); //added code
		puts("You did it! Submit the input as the flag");
	}
	else
	{
		printf("\n");
		puts("Nope.");
	}
	
	return 0;
}