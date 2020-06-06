#include<stdio.h>
#include<conio.h>
#include<string.h>

#define MAX 10
#define inputfile "D:/bt/test8.txt"

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


void DiTimCacDinhLienThong(DOTHI g, int nhan[MAX], int i)
{
	for(int j = 0; j < g.n; j++)
	{
		if(g.a[i][j] != 0 && nhan[j] != nhan[i])
		{
			nhan[j] = nhan[i];
			DiTimCacDinhLienThong(g, nhan, j);
		}
	}
}

int XetLienThong(DOTHI g)
{
	int Nhan[MAX];
	int i;
	for(i = 0; i < g.n; i++)
		Nhan[i] = 0;
	
	int SoThanhPhanLT = 0;
	for(i = 0; i < g.n; i++)
	{
		if(Nhan[i] == 0)
		{
			SoThanhPhanLT++;
			Nhan[i] = SoThanhPhanLT;
		}
		
		if(Nhan[i]!= 0)
			DiTimCacDinhLienThong(g, Nhan, i);
	}
	for(i = 1; i <= SoThanhPhanLT; i++)
	{
		printf("Thanh phan lien thong thu %d gom cac dinh: ", i);
		for(int j = 0; j < g.n; j++) {
			if(Nhan[j] == i)
				printf("%c", j + '1');
		}
		printf("\n");
	}
	
	return SoThanhPhanLT;
}


int ChuaXet[MAX];

typedef struct EDGE {
	int u;
	int v;
	int value;
}CANH;


CANH T[MAX];

void Prim(DOTHI g, int x)
{
	if(XetLienThong(g) != 1)
	{
		printf("Do thi khong lien thong, khong the thuc hien duoc thuat toan Prim tim cay khung nho nhat");
		return;
	}
	
	int nT = 0;
	for(int i = 0; i < g.n; i++)
	{
		ChuaXet[i] = 0;
	}
	
	ChuaXet[x] = 1;
	while(nT < g.n - 1)
	{
		CANH CanhNhoNhat;
		int GiaTriNhoNhat = 100;
		for(int i = 0; i < g.n; i++)
		{
			if(ChuaXet[i] == 1)
			{
				for(int j = 0; j < g.n; j++)
				{
					if(ChuaXet[j] == 0 && g.a[i][j] != 0 && GiaTriNhoNhat > g.a[i][j])
					{
						CanhNhoNhat.u = i;
						CanhNhoNhat.v = j;
						CanhNhoNhat.value = g.a[i][j];
						GiaTriNhoNhat = g.a[i][j];
					}
					
				}
			}	
		}
		
		T[nT] = CanhNhoNhat;
		nT++;
		ChuaXet[CanhNhoNhat.v] = 1;
	}
	
	int TongTrongSoCuaCayKhung = 0;
	printf("Cay khung nho nhat cua do thi \n");
	for(int i = 0; i < nT - 1;i++)
	{
		printf("(%d, %d), ", T[i].u + 1, T[i].v + 1);
		TongTrongSoCuaCayKhung += T[i].value;
	}
	
	printf("(%d, %d).\n", T[nT - 1].u + 1, T[nT - 1].v + 1);
	TongTrongSoCuaCayKhung += T[nT - 1].value;
	printf("Tong gia tri cua cay khung la: %d\n", TongTrongSoCuaCayKhung);
}

/*void Prim_LonNhat(DOTHI g, int x)
{
	if(XetLienThong(g) != 1)
	{
		printf("Do thi khong lien thong, khong the thuc hien duoc thuat toan Prim tim cay khung nho nhat");
		return;
	}
	
	int nT = 0;
	for(int i = 0; i < g.n; i++)
	{
		ChuaXet[i] = 0;
	}
	
	ChuaXet[x] = 1;
	while(nT < g.n - 1)
	{
		CANH CanhLonNhat;
		int GiaTriLonNhat = -1;
		for(int i = 0; i < g.n; i++)
		{
			if(ChuaXet[i] == 1)
			{
				for(int j = 0; j < g.n; j++)
				{
					if(ChuaXet[j] == 0 && g.a[i][j] != 0 && GiaTriLonNhat < g.a[i][j])
					{
						CanhLonNhat.u = i;
						CanhLonNhat.v = j;
						CanhLonNhat.value = g.a[i][j];
						GiaTriLonNhat = g.a[i][j];
					}
					
				}
			}
			
		}
		
		T[nT] = CanhLonNhat;
		nT++;
		ChuaXet[CanhLonNhat.v] = 1;
	}
	
	int TongTrongSoCuaCayKhung = 0;
	printf("Cay khung lon nhat cua do thi \n");
	for(int i = 0; i < nT - 1;i++)
	{
		printf("(%d, %d), ", T[i].u, T[i].v);
		TongTrongSoCuaCayKhung += T[i].value;
	}
	
	printf("(%d, %d).\n", T[nT - 1].u, T[nT - 1].v);
	TongTrongSoCuaCayKhung += T[nT - 1].value;
	printf("Tong gia tri cua cay khung la: %d\n", TongTrongSoCuaCayKhung);
}
*/
void NhapDinhBatDau(int &x)
{
	printf("Nhap dinh bat dau : ");
	scanf("%d", &x);
}

void main()
{
	DOTHI g;
	if(DocMaTranKe(inputfile, g) == 1)
	{
		printf("Da lay thong tin do thi tu file thanh cong\n\n");
		XuatMaTranKe(g);
		
		printf("\n\n======== CAY KHUNG NHO NHAT ========\n");
		int x;
		NhapDinhBatDau(x);
		Prim(g, x);
		
	/*	printf("\n\n======== CAY KHUNG LON NHAT ========\n");
		NhapDinhBatDau(x);
    	Prim_LonNhat(g, x);
    	*/
	}
	getch();
}
