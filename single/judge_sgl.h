#ifndef JUDGE_SGL_H

#define JUDGE_SGL_H
#include "Picture.h"

typedef pair <char, double> JudgeReturn;
typedef struct Position {
	int x, y;
	Position(int, int);
} pos_t;


class JudgeSingle {
	private:
		Picture obj;	//	object
		pos_t cog;	//	center of gravity
		int sr;	//	max distance between a black pixel and the center (squared)
		int hei, wid;	//	object's height and width
		void init();	//	load args from object
	public:
		JudgeReturn judge(const Picture& x);
};

#endif
