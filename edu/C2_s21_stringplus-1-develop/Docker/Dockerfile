FROM ubuntu:latest

# Установка необходимых пакетов
RUN apt-get update && apt-get install -y \
    gcc \
    g++ \
    make \
    valgrind \
    check \
    && rm -rf /var/lib/apt/lists/*

# Установка рабочей директории
WORKDIR /project

# Копирование файлов проекта в контейнер
# Это можно настроить позже, в зависимости от вашей структуры проекта
COPY . /project

# Команда по умолчанию: запуск bash
CMD ["bash"]