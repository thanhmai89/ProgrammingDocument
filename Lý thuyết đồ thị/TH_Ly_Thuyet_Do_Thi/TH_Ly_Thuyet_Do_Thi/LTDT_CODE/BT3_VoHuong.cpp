#include<stdio.h>
#include<conio.h>
#include<string.h>

#define MAX 10
#define inputfile "E:/CODE/BT3/matran2.txt"

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
	int x = 3; // x la gia tri dinh bat dau xet chu trinh euler, dieu kien x la dinh phai co bac > 0
	
	/*int flag = 0;
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
	}*/
	
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
	//for(i = stack.size - 1; i >= 0; i--)
		//printf("%d ", stack.array[i] + 1);
	
	for(i = 0; i < stack.size; i++)
		printf("%d ", stack.array[i] + 1);
	
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
	
	return 1;
}

void main()
{
	DOTHI g;

	if(DocMaTranKe(inputfile, g) == 1)
	{
		/*******************************************
		* BT 1 - BT 1 - Kiem tra do thi vo huong
		********************************************/
		printf("Da lay thong tin do thi tu file thanh cong. \n\n");
		XuatMaTranKe(g);
		
		//if(KiemTraMaTranKeHopLe(g) == 1)
			//printf("Do thi hop le.\n");
		//else
			//printf("Do thi khong hop le\n");
		
		//if(KiemTraDoThiVoHuong(g) == 1)
			//printf("Do thi vo huong\n");
		//else
			//printf("Do thi co huong\n");
		
		/*******************************************
		* BT 2 - Xet tinh lien thong
		********************************************/
		//XetLienThong(g);
		
		/*******************************************
		* BT 3 - Duong di Euler
		********************************************/
		if(!KiemTraChuTrinhEuler(g))
		{
			printf("Khong co chu trinh Euler trong d
			o thi cua ban\n");
			
			if(!KiemTraDuongDiEuler(g))
			{
				printf("Khong co duong di euler trong do thi cua ban \n");
			}
		}
	}
	getch();
}
