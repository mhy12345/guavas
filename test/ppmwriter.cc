#include <bits/stdc++.h>

using namespace std;

const int maxn = 1009;

int n, m, a[maxn][maxn];

void printToFile() {
	FILE* opf = fopen("a.ppm", "w");
	fprintf(opf, "P3\n%d %d\n255\n", m, n);
	for (int i = 0; i < n; ++ i, fputc(10, opf))
		for (int j = 0; j < m; ++ j)
			for (int k = 0, v = a[i][j]; k < 3; ++ k, v >>= 8)
				fprintf(opf, "%d ", v & 0xff);
	fclose(opf);
}

int main() {
	srand(19980628);
	n = 48;
	m = 48;
	int bl = 24;
	for (int i = 0; i < n; i += bl)
		for (int j = 0; j < m; j += bl) {
			int c(rand() & 0x00ffffff);
			for (int k = i; k < i + bl; ++ k)
				for (int l = j; l < j + bl; ++ l)
					a[k][l] = c;
		}
	printToFile();
}
