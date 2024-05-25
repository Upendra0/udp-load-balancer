EXE_PREFIX=crestel
NODE_NAME=collector_load_balancer
PACK_NAME=crestel_collector_load_balancer
VERSION=$(shell cat VERSION)
BUILD_TS=$(shell date -u +"%Y-%m-%d-%H:%M:%S-%Z")

COMPILER=gcc

C_FLAGS = -Wall
C_FLAGS += -g
C_FLAGS += -m64

INC_FLAGS = -I/usr/include
INC_FLAGS += -I/usr/include/openssl
INC_FLAGS += -I/usr/include/libxml2
INC_FLAGS += -Iinc/
INC_FLAGS += -Iinc/logger

#LIB_DIR = -L/usr/lib/x86_64-linux-gnu
LIB_DIR = -L/usr/lib64

LIB_FLAGS = -lpthread
#LIB_FLAGS += -lnsl
LIB_FLAGS += -lxml2

#SRCS=$(wildcard src/*.c)
SRCS=$(shell find . -name "*.c")
DEPS=$(SRCS:.c=.o)

.c.o:
	$(COMPILER) $(C_FLAGS) -c $< $(INC_FLAGS) $(C_DEFS) -o $@

all: $(DEPS)
	@echo "preparing installable executable.";\
	if [ ! -d "./bin" ]; then \
		mkdir ./bin ; \
	fi
	$(COMPILER) $(LNK_FLAGS) -o bin/$(EXE_PREFIX)_$(NODE_NAME) $(DEPS) $(LIB_DIR) $(LIB_FLAGS) -DVERSION=$(VERSION) -DBUILD_TS=$(BUILD_TS)

release: all
	@echo "preparing installable package [$(PACK_NAME).tar.gz]."; \
	rm -f $(PACK_NAME).tar.gz
	mkdir -p $(PACK_NAME)/bin
	mkdir -p $(PACK_NAME)/config
	cp -r ./bin/$(EXE_PREFIX)_$(NODE_NAME) ./$(PACK_NAME)/bin/
	cp -r ./cfg/*.xml ./$(PACK_NAME)/config/
	cp -r ./$(NODE_NAME).service ./$(PACK_NAME)/bin/
	tar -cvf - $(PACK_NAME) | gzip -c > $(PACK_NAME).tar.gz
	rm -rf $(PACK_NAME)

clean:
	rm -f $(DEPS)
	rm -f bin/$(EXE_PREFIX)_$(NODE_NAME)
	rm -f $(PACK_NAME).tar.gz
