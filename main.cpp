#include <cstdio>
#include <cstring>

void usage()
{
	printf("\n  Usage:\n\
\n\
\t'filename.exe' this help\n\
\t'filename.exe <minusGradus> <input file name>'\n\
\t'filename.exe <minusGradus> <input file name> <output file name>'\n\
\n\
  Example:\n\
\n\
\t1) if use 'filename.exe 360 in.cnc' then program reading file\n\
\t'in.cnc' and writing file 'in_out.cnc' for output data\n\
\n\
\t2) if use 'filename.exe 360 in.cnc out.cnc' then program reading\n\
\tfile 'in.cnc' and writing new data to 'output.cnc' file.\n\n");
}

int main(int argc, char *args[])
{
	std::FILE *fi = nullptr;
	char filename[1024] = {0};
	char *pch = nullptr;
	int minusGradus = 0, tekGradus = 0, feedRate = 0;

	switch (argc)
	{
		case 4:
		    sscanf(args[1], "%d", &minusGradus);
			fi = std::fopen(args[2], "r");
			pch = args[3];
			break;
		case 3:
		    sscanf(args[1], "%d", &minusGradus);
			strcpy(filename, args[0]);
			pch = strrchr(filename, '.');
			if (nullptr != pch)
				*pch = 0;
			pch = filename;
			strcat(pch, "_out.cnc");
			fi = std::fopen(args[2], "r");
			pch = filename;
			break;
		default:
			usage();
			return 0;
	}

	if (nullptr == fi)
	{
		printf("Error open input file: '%s'!\nEnd program.\n", args[2]);
		return 1;
	}

	std::FILE *fo = std::fopen(pch, "w");

	if (nullptr == fo)
	{
		fclose(fi);
		printf("Error open output file: '%s'!\nEnd program.\n", pch);
		return 2;
	}

	int sLen = 255;
	char s[256] = { 0 };

	while(!std::feof(fi))
	{
		s[0] = 0;
		std::fgets(s, sLen, fi);
		if ((pch = strstr(s, "B")) != NULL)
		{
			sscanf(pch + 1, "%d", &tekGradus);
			if ((pch = strstr(s, "F")) != NULL)
			{
				sscanf(pch + 1, "%d", &feedRate);
				s[0] = 0;
				sprintf(s, "G1 B%d. F%d\n", tekGradus - minusGradus, feedRate);
			}
			else
			{
				s[0] = 0;
				sprintf(s, "G1 B%d.\n", tekGradus - minusGradus);
			}
		}
		std::fputs(s, fo);
	}

	std::fclose(fi);
	std::fclose(fo);

	printf("All complete.\n");

	return 0;
}
