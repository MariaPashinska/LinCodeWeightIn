#include <time.h>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>

#include "testDriver.h"

struct eval
{
	int n, k, q, count;
	double time;
};

eval WD_test[100000], MD_test[100000], SL_test[100000], SE_test[100000], CL_test[100000], CE_test[100000];

void dreadgmat_specv(FILE *fpr, dmat_type &genmat, unsigned long long int SP[]) // general  chete  finami`na matrica
{

	int d = 0, m = 0, n = 0, q = 0;

	char *ch;
	char cc;
	char chh[301];

	int error = 0;

	error = fscanf(fpr, "%d", &m); // if(error ==0){ ERRORQ("Error in reading,\n\n"); }
	error = fscanf(fpr, "%d", &n); // if(error ==0){ ERRORQ("Error in reading,\n\n"); }

	error = fscanf(fpr, "%d", &q); // if(error ==0){ ERRORQ("Error in reading,\n\n"); }

	fgets(chh, 300, fpr);
	int y = 0;
	if (chh[0] != '\n')
	{
		strcpy(genmat.name, "");
		int ii = 0;
		while (chh[ii] != '\n')
		{
			genmat.name[ii] = chh[ii];
			ii++;
		}
		genmat.name[ii] = '\0';
		// strcpy(genmat.name, chh);
	}
	else
	{
		strcpy(genmat.name, "  ");
	}

	// int j=sizeof( char);
	ch = (char *)malloc((n) * 4);
	int lch = n * 4;
	// fgets(ch, sizeof(ch), fpr);
	dmat_new(genmat, m, n, q); // otdelia pamet za matricata ako ne e otdelena

	// maketable(genmat.q); // zaregda tablicite na poleto

	// genmat.k = genmat.k;
	char c = 1;
	// while (c!='\n'){
	//      c=getc(fpr);}
	for (int kk = 1; kk <= genmat.k; kk++)
	{
		fgets(ch, lch, fpr);
		int len = 0;
		while (ch[len])
		{
			len++;
		}
		// int y=sizeof(ch*);
		if ('\n' == ch[len - 1])
		{
			len--;
		}
		int com = 0;
		for (int i = 0; i < len; i++)
		{
			if (',' == ch[i])
			{
				com++;
			}
			// if('\n'==ch[i]){len=i-1;break;}
		}

		char ct, st[10];
		int tt = -1, nn = 0, comh = 0;
		if ((com > 0) && (com != n))
		{
			ERRORQ((com > 0) && (com != n));
			// printf("error\n"); return;
		}
		if (com > 0)
		{ // ako ima zapetajki
			for (int i = 0; i < len; i++)
			{
				if (',' != ch[i])
				{
					if ((48 <= ch[i]) && (48 + q - 1 >= ch[i]))
					{
						tt++;
						st[tt] = ch[i];
					}
					else
					{
						// printf("error\n"); return;
						ERRORQ(!((48 <= ch[i]) && (48 + q - 1 >= ch[i])))
					}
				}
				if (',' == ch[i])
				{
					tt++;
					st[tt] = '\n';
					int r = atoi(st);
					nn++;
					genmat.a[kk][nn] = atoi(st);
					;
					tt = -1;
					comh++;
					if (comh == n)
					{
						i = len;
						break;
					}
				}
			}
		}
		else
		{ // ako niama zapetajki megdu elementite - bsiako chislo e element
			for (int i = 0; i < n; i++)
			{
				if ((48 <= ch[i]) && (48 + q - 1 >= ch[i]))
				{
				}
				else
				{
					// printf("error\n"); return;
					ERRORQ(!((48 <= ch[i]) && (48 + q - 1 >= ch[i])))
				}

				st[0] = ch[i];
				st[1] = '\n';
				int r = atoi(st);
				nn++;
				genmat.a[kk][nn] = atoi(st);
				;
			}
		} // kraj ako niama zapetajki
	}
	free(ch);
	for (int i = 0; i < 3000; i++)
	{
		SP[i] = 0;
	}
	for (int i = 0; i <= n; i++)
	{
		error = fscanf(fpr, "%llu", &SP[i]);
	}
	return;
}

bool testWD(dmat_type &dgenmatv, unsigned long long int *SP, int id)
{
	int **G;
	G = new int *[dgenmatv.k + 1];
	for (int i = 0; i <= dgenmatv.k; i++)
	{
		G[i] = new int[dgenmatv.n + 1];
		for (int j = 0; j <= dgenmatv.n; j++)
		{
			G[i][j] = 0;
		}
	}
	for (int i = 0; i < dgenmatv.k; i++)
	{
		for (int j = 0; j < dgenmatv.n; j++)
		{
			G[i][j] = dgenmatv.a[i + 1][j + 1];
		}
	}
	clock_t begin, end;
	double t = 0;
	begin = clock();
	calculateWeightDistribution(G, dgenmatv.n, dgenmatv.k, dgenmatv.q, false);
	end = clock();
	t = (end - begin) / (double(CLOCKS_PER_SEC));

	for (int i = 1; i <= dgenmatv.n; i++)
	{
		if (SP[i] != weights[i])
		{
			printf("Error calculationg weight spectrum for code with parameters [%d,%d]_%d", dgenmatv.n, dgenmatv.k, dgenmatv.q);
			for (int i = 0; i <= dgenmatv.k; i++)
			{
				delete[] G[i];
			}
			delete[] G;
			ERRORQ(SP[i] != weights[i]);
			return false;
		}
	}
	WD_test[id].n = dgenmatv.n;
	WD_test[id].k = dgenmatv.k;
	WD_test[id].q = dgenmatv.q;
	WD_test[id].time += t;
	WD_test[id].count++;
	for (int i = 0; i <= dgenmatv.k; i++)
	{
		delete[] G[i];
	}
	delete[] G;
	return true;
}

bool testMD(dmat_type &dgenmatv, unsigned long long int *SP, int id)
{
	int **G;
	G = new int *[dgenmatv.k + 1];
	for (int i = 0; i <= dgenmatv.k; i++)
	{
		G[i] = new int[dgenmatv.n + 1];
		for (int j = 0; j <= dgenmatv.n; j++)
		{
			G[i][j] = 0;
		}
	}
	for (int i = 0; i < dgenmatv.k; i++)
	{
		for (int j = 0; j < dgenmatv.n; j++)
		{
			G[i][j] = dgenmatv.a[i + 1][j + 1];
		}
	}

	int d = 0, i = 0, d_res = 0;
	while (SP[i] == 0)
	{
		i++;
	}
	d = i;

	clock_t begin, end;
	double t = 0;
	begin = clock();
	d_res = min_dis(G, dgenmatv.n, dgenmatv.k, dgenmatv.q, false);
	end = clock();
	t = (end - begin) / (double(CLOCKS_PER_SEC));
	if (d != d_res)
	{
		printf("Error calculating minimal distance in code with parameters [%d,%d]_%d", dgenmatv.n, dgenmatv.k, dgenmatv.q);
		for (int i = 0; i <= dgenmatv.k; i++)
		{
			delete[] G[i];
		}
		delete[] G;
		ERRORQ(d != d_res);
		return false;
	}

	MD_test[id].n = dgenmatv.n;
	MD_test[id].k = dgenmatv.k;
	MD_test[id].q = dgenmatv.q;
	MD_test[id].time += t;
	MD_test[id].count++;
	for (int i = 0; i <= dgenmatv.k; i++)
	{
		delete[] G[i];
	}
	delete[] G;
	return true;
}

bool testSE(dmat_type &dgenmatv, unsigned long long int *SP, int id)
{
	int **G;
	G = new int *[dgenmatv.k + 1];
	for (int i = 0; i <= dgenmatv.k; i++)
	{
		G[i] = new int[dgenmatv.n + 1];
		for (int j = 0; j <= dgenmatv.n; j++)
		{
			G[i][j] = 0;
		}
	}
	for (int i = 0; i < dgenmatv.k; i++)
	{
		for (int j = 0; j < dgenmatv.n; j++)
		{
			G[i][j] = dgenmatv.a[i + 1][j + 1];
		}
	}

	clock_t begin, end;
	double t = 0;
	bool foundEQ = true, foundEQ_res = true;

	int min_w = 0;
	while (SP[min_w] == 0)
	{
		min_w++;
	}

	for (int i = min_w - 1; i <= min_w + 1; i++)
	{
		if (SP[i] == 0)
			foundEQ = false;
		else
			foundEQ = true;

		begin = clock();
		foundEQ_res = find_word_equal_to_fixed_weight(G, dgenmatv.n, dgenmatv.k, dgenmatv.q, i, false);
		end = clock();
		t = (end - begin) / (double(CLOCKS_PER_SEC));

		if (foundEQ != foundEQ_res)
		{
			printf("Error finding word with given weight in code with parameters [%d,%d]_%d", dgenmatv.n, dgenmatv.k, dgenmatv.q);
			for (int i = 0; i <= dgenmatv.k; i++)
			{
				delete[] G[i];
			}
			delete[] G;
			ERRORQ(foundEQ != foundEQ_res);
			return false;
		}
		SE_test[id].n = dgenmatv.n;
		SE_test[id].k = dgenmatv.k;
		SE_test[id].q = dgenmatv.q;
		SE_test[id].time += t;
		SE_test[id].count++;
	}

	for (int i = 0; i <= dgenmatv.k; i++)
	{
		delete[] G[i];
	}
	delete[] G;
	return true;
}

bool testSL(dmat_type &dgenmatv, unsigned long long int *SP, int id)
{
	int **G;
	G = new int *[dgenmatv.k + 1];
	for (int i = 0; i <= dgenmatv.k; i++)
	{
		G[i] = new int[dgenmatv.n + 1];
		for (int j = 0; j <= dgenmatv.n; j++)
		{
			G[i][j] = 0;
		}
	}
	for (int i = 0; i < dgenmatv.k; i++)
	{
		for (int j = 0; j < dgenmatv.n; j++)
		{
			G[i][j] = dgenmatv.a[i + 1][j + 1];
		}
	}

	clock_t begin, end;
	double t = 0;
	bool foundLT = false, foundLT_res = false;

	int min_w = 0;
	while (SP[min_w] == 0)
	{
		min_w++;
	}

	for (int i = min_w - 1; i <= min_w + 1; i++)
	{
		foundLT = false, foundLT_res = false;
		for (int j = 1; j < i; j++)
		{
			if (SP[j] != 0)
			{
				foundLT = true;
				break;
			}
		}

		begin = clock();
		foundLT_res = find_word_less_than_fixed_weight(G, dgenmatv.n, dgenmatv.k, dgenmatv.q, i, false);
		end = clock();
		t = (end - begin) / (double(CLOCKS_PER_SEC));

		if (foundLT != foundLT_res)
		{
			printf("Error finding word with weight less than given value in code with parameters [%d,%d]_%d", dgenmatv.n, dgenmatv.k, dgenmatv.q);
			for (int i = 0; i <= dgenmatv.k; i++)
			{
				delete[] G[i];
			}
			delete[] G;
			ERRORQ(foundLT != foundLT_res);
			return false;
		}
		SL_test[id].n = dgenmatv.n;
		SL_test[id].k = dgenmatv.k;
		SL_test[id].q = dgenmatv.q;
		SL_test[id].time += t;
		SL_test[id].count++;
	}

	for (int i = 0; i <= dgenmatv.k; i++)
	{
		delete[] G[i];
	}
	delete[] G;
	return true;
}

unsigned long long int testCE(dmat_type &dgenmatv, unsigned long long int *SP, int id)
{
	int **G;
	G = new int *[dgenmatv.k + 1];
	for (int i = 0; i <= dgenmatv.k; i++)
	{
		G[i] = new int[dgenmatv.n + 1];
		for (int j = 0; j <= dgenmatv.n; j++)
		{
			G[i][j] = 0;
		}
	}
	for (int i = 0; i < dgenmatv.k; i++)
	{
		for (int j = 0; j < dgenmatv.n; j++)
		{
			G[i][j] = dgenmatv.a[i + 1][j + 1];
		}
	}

	clock_t begin, end;
	double t = 0;
	unsigned long long int countEQ = 0, countEQ_res = 0;

	int min_w = 0;
	while (SP[min_w] == 0)
	{
		min_w++;
	}

	for (int i = min_w - 1; i <= min_w + 1; i++)
	{
		countEQ = SP[i];

		begin = clock();
		countEQ_res = calculate_number_of_words_with_fixed_w(G, dgenmatv.n, dgenmatv.k, dgenmatv.q, i, true, false);
		end = clock();
		t = (end - begin) / (double(CLOCKS_PER_SEC));

		if (countEQ != countEQ_res)
		{
			printf("Calculating number of words with given weight in code with parameters [%d,%d]_%d", dgenmatv.n, dgenmatv.k, dgenmatv.q);
			for (int i = 0; i <= dgenmatv.k; i++)
			{
				delete[] G[i];
			}
			delete[] G;
			ERRORQ(countEQ != countEQ_res);
			return false;
		}
		CE_test[id].n = dgenmatv.n;
		CE_test[id].k = dgenmatv.k;
		CE_test[id].q = dgenmatv.q;
		CE_test[id].time += t;
		CE_test[id].count++;
	}

	for (int i = 0; i <= dgenmatv.k; i++)
	{
		delete[] G[i];
	}
	delete[] G;
	return true;
}

unsigned long long int testCL(dmat_type &dgenmatv, unsigned long long int *SP, int id)
{
	int **G;
	G = new int *[dgenmatv.k + 1];
	for (int i = 0; i <= dgenmatv.k; i++)
	{
		G[i] = new int[dgenmatv.n + 1];
		for (int j = 0; j <= dgenmatv.n; j++)
		{
			G[i][j] = 0;
		}
	}
	for (int i = 0; i < dgenmatv.k; i++)
	{
		for (int j = 0; j < dgenmatv.n; j++)
		{
			G[i][j] = dgenmatv.a[i + 1][j + 1];
		}
	}

	clock_t begin, end;
	double t = 0;
	unsigned long long int countLT = 0, countLT_res = false;

	int min_w = 0;
	while (SP[min_w] == 0)
	{
		min_w++;
	}

	for (int i = min_w - 1; i <= min_w + 1; i++)
	{
		countLT = 0, countLT_res = 0;
		for (int j = 1; j < i; j++)
		{
			countLT += SP[j];
		}

		begin = clock();
		countLT_res = calculate_number_of_words_less_than_fixed_w(G, dgenmatv.n, dgenmatv.k, dgenmatv.q, i, true, false);
		end = clock();
		t = (end - begin) / (double(CLOCKS_PER_SEC));

		if (countLT != countLT_res)
		{
			printf("Calculating number of words with weight less than given value in code with parameters [%d,%d]_%d", dgenmatv.n, dgenmatv.k, dgenmatv.q);
			for (int i = 0; i <= dgenmatv.k; i++)
			{
				delete[] G[i];
			}
			delete[] G;
			ERRORQ(countLT != countLT_res);
			return false;
		}
		CL_test[id].n = dgenmatv.n;
		CL_test[id].k = dgenmatv.k;
		CL_test[id].q = dgenmatv.q;
		CL_test[id].time += t;
		CL_test[id].count++;
	}

	for (int i = 0; i <= dgenmatv.k; i++)
	{
		delete[] G[i];
	}
	delete[] G;
	return true;
}

void test_drive()
{

	clock_t begin_all, end_all;
	int scan_res;
	double time_all = 0;

	int option = -1;

	while (option < 1 || option > 6)
	{
		printf("Choose main function to test (SSE):\n");
		printf("1. Weight Distribution\n");
		printf("2. Minimal distance \n");
		printf("3. Searching for codewords with weight less than d\n");
		printf("4. Searching for codewords with weight equal to d\n");
		printf("5. Counting codewords with weight less than d\n");
		printf("6. Counting codewords with weight equal to d\n");

		scan_res = scanf("%d", &option);
		if (scan_res == 0 || scan_res == EOF)
		{
			printf("Reading input error!\n");
			return;
		}
		if (option < 1 || option > 6)
		{
			printf("Invalid input\n");
		}
	}
	test = 5;

	detect();
	if (instructionSet < test)
	{
		printf("Platform does not have chosen instruction set. No calculations are executed.\n\n");
		return;
	}

	dmat_type dgenmatv;
	unsigned long long int SP[3000];
	FILE *testfile, *resultFile;
	char fileName[100];
	int ii = 0;

	printf("Enter input file:\n");
	scan_res = scanf("%99s", fileName);
	if (scan_res == 0 || scan_res == EOF)
	{
		printf("Reading file name error! Using file \"TestDataSmall\"\n");
		testfile = fopen("TestDataSmall", "r");
		ERRORQ(testfile == NULL);
	}
	else
	{
		testfile = fopen(fileName, "r");
		if (testfile == NULL)
		{
			printf("File %s can't be opened. Using file \"TestDataSmall\".\n", fileName);
			testfile = fopen("TestDataSmall", "r");
			ERRORQ(testfile == NULL);
		}
	}

	printf("Results are written in file \"Results\".\n");
	resultFile = fopen("Results", "a");
	ERRORQ(resultFile == NULL);

	switch (option)
	{
	case 1:
		fprintf(resultFile, "Testing (Weight distribution):\n\n");
		break;
	case 2:
		fprintf(resultFile, "Testing (Minimal distance):\n\n");
		break;
	case 3:
		fprintf(resultFile, "Testing (Searching for codewords with weight less than d):\n\n");
		break;
	case 4:
		fprintf(resultFile, "Testing (Searching for codewords with weight equal to d):\n\n");
		break;
	case 5:
		fprintf(resultFile, "Testing (Counting codewords with weight less than d):\n\n");
		break;
	case 6:
		fprintf(resultFile, "Testing (Counting codewords with weight equal to d):\n\n");
		break;
	default:
		printf("Invalid input\n");
		break;
	}

	ii = fclose(resultFile);
	char c = 1;
	int num = 0, id = 0;

	for (int i = 0; i < 100000; i++)
	{
		WD_test[i].count = 0;	WD_test[i].time = 0;	WD_test[i].n = 0;	WD_test[i].k = 0;	WD_test[i].q = 0;
		MD_test[i].count = 0;	MD_test[i].time = 0;	MD_test[i].n = 0;	MD_test[i].k = 0;	MD_test[i].q = 0;
		SE_test[i].count = 0;	SE_test[i].time = 0;	SE_test[i].n = 0;	SE_test[i].k = 0;	SE_test[i].q = 0;
		SL_test[i].count = 0;	SL_test[i].time = 0;	SL_test[i].n = 0;	SL_test[i].k = 0;	SL_test[i].q = 0;
		CE_test[i].count = 0;	CE_test[i].time = 0;	CE_test[i].n = 0;	CE_test[i].k = 0;	CE_test[i].q = 0;
		CL_test[i].count = 0;	CL_test[i].time = 0;	CL_test[i].n = 0;	CL_test[i].k = 0;	CL_test[i].q = 0;
	}

	begin_all = clock();
	while (!(feof(testfile)))
	{
		c = getc(testfile);
		if (c == '?')
		{
			num++;
			dreadgmat_specv(testfile, dgenmatv, SP);
			switch (option) // not correct for neon
			{
			case 1:
				testWD(dgenmatv, SP, id);
				break;
			case 2:
				testMD(dgenmatv, SP, id);
				break;
			case 3:
				testSL(dgenmatv, SP, id);
				break;
			case 4:
				testSE(dgenmatv, SP, id);
				break;
			case 5:
				testCL(dgenmatv, SP, id);
				break;
			case 6:
				testCE(dgenmatv, SP, id);
				break;
			default:
				printf("Invalid input\n\n");
				break;
			}

			if (num % 100 == 0)
			{
				double ave = 0;

				resultFile = fopen("Results", "a");
				ERRORQ(resultFile == NULL);
				
				switch (option) // not correct for neon
				{
				case 1:
					fprintf(resultFile, "[%d,%d]_%d\n", WD_test[id].n, WD_test[id].k, WD_test[id].q);
					ave = WD_test[id].time / WD_test[id].count;
					fprintf(resultFile, "Weight spectrum: OK  %.5f sec. \n", ave);
					break;
				case 2:
					fprintf(resultFile, "[%d,%d]_%d\n", MD_test[id].n, MD_test[id].k, MD_test[id].q);
					ave = MD_test[id].time / MD_test[id].count;
					fprintf(resultFile, "Minimum distance: OK  %.5f sec. \n", ave);
					break;
				case 3:
					fprintf(resultFile, "[%d,%d]_%d\n", SL_test[id].n, SL_test[id].k, SL_test[id].q);
					ave = SL_test[id].time / SL_test[id].count;
					fprintf(resultFile, "Search less than: OK  %.5f sec. \n", ave);
					break;
				case 4:
					fprintf(resultFile, "[%d,%d]_%d\n", SE_test[id].n, SE_test[id].k, SE_test[id].q);
					ave = SE_test[id].time / SE_test[id].count;
					fprintf(resultFile, "Search equal: OK  %.5f sec. \n", ave);
					break;
				case 5:
					fprintf(resultFile, "[%d,%d]_%d\n", CL_test[id].n, CL_test[id].k, CL_test[id].q);
					ave = CL_test[id].time / CL_test[id].count;
					fprintf(resultFile, "Count less than: OK  %.5f sec. \n", ave);
					break;
				case 6:
					fprintf(resultFile, "[%d,%d]_%d\n", CE_test[id].n, CE_test[id].k, CE_test[id].q);
					ave = CE_test[id].time / CE_test[id].count;
					fprintf(resultFile, "Count equal: OK  %.5f sec. \n", ave);
					break;
				default:
					printf("Invalid input\n");
					break;
				}
				
				ii = fclose(resultFile);

				id++;


			}
		}
	}
	end_all = clock();
	time_all = (end_all - begin_all) / (double(CLOCKS_PER_SEC));
	resultFile = fopen("Results", "a");
	ERRORQ(resultFile == NULL);
	fprintf(resultFile, "\n\n\nTotal time: %f\n", time_all);
	ii = fclose(testfile);
	ii = fclose(resultFile);
	test = -1;
}

void test_driveSSE(int mode)
{
	// mode:
	// mode==1 => WD
	// mode==2 => MD
	// mode==3 => SE
	// mode==4 => SL
	// mode==5 => CE
	// mode==6 => CL

	clock_t begin_all, end_all;
	int scan_res;
	double time_all = 0;
	FILE *testfile, *resultFile;
	int option = 0;

	printf("Testing SSE4.1 functions \n");
	test = 5;

	detect();
	if (instructionSet < test)
	{
		printf("Platform does not have chosen instruction set. No calculations are executed.\n\n");
		ERRORQ("Platform does not have chosen instruction set. No calculations are executed.\n\n");
		return;
	}

	dmat_type dgenmatv;
	unsigned long long int SP[3000];

	testfile = fopen("ArticleData", "r");
	ERRORQ(testfile == NULL);

	for (int i = 0; i < 100000; i++)
	{
		WD_test[i].count = 0;
		WD_test[i].time = 0;
		WD_test[i].n = 0;
		WD_test[i].k = 0;
		WD_test[i].q = 0;
		MD_test[i].count = 0;
		MD_test[i].time = 0;
		MD_test[i].n = 0;
		MD_test[i].k = 0;
		MD_test[i].q = 0;
		SE_test[i].count = 0;
		SE_test[i].time = 0;
		SE_test[i].n = 0;
		SE_test[i].k = 0;
		SE_test[i].q = 0;
		SL_test[i].count = 0;
		SL_test[i].time = 0;
		SL_test[i].n = 0;
		SL_test[i].k = 0;
		SL_test[i].q = 0;
		CE_test[i].count = 0;
		CE_test[i].time = 0;
		CE_test[i].n = 0;
		CE_test[i].k = 0;
		CE_test[i].q = 0;
		CL_test[i].count = 0;
		CL_test[i].time = 0;
		CL_test[i].n = 0;
		CL_test[i].k = 0;
		CL_test[i].q = 0;
	}

	char c = 1;
	int num = 0, id = 0, ii;

	switch (mode)
	{
	case 1: // weight distribution

		printf("Results are written in file \"Results_WeightDistribution_SSE\".\n");
		resultFile = fopen("Results_WeightDistribution_SSE", "a");
		ERRORQ(resultFile == NULL);
		fprintf(resultFile, "Testing with SSE4.1 instruction set:\n\n");

		ii = fclose(resultFile);
		c = 1;
		num = 0, id = 0;
		begin_all = clock();
		while (!(feof(testfile)))
		{
			c = getc(testfile);
			if (c == '?')
			{
				num++;
				dreadgmat_specv(testfile, dgenmatv, SP);
				testWD(dgenmatv, SP, id);

				if (num % 100 == 0)
				{
					double ave = 0;

					resultFile = fopen("Results_WeightDistribution_SSE", "a");

					ERRORQ(resultFile == NULL);
					fprintf(resultFile, "[%d,%d]_%d\n", WD_test[id].n, WD_test[id].k, WD_test[id].q);
					printf("[%d,%d]_%d\n", WD_test[id].n, WD_test[id].k, WD_test[id].q);
					ave = WD_test[id].time / WD_test[id].count;
					fprintf(resultFile, "Weight spectrum: OK  %.5f sec. \n", ave);
					printf("Weight spectrum: OK  %.5f sec. \n", ave);
					ii = fclose(resultFile);
					id++; // printf("id=%d", id);
				}
			}
		}
		end_all = clock();
		time_all = (end_all - begin_all) / (double(CLOCKS_PER_SEC));
		resultFile = fopen("Results_WeightDistribution_SSE", "a");

		ERRORQ(resultFile == NULL);
		fprintf(resultFile, "\n\n\nTotal time: %f\n", time_all);
		printf("\n\n\nTotal time: %f\n", time_all);
		ii = fclose(resultFile);
		break;
	case 2: // Minimum distance
		printf("Results are written in file \"Results_MinimumDistance_SSE\".\n");
		resultFile = fopen("Results_MinimumDistance_SSE", "a");
		ERRORQ(resultFile == NULL);
		fprintf(resultFile, "Testing with SSE4.1 instruction set:\n\n");

		ii = fclose(resultFile);
		c = 1;
		num = 0, id = 0;
		begin_all = clock();
		while (!(feof(testfile)))
		{
			c = getc(testfile);
			if (c == '?')
			{
				num++;
				dreadgmat_specv(testfile, dgenmatv, SP);
				testMD(dgenmatv, SP, id);

				if (num % 100 == 0)
				{
					double ave = 0;

					resultFile = fopen("Results_MinimumDistance_SSE", "a");

					ERRORQ(resultFile == NULL);
					fprintf(resultFile, "[%d,%d]_%d\n", MD_test[id].n, MD_test[id].k, MD_test[id].q);
					printf("[%d,%d]_%d\n", MD_test[id].n, MD_test[id].k, MD_test[id].q);
					ave = MD_test[id].time / MD_test[id].count;
					fprintf(resultFile, "Minimum distance: OK  %.5f sec. \n", ave);
					printf("Minimum distance: OK  %.5f sec. \n", ave);
					ii = fclose(resultFile);
					id++; // printf("id=%d", id);
				}
			}
		}
		end_all = clock();
		time_all = (end_all - begin_all) / (double(CLOCKS_PER_SEC));
		resultFile = fopen("Results_MinimumDistance_SSE", "a");

		ERRORQ(resultFile == NULL);
		fprintf(resultFile, "\n\n\nTotal time: %f\n", time_all);
		printf("\n\n\nTotal time: %f\n", time_all);
		ii = fclose(resultFile);
		break;
	case 3: // search equal

		printf("Results are written in file \"Results_SearchEqual_SSE\".\n");
		resultFile = fopen("Results_SearchEqual_SSE", "a");
		ERRORQ(resultFile == NULL);
		fprintf(resultFile, "Testing with SSE4.1 instruction set:\n\n");

		ii = fclose(resultFile);
		c = 1;
		num = 0, id = 0;
		begin_all = clock();
		while (!(feof(testfile)))
		{
			c = getc(testfile);
			if (c == '?')
			{
				num++;
				dreadgmat_specv(testfile, dgenmatv, SP);
				testSE(dgenmatv, SP, id);

				if (num % 100 == 0)
				{
					double ave = 0;

					resultFile = fopen("Results_SearchEqual_SSE", "a");

					ERRORQ(resultFile == NULL);
					fprintf(resultFile, "[%d,%d]_%d\n", SE_test[id].n, SE_test[id].k, SE_test[id].q);
					printf("[%d,%d]_%d\n", SE_test[id].n, SE_test[id].k, SE_test[id].q);

					ave = SE_test[id].time / SE_test[id].count;
					fprintf(resultFile, "Search equal: OK  %.5f sec. \n", ave);
					printf("Search equal: OK  %.5f sec. \n", ave);
					ii = fclose(resultFile);

					id++; // printf("id=%d", id);
				}
			}
		}
		end_all = clock();
		time_all = (end_all - begin_all) / (double(CLOCKS_PER_SEC));
		resultFile = fopen("Results_SearchEqual_SSE", "a");

		ERRORQ(resultFile == NULL);
		fprintf(resultFile, "\n\n\nTotal time: %f\n", time_all);
		printf("\n\n\nTotal time: %f\n", time_all);
		ii = fclose(resultFile);
		break;
	case 4: // search less than
		printf("Results are written in file \"Results_SearchLessThan_SSE\".\n");
		resultFile = fopen("Results_SearchLessThan_SSE", "a");
		ERRORQ(resultFile == NULL);
		fprintf(resultFile, "Testing with SSE4.1 instruction set:\n\n");

		ii = fclose(resultFile);
		c = 1;
		num = 0, id = 0;
		begin_all = clock();
		while (!(feof(testfile)))
		{
			c = getc(testfile);
			if (c == '?')
			{
				num++;
				dreadgmat_specv(testfile, dgenmatv, SP);
				testSL(dgenmatv, SP, id);

				if (num % 100 == 0)
				{
					double ave = 0;
					resultFile = fopen("Results_SearchLessThan_SSE", "a");

					ERRORQ(resultFile == NULL);
					fprintf(resultFile, "[%d,%d]_%d\n", SL_test[id].n, SL_test[id].k, SL_test[id].q);
					printf("[%d,%d]_%d\n", SL_test[id].n, SL_test[id].k, SL_test[id].q);
					ave = SL_test[id].time / SL_test[id].count;
					fprintf(resultFile, "Search less than: OK  %.5f sec. \n", ave);
					printf("Search less than: OK  %.5f sec. \n", ave);
					ii = fclose(resultFile);

					id++; // printf("id=%d", id);
				}
			}
		}
		end_all = clock();
		time_all = (end_all - begin_all) / (double(CLOCKS_PER_SEC));
		resultFile = fopen("Results_SearchLessThan_SSE", "a");

		ERRORQ(resultFile == NULL);
		fprintf(resultFile, "\n\n\nTotal time: %f\n", time_all);
		printf("\n\n\nTotal time: %f\n", time_all);
		ii = fclose(resultFile);
		break;
	case 5: // count equal
		printf("Results are written in file \"Results_CountEqual_SSE\".\n");
		resultFile = fopen("Results_CountEqual_SSE", "a");
		ERRORQ(resultFile == NULL);
		fprintf(resultFile, "Testing with SSE4.1 instruction set:\n\n");

		ii = fclose(resultFile);
		c = 1;
		num = 0, id = 0;
		begin_all = clock();
		while (!(feof(testfile)))
		{
			c = getc(testfile);
			if (c == '?')
			{
				num++;
				dreadgmat_specv(testfile, dgenmatv, SP);
				testCE(dgenmatv, SP, id);

				if (num % 100 == 0)
				{
					double ave = 0;
					resultFile = fopen("Results_CountEqual_SSE", "a");

					ERRORQ(resultFile == NULL);
					fprintf(resultFile, "[%d,%d]_%d\n", CE_test[id].n, CE_test[id].k, CE_test[id].q);
					printf("[%d,%d]_%d\n", CE_test[id].n, CE_test[id].k, CE_test[id].q);

					ave = CE_test[id].time / CE_test[id].count;
					fprintf(resultFile, "Count equal: OK  %.5f sec. \n", ave);
					printf("Count equal: OK  %.5f sec. \n", ave);
					ii = fclose(resultFile);

					id++; // printf("id=%d", id);
				}
			}
		}
		end_all = clock();
		time_all = (end_all - begin_all) / (double(CLOCKS_PER_SEC));
		resultFile = fopen("Results_CountEqual_SSE", "a");

		ERRORQ(resultFile == NULL);
		fprintf(resultFile, "\n\n\nTotal time: %f\n", time_all);
		printf("\n\n\nTotal time: %f\n", time_all);
		ii = fclose(resultFile);
		break;
	case 6: // Count Less Than
		printf("Results are written in file \"Results_CountLessThan_SSE\".\n");
		resultFile = fopen("Results_CountLessThan_SSE", "a");
		ERRORQ(resultFile == NULL);
		fprintf(resultFile, "Testing with SSE4.1 instruction set:\n\n");

		ii = fclose(resultFile);
		c = 1;
		num = 0, id = 0;
		begin_all = clock();
		while (!(feof(testfile)))
		{
			c = getc(testfile);
			if (c == '?')
			{
				num++;
				dreadgmat_specv(testfile, dgenmatv, SP);
				testCL(dgenmatv, SP, id);

				if (num % 100 == 0)
				{
					double ave = 0;
					resultFile = fopen("Results_CountLessThan_SSE", "a");

					ERRORQ(resultFile == NULL);
					fprintf(resultFile, "[%d,%d]_%d\n", CL_test[id].n, CL_test[id].k, CL_test[id].q);
					printf("[%d,%d]_%d\n", CL_test[id].n, CL_test[id].k, CL_test[id].q);
					ave = CL_test[id].time / CL_test[id].count;
					fprintf(resultFile, "Count less than: OK  %.5f sec. \n", ave);
					printf("Count less than: OK  %.5f sec. \n\n\n", ave);
					ii = fclose(resultFile);
					id++; // printf("id=%d", id);
				}
			}
		}
		end_all = clock();
		time_all = (end_all - begin_all) / (double(CLOCKS_PER_SEC));
		resultFile = fopen("Results_CountLessThan_SSE", "a");

		ERRORQ(resultFile == NULL);
		fprintf(resultFile, "\n\n\nTotal time: %f\n", time_all);
		printf("\n\n\nTotal time: %f\n", time_all);
		ii = fclose(resultFile);
		break;
	}

	ii = fclose(testfile);
	test = -1;
}
