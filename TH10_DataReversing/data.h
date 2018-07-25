#pragma once
#include <windows.h>
#include <vector>

#define GAME_WIDTH 384
#define GAME_HEIGHT 448
#define GAME_X_OFFSET 192
#define GAME_Y_OFFSET 0

struct vec2
{
	float x, y;
	vec2();
	vec2(float x, float y);
	vec2(const vec2& other);
	vec2(vec2&& other) noexcept;
	vec2& operator=(const vec2& other);
	vec2& operator=(vec2&& other) noexcept;
	vec2 rotate(float arc) const;
};
vec2 operator+(const vec2& a, const vec2& b);
vec2 operator*(const vec2& a, float o);

struct Object
{
	vec2 p;
	vec2 v;
	float w, h;
	Object(){}
	Object(vec2 p, vec2 v, float w, float h);
};

struct Player : Object
{
	Player(){}
	float powers;

	int life;

	// type == 0 Reimu
	// type == 1 Marisa
	int type;

	// slow == 0 High Speed
	// slow == 1 Low Speed
	int slow;

	float itemObtainRange;

	// status == 0 ����״̬����ʱ�޵�
	// status == 1 ����״̬
	// status == 2 ����
	// status == 3 Unknown
	// status == 4 ��������������ʱ��B���Ծ���
	int status;

	// ʣ���޵�ʱ��
	int invinibleTime;
};

struct Laser : Object
{
	float arc;
	Laser(vec2 p, vec2 v, float w, float h, float arc);
	std::vector<vec2> getVertices() const;
};

struct Item : Object
{
	// �������Ϊ���¼���
	// type == 1 Power Items P�㣨��㣩
	// type == 2 Point Items �÷ֵ㣨���㣩
	// type == 3 Faith Items �����㣨�̵㣩
	// type == 4 Large Power Items ��P�㣨��㣩
	// type == 5 Large Point Items ��÷ֵ㣨����ɫ���ߵ����㣩����BOSS����
	// type == 6 Unknown
	// type == 7 Life Items �����㣨�ϵ㡢1UP�㣩
	// type == 8 Unknown
	// type == 9 Faith Items �����㣨�̵㣩��������ʱ��P��ת������
	// type == 10 Power Items P�㣨��㣩����BOSS����
	// ��û�п�Ⱥ͸߶ȣ��Ի�������ʱ���Զ���ȡ��Ϊ�˷�����ʾ�趨Ϊ6
	int type;
	Item(vec2 p, vec2 v, float w, float h, int type);
};

class DataReader
{
public:
	DataReader(HANDLE hProcess);

	void GetPlayerInfo(Player& plyr);
	void GetBulletsInfo(std::vector<Object>& bullets);
	void GetEnemiesInfo(std::vector<Object>& enemise);
	void GetLasersInfo(std::vector<Laser>& lasers);
	void GetItemsInfo(std::vector<Item>& items);

private:
	HANDLE GameProcess;

	template <class T> 
	T Read(int addr);
};