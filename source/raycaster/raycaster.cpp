#include "raycaster/raycaster.h"
#include "asm/graphics.h"
#include "asm/utils.h"
#include "input.h"
#include "delcs.h"

#include <cmath>

#define COLOR_256	0x2000
#define SIZE_8		0x0
#define SIZE_16		0x4000
#define SIZE_32		0x8000
#define SIZE_64		0xC000

#define 	CLR_BLACK   0x0000
#define 	CLR_RED   0x001F
#define 	CLR_LIME   0x03E0
#define 	CLR_YELLOW   0x03FF
#define 	CLR_BLUE   0x7C00
#define 	CLR_MAG   0x7C1F
#define 	CLR_CYAN   0x7FE0
#define 	CLR_WHITE   0x7FFF

static u32 clrScreenColor;

//raycaster member variables:
float posX = 22, posY = 7;  //x and y start position
float dirX = -1, dirY = 0; //initial direction vector
float planeX = 0, planeY = 0.66; //the 2d raycaster version of camera plane
//end raycaster variables

extern "C"{
    void raycaster_init()
    {
        initGraphics();

        clrScreenColor = 0xFFFFFFFF;
    }

    void raycaster_render()
    {
        g_GraphicsAddr = startDraw(g_GraphicsAddr);
        noCashStartTimer();
        clearScr(g_GraphicsAddr, (u32)(&clrScreenColor), 0);


        for(int x = 0; x < CANVAS_WIDTH; x++)
        {

            //calculate ray position and direction
            float cameraX = 2 * x / float(CANVAS_WIDTH) - 1; //x-coordinate in camera space
            float rayDirX = dirX + planeX * cameraX;
            float rayDirY = dirY + planeY * cameraX;

            //which box of the map we're in
            int mapX = int(posX);
            int mapY = int(posY);

            //length of ray from current position to next x or y-side
            float sideDistX;
            float sideDistY;

            //length of ray from one x or y-side to next x or y-side
            float deltaDistX = std::abs(1 / rayDirX);
            float deltaDistY = std::abs(1 / rayDirY);
            float perpWallDist;

            //what direction to step in x or y-direction (either +1 or -1)
            int stepX;
            int stepY;

            int hit = 0; //was there a wall hit?
            int side; //was a NS or a EW wall hit?

            //calculate step and initial sideDist
            if (rayDirX < 0)
            {
                stepX = -1;
                sideDistX = (posX - mapX) * deltaDistX;
            }
            else
            {
                stepX = 1;
                sideDistX = (mapX + 1.0 - posX) * deltaDistX;
            }
            if (rayDirY < 0)
            {
                stepY = -1;
                sideDistY = (posY - mapY) * deltaDistY;
            }
            else
            {
                stepY = 1;
                sideDistY = (mapY + 1.0 - posY) * deltaDistY;
            }

            //perform DDA
            while (hit == 0)
            {
                //jump to next map square, OR in x-direction, OR in y-direction
                if (sideDistX < sideDistY)
                {
                    sideDistX += deltaDistX;
                    mapX += stepX;
                    side = 0;
                }
                else
                {
                    sideDistY += deltaDistY;
                    mapY += stepY;
                    side = 1;
                }
                //Check if ray has hit a wall
                if (raycaster_map[mapY][mapX] > 0) hit = 1;
            }

            //Calculate distance projected on camera direction (Euclidean distance will give fisheye effect!)
            if (side == 0) perpWallDist = (mapX - posX + (1 - stepX) / 2) / rayDirX;
            else           perpWallDist = (mapY - posY + (1 - stepY) / 2) / rayDirY;

            //Calculate height of line to draw on screen
            int lineHeight = (int)(CANVAS_HEIGHT / perpWallDist);

            //calculate lowest and highest pixel to fill in current stripe
            int drawStart = -lineHeight / 2 + CANVAS_HEIGHT / 2;
            if(drawStart < 0)drawStart = 0;
            int drawEnd = lineHeight / 2 + CANVAS_HEIGHT / 2;
            if(drawEnd >= CANVAS_HEIGHT)drawEnd = CANVAS_HEIGHT - 1;

            //choose wall color
            u16 color;
            switch(raycaster_map[mapY][mapX])
            {
                case 1:  color = CLR_RED;  break; //red
                case 2:  color = CLR_LIME;  break; //green
                case 3:  color = CLR_BLUE;   break; //blue
                case 4:  color = CLR_MAG;  break; //white
                default: color = CLR_YELLOW; break; //yellow
            }

            //give x and y sides different brightness
            if (side == 1) {color = color / 2;}

            //draw the pixels of the stripe as a vertical line
            drawVertLine(g_GraphicsAddr, x, drawStart, drawEnd-drawStart, (u32)(&color));
        }
        
        noCashStopTimer();
        
        float moveSpeed = 0.5f;
        float rotSpeed = 0.5;
        //move forward if no wall in front of you
        if (keyIsDown(KEY_UP))
        {
        if(raycaster_map[int(posY)][int(posX + dirX * moveSpeed)] == false) posX += dirX * moveSpeed;
        if(raycaster_map[int(posY + dirY * moveSpeed)][int(posX)] == false) posY += dirY * moveSpeed;
        }
        //move backwards if no wall behind you
        if (keyIsDown(KEY_DOWN))
        {
        if(raycaster_map[int(posY)][int(posX - dirX * moveSpeed)] == false) posX -= dirX * moveSpeed;
        if(raycaster_map[int(posY - dirY * moveSpeed)][int(posX)] == false) posY -= dirY * moveSpeed;
        }
        //rotate to the right
        if (keyIsDown(KEY_RIGHT))
        {
        //both camera direction and camera plane must be rotated
        double oldDirX = dirX;
        dirX = dirX * cos(-rotSpeed) - dirY * sin(-rotSpeed);
        dirY = oldDirX * sin(-rotSpeed) + dirY * cos(-rotSpeed);
        double oldPlaneX = planeX;
        planeX = planeX * cos(-rotSpeed) - planeY * sin(-rotSpeed);
        planeY = oldPlaneX * sin(-rotSpeed) + planeY * cos(-rotSpeed);
        }
        //rotate to the left
        if (keyIsDown(KEY_LEFT))
        {
        //both camera direction and camera plane must be rotated
        double oldDirX = dirX;
        dirX = dirX * cos(rotSpeed) - dirY * sin(rotSpeed);
        dirY = oldDirX * sin(rotSpeed) + dirY * cos(rotSpeed);
        double oldPlaneX = planeX;
        planeX = planeX * cos(rotSpeed) - planeY * sin(rotSpeed);
        planeY = oldPlaneX * sin(rotSpeed) + planeY * cos(rotSpeed);
        }
        
        busywait_vsync();
    }

    void raycaster_cleanup()
    {
    }
}