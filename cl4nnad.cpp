#define _CRT_SECURE_NO_WARNINGS 1

#include <windows.h>
#include <iostream>
#include <psapi.h>  
#include <stdio.h>  
#include <tchar.h> 
#include <tlhelp32.h>  
#include <wchar.h>
#include "starfish.h"
#include <conio.h>
#include <time.h>
//#pragma comment(lib, "starfish.lib")

 

typedef DWORD(WINAPI* ZW_SET_INFORMATION_THREAD) (HANDLE, DWORD, PVOID, ULONG);
#define ThreadHideFromDebugger 0x11
VOID DisableDebugEvent(VOID)
{
	HINSTANCE hModule;
	ZW_SET_INFORMATION_THREAD ZwSetInformationThread;
	hModule = GetModuleHandleA("Ntdll");
	ZwSetInformationThread = (ZW_SET_INFORMATION_THREAD)GetProcAddress(hModule, "ZwSetInformationThread");
	ZwSetInformationThread(GetCurrentThread(), ThreadHideFromDebugger, 0, 0);
}

void screen()
{
	DisableDebugEvent();
	system("cls");
	printf("------Guess number--------\n");
	printf("---------1.Play ----------\n");
	printf("--------------------------\n");
	printf("---------2.Esc  ----------\n");
	printf("--------------------------\n");
}

class Initialize1r {
public:
	Initialize1r() {
		__asm {
			push rax
			xor rax, rax
			xor rax, 1
			call label
			label :
			add rax, 3
				add rax, 1
				sar rax, 1
				shl rax, 1
				sar rax, 1
				shl rax, 1
				shl rax, 1
				add rax, 4
				shl rax, 1
				sar rax, 1
				sub rax, 1
				shl rax, 1
				sar rax, 1
				xor rax, 3
				shl rax, 1
				sar rax, 1
				sub rax, 4
				add rax, 2
				cmp rax, 0x12
				jz end
				retn
				end :
			pop rax
		}
		if (IsDebuggerPresent())
		{
			exit(0);
		}
	}
};
Initialize1r initialize1r;

bool game()
{
	//按照时间设定随机数种子
	srand((unsigned)time(NULL));
	//第一步，生成随机数字，范围在1--100之间
	int ret = rand() % 100 + 1;//生成随机数，赋值给ret
	//printf("随机数为%d\n", ret);//测试输出是否正常

	//第二步，猜数字
	int guess = 0;//记录猜的值
	int times = 0;//记录猜的次数
	while (1)
	{	
		
		printf("please input a number :");
		scanf("%d", &guess);
		
		
		if (guess < ret)
			printf("too small!\n");
		else if (guess > ret)
			printf("too big!\n");
		else
		{
			printf("u win!\n");
			return true;
		}
		times++;
		if (times >= 10)
		{
			printf("u lose!\n");
			return false;
		}
	}
}

void play_guess()
{
	while (1)
	{
		screen();
		int a = 0;
		scanf_s("%d", &a);
		if (a == 1)
		{
			if (game()) {
				//printf("恭喜你，猜对了！\n");
				printf("Congratulations, you are right!\n");
				//printf("那么，来玩风子的第二个游戏吧！\n");
				printf("Then, let's play Fuko's second game!\n");
				Sleep(2000);
				system("cls");
				play_snake();
				break;
			}
			else {
				break;
			}
		}
		else if (a == 2)
		{
			break;
		}
	}
}



int main() {

    HMODULE hModule = LoadLibrary(L"starfish.dll"); // 用正确的 DLL 名称替换   
    if (hModule == NULL) {
        DWORD error = GetLastError();
        std::cerr << "Failed to load the DLL. Error code: " << error << "\n";
        return 1;
    }
	//你好CTFer，我是伊吹风子，想要获得我的海星，你需要完成我的三个游戏！让我们开始吧 :)
	//printf("你好 ctfer\n");

	printf("\nhello ctfer\n");

	//printf("我是伊吹风子!\n");
	printf("I am Ibuki Fuko!\n");

	//printf("想要获得我的海星\n");
	printf("If you want to get my starfish\n");

	//printf("你需要完成我的三个游戏!\n");
	printf("You need to complete my three games!\n");

	//printf("准备好了吗?\n");
	printf("Are you ready?\n");

	//printf("让我们开始吧!\n");
	printf("Let's start!\n");
	Sleep(2000);
	system("cls");
	play_guess();
	//printf("再见喽\n");
	printf("Goodbye\n");
	//play_snake();

    
    FreeLibrary(hModule);


    return 0;
}
