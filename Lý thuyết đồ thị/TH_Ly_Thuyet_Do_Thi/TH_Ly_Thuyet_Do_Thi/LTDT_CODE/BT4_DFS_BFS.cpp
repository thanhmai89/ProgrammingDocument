#include<stdio.h>
#include<conio.h>
#include<string.h>

#define MAX 10
#define inputfile "E:/CODE/BT3/matran.txt"

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

void DFS(int v, GRAPH g)
{
	ChuaXet[v] = 1;
	
	int u;
	for(u = 0; u <= g.n; u++)
	{
		if(g.a[v][u] != 0 && ChuaXet[u] == 0)
		{
			LuuVet[u] = v;
			DFS(u, g);
		}
	}
}

void DuyetTheoDFS(int S, int F, GRAPH g)
{
	int i;
	for(i = 0; i < MAX; i++)
	{
		LuuVet[i] = -1;
		ChuaXet[i] = 0;
	}
	DFS(S, g);
	
	if(ChuaXet[F] == 1)
	{
		printf("Duong di tu dinh %d den dinh %d la \n\t", S, F);

		i = S;
		printf("%d", F);
		while(LuuVet[i] != S)
		{	
			printf("<-%d", LuuVet[i]);
			i = LuuVet[i];
		}
		printf("<-%d\n", LuuVet[i]);
	}
	else
	{
		printf("Khong co duong di tu dinh %d den dinh %d \n", S, F);
	}
}

struct QUEUE
{
	int size;
	int array[MAX];
};

void KhoiTaoQueue(QUEUE &Q)
{
	Q.size = 0;
}

int DayGiaTriVaoQueue(QUEUE &Q, int value)
{
	if(Q.size + 1 >= 100)
		return 0;
	Q.array[Q.size] = value;
	Q.size++;
	return 1;
}

int LayGiaTriRaKhoiQueue(QUEUE &Q, int &value)
{
	if(Q.size <= 0)
		return 0;
	value = Q.array[0];
	for(int i = 0; i < Q.size - 1; i++)
		Q.array[i] = Q.array[i+1];
	Q.size--;
	return 1;
}

int KiemTraQueueRong(QUEUE Q)
{
	if(Q.size <= 0)
		return 1;
	return 0;
}

void BFS(int v, GRAPH g)
{
	QUEUE Q;
	KhoiTaoQueue(Q);
	
	DayGiaTriVaoQueue(Q, v);
	while(!KiemTraQueueRong(Q))
	{
		LayGiaTriRaKhoiQueue(Q, v);
		ChuaXet[v] = 1;
		for(int u = 0; u < g.n; u++)
		{
			if(g.a[v][u] != 0 && ChuaXet[u] == 0)
			{
				DayGiaTriVaoQueue(Q, u);
				LuuVet[u] = v;
			}
		}
	}
}

void DuyetTheoBFS(int S, int F, GRAPH g)
{
	int i;
	for(i = 0; i < MAX; i++)
	{
		LuuVet[i] = -1;
		ChuaXet[i] = 0;
	}
	
	BFS(S, g);
	
	if(ChuaXet[F] == 1)
	{
		printf("Duong di tu dinh %d den dinh %d la: \n\t", S, F);
		i = F;
		printf("%d", F);
		while(LuuVet[i] != S)
		{
			printf("<-%d", LuuVet[i]);
			i = LuuVet[i];
		}
		printf("<-%d\n", LuuVet[i]);
	
		
	}
	else
	{
		printf("\nKhong co duong di tu dinh %d den dinh %d \n", S, F);
	}
}

void main()
{
	DOTHI g;
	if(DocMaTranKe(inputfile, g) == 1)
	{
		printf("Da lay thong tin do thi tu file thanh cong\n\n");
		XuatMaTranKe(g);
		printf("\n\nKet qua duyet theo DFS:\n");
		
		DuyetTheoDFS(0, 5, g);
		printf("\n\nKet qua duyet theo BFS:\n");
		DuyetTheoBFS(0, 5, g);
	}
	getch();
}
