<div align="center">
  <h1>simple_pow_miner_architecture</h1>
  <p><i>Simulación multiproceso y multihilo de minería Proof of Work (PoW) en C</i></p>
</div>

<br>

## Descripción

[cite_start]Desarrollada en C bajo el estándar POSIX que emula el comportamiento de una red de minería de bloques inspirada en la tecnología Blockchain. [cite_start]El sistema resuelve retos matemáticos y criptográficos (Proof of Work) mediante fuerza bruta, distribuyendo la carga de trabajo de forma eficiente[cite: 1002, 1004].

[cite_start]La arquitectura de la aplicación se basa en un modelo **multiproceso** y **multihilo**[cite: 1013]:
- [cite_start]Un proceso **Minero** que divide el espacio de búsqueda entre múltiples hilos paralelos[cite: 1031].
- [cite_start]Un proceso **Registrador (Log)** que escucha asíncronamente a través de una tubería (*pipe*) y persiste los bloques validados en disco[cite: 1041, 1042].

<br>

## ✨ Características Principales

- [cite_start]**Concurrencia escalable**: Uso de la librería `pthread` para dividir el espacio de búsqueda matemático equitativamente entre los hilos asignados[cite: 1034].
- [cite_start]**Comunicación Inter-procesos (IPC)**: Sincronización y paso de mensajes entre el minero y el registrador mediante el uso de tuberías unidireccionales[cite: 1042].
- [cite_start]**Gestión segura de memoria**: Código robusto frente a fugas de memoria (*memory leaks*) y procesos huérfanos, verificable a través de Valgrind.
- [cite_start]**Persistencia de Datos**: Generación automática de archivos de registro (`.log`) estructurados que detallan cada ronda, tiempos, votos y el identificador del ganador.

<br>

## 🚀 Compilación y Uso

[cite_start]El proyecto incluye un `Makefile` preconfigurado para automatizar la compilación, la ejecución y las pruebas del sistema.

### Compilar el proyecto
Para generar el ejecutable, simplemente sitúate en la raíz del proyecto y ejecuta:
```bash
make
