#include "ripes_system.h"

void set_pixel(unsigned int x, unsigned int y, unsigned int color);
void create_snake(unsigned int x, unsigned int y);

void main(){
    unsigned int *up = D_PAD_0_UP;
    unsigned int *down = D_PAD_0_DOWN;
    unsigned int *left = D_PAD_0_LEFT;
    unsigned int *right = D_PAD_0_RIGHT;
    unsigned int key_up_pressed = 0;
    unsigned int key_down_pressed = 0;
    unsigned int key_left_pressed = 0;
    unsigned int key_right_pressed = 0;
    unsigned int x = 17;
    unsigned int y = 12;

    create_snake(x, y);

    while(1){
        if(*up == 1 && key_up_pressed == 0){
            key_up_pressed = 1;
            y += 1;
            create_snake(x, y);
        } else if(*down == 1 && key_down_pressed == 0){
            key_down_pressed = 1;
            y -= 1;
            create_snake(x, y);
        } else if(*left == 1 && key_left_pressed == 0){
            key_left_pressed = 1;
            x -= 1;
            create_snake(x, y);
        } else if(*right == 1 && key_right_pressed == 0){
            key_right_pressed = 1;
            x += 1;
            create_snake(x, y);
        } else if(*up == 0 && key_up_pressed == 1){
            key_up_pressed = 0;   
        } else if(*down == 0 && key_down_pressed == 1){
            key_down_pressed = 0;
        } else if(*left == 0 && key_left_pressed == 1){
            key_left_pressed = 0;
        } else if(*right == 0 && key_right_pressed == 1){
            key_right_pressed = 0;
        }
    }
}

void set_pixel(unsigned int x, unsigned int y, unsigned int color){
    unsigned int *led_base = LED_MATRIX_0_BASE;
    unsigned int offset = LED_MATRIX_0_WIDTH*((LED_MATRIX_0_HEIGHT-1)-y) + x;
    *(led_base + offset) = color;
}

void create_snake(unsigned int x, unsigned int y){
    set_pixel(x, y, 0x00FF0000);
    set_pixel(x+1, y, 0x00FF0000);
    set_pixel(x, y-1, 0x00FF0000);
    set_pixel(x+1, y-1, 0x00FF0000);

}
