# SEyTR · Primer proyecto

Proyecto de ejemplo de **Sistemas Empotrados y de Tiempo Real**. Se usa en las
sesiones **U1-S4** y **U1-S5**: en la primera lo clonas, lo compilas y lo grabas
en tu placa; en la segunda lo abres por dentro.

No hace falta cuenta ni permisos para clonarlo: el repositorio es público.

## Qué hace

Recorre una serie de lecturas de distancia y publica por el monitor serie un
resumen de cada ventana de lecturas —mínimo, media y máximo—, avisando cuando
el mínimo baja de un umbral.

**Aquí no hay ningún sensor.** Las lecturas están escritas dentro del programa.
Sirven para tener algo que contar mientras aprendes a manejar el proyecto; los
sensores llegan en la unidad 2.

## Qué necesitas antes

El entorno instalado y verificado con la guía de instalación de la asignatura,
la placa y su cable USB de datos. Nada más.

## Cómo obtenerlo

Clona el repositorio en una carpeta de tu equipo con una ruta **corta y sin
espacios ni tildes**, y abre en el editor la carpeta que contiene el
`CMakeLists.txt` de la raíz. Si abres una carpeta por encima o por debajo, el
entorno no reconoce el proyecto y el error no te dirá eso.

## Qué deberías ver

Primero, tres líneas de presentación: quién firma el programa, cuántas lecturas
trae y con qué ventana y umbral, y sobre qué chip está corriendo —destino,
número de núcleos y revisión del silicio—. Esa última línea es útil: el destino
lo fija `sdkconfig.defaults` y los núcleos y la revisión los cuenta el propio
chip, así que si no coinciden es que se está grabando otra cosa.

Después, con la configuración de partida, cuatro resúmenes separados por una
pausa, y un aviso en el último porque la distancia mínima baja del umbral. Al
final, una línea diciendo que no quedan lecturas.

Si el monitor muestra texto ilegible, mira la velocidad del puerto. Si dice que
no encuentra la placa, empieza siempre por el puerto.

## Qué puedes cambiar sin tocar el código

En la configuración del proyecto, en el menú **«SEyTR - Primer proyecto»**,
que aparece arriba del todo:

| Opción | Qué hace |
| --- | --- |
| Lecturas por ventana | Cuántas lecturas entran en cada resumen |
| Tiempo entre resúmenes | La pausa entre uno y el siguiente |
| Umbral de aviso | A partir de qué distancia avisa |
| Provocar un fallo al terminar | Hace que el chip imprima un volcado de fallo, para practicar su lectura |

Las opciones de registro vienen preparadas para que las trazas de depuración y
verbosas **existan** en la imagen aunque no se vean. Para que aparezcan basta
con subir el nivel por omisión en la configuración: no hay que escribir ni una
traza nueva. Lo que queda por encima del nivel máximo, en cambio, se descarta al
compilar y no hay forma de hacerlo aparecer después.

## Estructura

```
CMakeLists.txt          define el proyecto
sdkconfig.defaults      configuración de partida; se escribe a mano y se versiona
main/
  CMakeLists.txt        registra las fuentes del componente principal
  Kconfig.projbuild     las opciones de la tabla de arriba
  primer_proyecto.c     el programa
components/
  estadistica/          componente propio: cuentas sobre las lecturas
```

Dos ficheros que **no** se versionan y que por eso no están aquí: `sdkconfig`,
que genera la herramienta a partir de `sdkconfig.defaults`, y la carpeta
`build/`. Se guarda en el repositorio lo que escribe una persona, no lo que
genera una herramienta.

## Un aviso

Este repositorio es material de la asignatura. El repositorio de tu **proyecto
final** es otro distinto, con su propio nombre y sus propias reglas, y llega más
adelante en el curso.
