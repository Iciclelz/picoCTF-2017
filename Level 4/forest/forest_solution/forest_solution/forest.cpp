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

	return result;
}

int checkbuf[52];
int check(foreststructure *pforest, char *string1, char *string2)
{
	int z = 0;
	if (pforest && string1 && string2)
	{
		int n = 1;
		while (*string1 && *string2)
		{

			int m = check2(pforest, string1, *string2++);
			n &= m;
			while (*string1 == 'L' || *string1 == 'R')
			{
				++string1;
			}
			++string1;

			checkbuf[z] = m;
			z++;
		}
		return (*string1 == 0 && *string2 == 0) & (byte)n;
	}


	return 0;
}


char *make_data(char c)
{
	char data[52];
	for (int i = 0; i < 51; ++i)
	{
		data[i] = c;
	}
	printf("%c", c);
	return data;
}


int main(int argc, char **argv)
{
	foreststructure *forest = get_third_argument("yuoteavpxqgrlsdhwfjkzi_cmbn");

	char flag[52]; //size is 52
	memset(flag, 0, sizeof(flag));

	for (int i = 'a'; i <= 'z'; ++i)
	{
		check(forest,
			"DLLDLDLLLLLDLLLLRLDLLDLDLLLRRDLLLLRDLLLLLDLLRLRRRDLLLDLLLDLLLLLDLLRDLLLRRLDLLLDLLLLLDLLLRLDLLDLLRLRRDLLLDLLRLRRRDLLRDLLLLLDLLLRLDLLDLLRLRRDLLLLLDLLRDLLLRRLDLLLDLLLLLDLLRDLLRLRRDLLLDLLLDLLRLRRRDLLLLLDLLLLRLDLLLRRLRRDDLLLRRDLLLRRLRDLLLRLDLRRDDLLLRLDLLLRRRDLLRLRRRDLRRLD",
			make_data(i)); 

		for (int n = 0; n < 51; ++n)
		{
			if (checkbuf[n] == 1)
			{
				flag[n] = i;
			}
		}
	}

	printf("\r\n");
	for (int i = 0; i < 51; ++i)
	{
		if (flag[i] == 0)
		{
			printf("_");
		}
		else
		{
			printf("%c", flag[i]);
		}
	}

	

	getchar();
	return 0;
}