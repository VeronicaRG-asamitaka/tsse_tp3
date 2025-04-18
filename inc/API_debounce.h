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
#ifndef API_INC_API_DEBOUNCE_H_
#define API_INC_API_DEBOUNCE_H_

/**
 * @file API_debounce.h
 * @brief Máquina de estados finitos (FSM) para antirrebote de botones
 * @date 2025
 * @author Veronica Ruíz Galván
 */

/* === Headers files inclusions ================================================================ */
#ifndef __STDINT_H_
#include <stdint.h>
#endif

#ifndef __STDBOOL_H_
#include <stdbool.h>
#endif

// #include "stm32f4xx_hal.h"
#include "API_delay.h"
#include "API_IO.h"

/* === Cabecera C++ ============================================================================ */

#ifdef __cplusplus
extern "C" {
#endif

/* === Public macros definitions =============================================================== */
/**
 * @def TIEMPO_RETARDO
 * @brief Tiempo de retardo para anti-rebote en milisegundos
 */
#define TIEMPO_RETARDO 40

/* === Public data type declarations =========================================================== */

/* === Public variable declarations ============================================================ */

/* === Public function declarations ============================================================ */

/**
 * @brief Inicializa la FSM de antirrebote
 */
void debounceFSM_Init(void);

/**
 * @brief Actualiza el estado de la FSM
 * @details Debe ser llamado periódicamente en el main loop
 */
void debounceFSM_Update(void);

/**
 * @brief Maneja el evento de botón presionado
 * @note Activa la bandera de flanco descendente y enciende el LED de depuración
 */
void button_Pressed();

/**
 * @brief Maneja el evento de botón liberado
 * @note Activa la bandera de flanco ascendente y apaga el LED de depuración
 */
void button_Released();

/**
 * @brief Verifica si hubo flanco descendente
 * @return true si se detectó flanco descendente (botón presionado)
 * @note Resetea automáticamente el estado después de leer
 */
bool_t readKeyDesc(void);

/**
 * @brief Verifica si hubo flanco ascendente
 * @return true si se detectó flanco ascendente (botón liberado)
 * @note Resetea automáticamente el estado después de leer
 */
bool_t readKeyAsc(void);

#ifdef __cplusplus
}
#endif

#endif /* API_INC_API_DEBOUNCE_H_ */
