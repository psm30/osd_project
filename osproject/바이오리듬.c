/*
  바이오리듬 계산기(Biorhythm calculator)
  2020037030 박소민
*/

#include <stdio.h>
#include <math.h>

#define PI 3.141592

long total_days(int year, int month, int day);    //기준일로 부터 특정일 사이 날짜수 계산 함수
void print_biorhythm(long total, int month);    //바이오리듬 계산 결과 출력 함수
char bio_status(int val, int mod);    //바이오리듬 상태 판단 함수

int main(void)
{
	int byr, bmon, bday;    //생년월일 저장 변수
	int tyr, tmon, tday;    //계산할 날짜 저장 변수
	long total = 0;    //생년월일과 계산할 날짜 사이의 일수

	printf("*****특정 월의 바이오리듬 계산*****\n");
	printf("\n");
	printf("생년 월일을 입력하세요 (ex: 2000 01 01): ");
	scanf("%d%d%d", &byr, &bmon, &bday);    //입력한 생년월일 저장
	printf("보시고 싶은 년도와 월을 입력하세요. (ex: 2021 11): ");
	scanf("%d%d", &tyr, &tmon);    //입력한 년도와 월 저장

	tday = 1;
	total = total_days(tyr, tmon, tday) - total_days(byr, bmon, bday);    //생년월일과 입력한 년월의 날짜수 계산
	printf("두 날짜 사이의 날짜수는 %ld일 입니다. \n\n", total);    //두 날짜 사이 날짜수 출력

	printf("[바이오리듬 결과]\n\n");
	print_biorhythm(total, tmon);    //바이오 리듬 결과 출력 함수 호출
	return 0;
}

/*

기준일(1년 1월 1일)로부터 특정일 사이의 날짜 수의 계산 함수 total_days

*/
long total_days(int year, int month, int day)
{
	int months[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };    //1~12월 날짜 수
	int i;
	long total = 0L;
	total = (year - 1) * 365L + (year - 1) / 4 - (year - 1) / 100 + (year - 1) / 400;
	//total에 year-1년도 까지의 날짜수 저장
	//4로 나누어지는 횟수 - 100으로 나누어지는 횟수(평년) + 400으로 나누어지는 횟수 = 윤년 횟수
	if (year % 4 == 0 && year % 100 != 0 || year % 400 == 0) //윤년일 때만 2월달 일 수 하루 추가
		months[1]++;
	for (i = 0; i < month - 1; i++)    
		total += months[i];    //total에 month-1월 까지의 날짜수 더함
	total += day;    //total에 남은 날짜수 더함
	return total;    //계산한 날짜 수 반환
}

/*
바이오리듬의 상태를 판단하는 함수 bio_status
*/

char bio_status(int v, int mod)
{
	char result;
	double r;
	r = sin(v * 3.141592 / (mod / 2.0));   //바이오 리듬 계산식
	//r의 값에 따라 저조기 위험기 고조기 결정
	if (r < -0.2)
		result = '-'; //저조기
	else if ((-0.2 <= r) && (r <= 0.2))
		result = 'D'; //위험기
	else
		result = '+'; //고조기
	return result;
}


/*
바이오리듬의 결과를 출력하는 함수 print_biorhythm
*/

void print_biorhythm(long total, int month)
{
	int dayindex = 0;
	int dayend = 0;
	int physical, emotion, intellect;    //신체, 감정, 지능
	int p_high[31] = { 0 }, p_danger[31] = { 0 }, p_low[31] = { 0 };    //신체 고조, 위험, 저조일 배열
	int e_high[31] = { 0 }, e_danger[31] = { 0 }, e_low[31] = { 0 };    //감정 고조, 위험, 저조일 배열
	int i_high[31] = { 0 }, i_danger[31] = { 0 }, i_low[31] = { 0 };    //지능 고조, 위험, 저조일 배열
	int p_idx1 = 0, p_idx2 = 0, p_idx3 = 0;    //신체 배열의 인덱스
	int e_idx1 = 0, e_idx2 = 0, e_idx3 = 0;    //감정 배열의 인덱스
	int i_idx1 = 0, i_idx2 = 0, i_idx3 = 0;    //지능 배열의 인덱스


	//월 별 일 수 저장
	if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12)
	{
		dayend = 31;    //마지막 날은 31일
	}
	else if (month == 2)
	{
		dayend = 28;    //마지막 날은 28일
	}
	else if (month == 4 || month == 6 || month == 11)
	{
		dayend = 30;    //마지막 날은 30일
	}


	for (dayindex = 1; dayindex <= dayend; dayindex++)    //일 수 만큼 반복
	{
		//바이오리듬을 계산하기 위한 변수
		physical = total % 23;
		emotion = total % 28;
		intellect = total % 33;

		char result1 = bio_status(physical, 23);    //신체 리듬을 계산하여 result1에 저장
		switch (result1)
		{
		case '-':    //저조기
			p_low[p_idx1++] = dayindex;    //p_low[p_idx1]에 dqyindex를 저장하고 p_idx1 값을 1 증가
			break;
		case 'D':    //위험기
			p_danger[p_idx2++] = dayindex;    //p_danger[p_idx2]에 dqyindex를 저장하고 p_idx2 값을 1 증가
			break;
		case '+':    //고조기
			p_high[p_idx3++] = dayindex;    //p_high[p_idx3]에 dayindex을 저장하고 p_idx3 값을 1 증가
			break;
		}

		char result2 = bio_status(emotion, 28);    //감정 리듬을 계산하여 result2에 저장
		switch (result2)
		{
		case '-':    //저조기
			e_low[e_idx1++] = dayindex;    //e_low[e_idx1]에 dqyindex를 저장하고 e_idx1 값을 1 증가
			break;
		case 'D':    //위험기
			e_danger[e_idx2++] = dayindex;    //e_danger[e_idx2]에 dqyindex를 저장하고 e_idx2 값을 1 증가
			break;
		case '+':    //고조기
			e_high[e_idx3++] = dayindex;    //e_high[e_idx3]에 dayindex을 저장하고 e_idx3 값을 1 증가
			break;
		}

		char result3 = bio_status(intellect, 33);    //지능 리듬을 계산하여 result3에 저장
		switch (result3)
		{
		case '-':    //저조기
			i_low[i_idx1++] = dayindex;    //i_low[i_idx1]에 dqyindex를 저장하고 i_idx1 값을 1 증가
			break;
		case 'D':    //위험기
			i_danger[i_idx2++] = dayindex;    //i_danger[i_idx2]에 dqyindex를 저장하고 i_idx2 값을 1 증가
			break;
		case '+':    //고조기   
			i_high[i_idx3++] = dayindex;    //i_high[i_idx3]에 dayindex을 저장하고 i_idx3 값을 1 증가
			break;
		}
		total++;    //total 1 증가
	}


	/*
	신체
	*/
	printf("%10s\t", "<신체>");

	//신체의 고조일 출력
	printf("고조일: ");
	int index = 0;
	while (1)    //무한 루프
	{
		int cnt = 0;
		printf("%d", p_high[index]);    //고조일에 해당되는 날짜 출력
		while (p_high[index] + 1 == p_high[index + 1])    //배열의 다음 인덱스 값이 다음 날짜 일 경우 반복
			index++, cnt++;    //index와 cnt 1씩 증가
		if (cnt > 0)    //cnt > 0 일경우 날짜 이어서 출력
			printf("~%d", p_high[index]);
		if (!p_high[++index])    //배열 p_high에 저장된 원소 값이 0일 경우 break
			break;
		else
			printf(",  ");
	}
	printf("\n");

	//신체의 위험일 출력
	index = 0;
	printf("\t\t");
	printf("위험일: ");
	while (1)
	{
		int cnt = 0;
		printf("%d", p_danger[index]);    //위험일에 해당되는 날짜 출력
		while (p_danger[index] + 1 == p_danger[index + 1])    //배열의 다음 인덱스 값이 다음 날짜 일 경우 반복
			index++, cnt++;    //index와 cnt 1씩 증가
		if (cnt > 0)    //cnt > 0 일경우 날짜 이어서 출력
			printf("~%d", p_danger[index]);  
		if (!p_danger[++index])     //배열 p_high에 저장된 원소 값이 0일 경우 break
			break;
		else
			printf(", ");
	}
	printf("\n");

	//신체의 저조일 출력
	index = 0;
	printf("\t\t");
	printf("저조일: ");    
	while (1)
	{
		int cnt = 0;
		printf("%d", p_low[index]);    //저조일에 해당되는 날짜 출력
		while (p_low[index] + 1 == p_low[index + 1])    //배열의 인덱스 값이다음 날짜 일 경우 반복
			index++, cnt++;    //index와 cnt 1씩 증가
		if (cnt > 0)     //cnt > 0 일경우 날짜 이어서 출력
			printf("~%d", p_low[index]);   
		if (!p_low[++index])    //배열 p_high에 저장된 원소 값이 0일 경우 break
			break;
		else
			printf(", ");
	}
	printf("\n");


	/*
	감정
	*/
	printf("\n%10s\t", "<감정>");

	//감정 고조일 출력
	printf("고조일: ");
	index = 0;
	while (1)
	{
		int cnt = 0;
		printf("%d", e_high[index]);
		while (e_high[index] + 1 == e_high[index + 1])
			index++, cnt++;
		if (cnt > 0)
			printf("~%d", e_high[index]);
		if (!e_high[++index])
			break;
		else
			printf(", ");
	}
	printf("\n");
	
	//감정 위험일 출력
	index = 0;
	printf("\t\t");
	printf("위험일: ");
	while (1)
	{
		int cnt = 0;
		printf("%d", e_danger[index]);
		while (e_danger[index] + 1 == e_danger[index + 1])
			index++, cnt++;
		if (cnt > 0)
			printf("~%d", e_danger[index]);
		if (!e_danger[++index])
			break;
		else
			printf(", ");
	}
	printf("\n");

	//감정 저조일 출력
	index = 0;
	printf("\t\t");
	printf("저조일: ");
	while (1)
	{
		int cnt = 0;
		printf("%d", e_low[index]);
		while (e_low[index] + 1 == e_low[index + 1])
			index++, cnt++;
		if (cnt > 0)
			printf("~%d", e_low[index]);
		if (!e_low[++index])
			break;
		else
			printf(", ");
	}
	printf("\n");


	/*
	지능
	*/
	printf("\n%10s\t", "<지능>");

	//지능 고조일 출력
	index = 0;
	printf("고조일: ");
	while (1)
	{
		int cnt = 0;
		printf("%d", i_high[index]);
		while (i_high[index] + 1 == i_high[index + 1])
			index++, cnt++;
		if (cnt > 0)
			printf("~%d", i_high[index]);
		if (!i_high[++index])
			break;
		else
			printf(", ");
	}
	printf("\n");

	//지능 위험일 출력
	index = 0;
	printf("\t\t");
	printf("위험일: ");
	while (1)
	{
		int cnt = 0;
		printf("%d", i_danger[index]);
		while (i_danger[index] + 1 == i_danger[index + 1])
			index++, cnt++;
		if (cnt > 0)
			printf("~%d", i_danger[index]);
		if (!i_danger[++index])
			break;
		else
			printf(", ");

	}
	printf("\n");

	//지능 저조일 출력
	index = 0;
	printf("\t\t");
	printf("저조일: ");
	while (1)
	{
		int cnt = 0;
		printf("%d", i_low[index]);
		while (i_low[index] + 1 == i_low[index + 1])
			index++, cnt++;
		if (cnt > 0)
			printf("~%d", i_low[index]);
		if (!i_low[++index])
			break;
		else
			printf(", ");
	}
	printf("\n");
}