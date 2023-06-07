// �ʿ��� ��� ����, ���� ���� �����
#ifndef O_H_
#define O_H_

#include <stdlib.h>
#include <cmath>
#include <stdio.h>
#include <Windows.h>
#include <vector>
#include <iostream>

#include "glut.h"
#include "Vector2D.h"
#include "Color4f.h"
// #include "Texture.h"
#include "Sprite.h"
#include "Player.h"
#include "Ground.h"
#include "Stage.h"

// �ܺ� ���� ����ü g_Extern ����
// �ܺ� �ҽ����Ͽ��� ���� ��, extern Ű����� �Բ� ���.
struct WindowSize 
{
	int WINDOWSIZE_WIDTH;
	int WINDOWSIZE_HEIGHT;
};
extern WindowSize g_Extern;

// Ű �Է��Լ�
static int KeyDown(int vk)
{
	// GetAsyncKeyState() �Լ��� �ش� ���� Ű �ڵ��� ���¸� ��ȯ 
	// ��ȯ�� ���� 0x8000�� AND �����Ͽ� Ű�� ���� �����ִ��� Ȯ���� �� �ִ�.
	// ������ ���׿����ڿ� ���� 1�� return�Ѵ�. 
	return ((GetAsyncKeyState(vk) & 0x8000) ? 1 : 0);
}

static int KeyUp(int vk)
{
	return ((GetAsyncKeyState(vk) & 0x8000) ? 0 : 1);
}

#endif