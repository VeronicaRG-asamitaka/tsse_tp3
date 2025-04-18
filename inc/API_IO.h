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
#ifndef API_IO_H
#define API_IO_H
/**
 * @file API_IO.h
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

/* === Cabecera C++ ============================================================================ */

#ifdef __cplusplus
extern "C" {
#endif

/* === Public macros definitions =============================================================== */
/** @brief Puerto GPIO donde está conectado el botón de usuario*/
#define BUTTON_PORT GPIOB
/** @brief Pin GPIO donde está conectado el botón de usuario */
#define BUTTON_PIN GPIO_PIN_3
/** @brief Puerto GPIO donde está conectado el LED de debug */
#define LED_PORT GPIOC
/** @brief Pin GPIO donde está conectado el LED de debug */
#define LED_PIN GPIO_PIN_13

// En API_IO.h (preferiblemente al inicio, después de los includes)

#ifndef GPIO_PIN_SET
#define GPIO_PIN_SET   1
#define GPIO_PIN_RESET 0
#endif

/* === Public data type declarations =========================================================== */
/**
 * @enum IO_Device_t
 * @brief Dispositivos GPIO disponibles
 */
typedef enum {
    IO_BUTTON_USER, // Botón de usuario (PB10)
    IO_LED_DEBUG,   // LED de debug (PC13)
    IO_DEVICE_COUNT
} IO_Device_t;

/**
 * @enum IO_Status_t
 * @brief Resultados de operaciones GPIO
 */
typedef enum { IO_OK, IO_ERROR, IO_INVALID_DEVICE } IO_Status_t;
/* === Public variable declarations ============================================================ */

/* === Public function declarations ============================================================ */
/**
 * @brief Inicializa el módulo de GPIO
 * @note Configura el estado inicial del LED (apagado)
 */
void IO_Init(void);

/**
  * @brief Lee el estado de un dispositivo GPIO
  * @param device Dispositivo a leer
  * @param state Puntero donde se almacenará el estado leído
  * @return Resultado de la operación (IO_OK si la operación fue exitosa,
    IO_INVALID_DEVICE si el dispositivo no existe, IO_ERROR si el puntero state es NULL)
    */
IO_Status_t IO_Read(IO_Device_t device, bool * state);

/**
  * @brief Escribe un estado en un dispositivo GPIO
  * @param device Dispositivo a escribir
  * @param state Estado a escribir (true=HIGH, false=LOW)
  * @return Resultado de la operación (IO_OK si la operación fue exitosa,
    IO_INVALID_DEVICE si el dispositivo no existe)
  */
IO_Status_t IO_Write(IO_Device_t device, bool state);

/**
  * @brief Cambia el estado de un dispositivo GPIO
  * @param device Dispositivo a cambiar
  * @return Resultado de la operación(IO_OK si la operación fue exitosa,
    IO_INVALID_DEVICE si el dispositivo no existe)
  */
IO_Status_t IO_Toggle(IO_Device_t device);

#ifdef __cplusplus
}
#endif

#endif /* API_IO_H */
