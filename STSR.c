#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>


#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

#define LEN 70
//#define DEBUG TRUE

int main()
{
	char FileDirName[LEN];
	char FileDirNameOut[LEN];
	char plusorminus;
	int inhr, inmin, insec, inmill;//input hour, min, sec, mill
								   //	int MINUSVALUE;

	system("COLOR 02");
	//	system("COLOR 05");//purple

	/*- 27 Jan 2019*/

	printf("Subtitle Time Stamp Reducer \nJustin Bentley v1.1\n\n");

	printf("Enter File Directory & Name?\n");
	fseek(stdin, 0, SEEK_END);
	scanf("%s", FileDirName);

	printf("Amount to subtract or add?\nHH MM SS mmm, eg 1 2 3 400\n");
	fseek(stdin, 0, SEEK_END);
	scanf("%d %d %d %d", &inhr, &inmin, &insec, &inmill);

	inmin = inmin + (inhr * 60);
	insec = insec + (inmin * 60);
	inmill = inmill + (insec * 1000);//inmill = total milliseconds

	while (1) {
		printf("Add or Subtract (+) or (-)?\n");
		fseek(stdin, 0, SEEK_END);
		scanf("%c", &plusorminus);
		if (plusorminus == '+') { break; }
		if (plusorminus == '-') { inmill *= -1; break; }
	}

	printf("File %s\n", FileDirName);

	FILE *infile, *outfile;
	strcpy(FileDirNameOut, FileDirName);
	strcat(FileDirNameOut, "_Output.srt");
	char line[LEN];
	infile = fopen(FileDirName, "r"); if (infile == NULL) { return EXIT_FAILURE; }
	outfile = fopen(FileDirNameOut, "w");
	int hr, min, sec, mill, phr, pmin, psec, pmill;
	while (fgets(line, LEN, infile) > 0) {
		if (line[2] == ':' && line[5] == ':' && line[8] == ','&& line[15] == '>') {
			//	00:00:00,630 --> 00:00:02,439	// target
			for (int i = 0; i < 33; i++) {
				if (line[i] == ':' || line[i] == ',' ||
					line[i] == '-' || line[i] == '>') {
					line[i] = ' ';
				}
			}
			sscanf(line, "%d %d %d %d %d %d %d %d", &hr, &min, &sec, &mill, &phr, &pmin, &psec, &pmill);
			min = min + (hr * 60);
			sec = sec + (min * 60);
			mill = mill + (sec * 1000);
			pmin = pmin + (phr * 60);
			psec = psec + (pmin * 60);
			pmill = pmill + (psec * 1000);	//convert to milliseconds

			mill = mill + inmill;
			pmill = pmill + inmill;		//add or minus milliseconds

			hr = mill / 3600000; mill = mill - (hr * 3600000);
			min = mill / 60000; mill = mill - (min * 60000);
			sec = mill / 1000; mill = mill - (sec * 1000);
			phr = pmill / 3600000; pmill = pmill - (phr * 3600000);
			pmin = pmill / 60000; pmill = pmill - (pmin * 60000);
			psec = pmill / 1000; pmill = pmill - (psec * 1000);	//convert to time
			sprintf(line, "%2d:%2d:%2d,%3d --> %2d:%2d:%2d,%3d\n",
				hr, min, sec, mill, phr, pmin, psec, pmill);
			if (line[0] == ' ') { line[0] = '0'; }
			if (line[3] == ' ') { line[3] = '0'; }
			if (line[6] == ' ') { line[6] = '0'; }
			if (line[9] == ' ') { line[9] = '0'; }
			if (line[10] == ' ') { line[10] = '0'; }
			if (line[17] == ' ') { line[17] = '0'; }
			if (line[20] == ' ') { line[20] = '0'; }
			if (line[23] == ' ') { line[23] = '0'; }
			if (line[26] == ' ') { line[26] = '0'; }
			if (line[27] == ' ') { line[27] = '0'; }
		}
		fputs(line, outfile);
#ifdef DEBUG	printf("%s", line);
#endif
	}
	fclose(infile);
	fclose(outfile);

	printf("\nDONE");

	scanf("%s", FileDirName);	//halt

	return EXIT_SUCCESS;				/*TERMINATE*/

}
/*Color Codes : (FOR: system("COLOR ##"))
0 = Black
1 = Blue
2 = Green
3 = Aqua
4 = Red
5 = Purple
6 = Yellow
7 = White
8 = Gray
9 = Light Blue
A = Light Green
B = Light Aqua
C = Light Red
D = Light Purple
E = Light Yellow
F = Bright White*/
