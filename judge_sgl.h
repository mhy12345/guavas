/******************************************
 * Project Guavas
 * Judge for single digit
 * Source code
 * By CDQZ_laekov
 * ***************************************/
#ifndef JUDGE_SGL_H

#define JUDGE_SGL_H
#include "Picture.h"

typedef pair <char, double> JudgeReturn;
typedef struct Position {
	int x, y;
	Position();
	Position(int, int);
} pos_t;


class JudgeSingle {
	private:
		Picture obj;	//	object
		pos_t cog;	//	center of gravity
		int sr;	//	max distance between a black pixel and the center (squared)
		double maxr;	//	sqrt(sr)
		pos_t lu, rd;	//	Corners of number
		double ort;	//	Ratio of height and width
		int hei, wid;	//	object's height and width
		void init();	//	load args from object
	public:
		JudgeReturn judge(const Picture& x);
		void test(const Picture& x, char* outputFileName, int task);
		//	task: 1-Draw digits with circles; 2-Draw f(x) graph
};

#ifndef WIN32
#define RGB(_r_,_g_,_b_) (((_r_)<<16)|((_g_)<<8)|(_b_))
#endif

#define upmin(_a_,_b_) { \
	if (_a_ > _b_) \
		_a_ = _b_; \
}
#define upmax(_a_,_b_) { \
	if (_a_ < _b_) \
		_a_ = _b_; \
}
#define isItem(_x_) ((_x_)!=RGB(255,255,255))

const double cir0 = 0.25;
const double linew = 25;
const int funclen = 100;
const int def_colors[] = {RGB(255, 0, 0), RGB(0, 255, 255), RGB(255, 0, 0), RGB(255, 255, 0), RGB(255, 255, 255)};

#endif
