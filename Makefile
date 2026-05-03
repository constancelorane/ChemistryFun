CFLAGS = -Wall -Wextra

SRC = main.c razbavlenie.c rastvorenie.c

# Linux
CC = gcc
OBJ = main.o razbavlenie.o rastvorenie.o
TARGET = ChemistryFun

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET)

# Windows
CC_WIN = x86_64-w64-mingw32-gcc
OBJ_WIN = main_win.o razbavlenie_win.o rastvorenie_win.o
TARGET_WIN = ChemistryFun.exe

win: $(TARGET_WIN)

$(TARGET_WIN): $(OBJ_WIN)
	$(CC_WIN) $(OBJ_WIN) -o $(TARGET_WIN)

# правила сборки
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

%_win.o: %.c
	$(CC_WIN) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o *.exe ChemistryFun