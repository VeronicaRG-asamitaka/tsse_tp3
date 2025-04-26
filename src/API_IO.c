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
 * @file API_IO.c
 * @brief Máquina de estados finitos (FSM) para antirrebote de boton
 * @date 2025
 * @author Verónica Ruíz Galván
 */

/* === Headers files inclusions =============================================================== */

#include "API_IO.h"
#include "main.h"

/* === Macros definitions ====================================================================== */

/* === Private data type declarations ========================================================== */

/* === Private variable declarations =========================================================== */

/**
 * @struct io_mapping
 * @brief Mapeo de dispositivos io a pines físicos
 */
static const struct {
    GPIO_TypeDef * port;
    uint16_t pin;
} io_mapping[IO_DEVICE_COUNT] = {
    [IO_BUTTON_USER] = {BUTTON_PORT, BUTTON_PIN}, [IO_LED_DEBUG] = {LED_PORT, LED_PIN}};

/* === Private function declarations =========================================================== */

/* === Public variable definitions ============================================================= */

/* === Private variable definitions ============================================================ */

/* === Private function implementation ========================================================= */

/* === Public function implementation ========================================================== */
void IO_Init(void) {

    /* Estado inicial del LED (apagado) */
    IO_Write(IO_LED_DEBUG, false);
}

IO_Status_t IO_Read(IO_Device_t device, bool * state) {
    if (device >= IO_DEVICE_COUNT)
        return IO_INVALID_DEVICE;

    if (state == NULL)
        return IO_ERROR;

    *state = (HAL_GPIO_ReadPin(io_mapping[device].port, io_mapping[device].pin) == GPIO_PIN_SET);
    return IO_OK;
}

IO_Status_t IO_Write(IO_Device_t device, bool state) {
    if (device >= IO_DEVICE_COUNT)
        return IO_INVALID_DEVICE;

    HAL_GPIO_WritePin(io_mapping[device].port, io_mapping[device].pin,
                      state ? GPIO_PIN_SET : GPIO_PIN_RESET);
    return IO_OK;
}

IO_Status_t IO_Toggle(IO_Device_t device) {
    if (device >= IO_DEVICE_COUNT)
        return IO_INVALID_DEVICE;

    HAL_GPIO_TogglePin(io_mapping[device].port, io_mapping[device].pin);
    return IO_OK;
}

/* === End of documentation ==================================================================== */
