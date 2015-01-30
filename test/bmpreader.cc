#include <bits/stdc++.h>

using namespace std;

#define _str (char*)

const int maxn = 2009;

struct bmp {
	int a[maxn][maxn], n, m;
};

void perr(char* word = 0) {
	if (word)
		fprintf(stderr, "Error: %s\n", word);
	else
		fprintf(stderr, "Error\n");
	exit(1);
}

const int buf_len = 16;

unsigned char buf[buf_len];

void readBMP(bmp& g, FILE* pf) {
	while (!feof(pf)) {
		int g(fread(buf, 1, sizeof(buf), pf));
		for (int i = 0; i < g; ++ i)
			printf("%02x ", (int)buf[i]);
		putchar(10);
	}
}

bmp a;

int main(int argc, char* args[]) {
	FILE *ipf, *opf;
	if (argc < 2)
		perr(_str "Wrong args");
	ipf = fopen(args[1], "rb");
	if (!ipf)
		perr(_str "Wrong input file");
	if (argc > 3)
		opf = fopen(args[2], "w");
	else
		opf = stdout;
	readBMP(a, ipf);
	fclose(ipf);
	fclose(opf);
	return 0;
}

