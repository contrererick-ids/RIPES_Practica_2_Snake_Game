# Snake Game — RIPES Simulator (Computer Architecture Project)

Este proyecto consiste en la implementación del clásico juego **Snake** utilizando el simulador **RIPES**, como parte de la asignatura *Organización y Arquitectura de Computadoras*. El objetivo principal es **medir el impacto en el rendimiento (performance)** bajo diferentes configuraciones de **memoria caché**.

## 🎯 Objetivo

Desarrollar una versión del juego Snake en lenguaje C, ejecutado sobre RIPES, utilizando:

- **LED Matrix 0** como pantalla de visualización.
- **D-Pad 0** como control de entrada.
- **Switch 0** para reiniciar el juego tras una colisión.

Además del desarrollo funcional del juego, se evaluará el **hit rate** de distintas configuraciones de memoria caché para analizar su impacto en el desempeño del programa.

## 🕹️ Reglas del juego

- El jugador controla una **serpiente de color rojo**, inicialmente de tamaño 2×2 (4 LEDs).
- Las **manzanas** están representadas por 4 LEDs verdes (2×2).
- Al comer una manzana, la serpiente **incrementa su tamaño** a 2×4 LEDs.
- No se contabilizan puntos.
- El juego finaliza si la serpiente colisiona consigo misma o con los bordes.
- El juego puede reiniciarse con **Switch 0**.

## ⚙️ Consideraciones técnicas

- Uso de periféricos: `LED_MATRIX_0_BASE`, `D_PAD_0_*`, y `SWITCHES`.
- Código en lenguaje C compatible con la plataforma del simulador RIPES.
- El comportamiento visual y lógico depende de controladores definidos en `ripes_system.h`.

## 🧪 Pruebas de configuración de caché

Durante la ejecución del juego, se medirá el **hit rate** bajo las siguientes configuraciones de caché:

1. Mapeo directo, 4 líneas
2. Asociativa de 2 conjuntos, 2 vías
3. Totalmente asociativa, 4 vías
4. Mapeo directo, 16 líneas
5. Asociativa de 4 conjuntos, 4 vías
6. Totalmente asociativa, 16 vías

### Preguntas a responder

- ¿Cuál es el hit rate en cada configuración?
- ¿Cuál configuración tiene el mejor rendimiento?

## 📄 Entregables

- Implementación funcional del juego en lenguaje C.
- Capturas de pantalla y diagramas de flujo.
- Reporte con análisis de resultados y conclusiones individuales.
