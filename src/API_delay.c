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
/**
 * @file API_delay.c
 * @brief Implementación del módulo para manejo de retardos no bloqueantes
 * @date 2025
 * @author Verónica Ruíz Galván
 */

/* === Headers files inclusions =============================================================== */
#include "API_delay.h"

/* === Macros definitions ====================================================================== */
/** @brief Valor máximo permitido para un retardo */
#define DELAY_MAX 2000

/** @brief Valor mínimo permitido para un retardo */
#define DELAY_MIN 50
/* === Private data type declarations ========================================================== */

/* === Private variable declarations =========================================================== */

/* === Private function declarations =========================================================== */

/**
 * @brief Verifica y ajusta la duración del retardo a los límites permitidos
 * @param duration Duración solicitada del retardo
 * @return Duración ajustada dentro de los límites permitidos
 */
static tick_t checkDuration(tick_t duration);

/* === Public variable definitions ============================================================= */

/* === Private variable definitions ============================================================ */

/* === Private function implementation ========================================================= */
static tick_t checkDuration(tick_t duration) {
    if (DELAY_MAX < duration) {
        return DELAY_MAX;
    } else if (DELAY_MIN > duration) {
        return DELAY_MIN;
    } else {
        return duration;
    }
}
/* === Public function implementation ========================================================== */

void delayInit(delay_t * delay, tick_t duration) {
    /*asigna en delay.duracion la duracion definida despues de revisar el rango
    con la funcion checkDuration*/

    delay->duration = checkDuration(duration);

    delay->running = false; // asigna en delay.running "falso"
}

// Funcion de delayRead con retorno de dato tipo bool_t (bool)
bool_t delayRead(delay_t * delay) {

    /*verifica el estado de delay.running
    si delay.running es falso, empieza conteo y cambia su estado a verdadero*/
    if (delay->running == false) {
        delay->startTime = HAL_GetTick();
        delay->running = true;

    }
    /*si delay.running es verdadero, revisa si se ha alcanzado el periodo designado
    si se alcanzó, retorna "verdadero", y delay.running cambia a "falso";
    en caso contrario, retorna "falso"*/
    else {
        if ((HAL_GetTick() - delay->startTime) >= delay->duration) {
            delay->running = false;
            return true;
        }
    }

    return false;
}

// Funcion de delayWrite sin retorno
void delayWrite(delay_t * delay, tick_t duration) {
    /*Asigna un valor de duracion existente despues de revisar el rango
    con la funcion checkDuration*/
    delay->duration = checkDuration(duration);
}
/* === End of documentation ==================================================================== */
