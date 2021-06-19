#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include "ssu_score.h"

#define SECOND_TO_MICRO 1000000 //세컨드를 마이크로세컨드로 변환하기 위한 정의

void ssu_runtime(struct timeval *begin_t, struct timeval *end_t); //실행된 시간을 재기 위한 함수

int main(int argc, char *argv[])
{
	struct timeval begin_t, end_t;
	gettimeofday(&begin_t, NULL); // 시간 재기 시작

	ssu_score(argc, argv); // ssu_score 실행

	gettimeofday(&end_t, NULL); // 시간 재기 끝 
	ssu_runtime(&begin_t, &end_t); // ssu_score 실행하는데 걸린 시간 계산 

	exit(0);
}

void ssu_runtime(struct timeval *begin_t, struct timeval *end_t) // 시간 계산
{
	end_t->tv_sec -= begin_t->tv_sec; //(끝난 시간 - 시작한 시간) 계산함으로써 실행된 시간 계산

	if(end_t->tv_usec < begin_t->tv_usec){ //
		end_t->tv_sec--; //
		end_t->tv_usec += SECOND_TO_MICRO; //
	}

	end_t->tv_usec -= begin_t->tv_usec; //다시 계산
	printf("Runtime: %ld:%06ld(sec:usec)\n", end_t->tv_sec, end_t->tv_usec); //실행 시간 출력
}
