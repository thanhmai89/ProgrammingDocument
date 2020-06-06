#include<stdio.h>
#include<conio.h>
#include<string.h>

#define MAX 10
#define VOCUC 1000
#define inputfile "E:/BT7_Dijkstra/abc.txt"

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


int LuuVet[MAX];
int ChuaXet[MAX];
int DoDaiDuongDiToi[MAX];

int TimDuongDiNhoNhat(DOTHI g)
{
	int li = -1;
	float p = VOCUC;
	for(int i = 0; i < g.n; i++)
	{
		if(ChuaXet[i] == 0 && DoDaiDuongDiToi[i] < p)
		{
			p = DoDaiDuongDiToi[i];
			li = i;
		}
	}
	return li;
}

void CapNhatDuongDi(int u, DOTHI g)
{
	ChuaXet[u] = 1;
	for(int v = 0; v < g.n; v++)
	{
		if(ChuaXet[v] == 0 && g.a[u][v] > 0 && g.a[u][v] < VOCUC)
		{
			if(DoDaiDuongDiToi[v] > DoDaiDuongDiToi[u] + g.a[u][v])
			{
				DoDaiDuongDiToi[v] = DoDaiDuongDiToi[u] + g.a[u][v];
				LuuVet[v] = u;
			}	
		}
	}
}

// con Dijkstra
void Dijkstra(int S, int F, DOTHI g)
{
	int i;
	for(i = 0; i < g.n; i++)
	{
		ChuaXet[i] = 0;
		DoDaiDuongDiToi[i] = VOCUC;
		LuuVet[i] = -1;
	}
	DoDaiDuongDiToi[S] = 0;
	
	while(ChuaXet[F] == 0)
	{
		int u = TimDuongDiNhoNhat(g);
		if(u == -1) break;
		
		CapNhatDuongDi(u, g);
	}
	
	if(ChuaXet[F] == 1)
	{
		printf("Duong di ngan nhat tu dinh %d den dinh %d la: \n\t", S, F);
		i = F;
		printf("%d", F);
		while(LuuVet[i] != S)
		{
			printf("<-%d", LuuVet[i]);
			i = LuuVet[i];
		}
		printf("<-%d\n", LuuVet[i]);
		printf("\tVoi do dai la %d\n", DoDaiDuongDiToi[F]);
	}
	else
	{
		printf("Khong co duong di tu dinh %d den dinh %d \n", S, F);
	}
}

void main()
{
	DOTHI g;
	if(DocMaTranKe(inputfile, g) == 1)
	{
		printf("Da lay thong tin do thi tu file thanh cong\n\n");
		XuatMaTranKe(g);
		
		int S, F;
		printf("Nhap vao dinh bat dau: ");
		scanf("%d", &S);
		
		printf("Nhap vao dinh ket thuc: ");
		scanf("%d", &F);
		
		Dijkstra(S, F, g);
	}
	getch();
}
