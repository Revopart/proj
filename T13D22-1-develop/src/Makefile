CC=gcc
FLAGS=-Wall -Wextra  -Werror -std=c11

DATA1=cipher.c
DATA2=cipher.c logger.c

cipher: $(DATA1)
	$(CC) $(FLAGS) $^ -o ../build/cipher
	
 logging_cipher: $(DATA2)
	$(CC) $(FLAGS) $^ -DDOP -o ../build/logging_cipher


