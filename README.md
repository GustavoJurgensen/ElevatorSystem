![Logo UFSC](/Imagens/brasao_CTJ.png)

### Created by:
- Paulo Henrique Alves Kammradt
- Gustavo Jurgensen
- Matheus Wilgen Gonçalves

# Trabalho Elevador
---
### O trabalho consiste na implementacão de um sistema que abstrai a funcionalidade de um elevador, o objetivo principal é aplicar o conceito de testes na implementação.
---

Tabela de conteúdos
===================
<!--ts-->
   * [Instalacao](#instalacao)
   * [Como usar](#como-usar)
      * [Pre Requisitos](#pre-requisitos)
      * [Local files](#local-files)
      * [Remote files](#remote-files)
   * [Status do Projeto](#status-do-projeto)
   * [Licenca](#licenca)
   * [Testes](#testes)
   * [Tecnologias](#tecnologias)
<!--te-->

Instalacao
==========

Linux (manual installation):

```
cd <pasta_destino>
```
```
git clone https://github.com/GustavoJurgensen/ElevatorSystem.git
```

Como usar
=========

### To COMPILE and RUN this program, simple type the command:
1. COMPILE:
```
make all
```
2. To EXECUTE the program, type the command:
```
make run
```
3. To EXECUTE tests:
```
make runTest
```
4. To CLEAN the objects in repository, type the command:
```
make clean
```
5. To CLEAN the binaries in repository, type the command:
```
make clean_bin
```
6. To CLEAN the objects and binaries in repository, type the command:
```
make clean_all
```
7. To CHECK memory leaks, type the command:
```
make valgrind
```


Pre Requisitos
--------------

Para a interface gráfica é necessário a biblioteca SFML:

```
sudo apt-get install libsfml-dev
```

Para teste é necessário a biblioteca gTest:

```
sudo apt-get install libgtest-dev
```

Status do Projeto
=================

🚀 Em construção...  🚧

Licenca
=======

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

Testes
======

Em desenvolvimento... 🚧

Tecnologias
===========

As seguintes ferramentas foram usadas na construção do projeto:
🛠 
- [SFML](https://www.sfml-dev.org/index.php)
- [C++](https://isocpp.org/std/the-standard)
