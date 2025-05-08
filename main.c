#include <stdlib.h>
#include "ripes_system.h"

//Declaración de la función set_pixel() para encender un LED de una coordenada específica
void set_pixel(unsigned int x, unsigned int y, unsigned int color);
//Declaración de la función clear_screen() para apagar el LED de una coordenada específica
void clean_screen(unsigned int x, unsigned int y);
//Declaración de la función create_snake() para crear la serpiente mediante un matriz de LEDs
void create_snake(unsigned int x, unsigned int y);
//Declaración de la función create_apple() para crear una manzana en la matriz
void create_apple();

void main(){
    //D_PAD_0_UP es igual a 0xf0000db0
    unsigned int *up = D_PAD_0_UP;
    //D_PAD_0_DOWN es igual a 0xf0000db4
    unsigned int *down = D_PAD_0_DOWN;
    //D_PAD_0_LEFT es igual a 0xf0000db8
    unsigned int *left = D_PAD_0_LEFT;
    //D_PAD_0_RIGHT es igual a 0xf0000dbc
    unsigned int *right = D_PAD_0_RIGHT;
    // Flag para saber si se presionó la tecla arriba
    unsigned int key_up_pressed = 0;
    // Flag para saber si se presionó la tecla abajo
    unsigned int key_down_pressed = 0;
    // Flag para saber si se presionó la tecla izquierda
    unsigned int key_left_pressed = 0;
    // Flag para saber si se presionó la tecla derecha
    unsigned int key_right_pressed = 0;
    // Coordenada en x para el LED inicial
    unsigned int x = 17;
    // Coordenada en y para el LED inicial
    unsigned int y = 12;
    
    //Llamamos clean_screen() para apagar todos los LEDs
    clean_screen();
    //Llamamos create_snake() para crear la serpiente inicial en la posición x, y
    create_snake(x, y);
    //Llamamos create_apple() para crear la manzana inicial de forma aleatoria
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

// Definición de la función set_pixel()
void set_pixel(unsigned int x, unsigned int y, unsigned int color){
    // Obtenemos la dirección base de la matriz de LEDs
    unsigned int *led_base = LED_MATRIX_0_BASE;
    // Calculamos el desplazamiento en la matriz de LEDs para el LED especificado
    unsigned int offset = LED_MATRIX_0_WIDTH*((LED_MATRIX_0_HEIGHT-1)-y) + x;
    // Definimos el color del LED en la dirección obtenida por el desplazamiento
    *(led_base + offset) = color;
}

// Definición de la función clean_screen()
void clean_screen(unsigned int x, unsigned int y){
    // Apagamos el LED en la posición especificada
    set_pixel(x, y, 0x0);
}

// Definición de la función create_snake()
void create_snake(unsigned int x, unsigned int y){
    // Encendemos los LEDs en las posiciones especificadas
    set_pixel(x, y, 0x00FF0000);
    set_pixel(x+1, y, 0x00FF0000);
    set_pixel(x, y-1, 0x00FF0000);
    set_pixel(x+1, y-1, 0x00FF0000);

}

// Definición de la función check_color() para verificar si un LED está encendido
int check_color(unsigned int x, unsigned int y){
    unsigned int *led_base = LED_MATRIX_0_BASE;
    unsigned int offset = LED_MATRIX_0_WIDTH*((LED_MATRIX_0_HEIGHT-1)-y) + x;
    // Si el LED está encendido con cualquier color diferente a 0x0, retornamos 1
    if(*(led_base + offset) != 0x0){
        return 1;
    }
    // En caso contrario, retornamos 0
    return 0;
}

// Definición de la función create_apple() para crear una manzana en la matriz de LEDs
void create_apple(){
    // Definimos un flag para saber si la manzana ya fue creada
    int apple_created = 0;
    
    // Mientras el flag sea 0, creamos coordenadas aleatorias para la manzana y validamos si es posibel crearla en esa posición
    while(apple_created != 1){
        // Generamos una coordenada x aleatoria entre 0 y el ancho de la matriz
        int rand_x = rand() % (LED_MATRIX_0_WIDTH + 1);
        // Generamos una coordenada y aleatoria entre 0 y el alto de la matriz
        int rand_y = rand() % (LED_MATRIX_0_HEIGHT + 1);
        // Validamos si los LEDs en las coordenadas generadas son válidos para crear la manzana
        int valid_led_1 = check_color(rand_x, rand_y);
        int valid_led_2 = check_color(rand_x+1, rand_y);
        int valid_led_3 = check_color(rand_x, rand_y-1);
        int valid_led_4 = check_color(rand_x+1, rand_y-1);
        // Si todas las posiciones son válidas, creamos la manzana en esas coordenadas y cambiamos el flag a 1
        if(valid_led_1 == 0 && valid_led_2 == 0 && valid_led_3 == 0 && valid_led_4 == 0){
            set_pixel(rand_x, rand_y, 0x0000FF00);
            set_pixel(rand_x+1, rand_y, 0x0000FF00);
            set_pixel(rand_x, rand_y-1, 0x0000FF00);
            set_pixel(rand_x+1, rand_y-1, 0x0000FF00);
            apple_created = 1;
        }
    }
}