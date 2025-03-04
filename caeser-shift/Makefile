CC = gcc
CFLAGS = -Wall -Wextra -std=c11
TARGET = main
SRC = main.c

# Check for OpenSSL include and library paths
OPENSSL_INCLUDE ?= $(shell pkg-config --cflags openssl)
OPENSSL_LIBS ?= $(shell pkg-config --libs openssl)

# If pkg-config is not available, set default paths
ifeq ($(OPENSSL_INCLUDE),)
	OPENSSL_INCLUDE = -I/usr/local/include
endif

ifeq ($(OPENSSL_LIBS),)
	OPENSSL_LIBS = -L/usr/local/lib -lssl -lcrypto
endif

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(OPENSSL_INCLUDE) -o $(TARGET) $(SRC) $(OPENSSL_LIBS)

clean:
	rm -f $(TARGET)
