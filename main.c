#include <stdlib.h>
#include "ripes_system.h"

// Definición de una lista enlazada de nodos que almacena las coordenadas de los LEDs que forman la serpiente
struct snakeNode{
    unsigned int x;
    unsigned int y;
    struct snakeNode *next;
};
// Apuntador a la cabeza de la serpiente (el inicio de la lista enlazada)
struct snakeNode* snakeHead = NULL;
// Declaración de la función initSnake() para inicializar la serpiente en una posición específica
void initSnake(unsigned int x, unsigned int y);
// Declaración de la función increaseSnakeBody() para agregar un nuevo nodo a la serpiente
void increaseSnakeBody(unsigned int x, unsigned int y);
//Declaración de la función set_pixel() para encender un LED de una coordenada específica
void setPixel(unsigned int x, unsigned int y, unsigned int color);

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
    // Inicializamos la serpiente en la posición especificada
    initSnake(x, y);

    while(1){
        
        if(*up == 1 && key_up_pressed == 0){
            key_up_pressed = 1;
            y += 1;
        } else if(*down == 1 && key_down_pressed == 0){
            key_down_pressed = 1;
            y -= 1;
        } else if(*left == 1 && key_left_pressed == 0){
            key_left_pressed = 1;
            x -= 1;
        } else if(*right == 1 && key_right_pressed == 0){
            key_right_pressed = 1;
            x += 1;
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

// Definición de la función increaseSnakeBody()
void increaseSnakeBody(unsigned int x, unsigned int y){
    // Creamos un nuevo nodo para la serpiente
    struct snakeNode *newNode = malloc(sizeof(struct snakeNode));
    // Asignamos las coordenadas al nuevo nodo
    newNode->x = x;
    newNode->y = y;
    newNode->next = NULL;
    // Encendemos el LED en las coordenadas del nuevo nodo
    setPixel(x, y, 0x00FF0000);

    if(snakeHead == NULL){
        snakeHead = newNode;
    }else{
        // Agregamos el nuevo nodo al final de la lista enlazada
        struct snakeNode *current = snakeHead;
        while(current->next != NULL){
            current = current->next;
        }
        current->next = newNode;
    }
}

// Definición de la función initSnake()
void initSnake(unsigned int x, unsigned int y){
    increaseSnakeBody(x, y);
    increaseSnakeBody(x, y-1);
    increaseSnakeBody(x+1, y);
    increaseSnakeBody(x+1, y-1);
}

// Definición de la función set_pixel()
void setPixel(unsigned int x, unsigned int y, unsigned int color){
    // Obtenemos la dirección base de la matriz de LEDs
    unsigned int *led_base = LED_MATRIX_0_BASE;
    // Calculamos el desplazamiento en la matriz de LEDs para el LED especificado
    unsigned int offset = LED_MATRIX_0_WIDTH*((LED_MATRIX_0_HEIGHT-1)-y) + x;
    // Definimos el color del LED en la dirección obtenida por el desplazamiento
    *(led_base + offset) = color;
}