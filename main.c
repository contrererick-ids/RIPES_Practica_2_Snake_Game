#include <stdlib.h>                    // Librería estándar: funciones rand(), exit()

#ifndef RIPES_IO_HEADER               // Evita múltiples inclusiones del header
#define RIPES_IO_HEADER

// *****************************************************************************
// * Definiciones para el D-Pad (botones dirección)
// *****************************************************************************
#define D_PAD_0_BASE	(0xf0000db0)  // Dirección base memoria para el D-pad
#define D_PAD_0_SIZE	(0x10)        // Tamaño del periférico (no usado aquí)
#define D_PAD_0_UP_OFFSET	(0x0)     // Offset para botón arriba
#define D_PAD_0_UP	(0xf0000db0)     // Dirección botón arriba
#define D_PAD_0_DOWN_OFFSET	(0x4)   // Offset para botón abajo
#define D_PAD_0_DOWN	(0xf0000db4)   // Dirección botón abajo
#define D_PAD_0_LEFT_OFFSET	(0x8)   // Offset para botón izquierda
#define D_PAD_0_LEFT	(0xf0000db8)   // Dirección botón izquierda
#define D_PAD_0_RIGHT_OFFSET	(0xc)  // Offset para botón derecha
#define D_PAD_0_RIGHT	(0xf0000dbc)  // Dirección botón derecha

// *****************************************************************************
// * Definiciones para la matriz LED
// *****************************************************************************
#define LED_MATRIX_0_BASE	(0xf0000000) // Dirección base memoria matriz LED
#define LED_MATRIX_0_SIZE	(0xdac)      // Tamaño matriz (no usado)
#define LED_MATRIX_0_WIDTH	(0x23)       // Ancho matriz (35 decimal)
#define LED_MATRIX_0_HEIGHT	(0x19)       // Alto matriz (25 decimal)

// *****************************************************************************
// * Definiciones para los switches
// *****************************************************************************
#define SWITCHES_0_BASE	(0xf0000dac)   // Dirección base memoria switches
#define SWITCHES_0_SIZE	(0x4)          // Tamaño switches (no usado)
#define SWITCHES_0_N	(0x8)          // Número de switches (8)

#endif // RIPES_IO_HEADER

// Definiciones del tamaño de la matriz en píxeles (para lógica del juego)
#define HEIGHT 25                      // Alto matriz LED
#define WIDTH 35                       // Ancho matriz LED

// Constantes para las direcciones del movimiento
#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3

// Punteros para acceder a memoria mapeada del hardware
int *mled;           // Puntero a matriz LED
int *dpad;           // Puntero a D-pad (botones dirección)
int *switches;       // Puntero a switches (interruptores físicos)

// Arrays para las posiciones X y Y de la serpiente (máx 100 segmentos)
int snakeX[100];
int snakeY[100];
int snakeLength = 1; // Longitud inicial

// Posición de la manzana
int appleX = 0;
int appleY = 0;

// Dirección actual de movimiento; -1 = sin movimiento
int direction = -1;

// Prototipos de funciones
void startGame();                  // Dibuja serpiente y manzana en la matriz LED
void moveSnake(int d);             // Actualiza posición serpiente según dirección
void randomApple();                // Genera posición aleatoria para la manzana

// Función para detectar si dos bloques 2x2 se superponen (colisión)
int blocksOverlap(int x1, int y1, int x2, int y2) {
    // Recorrer todos los píxeles del primer bloque (4 en total)
    for (int dx1 = 0; dx1 <= 1; dx1++) {
        for (int dy1 = 0; dy1 <= 1; dy1++) {
            int px1 = (x1 + dx1) % WIDTH;    // Posición X del pixel del bloque 1 (con wrap-around)
            int py1 = (y1 + dy1) % HEIGHT;   // Posición Y del pixel del bloque 1

            // Recorrer todos los píxeles del segundo bloque (4 en total)
            for (int dx2 = 0; dx2 <= 1; dx2++) {
                for (int dy2 = 0; dy2 <= 1; dy2++) {
                    int px2 = (x2 + dx2) % WIDTH;   // Posición X del pixel bloque 2
                    int py2 = (y2 + dy2) % HEIGHT;  // Posición Y del pixel bloque 2

                    // Si alguna posición coincide, los bloques se superponen
                    if (px1 == px2 && py1 == py2) {
                        return 1;  // Colisión detectada
                    }
                }
            }
        }
    }
    return 0;  // No hay colisión
}

void main(){
    mled = LED_MATRIX_0_BASE;    // Inicializa puntero a matriz LED
    dpad = D_PAD_0_BASE;         // Inicializa puntero a D-pad
    switches = SWITCHES_0_BASE;  // Inicializa puntero a switches

    // Apaga todos los LEDs al iniciar (limpia la pantalla)
    for (int i = 0; i < WIDTH * HEIGHT; i++) {
        mled[i] = 0;
    }

    // Posición inicial de la serpiente (puedes ajustar si quieres)
    snakeX[0] = WIDTH / 2;
    snakeY[0] = HEIGHT / 2;

    startGame();    // Dibuja serpiente y manzana iniciales
    randomApple();  // Coloca manzana en posición aleatoria

    while(1){       // Bucle principal del juego
        // Detecta si switch 0 está encendido (bit 0 del registro switches)
        if ((*switches & 0x1) == 1) {
            // Limpia matriz LED
            for (int i = 0; i < WIDTH * HEIGHT; i++) {
                mled[i] = 0;
            }
            // Reinicia variables del juego
            snakeLength = 1;
            direction = -1;
            snakeX[0] = WIDTH / 2;
            snakeY[0] = HEIGHT / 2;

            randomApple();   // Nueva posición para la manzana
            startGame();     // Dibuja estado inicial
        }

        // Lee input del D-pad para actualizar dirección
        if (*dpad) {
            direction = UP;
        } else if (*(dpad + 1)) {
            direction = DOWN;
        } else if (*(dpad + 2)) {
            direction = LEFT;
        } else if (*(dpad + 3)) {
            direction = RIGHT;
        }

        // Mueve la serpiente en la dirección actual
        moveSnake(direction);
    }
}

// Función que dibuja serpiente y manzana en la matriz LED
void startGame(){
    int tempMatrix[WIDTH * HEIGHT];  // Matriz temporal para preparar el dibujo

    // Apaga todos los píxeles en la matriz temporal
    for (int i = 0; i < WIDTH * HEIGHT; i++) {
        tempMatrix[i] = 0;
    }

    // Dibuja cada segmento de la serpiente (bloques 2x2 en rojo)
    for (int i = 0; i < snakeLength; i++) {
        tempMatrix[snakeY[i] * WIDTH + snakeX[i]] = 0xFF0000;                              // arriba-izquierda
        tempMatrix[snakeY[i] * WIDTH + (snakeX[i] + 1) % WIDTH] = 0xFF0000;               // arriba-derecha
        tempMatrix[((snakeY[i] + 1) % HEIGHT) * WIDTH + snakeX[i]] = 0xFF0000;             // abajo-izquierda
        tempMatrix[((snakeY[i] + 1) % HEIGHT) * WIDTH + (snakeX[i] + 1) % WIDTH] = 0xFF0000; // abajo-derecha
    }

    // Dibuja la manzana (bloque 2x2 en verde)
    tempMatrix[appleY * WIDTH + appleX] = 0x00FF00;
    tempMatrix[appleY * WIDTH + (appleX + 1) % WIDTH] = 0x00FF00;
    tempMatrix[((appleY + 1) % HEIGHT) * WIDTH + appleX] = 0x00FF00;
    tempMatrix[((appleY + 1) % HEIGHT) * WIDTH + (appleX + 1) % WIDTH] = 0x00FF00;

    // Copia matriz temporal a matriz real para actualizar pantalla
    for (int i = 0; i < WIDTH * HEIGHT; i++) {
        *(mled + i) = tempMatrix[i];
    }
}

// Función para mover la serpiente según dirección
void moveSnake(int direction){
    // Mueve el cuerpo: cada segmento copia posición del anterior
    for (int i = snakeLength - 1; i > 0; i--) {
        snakeX[i] = snakeX[i - 1];
        snakeY[i] = snakeY[i - 1];
    }

    // Actualiza posición cabeza según dirección, con wrap-around
    switch (direction) {
        case UP:
            snakeY[0] = (snakeY[0] - 1 + HEIGHT) % HEIGHT;
            break;
        case DOWN:
            snakeY[0] = (snakeY[0] + 1) % HEIGHT;
            break;
        case LEFT:
            snakeX[0] = (snakeX[0] - 1 + WIDTH) % WIDTH;
            break;
        case RIGHT:
            snakeX[0] = (snakeX[0] + 1) % WIDTH;
            break;
        default:
            break;
    }
    // Validación para colisiones de la serpiente contra los bordes del tablero
    if(snakeX[0] < 0 || snakeX[0] >= WIDTH - 1 || snakeY[0] < 0 || snakeY[0] >= HEIGHT - 1){
        exit(0);
    }

    // Verifica colisión cabeza contra cuerpo (fin juego)
    for (int i = 1; i < snakeLength; i++){
        if (snakeX[0] == snakeX[i] && snakeY[0] == snakeY[i]){
            exit(0);
        }
    }

    // Verifica colisión cabeza contra manzana (bloques 2x2)
    if(blocksOverlap(snakeX[0], snakeY[0], appleX, appleY)){
        snakeLength += 2;    // Crece la serpiente
        randomApple();       // Nueva manzana
    }

    startGame();            // Actualiza pantalla
}

// Función para generar manzana en posición válida (sin superponer serpiente)
void randomApple(){
    int valid = 0;
    while(!valid){
        valid = 1;
        appleX = rand() % WIDTH;    // Posición aleatoria X
        appleY = rand() % HEIGHT;   // Posición aleatoria Y

        // Verifica que la manzana no esté encima de la serpiente
        for (int i = 0; i < snakeLength; ++i) {
            if (blocksOverlap(appleX, appleY, snakeX[i], snakeY[i])){
                valid = 0;           // Si colisiona, genera otra posición
                break;
            }
        }
    }
}