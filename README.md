# Estructuras de Datos

Repositorio con las implementaciones en C++ de los distintos **Tipos Abstractos de Datos (TAD)** que voy desarrollando en la asignatura **Estructuras de Datos** (curso 2026-2027).

Cada TAD está en un único fichero de cabecera (`.h`) con su especificación algebraica, la declaración de la clase y la implementación. Las operaciones documentan su precondición, postcondición y coste.

## TADs incluidos

| TAD | Fichero | Implementación | Genérico |
|---|---|---|---|
| Números complejos | [`Complejo.h`](Complejo.h) | Dos campos `float` (parte real e imaginaria) | No |
| Conjuntos finitos | [`Conjunto.h`](Conjunto.h) | Array ordenado sin repeticiones (máx. 100 elementos) | Sí (`TCjto<TElem>`) |
| Pilas | [`pila_dinamica.h`](pila_dinamica.h) | Lista enlazada con punteros | Sí (`TPila<TElem>`) |
| Colas | [`cola_dinamica_1.h`](cola_dinamica_1.h) | Lista enlazada con punteros al primero y al último | Sí (`TColaDinamica<TElem>`) |

## Operaciones por TAD

### Complejos (`MiComplejo`)

Constructoras `MiComplejo()` y `MiComplejo(re, im)`, consultoras `re()` e `im()`, y las operaciones `suma`, `resta`, `producto`, `modulo`, `conjugado`, `iguales`, `operator==`, `operator=` y `mostrar`.

### Conjuntos (`TCjto<TElem>`)

| Operación | Descripción | Coste |
|---|---|---|
| `esVacio()` | Determina si el conjunto está vacío | O(1) |
| `pon(x)` | Añade `x` al conjunto | O(n) |
| `quita(x)` | Elimina `x` del conjunto | O(n) |
| `pertenece(x)` | Determina si `x` está en el conjunto (búsqueda binaria) | O(log n) |
| `esLleno()` | Determina si el conjunto tiene `longMax` elementos | O(1) |
| `diferencia(c)` | Devuelve la diferencia de dos conjuntos | O(n²) |
| `escribe(salida)` | Escribe el contenido del conjunto | O(n) |

### Pilas (`TPila<TElem>`)

| Operación | Descripción | Coste |
|---|---|---|
| `apila(x)` / `desapila()` | Añade / quita el elemento de la cima | O(1) |
| `cima()` | Devuelve el elemento de la cima | O(1) |
| `fondo()` | Devuelve el elemento del fondo | O(n) |
| `esVacio()` | Determina si la pila está vacía | O(1) |
| `inversa()` | Invierte la pila | O(n) |
| `duplicar()` | Duplica cada elemento de la pila | O(n) |
| `concatenar(p)` | Coloca los elementos de `p` sobre la pila | O(n) |
| `entremezclar(p)` | Entremezcla la pila con `p` | O(máx{n, m}) |
| `borrar()` | Vacía la pila | O(n) |
| `escribe()` | Escribe el contenido de la pila | O(n) |

### Colas (`TColaDinamica<TElem>`)

| Operación | Descripción | Coste |
|---|---|---|
| `ponDetras(x)` | Añade `x` al final de la cola | O(1) |
| `quitaPrim()` | Elimina el primer elemento | O(1) |
| `primero()` | Devuelve el primer elemento | O(1) |
| `esVacio()` | Determina si la cola está vacía | O(1) |
| `divide(pares, impares)` | Reparte los elementos en dos colas según su posición (par / impar) | O(n) |
| `colapsar()` | Sustituye cada tramo separado por ceros por la suma de sus elementos | O(n) |
| `escribe()` | Escribe el contenido de la cola | O(n) |

Las operaciones que acceden a una estructura vacía lanzan o deben lanzar la excepción `EAccesoIndebido`.

## Ejemplos de uso

```cpp
#include "Complejo.h"

int main() {
    MiComplejo a(1, 2), b(3, 4);
    a.suma(b);        // a = 4 + 6i
    a.mostrar();
    cout << a.modulo() << endl;
}
```

```cpp
#include "Conjunto.h"

int main() {
    TCjto<int> a, b;
    a.pon(1); a.pon(2); a.pon(3);
    b.pon(2);

    TCjto<int> d = a.diferencia(b);   // {1, 3}
    cout << d << endl;
}
```

```cpp
#include "pila_dinamica.h"

int main() {
    TPila<int> p;
    p.apila(1); p.apila(2); p.apila(3);
    p.inversa();
    p.escribe();      // 1 2 3
}
```

```cpp
#include "cola_dinamica_1.h"

int main() {
    TColaDinamica<int> c, pares, impares;
    for (int i = 1; i <= 6; i++) c.ponDetras(i);

    c.divide(pares, impares);
    pares.escribe();    // 1, 3, 5
    impares.escribe();  // 2, 4, 6
}
```

## Compilación

Todos los TADs son cabeceras, así que basta con incluirlas desde tu `main.cpp`:

```bash
g++ -std=c++11 -Wall main.cpp -o main
./main
```

## Estructura del repositorio

```
.
├── Complejo.h
├── Conjunto.h
├── pila_dinamica.h
├── cola_dinamica_1.h
└── README.md
```

## Notas y limitaciones conocidas

- `pila_dinamica.h` y `cola_dinamica_1.h` definen ambos la clase `EAccesoIndebido`, por lo que no se pueden incluir a la vez en el mismo fichero sin antes extraerla a una cabecera común.
- `Conjunto.h` y `Complejo.h` no tienen guardas de inclusión (`#ifndef`), y `Conjunto.h` define una función no plantilla (`error`), por lo que solo deben incluirse una vez por unidad de compilación.
- Las pilas no tienen destructora automática: hay que llamar a `borrar()` para liberar la memoria.

Estructuras de Datos, curso 2026-2027, Universidad Complutense de Madrid.
