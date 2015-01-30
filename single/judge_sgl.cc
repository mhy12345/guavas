#include "judge_sgl.h"

inline int sqr(int x) {
	return x * x;
}

inline int dist(int x0, int y0, int x1, int y1) {
	return sqr(x0 - x1) + sqr(y0 - y1);
}

Position :: Position(int x0 = 0, int y0 = 0) {
	x = x0, y = y0;
}

void JudgeSingle :: init() {
	int tot(0), xtot(0), ytot(0);
	hei = obj. GetHeight();
	wid = obj. GetWidth();
	for (int i = 0; i < hei; ++ i)
		for (int j = 0; j < wid; ++ j)
			if (obj. GetPixel(i, j)) {
				++ tot;
				xtot += i;
				ytot += j;
			}
	cog. x = (int)round((double)xtot / tot);
	cog. y = (int)round((double)ytot / tot);
	sr = 0;
	for (int i = 0; i < hei; ++ i)
		for (int j = 0; j < wid; ++ j)
			if (obj. GetPixel(i, j))
				sr = max(r, dist(i, j, cog. x, cog. y));
}

JudgeReturn JudgeSingle :: judge(const Picture& x) {
	obj = x;
	return JudgeReturn(rand() & 0xff, rand());
}

