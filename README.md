# sysutil

Консольная утилита на C. Разбирает аргументы и печатает:
- `-u, --users` — список пользователей и их домашние каталоги (из `/etc/passwd`, по алфавиту)
- `-p, --processes` — запущенные процессы (из `/proc`, PID + имя, по PID)
- `-l PATH, --log PATH` — перенаправить **stdout** в файл `PATH`
- `-e PATH, --errors PATH` — перенаправить **stderr** в файл `PATH`
- `-h, --help` — справка

## Сборка (CMake)
```bash
mkdir -p build && cd build
cmake .. -G "MinGW Makefiles"        # в MSYS2 UCRT64
cmake --build .

## Примеры
./sysutil -u
./sysutil -p | head
./sysutil -u -l users.txt
./sysutil -p -e errs.txt

## PS
Работает в Linux/WSL/MSYS2 (использует /etc/passwd и /proc).
