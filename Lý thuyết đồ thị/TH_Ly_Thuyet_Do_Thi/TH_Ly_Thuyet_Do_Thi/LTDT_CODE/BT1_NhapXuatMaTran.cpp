#define MAX 10
#define FILE_INPUT "E:/CODE/BT1/matran_test_1.txt"

#include <conio.h>
#include <stdio.h>

typedef struct GRAPH {
	int n;
	int a[MAX][MAX];
}DOTHI;

DOTHI g;

int DocMaTranKe(char TenFile[100], DOTHI &g)
{
	FILE *f; 
	f = fopen(TenFile, "rt");
	if (f == NULL)
	{
		printf("Khong the mo duoc file\n");
		return 0;
	}
	
	// Doc file
	fscanf(f, "%d", &g.n);
	
	for(int i = 0; i < g.n; i++) 
	{
		for(int j = 0; j < g.n; j++)
		{
			fscanf(f, "%d", &g.a[i][j]);
		}	
	}
	
	fclose(f);
		
	return 1;
}

void XuatMaTranKe(DOTHI g)
{
	printf("So dinh cua do thi %d\n", g.n);
	printf("Ma tran ke cua do thi la: \n");
	
	for(int i = 0; i < g.n; i++)
	{
		printf("   ");
		
		for(int j = 0; j < g.n; j++)
		{
			printf("%d ", g.a[i][j]);
		}
		
		printf("\n");
	}
	
}

// Kiem tra duong cheo chinh -> tat ca bang 0
int KiemTraMaTranKeHopLe(DOTHI g)
{
	int i;
	for(i = 0; i < g.n; i++)
	{
		// 
		if(g.a[i][i] != 0)
		{
			return 0;
		}
	}
	
	return 1;
}

// Doi xung qua duong cheo chinh
int KiemTraDoThiVoHuong(DOTHI g)
{
	int i, j;
	for(i = 0; i < g.n; i++) 
	{
		for(j = 0; j < g.n; j++)
		{
			if(g.a[i][j] != g.a[j][i])
				return 0;
		}
	}
	return 1;
}

void main()
{
	DOTHI g;
	int isRead = DocMaTranKe(FILE_INPUT, g);
	
	if(isRead == 1)
	{
		XuatMaTranKe(g);
		
		printf("\n");
	
		if(KiemTraMaTranKeHopLe(g) == 1)
		{
			printf("Do thi hop le!\n"); 
		}
		else
		{
			printf("Do thi khong hop le!\n");
		}
		
		if(KiemTraDoThiVoHuong(g) == 1)
		{
			printf("Do thi vo huong!\n");
		}
		else
		{
			printf("Do thi co huong!\n");
		}
	}

	getch();
}
