/******************************************
 * Project Guavas
 * Judge for single digit
 * Source code
 * By CDQZ_laekov
 * ***************************************/
#include "judge_sgl.h"
#include "linear_match.h"

Position :: Position() {
	x = 0, y = 0;
}

Position :: Position(int x0, int y0) {
	x = x0, y = y0;
}

double f[5][funclen];
double funcdef[10][5][funclen];
void initFuncDef(char* fileName) {
	FILE* ipf = fopen(fileName, "rb");
	for (int i = 0; i < 10; ++ i)
		for (int j = 0; j <= 4; ++ j)
			fread(funcdef[i][j], sizeof(double), funclen, ipf);
	fclose(ipf);
}

void JudgeSingle :: init(const Picture& x) {
	obj = x;
	int tot(0), xtot(0), ytot(0);
	hei = obj. GetHeight();
	wid = obj. GetWidth();
	lu = pos_t(hei, wid);
	rd = pos_t(0, 0);
	for (int i = 0; i < hei; ++ i)
		for (int j = 0; j < wid; ++ j)
			if (isItem(obj. GetPixel(i, j))) {
				++ tot;
				xtot += i;
				ytot += j;
				upmin(lu. x, i);
				upmin(lu. y, j);
				upmax(rd. x, i);
				upmax(rd. y, j);
			}
	ort = ((double)rd. x - lu. x + 1) / ((double)rd. y - lu. y);
	if (tot) {
		cog. x = (int)round((double)xtot / tot);
		cog. y = (int)round((double)ytot / tot);
	}
	else {
		fprintf(stderr, "No black points!\n");
	}
	sr = 0;
	for (int i = 0; i < hei; ++ i)
		for (int j = 0; j < wid; ++ j)
			if (isItem(obj. GetPixel(i, j))) {
				upmax(sr, dist(i, j, cog. x, cog. y));
			}
	maxr = sqrt(sr);
}

bool cmpSecond(const JudgeReturn& a, const JudgeReturn& b) {
	return a. second < b. second;
}

JudgeReturn JudgeSingle :: judge() {
	JudgeReturn ret[10];
	this-> makeCircles(0, (char*)0);
	double vx[10][5], sr[10] = {0};
	int vse(-1);
	for (int d = 0; d < 10; ++ d) {
		//printf("%c ", d + 48);
		for (int i = 1; i <= 4; ++ i) {
			vx[d][i] = LinearMatch :: matchArrs(f[i], f[i] + funclen, funcdef[d][i]);
			sr[d] += vx[d][i] * (i + 4);
	//		printf("%8.3lf\t", vx[d][i]);
		}
	//	printf("%8.3lf\n", sr[d]);
		ret[d] = JudgeReturn(d + 48, sr[d]);
	}
	sort(ret, ret + 10, cmpSecond);
	double rat(ret[0]. second / ret[1]. second);
	if (rat >= 0.9) {
		for (int i = 0; i < 10; ++ i)
			printf("\33[31m%3c: \33[32m%5.3lf", ret[i]. first, ret[i]. second);
		printf("\33[0m");
		putchar(10);
	}
	ret[0]. second /= ret[1]. second;
	return ret[0];
}

void JudgeSingle :: makeCircles(int task, char* outputFileName) {
	static int cnt[5][funclen];
	memset(f, 0, sizeof(f));
	memset(cnt, 0, sizeof(cnt));
	Picture* debo;
	if (task == 1 || task == 2 || task == 3)
		debo = new Picture;
	if (task == 1) {
		debo-> SetHeight(hei);
		debo-> SetWidth(wid);
		for (int i = 0; i < hei; ++ i)
			for (int j = 0; j < wid; ++ j)
				debo-> SetPixel(i, j, def_colors[6]);
		for (int i = cog. x - 3; i <= cog. x + 3; ++ i)
			for (int j = cog. y - 3; j <= cog. y + 3; ++ j)
				debo-> SetPixel(i, j, def_colors[5]);
	}
	if (task == 3) {
		*debo = obj;
		for (int i = cog. x - 3; i <= cog. x + 3; ++ i)
			for (int j = cog. y - 3; j <= cog. y + 3; ++ j)
				debo-> SetPixel(i, j, def_colors[0]);
		debo-> PrintIntoFile(outputFileName);
		return;
	}
	for (int rt = 1; rt <= 4; ++ rt) {
		double r(rt * cir0);
		for (int x = lu. x; x <= rd. x; ++ x)
			for (int y = lu. y; y <= rd. y; ++ y)
				if (fabs(sqr(x - cog. x) + sqr(y - cog. y) - sqr(r * maxr)) < linew * r) {
					double tht(atan2(y - cog. y, x - cog. x) + PI);
					int fpos(tht / (PI * 2.0) * funclen - 1e-7);
					int isi(isItem(obj. GetPixel(x, y)));
					if (fpos >= funclen) {
						fpos = funclen - 1;
					}
					else if (fpos < 0) {
						fpos = 0;
					}
					for (int i = - guesslen; i <= guesslen; ++ i) {
						int q((i + fpos + funclen) % funclen);
						if (task == 3)
							q = fpos;
						cnt[rt][q] += sqr(guesslen - abs(i) + 1);
						f[rt][q] += sqr(guesslen - abs(i) + 1) * isi;
					}
					if (task == 1) {
						if (isi)
							debo-> SetPixel(x, y, def_colors[rt]);
					}
				}
	}
	for (int i = 1; i <= 4; ++ i)
		for (int j = 0; j < funclen; ++ j)
			f[i][j] /= (double)cnt[i][j] + 1e-8;
	if (task == 1)
		debo-> PrintIntoFile(outputFileName);
	else if (task == 2) {
		debo-> SetWidth(funclen * 5);
		debo-> SetHeight(210);
		for (int c = 1; c <= 4; ++ c) {
			for (int i = 0; i < funclen; ++ i)
				if (f[c][i])
					for (int j = 0; j < 5; ++ j)
						for (int k = -1; k < 1; ++ k)
							debo-> SetPixel(max(0, 200 + k - 20 * (c + 1)), 
									i * 5 + j, def_colors[c]);
		}
		debo-> PrintIntoFile(outputFileName);
	}
	if (task == 1 || task == 2)
		delete debo;
}

void JudgeSingle :: makeData(char *listFileName) {
	static int cnt[10][5][funclen];
	FILE* opf = fopen("indicatingdata", "wb");
	FILE* listf = fopen(listFileName, "r");
	char fileName[109];
	memset(cnt, 0, sizeof(cnt));
	memset(funcdef, 0, sizeof(funcdef));
	while (fscanf(listf, "%s", fileName) != EOF) {
		int d(-1);
		if (!strstr(fileName, ".ppm"))
			continue;
		for (char* i = fileName; *i; ++ i)
			if (isdigit(*i)) {
				d = *i - 48;
				break;
			}
		if (d == -1)
			continue;
		printf("Learning from %s\t", fileName);
		Picture *pic = new Picture;
		pic-> AttachFromFile(fileName);
		this-> init(*pic);
		this-> makeCircles(0, (char*)0);
		for (int i = 0; i <= 4; ++ i)
			for (int j = 0; j < funclen; ++ j) {
				++ cnt[d][i][j];
				funcdef[d][i][j] += f[i][j];
			}
		delete pic;
		printf("Done\n");
	}
	fclose(listf);
	for (int i = 0; i < 10; ++ i) {
		for (int j = 0; j <= 4; ++ j) {
			for (int k = 0; k < funclen; ++ k)
				f[j][k] = funcdef[i][j][k] / (cnt[i][j][k] + 1e-8);
			fwrite(f[j], sizeof(double), funclen, opf);
		}
	}
	fclose(opf);
}

