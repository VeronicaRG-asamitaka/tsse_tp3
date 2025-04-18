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
 * @file test_API_debounce.c
 * @brief Pruebas unitarias para la librería de API_debounce
 */

/*
1. Inicialización: FSM inicia en BUTTON_UP con flags en false.
2. Pulsación válida: transición completa UP → FALLING → DOWN con LED encendido.
3. Liberación válida: transición completa DOWN → RISING → UP con LED apagado.
4. Rebotes en pulsación: la FSM descarta cambios bruscos durante FALLING.
5. Rebotes en liberación: la FSM descarta cambios bruscos durante RISING.
*/

/* === Headers files inclusions =============================================================== */
#include "unity.h"
#include "mock_API_delay.h"
#include "mock_API_IO.h"
#include "API_debounce.h"

/* === Macros definitions ====================================================================== */

/* === Private data type declarations ========================================================== */

/* === Private variable declarations =========================================================== */

/* === Private function declarations =========================================================== */

/* === Public variable definitions ============================================================= */

/* === Private variable definitions ============================================================ */

/* === Private function implementation ========================================================= */

/* === Public function implementation ========================================================== */

void setUp(void) {

    delayInit_Ignore();
    // Inicializa el FSM de debounce antes de cada test.
    debounceFSM_Init();

    // Inicializa el LED en estado apagado al principio de cada test.
    IO_Write_ExpectAndReturn(IO_LED_DEBUG, false, IO_OK);
}

void test_LED_enciende_con_pulsacion_estable(void) {
    bool btn_state;

    btn_state = true; // Simula que el botón está presionado.

    // Ignoramos la llamada a delayInit() para evitar conflictos en la simulación.
    delayInit_Ignore();

    // Esperamos que delayInit sea llamado una vez, solo al principio
    delayInit_Expect(NULL, TIEMPO_RETARDO);

    // Primera comprobación de la lectura del botón.
    IO_Read_ExpectAndReturn(IO_BUTTON_USER, &btn_state, IO_OK);
    IO_Read_ReturnThruPtr_state(&btn_state);

    // El primer delayRead devuelve verdadero (para simular que pasó el tiempo necesario).
    delayRead_ExpectAndReturn(NULL, true);

    // Segunda comprobación de la lectura del botón.
    IO_Read_ExpectAndReturn(IO_BUTTON_USER, &btn_state, IO_OK);
    IO_Read_ReturnThruPtr_state(&btn_state);

    // Se espera que la función IO_Write encienda el LED.
    IO_Write_ExpectAndReturn(IO_LED_DEBUG, true, IO_OK);

    // Llamadas a debounceFSM_Update para simular el flujo del programa.
    debounceFSM_Update();
    debounceFSM_Update();
}

/* === End of documentation ==================================================================== */
