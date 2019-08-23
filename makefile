# Project: cg20192

CPP      = "$(MGW)\bin\g++.exe" -D__DEBUG__
CC       = "$(MGW)\bin\g++.exe" -D__DEBUG__
WINDRES  = windres.exe
OBJ      = build//main.o build//glad.o build//callbacks.o build//renderLoop.o build//globals.o build//shaders.o build//objLoader.o
LINKOBJ  = build//main.o build//glad.o build//callbacks.o build//renderLoop.o build//globals.o build//shaders.o build//objLoader.o
LIBS     = -L"$(MGW)/lib" -L"$(MGW)/x86_64-w64-mingw32/lib" -static-libgcc -L"external/glfw/lib/" -lglu32 -lopengl32 -lglfw3dll -g3
INCS     = -I"$(MGW)/include" -I"$(MGW)/x86_64-w64-mingw32/include" -I"$(MGW)/lib/gcc/x86_64-w64-mingw32/4.9.2/include" -I"external/glad/include/" -I"external/glfw/include/" -I"external/glm/include/"
CXXINCS  = -I"$(MGW)/include" -I"$(MGW)/x86_64-w64-mingw32/include" -I"$(MGW)/lib/gcc/x86_64-w64-mingw32/4.9.2/include" -I"$(MGW)/lib/gcc/x86_64-w64-mingw32/4.9.2/include/c++" -I"external/glad/include/" -I"external/glfw/include/" -I"external/glm/include/"
BIN      = build/cg20192.exe
CXXFLAGS = $(CXXINCS) -g3 -std=c++11 -DGLM_ENABLE_EXPERIMENTAL
CFLAGS   = $(INCS) -g3
RM       = rm.exe -f

.PHONY: all all-before all-after clean clean-custom

all: all-before $(BIN) all-after

clean: clean-custom
	${RM} $(OBJ) $(BIN)

$(BIN): $(OBJ)
	$(CPP) $(LINKOBJ) -o $(BIN) $(LIBS)

build//main.o: src/main.cpp
	$(CPP) -c src/main.cpp -o build//main.o $(CXXFLAGS)

build//glad.o: external/glad/src/glad.cpp
	$(CPP) -c external/glad/src/glad.cpp -o build//glad.o $(CXXFLAGS)

build//callbacks.o: src/callbacks.cpp
	$(CPP) -c src/callbacks.cpp -o build//callbacks.o $(CXXFLAGS)

build//renderLoop.o: src/renderLoop.cpp
	$(CPP) -c src/renderLoop.cpp -o build//renderLoop.o $(CXXFLAGS)

build//globals.o: src/globals.cpp
	$(CPP) -c src/globals.cpp -o build//globals.o $(CXXFLAGS)

build//shaders.o: src/shaders.cpp
	$(CPP) -c src/shaders.cpp -o build//shaders.o $(CXXFLAGS)

build//objLoader.o: src/objLoader.cpp
	$(CPP) -c src/objLoader.cpp -o build//objLoader.o $(CXXFLAGS)
