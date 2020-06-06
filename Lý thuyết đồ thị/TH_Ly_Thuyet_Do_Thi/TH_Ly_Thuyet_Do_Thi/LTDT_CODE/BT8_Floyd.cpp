#include<stdio.h>
#include<conio.h>
#include<string.h>

#define MAX 10
#define VOCUC 1000
#define inputfile "E:/CODE/BT5_Prim/matran.txt"

typedef struct GRAPH {
	int n;
	int a[MAX][MAX];
}DOTHI;


/*******************************************
* BT 1 - BT 1 - Kiem tra do thi vo huong
********************************************/
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

int KiemTraMaTranKeHopLe(DOTHI g)
{
	int i;
	for(i = 0; i < g.n; i++)
	{
		if(g.a[i][i] != 0)
			return 0;
	}
	return 1;
}

int Sau_Nut[MAX][MAX];
int L[MAX][MAX];

void Floyd(DOTHI g)
{
	int i, j;
	for(i = 0; i < g.n; i++)
	{
		for(j = 0; j < g.n; j++)
		{
			if(g.a[i][j] > 0)
			{
				Sau_Nut[i][j] = j;
				L[i][j] = g.a[i][j];
			}
			else
			{
				Sau_Nut[i][j] = -1;
				L[i][j] = VOCUC;
			}
		}
	}
	
	for(int k = 0; k < g.n; k++)
	{
		for(int i = 0; i < g.n; i++)
		{
			for(int j = 0; j < g.n; j++)
			{
				if(L[i][j] > L[i][k] + L[k][j])
				{
					L[i][j] = L[i][k] + L[k][j];
					Sau_Nut[i][j] = Sau_Nut[i][k];
				}
			}
		}
	}
	
	// Xuat ket qua duong di ngan nhat tu S -> F
	int S, F;
	printf("Nhap vao dinh bat dau: ");
	scanf("%d", &S);
	
	printf("Nhap vao dinh ket thuc: ");
	scanf("%d", &F);
	
	if(Sau_Nut[S][F] == -1)
	{
		printf("Khong co duong di tu dinh %d den dinh %d la: \n", S, F);
	} // Nguoc lai co duong di tu S den F
	else
	{
		printf("Duong di tu dinh %d den dinh %d la: \n", S, F);
		printf("\t%d", S);
		int u = S;
		while(Sau_Nut[u][F] != F)
		{
			u = Sau_Nut[u][F];
			printf("--> %d", u);
		}
		printf("--> %d", F);
		printf("\nVoi tong trong so la %d \n\n", L[S][F]);
	}
}

void main()
{
	DOTHI g;
	if(DocMaTranKe(inputfile, g) == 1)
	{
		printf("Da lay thong tin do thi tu file thanh cong\n\n");
		XuatMaTranKe(g);
		
		Floyd(g);
	}
	getch();
}
