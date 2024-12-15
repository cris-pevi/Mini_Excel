# Nombre del compilador
CXX = g++

# Opciones de compilación
CXXFLAGS = -std=c++17

# Archivos fuente y ejecutable
SOURCES = main.cpp test.cpp
HEADERS = test.h Mini_Excel.h Node.h
EXECUTABLE = main

# Regla por defecto
all: $(EXECUTABLE)

# Regla para compilar el ejecutable
$(EXECUTABLE): $(SOURCES) $(HEADERS)
	$(CXX) $(CXXFLAGS) -o $(EXECUTABLE) $(SOURCES)

# Regla para limpiar los archivos generados
clean:
	rm -f $(EXECUTABLE)
