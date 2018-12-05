#include "../include/asm/graphics.h"
#include "../include/asm/utils.h"
#include "../include/input.h"

static inline void project2d(s32 x, s32 y, s32 z, s32& sX, s32& sY) {
    s32 xcalc = 256 * x;
    s32 ycalc = 256 * y;
    s32 zcalc = 256 * z + 2560;
    zcalc = zcalc >> 8;

    if (zcalc == 0) {
        sX = (SCREEN_WIDTH >> 1);
        sY = (SCREEN_HEIGHT >> 1);
    } else {
        sX = xcalc / zcalc + (SCREEN_WIDTH >> 1);
        sY = ycalc / zcalc + (SCREEN_HEIGHT >> 1);
    }
}

int main()
{
    u32 vramAddr = ADDR_VRAM;
    u32 clrScreenColor = 0xFFFFFFFF;
    u32 testColor = 0xF00FF00F;
    u32 testColor2 = 0xE00EE00E;
    initGraphics();
    
    s32 triangles2[12][3][3] = {
        {{ 8,  8, -8}, {-8, -8, -8}, {-8,  8, -8}},
        {{ 8,  8, -8}, { 8, -8, -8}, {-8, -8, -8}},
        {{-8, -8, -8}, { 8, -8, -8}, { 8, -8,  8}},
        {{-8,  8, -8}, {-8, -8, -8}, {-8,  8,  8}},
        {{ 8, -8, -8}, { 8,  8, -8}, { 8,  8,  8}},
        {{ 8,  8, -8}, {-8,  8, -8}, { 8,  8,  8}},
        {{-8, -8, -8}, {-8, -8,  8}, {-8,  8,  8}},
        {{ 8, -8, -8}, { 8,  8,  8}, { 8, -8,  8}},
        {{-8, -8, -8}, { 8, -8,  8}, {-8, -8,  8}},
        {{-8,  8, -8}, {-8,  8,  8}, { 8,  8,  8}},
        {{-8,  8,  8}, {-8, -8,  8}, { 8, -8,  8}},
        {{ 8,  8,  8}, {-8,  8,  8}, { 8, -8,  8}}
    };

    s32 triangles[164][3][3] = {
        {{-37,-44,-1}, {38,-44,-1}, {38,44,-1}},
        {{38,44,-1}, {-37,44,-1}, {-37,-44,-1}},
        {{-25,25,0}, {-25,20,0}, {-9,16,0}},
        {{-6,10,0}, {2,14,0}, {-5,15,0}},
        {{-6,10,0}, {-5,15,0}, {-9,16,0}},
        {{-9,16,0}, {-13,16,0}, {-6,10,0}},
        {{2,14,0}, {0,16,0}, {-5,15,0}},
        {{3,16,0}, {0,16,0}, {2,14,0}},
        {{-9,16,0}, {-5,15,0}, {0,16,0}},
        {{-9,16,0}, {-5,16,0}, {-5,21,0}},
        {{0,16,0}, {5,17,0}, {-5,21,0}},
        {{-5,21,0}, {-5,16,0}, {0,16,0}},
        {{-9,3,0}, {-6,10,0}, {-13,16,0}},
        {{-9,3,0}, {-6,2,0}, {-6,10,0}},
        {{-14,3,0}, {-9,3,0}, {-13,16,0}},
        {{10,10,0}, {2,14,0}, {-6,10,0}},
        {{-13,16,0}, {-19,12,0}, {-14,3,0}},
        {{-5,31,0}, {-5,30,0}, {-3,30,0}},
        {{-15,27,0}, {-15,26,0}, {-13,27,0}},
        {{-10,33,0}, {-10,32,0}, {-7,33,0}},
        {{-10,33,0}, {-12,29,0}, {-10,32,0}},
        {{-13,30,0}, {-12,29,0}, {-10,33,0}},
        {{-13,30,0}, {-10,26,0}, {-12,29,0}},
        {{17,-16,0}, {18,-17,0}, {20,-16,0}},
        {{14,-9,0}, {12,-14,0}, {14,-11,0}},
        {{17,-10,0}, {14,-9,0}, {14,-11,0}},
        {{14,-9,0}, {10,-12,0}, {12,-14,0}},
        {{10,-12,0}, {10,-13,0}, {12,-14,0}},
        {{10,-13,0}, {14,-17,0}, {12,-14,0}},
        {{16,18,0}, {19,12,0}, {19,18,0}},
        {{15,20,0}, {12,18,0}, {16,18,0}},
        {{19,12,0}, {12,18,0}, {11,14,0}},
        {{11,14,0}, {20,10,0}, {19,12,0}},
        {{12,18,0}, {5,17,0}, {11,14,0}},
        {{15,20,0}, {5,17,0}, {12,18,0}},
        {{12,18,0}, {19,12,0}, {16,18,0}},
        {{21,13,0}, {23,14,0}, {19,15,0}},
        {{25,13,0}, {23,14,0}, {21,13,0}},
        {{21,13,0}, {24,12,0}, {25,13,0}},
        {{25,11,0}, {24,12,0}, {21,13,0}},
        {{19,12,0}, {21,13,0}, {19,15,0}},
        {{19,15,0}, {23,14,0}, {19,18,0}},
        {{-8,-7,0}, {-6,-6,0}, {-10,-5,0}},
        {{-4,-7,0}, {-6,-6,0}, {-8,-7,0}},
        {{-8,-7,0}, {-5,-8,0}, {-4,-7,0}},
        {{-4,-9,0}, {-5,-8,0}, {-8,-7,0}},
        {{-10,-8,0}, {-8,-7,0}, {-10,-5,0}},
        {{-10,-5,0}, {-6,-6,0}, {-10,-2,0}},
        {{-17,-2,0}, {-10,-8,0}, {-10,-2,0}},
        {{-18,12,0}, {-16,13,0}, {-20,14,0}},
        {{-14,12,0}, {-16,13,0}, {-18,12,0}},
        {{-18,12,0}, {-15,11,0}, {-14,12,0}},
        {{-14,10,0}, {-15,11,0}, {-18,12,0}},
        {{-20,11,0}, {-18,12,0}, {-20,14,0}},
        {{-20,14,0}, {-16,13,0}, {-20,17,0}},
        {{-27,17,0}, {-20,11,0}, {-20,17,0}},
        {{4,29,0}, {6,30,0}, {2,31,0}},
        {{8,29,0}, {6,30,0}, {4,29,0}},
        {{4,29,0}, {7,28,0}, {8,29,0}},
        {{8,27,0}, {7,28,0}, {4,29,0}},
        {{2,28,0}, {4,29,0}, {2,31,0}},
        {{2,31,0}, {6,30,0}, {2,34,0}},
        {{-5,34,0}, {2,28,0}, {2,34,0}},
        {{-9,16,0}, {-5,21,0}, {-25,25,0}},
        {{-5,21,0}, {5,17,0}, {4,23,0}},
        {{15,20,0}, {4,23,0}, {5,17,0}},
        {{11,14,0}, {14,7,0}, {20,10,0}},
        {{14,7,0}, {12,0,0}, {19,-1,0}},
        {{19,-1,0}, {20,10,0}, {14,7,0}},
        {{12,0,0}, {6,-4,0}, {11,-8,0}},
        {{11,-8,0}, {19,-1,0}, {12,0,0}},
        {{6,-4,0}, {0,-14,0}, {7,-16,0}},
        {{7,-16,0}, {11,-8,0}, {6,-4,0}},
        {{0,-14,0}, {-2,-33,0}, {4,-34,0}},
        {{4,-34,0}, {7,-16,0}, {0,-14,0}},
        {{18,-17,0}, {19,-18,0}, {19,-17,1}},
        {{18,-17,0}, {19,-17,1}, {20,-16,0}},
        {{20,-16,0}, {19,-17,1}, {19,-18,0}},
        {{-11,29,1}, {-12,29,0}, {-10,26,0}},
        {{-12,29,0}, {-11,29,1}, {-10,32,0}},
        {{-15,26,0}, {-14,25,0}, {-14,26,1}},
        {{-15,26,0}, {-14,26,1}, {-13,27,0}},
        {{-13,27,0}, {-14,26,1}, {-14,25,0}},
        {{-5,30,0}, {-4,29,0}, {-4,30,1}},
        {{-5,30,0}, {-4,30,1}, {-3,30,0}},
        {{-3,30,0}, {-4,30,1}, {-4,29,0}},
        {{13,-14,2}, {12,-14,0}, {14,-17,0}},
        {{12,-14,0}, {13,-14,2}, {14,-11,0}},
        {{14,-11,0}, {17,-11,2}, {17,-10,0}},
        {{17,-10,0}, {17,-11,2}, {19,-15,0}},
        {{-10,32,0}, {-7,32,2}, {-7,33,0}},
        {{-7,33,0}, {-7,32,2}, {-5,28,0}},
        {{16,-15,3}, {14,-17,0}, {19,-15,0}},
        {{-8,28,3}, {-10,26,0}, {-5,28,0}},
        {{-11,29,1}, {-7,32,2}, {-10,32,0}},
        {{8,29,4}, {8,29,0}, {7,28,0}},
        {{8,27,0}, {9,28,0}, {9,28,4}},
        {{7,28,4}, {7,28,0}, {8,27,0}},
        {{9,28,0}, {8,29,0}, {8,29,4}},
        {{-13,11,0}, {-14,12,0}, {-14,12,4}},
        {{-14,12,4}, {-14,12,0}, {-15,11,0}},
        {{13,-14,2}, {17,-11,2}, {14,-11,0}},
        {{-15,11,4}, {-15,11,0}, {-14,10,0}},
        {{-5,-8,4}, {-5,-8,0}, {-4,-9,0}},
        {{-4,-7,4}, {-4,-7,0}, {-5,-8,0}},
        {{26,12,0}, {25,13,0}, {25,13,4}},
        {{-14,10,0}, {-13,11,0}, {-13,11,4}},
        {{24,12,4}, {24,12,0}, {25,11,0}},
        {{25,11,0}, {26,12,0}, {26,12,4}},
        {{25,13,4}, {25,13,0}, {24,12,0}},
        {{-3,-8,0}, {-4,-7,0}, {-4,-7,4}},
        {{-11,29,1}, {-10,26,0}, {-8,28,3}},
        {{-4,-9,0}, {-3,-8,0}, {-3,-8,4}},
        {{13,-14,2}, {14,-17,0}, {16,-15,3}},
        {{16,-15,3}, {19,-15,0}, {17,-11,2}},
        {{-8,28,3}, {-5,28,0}, {-7,32,2}},
        {{-7,32,2}, {-11,29,1}, {-8,28,3}},
        {{-6,2,6}, {-6,2,0}, {10,2,0}},
        {{10,10,6}, {10,10,0}, {-6,10,0}},
        {{17,-11,2}, {13,-14,2}, {16,-15,3}},
        {{7,28,0}, {7,28,4}, {8,29,4}},
        {{-6,2,0}, {-6,6,8}, {-6,10,0}},
        {{9,28,4}, {8,27,4}, {8,27,0}},
        {{8,27,0}, {8,27,4}, {7,28,4}},
        {{8,29,4}, {9,28,4}, {9,28,0}},
        {{-14,12,4}, {-13,11,4}, {-13,11,0}},
        {{-5,-8,0}, {-5,-8,4}, {-4,-7,4}},
        {{-14,10,0}, {-14,10,4}, {-15,11,4}},
        {{-4,-7,4}, {-3,-8,4}, {-3,-8,0}},
        {{-13,11,4}, {-14,10,4}, {-14,10,0}},
        {{10,2,0}, {10,10,0}, {10,6,8}},
        {{-4,-9,0}, {-4,-9,4}, {-5,-8,4}},
        {{25,13,4}, {26,12,4}, {26,12,0}},
        {{24,12,0}, {24,12,4}, {25,13,4}},
        {{-15,11,0}, {-15,11,4}, {-14,12,4}},
        {{26,12,4}, {25,11,4}, {25,11,0}},
        {{-3,-8,4}, {-4,-9,4}, {-4,-9,0}},
        {{25,11,0}, {25,11,4}, {24,12,4}},
        {{-6,10,0}, {-6,10,6}, {10,10,6}},
        {{10,2,0}, {10,2,6}, {-6,2,6}},
        {{-6,6,8}, {-6,10,6}, {-6,10,0}},
        {{-6,2,0}, {-6,2,6}, {-6,6,8}},
        {{10,10,0}, {10,10,6}, {10,6,8}},
        {{10,6,8}, {10,2,6}, {10,2,0}},
        {{5,28,4}, {8,25,4}, {8,28,10}},
        {{8,28,10}, {8,25,4}, {11,28,4}},
        {{-4,-5,4}, {-7,-8,4}, {-4,-8,10}},
        {{10,6,8}, {10,12,5}, {-6,12,5}},
        {{22,12,4}, {25,9,4}, {25,12,10}},
        {{-4,-8,10}, {-1,-8,4}, {-4,-5,4}},
        {{25,12,10}, {28,12,4}, {25,15,4}},
        {{-4,-8,10}, {-4,-11,4}, {-1,-8,4}},
        {{25,12,10}, {25,9,4}, {28,12,4}},
        {{-7,-8,4}, {-4,-11,4}, {-4,-8,10}},
        {{-6,6,8}, {-6,0,5}, {10,0,5}},
        {{-17,11,4}, {-14,8,4}, {-14,11,10}},
        {{8,28,10}, {11,28,4}, {8,31,4}},
        {{-14,11,10}, {-14,8,4}, {-11,11,4}},
        {{-14,14,4}, {-17,11,4}, {-14,11,10}},
        {{-14,11,10}, {-11,11,4}, {-14,14,4}},
        {{25,15,4}, {22,12,4}, {25,12,10}},
        {{8,31,4}, {5,28,4}, {8,28,10}},
        {{-6,12,5}, {-6,6,8}, {10,6,8}},
        {{10,0,5}, {10,6,8}, {-6,6,8}}};

    s32 camX = 0;
    s32 camY = 0;
    s32 camZ = 0;

    s16 triangles3[164][10] = {
        {-37,-44,-1,38,-44,-1,38,44,-1,2633}, 
		{38,44,-1,-37,44,-1,-37,-44,-1,2633}, 
		{-25,25,0,-25,20,0,-9,16,0,3407}, 
		{-6,10,0,2,14,0,-5,15,0,1316}, 
		{-6,10,0,-5,15,0,-9,16,0,1316}, 
		{-9,16,0,-13,16,0,-6,10,0,1316}, 
		{2,14,0,0,16,0,-5,15,0,1316}, 
		{3,16,0,0,16,0,2,14,0,1316}, 
		{-9,16,0,-5,15,0,0,16,0,2216}, 
		{-9,16,0,-5,16,0,-5,21,0,3407}, 
		{0,16,0,5,17,0,-5,21,0,3407}, 
		{-5,21,0,-5,16,0,0,16,0,3407}, 
		{-9,3,0,-6,10,0,-13,16,0,1316}, 
		{-9,3,0,-6,2,0,-6,10,0,1316}, 
		{-14,3,0,-9,3,0,-13,16,0,1316}, 
		{10,10,0,2,14,0,-6,10,0,1316}, 
		{-13,16,0,-19,12,0,-14,3,0,1316}, 
		{-5,31,0,-5,30,0,-3,30,0,1316}, 
		{-15,27,0,-15,26,0,-13,27,0,1316}, 
		{-10,33,0,-10,32,0,-7,33,0,1316}, 
		{-10,33,0,-12,29,0,-10,32,0,1316}, 
		{-13,30,0,-12,29,0,-10,33,0,1316}, 
		{-13,30,0,-10,26,0,-12,29,0,1316}, 
		{17,-16,0,18,-17,0,20,-16,0,1316}, 
		{14,-9,0,12,-14,0,14,-11,0,1316}, 
		{17,-10,0,14,-9,0,14,-11,0,1316}, 
		{14,-9,0,10,-12,0,12,-14,0,1316}, 
		{10,-12,0,10,-13,0,12,-14,0,1316}, 
		{10,-13,0,14,-17,0,12,-14,0,1316}, 
		{16,18,0,19,12,0,19,18,0,1316}, 
		{15,20,0,12,18,0,16,18,0,3407}, 
		{19,12,0,12,18,0,11,14,0,3407}, 
		{11,14,0,20,10,0,19,12,0,3407}, 
		{12,18,0,5,17,0,11,14,0,3407}, 
		{15,20,0,5,17,0,12,18,0,3407}, 
		{12,18,0,19,12,0,16,18,0,2216}, 
		{21,13,0,23,14,0,19,15,0,1316}, 
		{25,13,0,23,14,0,21,13,0,1316}, 
		{21,13,0,24,12,0,25,13,0,1316}, 
		{25,11,0,24,12,0,21,13,0,1316}, 
		{19,12,0,21,13,0,19,15,0,1316}, 
		{19,15,0,23,14,0,19,18,0,1316}, 
		{-8,-7,0,-6,-6,0,-10,-5,0,1316}, 
		{-4,-7,0,-6,-6,0,-8,-7,0,1316}, 
		{-8,-7,0,-5,-8,0,-4,-7,0,1316}, 
		{-4,-9,0,-5,-8,0,-8,-7,0,1316}, 
		{-10,-8,0,-8,-7,0,-10,-5,0,1316}, 
		{-10,-5,0,-6,-6,0,-10,-2,0,1316}, 
		{-17,-2,0,-10,-8,0,-10,-2,0,1316}, 
		{-18,12,0,-16,13,0,-20,14,0,1316}, 
		{-14,12,0,-16,13,0,-18,12,0,1316}, 
		{-18,12,0,-15,11,0,-14,12,0,1316}, 
		{-14,10,0,-15,11,0,-18,12,0,1316}, 
		{-20,11,0,-18,12,0,-20,14,0,1316}, 
		{-20,14,0,-16,13,0,-20,17,0,1316}, 
		{-27,17,0,-20,11,0,-20,17,0,1316}, 
		{4,29,0,6,30,0,2,31,0,1316}, 
		{8,29,0,6,30,0,4,29,0,1316}, 
		{4,29,0,7,28,0,8,29,0,1316}, 
		{8,27,0,7,28,0,4,29,0,1316}, 
		{2,28,0,4,29,0,2,31,0,1316}, 
		{2,31,0,6,30,0,2,34,0,1316}, 
		{-5,34,0,2,28,0,2,34,0,1316}, 
		{-9,16,0,-5,21,0,-25,25,0,3407}, 
		{-5,21,0,5,17,0,4,23,0,3407}, 
		{15,20,0,4,23,0,5,17,0,3407}, 
		{11,14,0,14,7,0,20,10,0,3407}, 
		{14,7,0,12,0,0,19,-1,0,3407}, 
		{19,-1,0,20,10,0,14,7,0,3407}, 
		{12,0,0,6,-4,0,11,-8,0,3407}, 
		{11,-8,0,19,-1,0,12,0,0,3407}, 
		{6,-4,0,0,-14,0,7,-16,0,3407}, 
		{7,-16,0,11,-8,0,6,-4,0,3407}, 
		{0,-14,0,-2,-33,0,4,-34,0,3407}, 
		{4,-34,0,7,-16,0,0,-14,0,3407}, 
		{18,-17,0,19,-18,0,19,-17,1,13808}, 
		{18,-17,0,19,-17,1,20,-16,0,6375}, 
		{20,-16,0,19,-17,1,19,-18,0,12751}, 
		{-11,29,1,-12,29,0,-10,26,0,7432}, 
		{-12,29,0,-11,29,1,-10,32,0,7432}, 
		{-15,26,0,-14,25,0,-14,26,1,13808}, 
		{-15,26,0,-14,26,1,-13,27,0,6375}, 
		{-13,27,0,-14,26,1,-14,25,0,12751}, 
		{-5,30,0,-4,29,0,-4,30,1,13808}, 
		{-5,30,0,-4,30,1,-3,30,0,7433}, 
		{-3,30,0,-4,30,1,-4,29,0,14898}, 
		{13,-14,2,12,-14,0,14,-17,0,6408}, 
		{12,-14,0,13,-14,2,14,-11,0,6375}, 
		{14,-11,0,17,-11,2,17,-10,0,7432}, 
		{17,-10,0,17,-11,2,19,-15,0,13808}, 
		{-10,32,0,-7,32,2,-7,33,0,7432}, 
		{-7,33,0,-7,32,2,-5,28,0,13808}, 
		{16,-15,3,14,-17,0,19,-15,0,15923}, 
		{-8,28,3,-10,26,0,-5,28,0,15923}, 
		{-11,29,1,-7,32,2,-10,32,0,5319}, 
		{8,29,4,8,29,0,7,28,0,1194}, 
		{8,27,0,9,28,0,9,28,4,2353}, 
		{7,28,4,7,28,0,8,27,0,1193}, 
		{9,28,0,8,29,0,8,29,4,2353}, 
		{-13,11,0,-14,12,0,-14,12,4,2353}, 
		{-14,12,4,-14,12,0,-15,11,0,1194}, 
		{13,-14,2,17,-11,2,14,-11,0,8490}, 
		{-15,11,4,-15,11,0,-14,10,0,1193}, 
		{-5,-8,4,-5,-8,0,-4,-9,0,1193}, 
		{-4,-7,4,-4,-7,0,-5,-8,0,1194}, 
		{26,12,0,25,13,0,25,13,4,2353}, 
		{-14,10,0,-13,11,0,-13,11,4,2353}, 
		{24,12,4,24,12,0,25,11,0,1193}, 
		{25,11,0,26,12,0,26,12,4,2353}, 
		{25,13,4,25,13,0,24,12,0,1194}, 
		{-3,-8,0,-4,-7,0,-4,-7,4,2353}, 
		{-11,29,1,-10,26,0,-8,28,3,15955}, 
		{-4,-9,0,-3,-8,0,-3,-8,4,2353}, 
		{13,-14,2,14,-17,0,16,-15,3,13809}, 
		{16,-15,3,19,-15,0,17,-11,2,14865}, 
		{-8,28,3,-5,28,0,-7,32,2,14865}, 
		{-7,32,2,-11,29,1,-8,28,3,12751}, 
		{-6,2,6,-6,2,0,10,2,0,14902}, 
		{10,10,6,10,10,0,-6,10,0,6410}, 
		{17,-11,2,13,-14,2,16,-15,3,12751}, 
		{7,28,0,7,28,4,8,29,4,1194}, 
		{-6,2,0,-6,6,8,-6,10,0,5320}, 
		{9,28,4,8,27,4,8,27,0,2353}, 
		{8,27,0,8,27,4,7,28,4,1193}, 
		{8,29,4,9,28,4,9,28,0,2353}, 
		{-14,12,4,-13,11,4,-13,11,0,2353}, 
		{-5,-8,0,-5,-8,4,-4,-7,4,1194}, 
		{-14,10,0,-14,10,4,-15,11,4,1193}, 
		{-4,-7,4,-3,-8,4,-3,-8,0,2353}, 
		{-13,11,4,-14,10,4,-14,10,0,2353}, 
		{10,2,0,10,10,0,10,6,8,12755}, 
		{-4,-9,0,-4,-9,4,-5,-8,4,1193}, 
		{25,13,4,26,12,4,26,12,0,2353}, 
		{24,12,0,24,12,4,25,13,4,1194}, 
		{-15,11,0,-15,11,4,-14,12,4,1194}, 
		{26,12,4,25,11,4,25,11,0,2353}, 
		{-3,-8,4,-4,-9,4,-4,-9,0,2353}, 
		{25,11,0,25,11,4,24,12,4,1193}, 
		{-6,10,0,-6,10,6,10,10,6,6410}, 
		{10,2,0,10,2,6,-6,2,6,14902}, 
		{-6,6,8,-6,10,6,-6,10,0,5320}, 
		{-6,2,0,-6,2,6,-6,6,8,5320}, 
		{10,10,0,10,10,6,10,6,8,12755}, 
		{10,6,8,10,2,6,10,2,0,12755}, 
		{5,28,4,8,25,4,8,28,10,3363}, 
		{8,28,10,8,25,4,11,28,4,6854}, 
		{-4,-5,4,-7,-8,4,-4,-8,10,3395}, 
		{10,6,8,10,12,5,-6,12,5,8594}, 
		{22,12,4,25,9,4,25,12,10,3363}, 
		{-4,-8,10,-1,-8,4,-4,-5,4,7943}, 
		{25,12,10,28,12,4,25,15,4,7943}, 
		{-4,-8,10,-4,-11,4,-1,-8,4,6854}, 
		{25,12,10,25,9,4,28,12,4,6854}, 
		{-7,-8,4,-4,-11,4,-4,-8,10,3363}, 
		{-6,6,8,-6,0,5,10,0,5,12858}, 
		{-17,11,4,-14,8,4,-14,11,10,3363}, 
		{8,28,10,11,28,4,8,31,4,7943}, 
		{-14,11,10,-14,8,4,-11,11,4,6854}, 
		{-14,14,4,-17,11,4,-14,11,10,3395}, 
		{-14,11,10,-11,11,4,-14,14,4,7943}, 
		{25,15,4,22,12,4,25,12,10,3395}, 
		{8,31,4,5,28,4,8,28,10,3395}, 
		{-6,12,5,-6,6,8,10,6,8,8594}, 
		{10,0,5,10,6,8,-6,6,8,12858}
    };

    while(true) {
        vramAddr = startDraw(vramAddr);
        clearScr(vramAddr, (u32)(&clrScreenColor));
        startTimer();
        keyPoll();

        s32 v1Sx, v1Sy;
        s32 v2Sx, v2Sy;
        s32 v3Sx, v3Sy;
        for (int tri = 0; tri < 163; tri++) {
            drawTriangleClipped3D(vramAddr, -triangles3[tri][2] + camX, triangles3[tri][1] + camY, triangles3[tri][0] + camZ,
                                            -triangles3[tri][5] + camX, triangles3[tri][4] + camY, triangles3[tri][3] + camZ,
                                            -triangles3[tri][8] + camX, triangles3[tri][7] + camY, triangles3[tri][6] + camZ,
                                            (u32)(&triangles3[tri][9]));
            continue;

            drawTriangleClipped3D(vramAddr, -triangles[tri][0][2] + camX, triangles[tri][0][1] + camY, triangles[tri][0][0] + camZ,
                                            -triangles[tri][1][2] + camX, triangles[tri][1][1] + camY, triangles[tri][1][0] + camZ,
                                            -triangles[tri][2][2] + camX, triangles[tri][2][1] + camY, triangles[tri][2][0] + camZ, (u32)(&testColor) + tri);
            continue;

            s32 uX = triangles[tri][1][0] - triangles[tri][0][0];
            s32 uY = triangles[tri][1][1] - triangles[tri][0][1];
            s32 uZ = triangles[tri][1][2] - triangles[tri][0][2];
            s32 vX = triangles[tri][2][0] - triangles[tri][0][0];
            s32 vY = triangles[tri][2][1] - triangles[tri][0][1];
            s32 vZ = triangles[tri][2][2] - triangles[tri][0][2];

            project2d(triangles[tri][0][0] + camX, triangles[tri][0][1] + camY, triangles[tri][0][2] + camZ, v1Sx, v1Sy);
            project2d(triangles[tri][1][0] + camX, triangles[tri][1][1] + camY, triangles[tri][1][2] + camZ, v2Sx, v2Sy);
            project2d(triangles[tri][2][0] + camX, triangles[tri][2][1] + camY, triangles[tri][2][2] + camZ, v3Sx, v3Sy);

            s32 c1X = v2Sx - v1Sx;
            s32 c1Y = v2Sy - v1Sy;
            s32 c2X = v3Sx - v1Sx;
            s32 c2Y = v3Sy - v1Sy;
            //if (c1X * c2Y - c1Y * c2X < 0)
                //continue;
            
            if (uY * vZ - uZ * vY < 0 ||
                uX * vY - uY * vX < 0 ||
                uZ * vX - uX * vZ < 0)
                drawTriangleClipped(vramAddr, v1Sx, v1Sy, v2Sx, v2Sy, v3Sx, v3Sy, (u32)(&testColor));
            else
                drawTriangleClipped(vramAddr, v1Sx, v1Sy, v2Sx, v2Sy, v3Sx, v3Sy, (u32)(&testColor2));
        }
        
        if (keyIsDown(KEY_RIGHT))
            camY--;
        if (keyIsDown(KEY_LEFT))
            camY++;
        if (keyIsDown(KEY_L))
            camX--;
        if (keyIsDown(KEY_R))
            camX++;
        if (keyIsDown(KEY_UP))
            camZ--;
        if (keyIsDown(KEY_DOWN))
            camZ++;

        if (keyIsDown(KEY_START)) {
            volatile u32 time = stopTimer();
            BREAK
        } else 
            stopTimer();

        /*
        //Examples
        drawPixel(vramAddr, 0, 0, 0xFF);
        drawLine(vramAddr, 12, 12, 20, 55, 0xFF);
        drawHorzLine(vramAddr, 0, 22, 20, (u32)(&testColor));
        drawVertLine(vramAddr, 22, 0, 15, (u32)(&testColor));
        drawRectFromCenter(vramAddr, 40, 40, 10, 15, (u32)(&testColor));
        drawRectFromCorner(vramAddr, 60, 60, 25, 30, (u32)(&testColor));
        drawRectEmpty(vramAddr, 100, 100, 15, 20, (u32)(&testColor));
        drawCircle(vramAddr, 140, 30, 16, (u32)(&testColor));
        drawCircleEmpty(vramAddr, 140, 30, 20, 0xFF);
        drawTriangleClipped(vramAddr, 60, 120, 50, 100, 70, 100, (u32)(&testColor));
        drawTriangle(vramAddr, 30, 120, 20, 100, 40, 100, (u32)(&testColor));
        */
        
        //startTimer();
        //drawTriangleClipped(vramAddr, 0, 120, -80, 10, 80, 10, (u32)(&testColor));
        //volatile u32 time = stopTimer();  
        //BREAK
    }

	return 0;
}