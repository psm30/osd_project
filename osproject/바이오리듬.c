#include <stdio.h>
#include <math.h>

#define PI 3.141592

long total_days(int year, int month, int day);
void print_biorhythm(long total, int month);
char bio_status(int val, int mod);


int main(void)

{
    int byr, bmon, bday;
    int tyr, tmon, tday;
    long total = 0;;

    printf("특정월의 바이오리듬 계산\n");
    printf("생년 월일을 입력하세요:  ");
    scanf("%d%d%d", &byr, &bmon, &bday);
    printf("보시고 싶은 년도와 월을 입력하세요.: ");
    scanf("%d%d", &tyr, &tmon);
    tday = 1;
    total = total_days(tyr, tmon, tday) - total_days(byr, bmon, bday);
    printf("두 날짜 사이의 날짜수는 %ld일 입니다. \n\n", total);
    printf("바이오리듬 결과:\n");
    printf("%4d년 %2d월\t%12s\t%12s\t%12s\n", tyr, tmon, "고조일", "위험일", "저조일");
    print_biorhythm(total, tmon);
    return 0;
}

/*

기준일(1년 1월 1일)로부터 특정일 사이의 날짜 수의 계산 함수 total_days

*/
long total_days(int year, int month, int day)

{
    int months[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    int i;
    long total = 0L;
    //4로 나누어지는 회수-100으로 나누어지는 횟수(평년)+400으로 나누어지는 횟수
    total = (year - 1) * 365L + (year - 1) / 4 - (year - 1) / 100 + (year - 1) / 400;
    if (!(year % 4) && year % 100 || !(year % 400)) //윤년일 때만 2월달 일 수 하루 추가
        months[1]++;
    for (i = 0; i < month - 1; i++)
        total += months[i];
    total += day;
    return total;
}

/*
바이오리듬의 상태를 판단하는 함수 bio_status
*/

char bio_status(int v, int mod)
{
    char result;
    double r;
    r = sin(v * 3.141592 / (mod / 2.0));
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
    int dayindex;
    int physical, emotion, intellect;
    int p_high[31] = { 0 }, p_danger[31] = { 0 }, p_low[31] = { 0 };
    int e_high[31] = { 0 }, e_danger[31] = { 0 }, e_low[31] = { 0 };
    int i_high[31] = { 0 }, i_danger[31] = { 0 }, i_low[31] = { 0 };
    int p_idx1 = 0, p_idx2 = 0, p_idx3 = 0;
    int e_idx1 = 0, e_idx2 = 0, e_idx3 = 0;
    int i_idx1 = 0, i_idx2 = 0, i_idx3 = 0;

    if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12)
    {
        for (dayindex = 1; dayindex <= 31; dayindex++)
        {
            physical = total % 23;
            emotion = total % 28;
            intellect = total % 33;
            char result1 = bio_status(physical, 23);
            switch (result1)
            {
            case '-':
                p_low[p_idx1++] = dayindex;
                break;
            case 'D':
                p_danger[p_idx2++] = dayindex;
                break;
            case '+':
                p_high[p_idx3++] = dayindex;
                break;
            }
            char result2 = bio_status(emotion, 28);
            switch (result2)
            {
            case '-':
                e_low[e_idx1++] = dayindex;
                break;
            case 'D':
                e_danger[e_idx2++] = dayindex;
                break;
            case '+':
                e_high[e_idx3++] = dayindex;
                break;
            }

            char result3 = bio_status(intellect, 33);
            switch (result3)
            {
            case '-':
                i_low[i_idx1++] = dayindex;
                break;
            case 'D':
                i_danger[i_idx2++] = dayindex;
                break;
            case '+':
                i_high[i_idx3++] = dayindex;
                break;
            }
            total++;
        }
    }
    else if (month == 2)
    {
        for (dayindex = 1; dayindex <= 28; dayindex++)
        {
            physical = total % 23;
            emotion = total % 28;
            intellect = total % 33;
            char result1 = bio_status(physical, 23);
            switch (result1)
            {
            case '-':
                p_low[p_idx1++] = dayindex;
                break;
            case 'D':
                p_danger[p_idx2++] = dayindex;
                break;
            case '+':
                p_high[p_idx3++] = dayindex;
                break;
            }
            char result2 = bio_status(emotion, 28);
            switch (result2)
            {
            case '-':
                e_low[e_idx1++] = dayindex;
                break;
            case 'D':
                e_danger[e_idx2++] = dayindex;
                break;
            case '+':
                e_high[e_idx3++] = dayindex;
                break;
            }
            char result3 = bio_status(intellect, 33);
            switch (result3)
            {
            case '-':
                i_low[i_idx1++] = dayindex;
                break;
            case 'D':
                i_danger[i_idx2++] = dayindex;
                break;
            case '+':
                i_high[i_idx3++] = dayindex;
                break;
            }
            total++;
        }
    }

    else
    {
        for (dayindex = 1; dayindex <= 30; dayindex++)
        {
            physical = total % 23;
            emotion = total % 28;
            intellect = total % 33;
            char result1 = bio_status(physical, 23);
            switch (result1)
            {
            case '-':
                p_low[p_idx1++] = dayindex;
                break;
            case 'D':
                p_danger[p_idx2++] = dayindex;
                break;
            case '+':
                p_high[p_idx3++] = dayindex;
                break;
            }
            char result2 = bio_status(emotion, 28);

            switch (result2)
            {
            case '-':
                e_low[e_idx1++] = dayindex;
                break;
            case 'D':
                e_danger[e_idx2++] = dayindex;
                break;
            case '+':
                e_high[e_idx3++] = dayindex;
                break;
            }
            char result3 = bio_status(intellect, 33);
            switch (result3)
            {
            case '-':
                i_low[i_idx1++] = dayindex;
                break;
            case 'D':
                i_danger[i_idx2++] = dayindex;
                break;
            case '+':
                i_high[i_idx3++] = dayindex;
                break;
            }
            total++;
        }
    }

    int index = 0;
    printf("%10s\t", "신체");
    while (1)
    {
        int cnt = 0;
        printf("%2d", p_high[index]);
        while (p_high[index] + 1 == p_high[index + 1])
            index++, cnt++;
        if (cnt > 0)
            printf("~%2d", p_high[index]);
        if (!p_high[++index])
            break;
        else
            printf(" ");
    }

    index = 0;
    printf("\t\t");
    while (1)
    {
        int cnt = 0;
        printf("%2d", p_danger[index]);
        while (p_danger[index] + 1 == p_danger[index + 1])
            index++, cnt++;
        if (cnt > 0)
            printf("~%2d", p_danger[index]);
        if (!p_danger[++index])
            break;
        else
            printf(" ");
    }

    index = 0;
    printf("\t\t");
    while (1)
    {
        int cnt = 0;
        printf("%2d", p_low[index]);
        while (p_low[index] + 1 == p_low[index + 1])
            index++, cnt++;
        if (cnt > 0)
            printf("~%2d", p_low[index]);
        if (!p_low[++index])
            break;
        else
            printf(" ");
    }
    printf("\n%10s\t", "감정");
    index = 0;
    while (1)
    {
        int cnt = 0;
        printf("%2d", e_high[index]);
        while (e_high[index] + 1 == e_high[index + 1])
            index++, cnt++;
        if (cnt > 0)
            printf("~%2d", e_high[index]);
        if (!e_high[++index])
            break;
        else
            printf(" ");
    }
    index = 0;
    printf("\t\t");
    while (1)
    {
        int cnt = 0;
        printf("%2d", e_danger[index]);
        while (e_danger[index] + 1 == e_danger[index + 1])
            index++, cnt++;
        if (cnt > 0)
            printf("~%2d", e_danger[index]);
        if (!e_danger[++index])
            break;
        else
            printf(" ");
    }
    index = 0;
    printf("\t\t");

    while (1)
    {
        int cnt = 0;
        printf("%2d", e_low[index]);
        while (e_low[index] + 1 == e_low[index + 1])
            index++, cnt++;
        if (cnt > 0)
            printf("~%2d", e_low[index]);
        if (!e_low[++index])
            break;
        else
            printf(" ");
    }
    printf("\n%10s\t", "지능");
    index = 0;
    while (1)
    {
        int cnt = 0;
        printf("%2d", i_high[index]);
        while (i_high[index] + 1 == i_high[index + 1])
            index++, cnt++;
        if (cnt > 0)
            printf("~%2d", i_high[index]);
        if (!i_high[++index])
            break;
        else
            printf(" ");
    }
    index = 0;
    printf("\t\t");
    while (1)

    {
        int cnt = 0;
        printf("%2d", i_danger[index]);
        while (i_danger[index] + 1 == i_danger[index + 1])
            index++, cnt++;
        if (cnt > 0)
            printf("~%2d", i_danger[index]);
        if (!i_danger[++index])
            break;
        else
            printf(" ");

    }
    index = 0;
    printf("\t\t");

    while (1)
    {
        int cnt = 0;
        printf("%2d", i_low[index]);
        while (i_low[index] + 1 == i_low[index + 1])
            index++, cnt++;
        if (cnt > 0)
            printf("~%2d", i_low[index]);
        if (!i_low[++index])
            break;
        else
            printf(" ");
    }
    printf("\n");
}