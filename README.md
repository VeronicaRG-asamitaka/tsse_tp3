# Trabajo Práctico Número 3

## Descripción del proyecto

Este trabajo práctico consiste en pruebas unitarias de la implementación de una máquina de estados finitos (FSM) para el manejo del antirrebote de un botón físico (debounce) utilizando lenguaje C. Se incluye un conjunto de pruebas unitarias desarrolladas con Unity y CMock para verificar el correcto funcionamiento del sistema ante diferentes secuencias de entradas simuladas, asi como los archivos fuente necesarios.

## Uso del repositorio

Este repositorio utiliza [pre-commit](https://pre-commit.com) para validaciones de formato. Para trabajar con el mismo usted debería tener instalado:

1. pre-commit (https://pre-commit.com/#install)

Después de clonar el repositorio usted debería ejecutar el siguiente comando:

```
pre-commit install
```

Para generar la documentación del proyecto se utiliza el siguiente comando:

```
make doc

```

Para `compilar` el proyecto se utiliza el siguiente comando:

```
make all
```

## License

This work is distributed under the terms of the [MIT](https://spdx.org/licenses/MIT.html) license.
