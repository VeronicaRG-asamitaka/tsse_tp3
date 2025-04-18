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
 * @file API_debounce.c
 * @brief Máquina de estados finitos (FSM) para antirrebote de boton
 * @date 2025
 * @author Verónica Ruíz Galván
 */

/* === Headers files inclusions =============================================================== */

#include "API_debounce.h"

/* === Macros definitions ====================================================================== */

/* === Private data type declarations ========================================================== */
/* === Public variable definitions ============================================================= */

/** @brief Estados internos de la FSM */
typedef enum {
    BUTTON_UP,
    BUTTON_FALLING,
    BUTTON_DOWN,
    BUTTON_RISING,
} debounceState_t;
/* === Private variable declarations =========================================================== */

/** @brief  Estado actual de la FSM  */
static debounceState_t estadoActual;
/** @brief  Temporizador para antirrebote  */
static delay_t tiempoRetardo;
/** @brief  Flag de evento de presión  */
static bool_t keyButtonDesc;
/** @brief  Flag de evento de liberación  */
static bool_t keyButtonAsc;

/* === Private function declarations =========================================================== */

/* === Private variable definitions ============================================================ */

/* === Private function implementation ========================================================= */

/* === Public function implementation ========================================================== */

/*Se inicializa la FEM indicando el estado inicial e inicializando el delay*/
void debounceFSM_Init() {
    delayInit(&tiempoRetardo, TIEMPO_RETARDO);
    estadoActual = BUTTON_UP;
    IO_Write(IO_LED_DEBUG, false);
}

/*Contiene la trancisicion de estados en base al gráfico de transicion de estados*/
void debounceFSM_Update() {

    bool buttonState;

    switch (estadoActual) {
    case BUTTON_UP:
        IO_Read(IO_BUTTON_USER, &buttonState);
        if (buttonState) {
            estadoActual = BUTTON_FALLING;
            delayRead(&tiempoRetardo);
        }
        break;

    case BUTTON_FALLING:
        if (delayRead(&tiempoRetardo)) {

            IO_Read(IO_BUTTON_USER, &buttonState);

            if (!buttonState) {
                estadoActual = BUTTON_UP;
            }

            else {
                button_Pressed();
                estadoActual = BUTTON_DOWN;
            }
        }

        break;

    case BUTTON_DOWN:
        if (!buttonState) {
            estadoActual = BUTTON_RISING;
            delayRead(&tiempoRetardo);
        }
        break;

    case BUTTON_RISING:
        if (delayRead(&tiempoRetardo)) {

            IO_Read(IO_BUTTON_USER, &buttonState);

            if (buttonState) {
                estadoActual = BUTTON_DOWN;

            } else {
                button_Released();
                estadoActual = BUTTON_UP;
            }
        }

        break;

    default:
        estadoActual = BUTTON_UP;
    }
}

void button_Pressed() {
    keyButtonDesc = true;
    IO_Write(IO_LED_DEBUG, true);
}

void button_Released() {
    keyButtonAsc = true;
    IO_Write(IO_LED_DEBUG, false);
}

bool_t readKeyDesc() {
    if (keyButtonDesc) {
        keyButtonDesc = false;
        return true;
    }
    return false;
}

bool_t readKeyAsc() {
    if (keyButtonAsc) {
        keyButtonAsc = false;
        return true;
    }
    return false;
}
/* === End of documentation ==================================================================== */
