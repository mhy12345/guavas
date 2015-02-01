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
			if (obj. GetPixel(i, j) != RGB(255, 255, 255)) {
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
			if (obj. GetPixel(i, j))
				sr = max((double)sr, dist(i, j, cog. x, cog. y));
}

Picture debo;

int f[10][funclen];

JudgeReturn JudgeSingle :: judge(const Picture& x) {
	obj = x;
	this-> init();
	return JudgeReturn('u', rand());
}

void JudgeSingle :: test(const Picture& x, char* outputFileName) {
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

	for (int rt = 1; rt * cir0 <= 1; ++ rt) {
		double r(rt * cir0);
		for (int x = lu. x; x <= rd. x; ++ x)
			for (int y = lu. y; y <= rd. y; ++ y) {
				//printf("%.3lf\n", fabs(sqr(x - cog. x) + sqr((y - cog. y) * ort) - sqr(r)));
				if (fabs(sqr(x - cog. x) + sqr((y - cog. y) * ort) - sqr(r * (rd. x - cog. x))) < linew * r)
					debo. SetPixel(x, y, RGB(0, 255, 0));
			}
	}

	debo. PrintIntoFile(outputFileName);
}

