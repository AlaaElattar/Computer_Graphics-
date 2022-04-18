/**
* Alaa Mahmoud Ebrahim 20190105
* Joseph Diaa 20190155 
* CS-S4
**/

#include <math.h>
#include <Windows.h>

void swap(int& x1, int& y1, int& x2, int& y2){
	int tmp = x1;
	x1 = x2;
	x2 = tmp;
	tmp = y1;
	y1 = y2;
	y2 = tmp;
}

int Round(double x){
	return (int)(x + 0.5);
}

void DrawLine1(HDC hdc, int x1, int y1, int x2, int y2, COLORREF color){
	int dx = x2 - x1;
	int dy = y2 - y1;
	if (abs(dy) <= abs(dx))
	{
		if (x1 > x2)swap(x1, y1, x2, y2);
		SetPixel(hdc, x1, y1, color);
		int x = x1;
		while (x < x2)
		{
			x++;
			double y = y1 + (double)(x - x1) * dy / dx;
			SetPixel(hdc, x, ceil(y), color);
			SetPixel(hdc, x, floor(y), color);

		}
	}

}

void DrawLine2(HDC hdc, int x1, int y1, int x2, int y2, COLORREF color) {
	int dx = x2 - x1;
	int dy = y2 - y1;
	if (abs(dy)>abs(dx)){
		if (y1 > y2)swap(x1, y1, x2, y2);
		SetPixel(hdc, x1, y1, color);
		int y = y1;
		while (y < y2)
		{
			y++;
			double x = x1 + (double)(y - y1) * dx / dy;
			SetPixel(hdc, ceil(x), y, color);
			SetPixel(hdc, floor(x), y, color);
		}
	}

}

void draw8points(HDC hdc,int xc, int yc, int x, int y){
	SetPixel(hdc, xc + x, yc + y, RGB(128, 0, 0));
	DrawLine2(hdc, xc, yc, xc + x, yc + y, RGB(128, 0, 0));	//4

	SetPixel(hdc, xc + x, yc - y,RGB(0,0,205));
	DrawLine1(hdc, xc, yc, xc + x, yc - y, RGB(0, 0, 205)); //2

	SetPixel(hdc, xc - x, yc - y,RGB(124,252,0));
	DrawLine2(hdc, xc, yc, xc - x, yc - y, RGB(124, 252, 0));	//8


	SetPixel(hdc, xc - x, yc + y,RGB(0,100,0));
	DrawLine1(hdc, xc, yc, xc - x, yc + y, RGB(0, 100, 0)); //6

	SetPixel(hdc, xc + y, yc + x, RGB(128, 0, 0));
	DrawLine1(hdc, xc, yc, xc + x, yc + y, RGB(128, 0, 0));	//3

	SetPixel(hdc, xc + y, yc - x,  RGB(34, 139, 34));
	DrawLine2(hdc, xc, yc, xc + x, yc - y, RGB(34, 139, 34)); //1

	SetPixel(hdc, xc - y, yc - x, RGB(0, 0, 0));
	DrawLine1(hdc, xc, yc, xc - x, yc - y, RGB(0, 0, 0)); //7

	SetPixel(hdc, xc - y, yc + x, RGB(0, 0, 205));
	DrawLine2(hdc, xc, yc, xc - x, yc + y, RGB(0, 0, 205)); //5
}

void drawcircle1(HDC hdc, int xc, int yc, int r,COLORREF c){

	int x = 0;
	double y = r;
	draw8points(hdc,xc, yc, 0, r);
	while (x < y)
	{
		x++;
		y = sqrt((double)r * r - x * x);
		draw8points(hdc,xc, yc, x, Round(y));
	}

	double x1 = r, y1 = 0;
	while (x1 > y1)
	{
		y1++;
		x1 = sqrt((double)r * r - y1 * y1);
		draw8points(hdc, xc, yc, x1, Round(y1));
	}


}

LRESULT WINAPI MyWndProc(HWND hwnd, UINT mcode, WPARAM wp, LPARAM lp){
	HDC hdc;
	switch (mcode)
	{
	case WM_LBUTTONDOWN:
		hdc = GetDC(hwnd);
		drawcircle1(hdc, 300, 300, 100, RGB(255, 0, 0));
		ReleaseDC(hwnd, hdc);
		break;
	case WM_CLOSE:
		DestroyWindow(hwnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default: return DefWindowProc(hwnd, mcode, wp, lp);
	}
	return 0;
}

int APIENTRY WinMain(HINSTANCE hinst, HINSTANCE pinst, LPSTR cmd, int nsh){
	WNDCLASS wc;
	wc.cbClsExtra = wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH)GetStockObject(LTGRAY_BRUSH);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hInstance = hinst;
	wc.lpfnWndProc = MyWndProc;
	wc.lpszClassName = L"MyClass";
	wc.lpszMenuName = NULL;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&wc);
	HWND hwnd = CreateWindow(L"MyClass", L"My First Window", WS_OVERLAPPEDWINDOW, 0, 0, 800, 600, NULL, NULL, hinst, 0);
	ShowWindow(hwnd, nsh);
	UpdateWindow(hwnd);
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return 0;
}