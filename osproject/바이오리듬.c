/*
  ���̿����� ����(Biorhythm calculator)
  2020037030 �ڼҹ�
*/

#include <stdio.h>
#include <math.h>

#define PI 3.141592

long total_days(int year, int month, int day);    //��ƿ� �� �� ��� �Լ�
void print_biorhythm(long total, int month);    //���̿����� ��� ��� ��� �Լ�
char bio_status(int val, int mod);    //���̿����� ���� �Ǵ� �Լ�

int main(void)
{
	int byr, bmon, bday;    //������� ���� ����
	int tyr, tmon, tday;    //����� ��¥ ���� ����
	long total = 0;    //������ϰ� ����� ��¥ ������ �ϼ�

	printf("*****Ư�� ���� ���̿����� ���*****\n");
	printf("\n");
	printf("���� ������ �Է��ϼ��� (ex: 2000 01 01): ");
	scanf("%d%d%d", &byr, &bmon, &bday);    //�Է��� ������� ����
	printf("���ð� ���� �⵵�� ���� �Է��ϼ���. (ex: 2021 11): ");
	scanf("%d%d", &tyr, &tmon);    //�Է��� �⵵�� �� ����

	tday = 1;
	total = total_days(tyr, tmon, tday) - total_days(byr, bmon, bday);    //������ϰ� �Է��� ����� ��¥�� ���
	printf("�� ��¥ ������ ��¥���� %ld�� �Դϴ�. \n\n", total);    //�� ��¥ ���� ��¥�� ���

	printf("[���̿����� ���]\n\n");
	print_biorhythm(total, tmon);    //���̿� ���� ��� ��� �Լ� ȣ��
	return 0;
}

/*

������(1�� 1�� 1��)�κ��� Ư���� ������ ��¥ ���� ��� �Լ� total_days

*/
long total_days(int year, int month, int day)
{
	int months[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };    //1~12�� ��¥ ��
	int i;
	long total = 0L;
	total = (year - 1) * 365L + (year - 1) / 4 - (year - 1) / 100 + (year - 1) / 400;
	//total�� year-1�⵵ ������ ��¥�� ����
	//4�� ���������� Ƚ�� - 100���� ���������� Ƚ��(���) + 400���� ���������� Ƚ�� = ���� Ƚ��
	if (year % 4 == 0 && year % 100 != 0 || year % 400 == 0) //������ ���� 2���� �� �� �Ϸ� �߰�
		months[1]++;
	for (i = 0; i < month - 1; i++)    //total�� month-1�� ������ ��¥�� ����
		total += months[i];
	total += day;    //total�� ���� ��¥�� ����
	return total;    //����� ��¥ �� ��ȯ
}

/*
���̿������� ���¸� �Ǵ��ϴ� �Լ� bio_status
*/

char bio_status(int v, int mod)
{
	char result;
	double r;
	r = sin(v * 3.141592 / (mod / 2.0));   //���̿� ���� ����
	//r�� ���� ���� ������ ����� ������ ����
	if (r < -0.2)
		result = '-'; //������
	else if ((-0.2 <= r) && (r <= 0.2))
		result = 'D'; //�����
	else
		result = '+'; //������
	return result;
}


/*
���̿������� ����� ����ϴ� �Լ� print_biorhythm
*/

void print_biorhythm(long total, int month)
{
	int dayindex = 0;
	int dayend = 0;
	int physical, emotion, intellect;    //��ü, ����, ����
	int p_high[31] = { 0 }, p_danger[31] = { 0 }, p_low[31] = { 0 };    //��ü ����, ����, ������ �迭
	int e_high[31] = { 0 }, e_danger[31] = { 0 }, e_low[31] = { 0 };    //���� ����, ����, ������ �迭
	int i_high[31] = { 0 }, i_danger[31] = { 0 }, i_low[31] = { 0 };    //���� ����, ����, ������ �迭
	int p_idx1 = 0, p_idx2 = 0, p_idx3 = 0;    //��ü �迭�� �ε���
	int e_idx1 = 0, e_idx2 = 0, e_idx3 = 0;    //���� �迭�� �ε���
	int i_idx1 = 0, i_idx2 = 0, i_idx3 = 0;    //���� �迭�� �ε���


	//�� �� �� �� ����
	if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12)
	{
		dayend = 31;    //������ ���� 31��
	}
	else if (month == 2)
	{
		dayend = 28;    //������ ���� 28��
	}
	else if (month == 4 || month == 6 || month == 11)
	{
		dayend = 30;    //������ ���� 30��
	}


	for (dayindex = 1; dayindex <= dayend; dayindex++)    //�� �� ��ŭ �ݺ�
	{
		//���̿������� ����ϱ� ���� ����
		physical = total % 23;
		emotion = total % 28;
		intellect = total % 33;

		char result1 = bio_status(physical, 23);    //��ü ������ ����Ͽ� result1�� ����
		switch (result1)
		{
		case '-':    //������
			p_low[p_idx1++] = dayindex;    //p_low[p_idx1]�� dqyindex�� �����ϰ� p_idx1 ���� 1 ����
			break;
		case 'D':    //�����
			p_danger[p_idx2++] = dayindex;    //p_danger[p_idx2]�� dqyindex�� �����ϰ� p_idx2 ���� 1 ����
			break;
		case '+':    //������
			p_high[p_idx3++] = dayindex;    //p_high[p_idx3]�� dayindex�� �����ϰ� p_idx3 ���� 1 ����
			break;
		}

		char result2 = bio_status(emotion, 28);    //���� ������ ����Ͽ� result2�� ����
		switch (result2)
		{
		case '-':    //������
			e_low[e_idx1++] = dayindex;    //e_low[e_idx1]�� dqyindex�� �����ϰ� e_idx1 ���� 1 ����
			break;
		case 'D':    //�����
			e_danger[e_idx2++] = dayindex;    //e_danger[e_idx2]�� dqyindex�� �����ϰ� e_idx2 ���� 1 ����
			break;
		case '+':    //������
			e_high[e_idx3++] = dayindex;    //e_high[e_idx3]�� dayindex�� �����ϰ� e_idx3 ���� 1 ����
			break;
		}

		char result3 = bio_status(intellect, 33);    //���� ������ ����Ͽ� result3�� ����
		switch (result3)
		{
		case '-':    //������
			i_low[i_idx1++] = dayindex;    //i_low[i_idx1]�� dqyindex�� �����ϰ� i_idx1 ���� 1 ����
			break;
		case 'D':    //�����
			i_danger[i_idx2++] = dayindex;    //i_danger[i_idx2]�� dqyindex�� �����ϰ� i_idx2 ���� 1 ����
			break;
		case '+':    //������   
			i_high[i_idx3++] = dayindex;    //i_high[i_idx3]�� dayindex�� �����ϰ� i_idx3 ���� 1 ����
			break;
		}
		total++;    //total 1 ����
	}


	/*
	��ü
	*/
	printf("%10s\t", "<��ü>");

	//��ü�� ������ ���
	printf("������: ");
	int index = 0;
	while (1)    //���� ����
	{
		int cnt = 0;
		printf("%d", p_high[index]);    //�����Ͽ� �ش�Ǵ� ��¥ ���
		while (p_high[index] + 1 == p_high[index + 1])    //�迭�� ���� �ε��� ���� ���� ��¥ �� ��� �ݺ�
			index++, cnt++;    //index�� cnt 1�� ����
		if (cnt > 0)    //cnt > 0 �ϰ�� ��¥ �̾ ���
			printf("~%d", p_high[index]);
		if (!p_high[++index])    //�迭 p_high�� ����� ���� ���� 0�� ��� break
			break;
		else
			printf(",  ");
	}
	printf("\n");

	//��ü�� ������ ���
	index = 0;
	printf("\t\t");
	printf("������: ");
	while (1)
	{
		int cnt = 0;
		printf("%d", p_danger[index]);    //�����Ͽ� �ش�Ǵ� ��¥ ���
		while (p_danger[index] + 1 == p_danger[index + 1])    //�迭�� ���� �ε��� ���� ���� ��¥ �� ��� �ݺ�
			index++, cnt++;    //index�� cnt 1�� ����
		if (cnt > 0)    //cnt > 0 �ϰ�� ��¥ �̾ ���
			printf("~%d", p_danger[index]);  
		if (!p_danger[++index])     //�迭 p_high�� ����� ���� ���� 0�� ��� break
			break;
		else
			printf(", ");
	}
	printf("\n");

	//��ü�� ������ ���
	index = 0;
	printf("\t\t");
	printf("������: ");    
	while (1)
	{
		int cnt = 0;
		printf("%d", p_low[index]);    //�����Ͽ� �ش�Ǵ� ��¥ ���
		while (p_low[index] + 1 == p_low[index + 1])    //�迭�� �ε��� ���̴��� ��¥ �� ��� �ݺ�
			index++, cnt++;    //index�� cnt 1�� ����
		if (cnt > 0)     //cnt > 0 �ϰ�� ��¥ �̾ ���
			printf("~%d", p_low[index]);   
		if (!p_low[++index])    //�迭 p_high�� ����� ���� ���� 0�� ��� break
			break;
		else
			printf(", ");
	}
	printf("\n");


	/*
	����
	*/
	printf("\n%10s\t", "<����>");

	//���� ������ ���
	printf("������: ");
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
	
	//���� ������ ���
	index = 0;
	printf("\t\t");
	printf("������: ");
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

	//���� ������ ���
	index = 0;
	printf("\t\t");
	printf("������: ");
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
	����
	*/
	printf("\n%10s\t", "<����>");

	//���� ������ ���
	index = 0;
	printf("������: ");
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

	//���� ������ ���
	index = 0;
	printf("\t\t");
	printf("������: ");
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

	//���� ������ ���
	index = 0;
	printf("\t\t");
	printf("������: ");
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