#include "Map.h"


Line::Line() {

}


void Line::init(Terrain_t li[Map_Width]) {
    memcpy(line, li, sizeof(line));
}


GameMap::GameMap() {

}


void GameMap::init(Terrain_t fmap[Map_Height][Map_Width]) {
    for (int i = 0; i < Map_Height; i++) {
        map[i].init(fmap[i]);
        old_map[i].init(fmap[i]);
    }
}


void GameMap::Update(int px, int py, Terrain_t t) {
    map[px][py] = t;
}


void GameMap::Hold_Back(int px, int py) {
    map[px][py] = old_map[px][py];
}


bool GameMap::Is_In_Map(int px, int py) {
    if (px < 0 || px >= Map_Height || py < 0 || py >= Map_Width) {
        return false;
    }
    else {
        return true;
    }
}


void GameMap::Display() {
    Set_Cursor_Pos(0, 0);

    for (int i = 0; i < Map_Width + 2; i++) {
        cout << "■";
    }cout << endl;

    for (int x = 0; x < Map_Height; x++) {
        cout << "■";
        for (int y = 0; y < Map_Width; y++) {
            switch (map[x][y]) {
            case Path:
                cout << "  "; break;
            case MudWall:
                cout << "▓"; break;
            case IronWall:
                cout << "■"; break;
            case Base:
                cout << "♀"; break;
            case DesBase:
                cout << "Xb"; break;
            case Bush:
                cout << "⊙"; break;
            case River:
                cout << "¤"; break;
            case Tanki:
                cout << "Ξ"; break;
            case DesTanki:
                cout << "Xt"; break;
            case Bulleti:
                cout << "°"; break;
            default:
                cout << "? "; break;
            }
        }
        cout << "■";
        cout << endl;
    }

    for (int i = 0; i < Map_Width + 2; i++) {
        cout << "■";
    }
    cout << endl;
}


static void Set_Cursor_Pos(int x, int y) {
    COORD point = { x, y };
    HANDLE HOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(HOutput, point);
}