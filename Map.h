#pragma once
#ifndef __MAP__
#define __MAP__


#include "common.h"


const int Map_Height = 20;   // 地图高
const int Map_Width = 25;    // 地图宽


class Line {
public:
    Terrain_t line[Map_Width];
public:
    Line();
    void init(Terrain_t li[Map_Width]);
    Terrain_t& operator[](int i) { return line[i]; }
};


class GameMap {
public:
    Line map[Map_Height];
    Line old_map[Map_Height];
public:
    GameMap();
    GameMap(Terrain_t fmap[Map_Height][Map_Width]);
    void init(Terrain_t fmap[Map_Height][Map_Width]);
    Line& operator[](int i) { return map[i]; }

    void Update(int px, int py, Terrain_t t);   // 刷新
    void Hold_Back(int px, int py);             // 回滚，处理坦克/子弹离开后的复原

    bool Is_In_Map(int px, int py);

    void Display();
};


static void Set_Cursor_Pos(int x, int y);


#endif // !__MAP__