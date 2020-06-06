#include<stdio.h>
#include<conio.h>
#include<string.h>
#define MAX 10

typedef struct GRAPH {
	int n;
	int a[MAX][MAX];
}DOTHI;

DOTHI g;
char duongDanFile[1000];

/*******************************************
* BT 1 - Doc ma tran - Kiem tra hop le - vo huong
********************************************/
int DocMaTranKe(char TenFile[1000], DOTHI &g)
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
	int hopLe = 0;
	
	int i;
	for(i = 0; i < g.n; i++)
	{
		if(g.a[i][i] != 0)
			hopLe = 0;
	}
	hopLe = 1;
	
	if(hopLe == 1)
		printf("Ma tran ke hop le!\n\n");
	else
		printf("Ma tran ke khong hop le!\n\n");
	
	return hopLe;
}

int KiemTraDoThiVoHuong(DOTHI g)
{
	int isVoHuong;
	
	int i, j;
	for(i = 0; i < g.n; i++)
	{
		for(j = 0; j < g.n; j++)
		{
			if(g.a[i][j] != g.a[j][i])
				isVoHuong = 0;
		}
	}
	isVoHuong = 1;
	
	if(isVoHuong == 1)
		printf("Do thi vo huong!\n\n");
	else
		printf("Do thi co huong!\n\n");
		
	return isVoHuong;
}


/*******************************************
* BT 2 - Xet tinh lien thong
********************************************/
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

void XetLienThong(DOTHI g)
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
	
	printf("So thanh phan lien thong la %d\n", SoThanhPhanLT);
	for(i = 1; i <= SoThanhPhanLT; i++)
	{
		printf("Thanh phan lien thong thu %d gom cac dinh ", i);
		for(int j = 0; j < g.n; j++) {
			if(Nhan[j] == i)
				printf("%c", j + 'A');
				//printf("%d", j);
		}
		printf("\n");
	}
}

/*******************************************
* BT 3 - Duong di Euler
********************************************/
struct STACK 
{
	int array[100]; // Luu lai thu tu cac dinh trong chu trinh euler, duong di euler toi da 100 dinh
	int size; // so luong cac dinh trong chu trinh euler
};

void KhoiTaoStack(STACK &stack)
{
	stack.size = 0;
}

void DayGiaTriVaoStack(STACK &stack, int value)
{
	if(stack.size + 1 >= 100) // Neu stack day thi dung lai
		return;
	stack.array[stack.size] = value; // day gia tri value vao stack
	stack.size++; // Tang kich thuoc stack len
}

void TimDuongDi(int i, DOTHI &g, STACK &stack)
{
	for(int j = 0; j < g.n; j++) 
	{
		if(g.a[i][j] != 0) // vi do thi vo huong nen doi xung, do do chi can kiem tra g.a[i][j] != 0 thoi, khong can kiem tra g.a[j][i] != 0
		{
			g.a[i][j] = g.a[j][i] = 0; // loai bo canh noi dinh i toi dinh j khoi do thi
			TimDuongDi(j, g, stack); // de quy tim duong di tai cac dinh j
		}
	}
	DayGiaTriVaoStack(stack, i); // day dinh i vao trong stack
}

int KiemTraChuTrinhEuler(DOTHI g)
{
	int i, j;
	int x = 0; // x la gia tri dinh bat dau xet chu trinh euler, dieu kien x la dinh phai co bac > 0
	
	int flag = 0;
	for(i = 0; i < g.n; i++)
	{
		for(j = 0; j < g.n; j++)
		{
			if(g.a[i][j] != 0) // co canh noi tu dinh i den dinh j
			{
				x = i; // gan dinh bat dau di tim chu trinh x = i.
				flag = 1; // flag = 1 thi cho biet da tim thay co dinh bat dau x thoa co bac > 0
				break;
			}
		}
		
		if(flag == 1) // khong can lap nua de tim x vi da tim thay x o tren roi
			break;
	}
	
	DOTHI temp = g;
	STACK stack;
	
	KhoiTaoStack(stack);
	TimDuongDi(x, temp, stack);
	
	for(i = 0; i < temp.n; i++)
	{
		for(j = 0; j < temp.n; j++)
		{
			if(temp.a[i][j] != 0)
				return 0;
		}
	}
	
	if(stack.array[stack.size - 1] != stack.array[0]) // dinh dau va dinh cuoi trong stack phai giong nhau
		return 0; // khong tim thay chu trinh euler;
	
	printf("\nChu trinh Euler: ");
	for(i = 0; i < stack.size; i++)
		printf("%d ", stack.array[i] + 1);
	
	printf("\n\n");
	
	return 1;
}

int KiemTraDuongDiEuler(DOTHI g)
{
	int i, j;
	int x = 0;
	int flag = 0;
	int bac = 0;
	for(i = 0; i < g.n; i++)
	{
		bac = 0;
		for(j = 0; j < g.n; j++)
		{
			if(g.a[i][j] != 0)
			{
				bac++;
			}
		}
		
		if(bac % 2 != 0)
		{
			x = i;
			flag = 1;
			break;
		}
	}
	
	if(flag == 0)
		return 0;
	
	DOTHI temp = g;
	STACK stack;
	
	KhoiTaoStack(stack);
	TimDuongDi(x, temp, stack);
	
	for(i = 0; i < temp.n; i++)
	{
		for(j = 0; j < temp.n; j++)
		{
			if(temp.a[i][j] != 0)
				return 0;
		}
	}
	
	if(stack.array[stack.size - 1] == stack.array[0])
		return 0;
	
	printf("\nDuong di Euler: ");
	for(i = stack.size - 1; i >= 0; i--)
		printf("%d ", stack.array[i] + 1);
	
	printf("\n\n");
	
	return 1;
}

/*******************************************
* BT 4 - Tim theo chieu rong - chieu sau
********************************************/
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

void DuyetTheoDFS(GRAPH g)
{
	int S; // Dinh bat dau
	int F; // Dinh ket thuc
	
	printf("Nhap dinh bat dau: ");
	scanf("%d", &S);
	
	printf("Nhap dinh ket thuc: ");
	scanf("%d", &F);

	
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

void DuyetTheoBFS(GRAPH g)
{
	int S; // Dinh bat dau
	int F; // Dinh ket thuc
	
	printf("Nhap dinh bat dau: ");
	scanf("%d", &S);
	
	printf("Nhap dinh ket thuc: ");
	scanf("%d", &F);
	
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

/*******************************************
* BT 9 - Cay menu - bai thi thu
********************************************/
void NhapDuongDanFile()
{
	printf("Duong dan den file thong tin cua do thi la: ");
	scanf("%s", &duongDanFile);
	
	if(DocMaTranKe(duongDanFile, g) == 1)
	{
		printf("Da lay thong tin file thanh cong!\n");
	}
}

int HienThiMenu()
{
	int finished = 0;
	printf("Chuong trinh hien tai co nhung chuc nang sau: \n\n");
	printf("\t1. Nhap duong dan den file chua thong tin cua do thi");
	printf("\n\t2. Xuat thong tin do thi vua nhap");
	printf("\n\t3. Kiem tra do thi co hop le hay khong");	
	printf("\n\t4. Kiem tra do thi vo huong hay co huong");
	printf("\n\t5. Xet tinh lien thong cua do thi");
	printf("\n\t6. Tim chu trinh Euler");
	printf("\n\t7. Tim duong di Euler");	
	printf("\n\t8. Tim duong di theo DFS");
	printf("\n\t9. Tim duong di theo BFS");
	printf("\n\t0. Thoat\n\n");
	printf("Lua chon cua ban la: ");
	
	int menu;
	scanf("%d", &menu);
	switch(menu)
	{
		case 1:
			NhapDuongDanFile();
			break;
		case 2:
			XuatMaTranKe(g);
			break;
		case 3:
			KiemTraMaTranKeHopLe(g);
			break;
		case 4:
			KiemTraDoThiVoHuong(g);
			break;
		case 5:
			XetLienThong(g);
			break;
		case 6:
			KiemTraChuTrinhEuler(g);
			break;
		case 7:
			KiemTraDuongDiEuler(g);
			break;
		case 8:
			DuyetTheoDFS(g);
			break;	
		case 9:
			DuyetTheoBFS(g);
			break;
		case 0:
			finished = 1;
			break;
		default: 
			printf("Khong tim chuc nang cua ban!");
			break;
	}
	
	if(finished == 1)
		return finished;
	
	getch();
	printf("\nBam 1 phim bat ki de quay lai menu!\n\n");
	getch();
	
	return finished;
}


void main()
{
	do
	{
		
	}
	while(HienThiMenu() == 0);
}
