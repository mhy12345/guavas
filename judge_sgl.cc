/******************************************
 * Project Guavas
 * Judge for single digit
 * Source code
 * By CDQZ_laekov
 * ***************************************/
#include "judge_sgl.h"

inline double sqr(double x) {
	return x * x;
}

inline double dist(double x0, double y0, double x1, double y1) {
	return sqr(x0 - x1) + sqr(y0 - y1);
}

Position :: Position() {
	x = 0, y = 0;
}

Position :: Position(int x0, int y0) {
	x = x0, y = y0;
}

void JudgeSingle :: init() {
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

Picture debo;

int f[10][funclen];

JudgeReturn JudgeSingle :: judge(const Picture& x) {
	obj = x;
	this-> init();
	return JudgeReturn('u', rand());
}

void JudgeSingle :: test(const Picture& x, char* outputFileName, int task) {
	puts(outputFileName);
	obj = x;
	this-> init();

	/*debo = x;
	debo. SetPixel(cog. x, cog. y, RGB(255, 0, 0));
	for (int i = lu. x; i <= rd. x; ++ i) {
		debo. SetPixel(i, lu. y, RGB(0, 0, 255));
		debo. SetPixel(i, rd. y, RGB(0, 0, 255));
	}
	for (int i = lu. y; i <= rd. y; ++ i) {
		debo. SetPixel(lu. x, i, RGB(0, 0, 255));
		debo. SetPixel(rd. x, i, RGB(0, 0, 255));
	}*/

	memset(f, 0, sizeof(f));

	if (task == 1) {
		debo. SetHeight(hei * 10);
		debo. SetWidth(wid * 10);
		for (int i = 0; i < 10; ++ i)
			for (int j = 0; j < 10; ++ j)
				debo. SetPixel(cog. x * 10 + i, cog. y * 10 + j, def_colors[0]);
	}

	for (int rt = 0; rt * cir0 <= 1; ++ rt) {
		double r(rt * cir0);
		for (int x = lu. x; x <= rd. x; ++ x)
			for (int y = lu. y; y <= rd. y; ++ y)
				if (isItem(obj. GetPixel(x, y)))
					if (fabs(sqr(x - cog. x) + sqr(y - cog. y) - sqr(r * maxr)) < linew * r) {
						double tht(asin(((double)y - cog. y) / (r * maxr)) + PI / 2.0);
						if (x < cog. x || (x == cog. x && y > cog. y)) 
							tht += PI;
						int fpos(tht / (PI * 2.0) * funclen);
						if (fpos >= funclen)
							fpos = funclen - 1;
						else if (fpos < 0)
							fpos = 0;
						++ f[rt][fpos];
						if (task == 1) {
							for (int i = 0; i < 10; ++ i)
								for (int j = 0; j < 10; ++ j)
									debo. SetPixel(x * 10 + i, y * 10 + j, def_colors[rt]);
						}
					}
	}

	if (task == 2) {
		debo. SetWidth(funclen * 5);
		debo. SetHeight(210);
		for (int c = 0; c <= 4; ++ c) {
			for (int i = 0; i < funclen; ++ i)
				if (f[c][i])
					for (int j = 0; j < 5; ++ j)
						for (int k = -1; k < 1; ++ k)
							debo. SetPixel(max(0, 200 + k - 20 * (c + 1)), i * 5 + j, def_colors[c]);
		}
	}

	debo. PrintIntoFile(outputFileName);
}

