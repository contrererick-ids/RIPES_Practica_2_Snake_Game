#include <stdlib.h>
#include "ripes_system.h"

void set_pixel(unsigned int x, unsigned int y, unsigned int color);
void clean_screen();
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
    
    clean_screen();
    create_snake(x, y);
    create_apple();

    while(1){
        if(*up == 1 && key_up_pressed == 0){
            key_up_pressed = 1;
            y += 1;
            create_snake(x, y);
            clean_screen(x, y-2);
            clean_screen(x+1, y-2);
        } else if(*down == 1 && key_down_pressed == 0){
            key_down_pressed = 1;
            y -= 1;
            create_snake(x, y);
            clean_screen(x, y+1);
            clean_screen(x+1, y+1);
        } else if(*left == 1 && key_left_pressed == 0){
            key_left_pressed = 1;
            x -= 1;
            create_snake(x, y);
            clean_screen(x+2, y);
            clean_screen(x+2, y-1);
        } else if(*right == 1 && key_right_pressed == 0){
            key_right_pressed = 1;
            x += 1;
            create_snake(x, y);
            clean_screen(x-1, y);
            clean_screen(x-1, y-1);
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

void clean_screen(unsigned int x, unsigned int y){
    set_pixel(x, y, 0x0);
}

void create_snake(unsigned int x, unsigned int y){
    set_pixel(x, y, 0x00FF0000);
    set_pixel(x+1, y, 0x00FF0000);
    set_pixel(x, y-1, 0x00FF0000);
    set_pixel(x+1, y-1, 0x00FF0000);

}

int check_color(unsigned int x, unsigned int y){
    unsigned int *led_base = LED_MATRIX_0_BASE;
    unsigned int offset = LED_MATRIX_0_WIDTH*((LED_MATRIX_0_HEIGHT-1)-y) + x;
    if(*(led_base + offset) != 0x0){
        return 1;
    }
    return 0;
}

void create_apple(){
    int apple_created = 0;
    
    while(apple_created != 1){
        int rand_x = rand() % (LED_MATRIX_0_WIDTH + 1);
        int rand_y = rand() % (LED_MATRIX_0_HEIGHT + 1);
        int valid_led_1 = check_color(rand_x, rand_y);
        int valid_led_2 = check_color(rand_x+1, rand_y);
        int valid_led_3 = check_color(rand_x, rand_y-1);
        int valid_led_4 = check_color(rand_x+1, rand_y-1);
        if(valid_led_1 == 0 && valid_led_2 == 0 && valid_led_3 == 0 && valid_led_4 == 0){
            set_pixel(rand_x, rand_y, 0x0000FF00);
            set_pixel(rand_x+1, rand_y, 0x0000FF00);
            set_pixel(rand_x, rand_y-1, 0x0000FF00);
            set_pixel(rand_x+1, rand_y-1, 0x0000FF00);
            apple_created = 1;
        }
    }
}