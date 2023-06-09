// 필요한 헤더 파일, 전역 변수 저장소
#ifndef O_H_
#define O_H_

// #include "Include/glut.h"
#pragma comment(lib,"glut32.lib") 

// #include <stdlib.h>
#include <cmath>
#include <stdio.h>
#include <windows.h>
#include <vector>
#include <iostream>
#include <string>


#include "glut.h"
#include "Vector2D.h"
#include "Color4f.h"
#include "Sprite.h"
#include "Player.h"
#include "Ground.h"
#include "Stage.h"


// 외부 참조 구조체 g_Extern 선언
// 외부 소스파일에서 접근 시, extern 키워드와 함께 사용.
struct WindowSize 
{
	int WINDOWSIZE_WIDTH;
	int WINDOWSIZE_HEIGHT;
};
extern WindowSize g_Extern;

// 키 입력함수
static int KeyDown(int vk)
{
	// GetAsyncKeyState() 함수는 해당 가상 키 코드의 상태를 반환 
	// 반환된 값에 0x8000을 AND 연산하여 키가 현재 눌려있는지 확인할 수 있다.
	// 눌리면 삼항연산자에 의해 1을 return한다. 
	return ((GetAsyncKeyState(vk) & 0x8000) ? 1 : 0);
}

static int KeyUp(int vk)
{
	return ((GetAsyncKeyState(vk) & 0x8000) ? 0 : 1);
}

#endif