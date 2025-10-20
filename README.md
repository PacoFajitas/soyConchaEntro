# 🐚 Minishell

![C](https://img.shields.io/badge/C-00599C?style=for-the-badge&logo=c&logoColor=white)
![GNU Bash](https://img.shields.io/badge/Bash-4EAA25?style=for-the-badge&logo=gnu-bash&logoColor=white)
![Makefile](https://img.shields.io/badge/Makefile-1E90FF?style=for-the-badge)
![Linux](https://img.shields.io/badge/Linux-FCC624?style=for-the-badge&logo=linux&logoColor=black)

---

## 🇪🇸 Descripción

**Minishell** es un pequeño intérprete de comandos escrito en C, inspirado en **bash**.  
El objetivo del proyecto es recrear una shell básica capaz de ejecutar comandos, gestionar procesos, y manejar redirecciones y pipes, todo con el mínimo uso de librerías externas.  

> 🧠 Proyecto realizado en el marco de la escuela **42**, enfocado en la gestión de memoria, señales y procesos.

---

## ✨ Funcionalidades principales

- 💬 **Prompt interactivo** que espera comandos del usuario.  
- 🧩 **Ejecución de programas** (comandos del PATH o con ruta absoluta).  
- 🚀 **Comandos built-in** como:
  - `echo`  
  - `cd`  
  - `pwd`  
  - `export`  
  - `unset`  
  - `env`  
  - `exit`
- 🔁 **Pipes** (`|`) para conectar comandos entre sí.  
- 📂 **Redirecciones** (`>`, `<`, `>>`, `<<`) con manejo de errores.  
- ⚙️ **Variables de entorno** y expansión de `$`.  
- 😶‍🌫️ **Gestión de señales** (`Ctrl+C`, `Ctrl+D`, `Ctrl+\`) al estilo bash.  
- ❌ **Detección de errores** sintácticos y retorno de códigos de estado.  

---

## 🧱 Tecnologías

| Tecnología | Uso |
|-------------|-----|
| 🧠 **C** | Lenguaje principal del proyecto |
| 🐧 **Linux** | Entorno de desarrollo y ejecución |
| ⚙️ **Makefile** | Compilación automatizada |
| 🐚 **Bash** | Shell de referencia para comparación de comportamiento |

---

## 🇬🇧 Description

**Minishell** is a small command-line interpreter written in **C**, inspired by **bash**.  
Its goal is to replicate essential shell behavior — executing commands, handling redirections and pipes, and managing signals — using minimal external libraries.

> 🧠 A **42 School** project focused on process management, signals, and memory handling.

---

## ✨ Main Features

- 💬 **Interactive prompt** that waits for user input.  
- 🧩 **Program execution** (PATH commands or absolute paths).  
- 🚀 **Built-in commands**:
  - `echo`  
  - `cd`  
  - `pwd`  
  - `export`  
  - `unset`  
  - `env`  
  - `exit`
- 🔁 **Pipes** (`|`) for command chaining.  
- 📂 **Redirections** (`>`, `<`, `>>`, `<<`) with error handling.  
- ⚙️ **Environment variable expansion** with `$`.  
- 😶‍🌫️ **Signal handling** (`Ctrl+C`, `Ctrl+D`, `Ctrl+\`) like in bash.  
- ❌ **Error detection** and correct exit status codes.  

---

## 🧱 Technologies

| Technology | Usage |
|-------------|-------|
| 🧠 **C** | Core programming language |
| 🐧 **Linux** | Development & runtime environment |
| ⚙️ **Makefile** | Build automation |
| 🐚 **Bash** | Behavior reference shell |

