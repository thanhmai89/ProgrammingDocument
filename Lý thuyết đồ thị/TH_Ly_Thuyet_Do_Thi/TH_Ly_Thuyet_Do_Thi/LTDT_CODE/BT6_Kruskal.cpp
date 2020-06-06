#include<stdio.h>
#include<conio.h>
#include<string.h>

#define MAX 10
#define inputfile "D:/CODE/BT7_Dijkstra/matran.txt"

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



int ChuaXet[MAX];

typedef struct EDGE {
	int u;
	int v;
	int value;
}CANH;

void SapXepTang(CANH E[100], int tongSoCanh)
{
	CANH canhtam;
	for(int i = 0; i < tongSoCanh - 1; i++)
	{
		for(int j = 0; j < tongSoCanh; j++)
		{
			if(E[i].value > E[j].value)
			{
				canhtam = E[i];
				E[i] = E[j];
				E[j] = canhtam;
			}
		}
	}
}

void Kruskal(DOTHI g)
{
	CANH listEdge[MAX];
	int tongsocanh = 0;
	int i, j;
	for(i = 0; i < g.n; i++)
	{
		for(j = i + 1; j < g.n; j++)
		{
			if(g.a[i][j] > 0)
			{
				listEdge[tongsocanh].u = i;
				listEdge[tongsocanh].v = j;
				listEdge[tongsocanh].value = g.a[i][j];
				tongsocanh++;
			}
		}
	}
	
	SapXepTang(listEdge, tongsocanh);
	int nT = 0;
	CANH T[MAX];
	int nhan[MAX];
	for(i = 0; i < g.n; i++)
	{
		nhan[i] = i;
	}
	int canhdangxet = 0;
	while(nT < g.n && canhdangxet < tongsocanh)
	{
		if(nhan[listEdge[canhdangxet].u] != nhan[listEdge[canhdangxet].v])
		{
			T[nT] = listEdge[canhdangxet];
			nT++;
			int giatri = nhan[listEdge[canhdangxet].v];
			for(j = 0; j < g.n; j++)
			{
				if(nhan[j] == giatri)
					nhan[j] = nhan[listEdge[canhdangxet].u];
			}
		}
		canhdangxet++;
	}
	
	if(nT != g.n - 1)
	{
		printf("\nDo thi khong lien thong\n");
	}
	else
	{
		int TongTrongSoCayKhung = 0;
		printf("\nDo thi lien thong\n");
		printf("Cay khung nho nhat cua do thi la \n");
		for(i = 0; i < nT; i++)
		{
			printf("(%d, %d), ", T[i].u, T[i].v);
			TongTrongSoCayKhung += T[i].value;
		}
		printf("\nTong gia tri cua cay khung la: %d\n", TongTrongSoCayKhung);
	}
}



void main()
{
	DOTHI g;
	if(DocMaTranKe(inputfile, g) == 1)
	{
		printf("Da lay thong tin do thi tu file thanh cong\n\n");
		XuatMaTranKe(g);
		
		Kruskal(g);
	}
	getch();
}
