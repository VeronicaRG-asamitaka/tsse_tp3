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
#define MAX_LECTURAS              10
#define INDICE_INICIAL_LECTURA    0
#define CONTEO_INICIAL_ESCRITURAS 0

/* === Private data type declarations ========================================================== */

/* === Private variable declarations =========================================================== */
static int conteo_escrituras = CONTEO_INICIAL_ESCRITURAS;
static bool ultimo_estado_led = false;

static bool lecturas_boton[MAX_LECTURAS];
static int indice_lectura = INDICE_INICIAL_LECTURA;

/* === Private function declarations =========================================================== */

/* === Public variable definitions ============================================================= */

/* === Private variable definitions ============================================================ */

/* === Private function implementation ========================================================= */

/* === Public function implementation ========================================================== */

//! * @brief Carga una secuencia de lecturas de botón para simular en el test.
void simular_lecturas(bool * secuencia, int cantidad) {
    TEST_ASSERT_LESS_OR_EQUAL(MAX_LECTURAS, cantidad);
    memcpy(lecturas_boton, secuencia, cantidad * sizeof(bool));
    indice_lectura = INDICE_INICIAL_LECTURA;
}

//! * @brief Ejecuta la función debounceFSM_Update() la cantidad de veces especificada.
void realizar_actualizaciones(int cantidad) {
    for (int i = 0; i < cantidad; i++) {
        debounceFSM_Update();
    }
}

/* === Public function for Callcack ============================================================ */
//! * @brief Callback simulado que registra el número de escrituras y el último estado del LED.
void IO_Write_Callback(IO_Device_t device, bool state) {
    if (device == IO_LED_DEBUG) {
        conteo_escrituras++;
        ultimo_estado_led = state;
    }
}

//! * @brief Función fake que simula lecturas del botón desde una secuencia predefinida.
bool IO_Read_Fake(IO_Device_t device, bool * state) {
    if (indice_lectura < sizeof(lecturas_boton) / sizeof(lecturas_boton[INDICE_INICIAL_LECTURA])) {
        *state = lecturas_boton[indice_lectura++];
        return IO_OK;
    } else {
        *state = false;
        return IO_OK;
    }
}

void setUp(void) {
    conteo_escrituras = CONTEO_INICIAL_ESCRITURAS;
    ultimo_estado_led = false;
    indice_lectura = INDICE_INICIAL_LECTURA;

    IO_Write_StubWithCallback(IO_Write_Callback);
    IO_Read_StubWithCallback(IO_Read_Fake);

    delayInit_Ignore();
    delayRead_IgnoreAndReturn(true);
}

//! * @test 1. El LED se enciende correctamente al detectar una pulsación estable del botón.
// Llamadas  Entrada  Acción esperada
// 1         false    BUTTON_UP (estado inicial)
// 2         true     BUTTON_FALLING
// 3         true     BUTTON_DOWN (enciende LED)
void test_LED_enciende_con_pulsacion_estable(void) {

    bool secuencia[] = {false, true, true};
    simular_lecturas(secuencia, 3);

    debounceFSM_Init();

    realizar_actualizaciones(3);

    // Se verifica que se llamó a IO_Write 2 veces: (false en Init y true al presionar)
    TEST_ASSERT_EQUAL(2, conteo_escrituras);

    // Verificamos que el LED esté encendido
    TEST_ASSERT_TRUE(ultimo_estado_led);
}

//! * @test 2. El LED se apaga correctamente al soltar el botón después de una pulsación.
// Llamadas  Entrada  Acción esperada
// 1         false    BUTTON_UP (estado inicial)
// 2         true     BUTTON_FALLING
// 3         true     BUTTON_DOWN (enciende LED)
// 4         false    BUTTON_RISING
// 5         false    BUTTON_UP (apaga LED)
void test_LED_se_apaga_al_soltar_boton(void) {

    bool secuencia[] = {false, true, true, false, false};
    simular_lecturas(secuencia, 5);

    debounceFSM_Init();

    realizar_actualizaciones(5);

    TEST_ASSERT_EQUAL(3, conteo_escrituras);
    TEST_ASSERT_FALSE(ultimo_estado_led);
}

//! * @test 3. El estado del LED no cambia si el botón permanece sin cambios.
// Llamadas  Entrada  Acción esperada
// 1         false    BUTTON_UP (estado inicial)
// 2         false    BUTTON_UP
// 3         false    BUTTON_UP (sin cambios en el estado del LED)
void test_LED_no_cambia_si_estado_del_boton_no_cambia(void) {

    bool secuencia[] = {false, false, false};
    simular_lecturas(secuencia, 3);

    debounceFSM_Init();

    realizar_actualizaciones(3);

    TEST_ASSERT_EQUAL(1, conteo_escrituras); // Solo el Init
    TEST_ASSERT_FALSE(ultimo_estado_led);
}

//! * @test 4. El LED no se enciende si hay rebote en la señal del botón.
// Llamadas  Entrada  Acción esperada
// 1         false    BUTTON_UP (estado inicial)
// 2         true     BUTTON_FALLING
// 3         false    BUTTON_UP (rebote detectado)
// 4         false    BUTTON_UP (no se enciende el LED)
void test_LED_no_enciende_si_hay_rebote(void) {

    bool secuencia[] = {false, true, false, false};
    simular_lecturas(secuencia, 4);

    debounceFSM_Init();

    realizar_actualizaciones(4);

    TEST_ASSERT_EQUAL(1, conteo_escrituras); // Solo el init
    TEST_ASSERT_FALSE(ultimo_estado_led);
}

//! * @test 5. El LED se activa solo una vez por cada pulsación completa del botón.
// Llamadas  Entrada  Acción esperada
// 1         false    BUTTON_UP (estado inicial)
// 2         true     BUTTON_FALLING
// 3         true     BUTTON_DOWN (enciende LED)
// 4         true     BUTTON_DOWN
// 5         true     BUTTON_DOWN
// 6         false    BUTTON_RISING
// 7         false    BUTTON_UP (apaga LED)
void test_LED_solo_se_activa_una_vez_por_pulsacion(void) {

    bool secuencia[] = {false, true, true, true, true, false, false};
    simular_lecturas(secuencia, 7);

    debounceFSM_Init();

    realizar_actualizaciones(7);

    // LED se enciende al presionar (una vez), se apaga al soltar (una vez)
    TEST_ASSERT_EQUAL(3, conteo_escrituras);
    TEST_ASSERT_FALSE(ultimo_estado_led);
}

/* === End of documentation ==================================================================== */
