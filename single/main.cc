#include "judge_sgl.h"

int main(int argc, char* args[]) {
	if (argc < 2) {
		fputs("No arguments", stderr);
		exit(1);
	}
	Picture* pic = new Picture;
	pic-> AttachFromFile(args[1]);
	JudgeReturn ret(JudgeSingle(). judge(*pic));
	printf("%c %.10lf\n", ret. first, ret. second);
}
