TEMP_DIR=temp
HEAD_DIR=include
SOURCE_DIR=src

.PHONY: clean

package: size.o point.o color.o bitmap.o windowcontrol.o
	ar rcs libwc.a $(TEMP_DIR)/*.o

prepare:
ifeq ($(TEMP_DIR), $(wildcard $(TEMP_DIR)))
	echo $(TEMP_DIR) already exist.
else
	md $(TEMP_DIR)
endif

clean:
ifeq ($(TEMP_DIR), $(wildcard $(TEMP_DIR)))
	del /q /s temp
endif

test: prepare
	g++ -o $(TEMP_DIR)/main \
	-I $(HEAD_DIR) \
	-L . \
	test/main.cpp \
	-lwc -lgdi32

size.o: prepare
	g++ -c \
	-o $(TEMP_DIR)/size.o \
	-I $(HEAD_DIR) \
	$(SOURCE_DIR)/size.cpp

point.o: prepare
	g++ -c \
	-o $(TEMP_DIR)/point.o \
	-I $(HEAD_DIR) \
	$(SOURCE_DIR)/point.cpp

color.o: prepare
	g++ -c \
	-o $(TEMP_DIR)/color.o \
	-I $(HEAD_DIR) \
	$(SOURCE_DIR)/color.cpp

bitmap.o: prepare
	g++ -c \
	-o $(TEMP_DIR)/bitmap.o \
	-I $(HEAD_DIR) \
	$(SOURCE_DIR)/bitmap.cpp

windowcontrol.o: prepare
	g++ -c \
	-o $(TEMP_DIR)/windowcontrol.o \
	-I $(HEAD_DIR) \
	$(SOURCE_DIR)/windowcontrol.cpp
