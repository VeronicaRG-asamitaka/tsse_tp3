/************************************************************************************************
Copyright (c) 2025, Veronica Ruiz Galvan <veronica.ruizgalvan@hotmail.com>

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and
associated documentation files (the "Software"), to deal in the Software without restriction,
including without limitation the rights to use, copy, modify, merge, publish, distribute,
sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial
portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT
NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES
OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

SPDX-License-Identifier: MIT
*************************************************************************************************/

#ifndef API_INC_API_DELAY_H_
#define API_INC_API_DELAY_H_

/**
 * @file API_delay.h
 * @brief Módulo para manejo de retardos no bloqueantes
 * @date 2025
 * @author Verónica Ruíz Galván
 */

/* === Headers files inclusions ================================================================ */
#ifndef __STDINT_H_
#include <stdint.h>
#endif

#ifndef __STDBOOL_H_
#include <stdbool.h>
#endif

/* === Cabecera C++ ============================================================================ */

#ifdef __cplusplus
extern "C" {
#endif

/* === Public macros definitions =============================================================== */

/* === Public data type declarations =========================================================== */
/**
 * @typedef tick_t
 * @brief Tipo de dato para el manejo de ticks (milisegundos)
 */
typedef uint32_t tick_t;

/**
 * @typedef bool_t
 * @brief Tipo de dato booleano para compatibilidad
 */
typedef bool bool_t;

/**
 * @struct delay_t
 * @brief Estructura para el manejo de retardos
 */
typedef struct {
    tick_t startTime;
    tick_t duration;
    bool_t running;
} delay_t;

/* === Public variable declarations ============================================================ */

/* === Public function declarations ============================================================ */
/**
 * @brief Inicializa una estructura de retardo
 * @param delay Puntero a la estructura delay_t a inicializar
 * @param duration Duración del retardo en milisegundos
 * @note La estructura se inicializa en estado "no running"
 */
void delayInit(delay_t * delay, tick_t duration);

/**
 * @brief Verifica si ha terminado el retardo
 * @param delay Puntero a la estructura delay_t a verificar
 * @return true si el retardo ha terminado, false en caso contrario
 * @note Si el retardo no estaba corriendo, lo inicia automáticamente
 */
bool_t delayRead(delay_t * delay);

/**
 * @brief Cambia la duración de un retardo existente
 * @param delay Puntero a la estructura delay_t a modificar
 * @param duration Nueva duración del retardo en milisegundos
 */
void delayWrite(delay_t * delay, tick_t duration);

#ifdef __cplusplus
}
#endif

/** @} Final de la definición del modulo para doxygen */

#endif /* API_INC_API_DELAY_H_ */
