#ifndef __MINI_EXCEL_H__
#define __MINI_EXCEL_H__

#include <string>
#include <iomanip>
#include <sstream>
#include "Node.h"

template<typename T>
class MiniExcel {
    public:
        MiniExcel() {}

        // Método principal que inicia Mini-Excel: muestra la cuadrícula, procesa entradas del usuario, y actualiza los resultados.
        void run() {
            std::cout << "Mini-Excel Inicial:\n";
            printGrid();
            std::cout << "\nOperación (Ejemplo: C2 = A1 + A2 * B3), o 'exit' para salir:\n";

            std::string line;
            while (true) {
                std::cout << "> ";
                if(!std::getline(std::cin, line)) break;
                if (line == "exit") break;
                if (line.empty()) continue;

                processLine(line);
                printGrid();
            }
        }

    private:
        // En lugar de almacenar valores, almacenamos la expresión (nodo raíz) de cada celda.
        std::map<std::string, std::unique_ptr<Node<T>>> cellExpressions;

        bool isCellRef(const std::string &token) {
            bool letraEncontrada = false;
            bool numeroEncontrado = false;

            for (char c : token) {
                if (std::isalpha((unsigned char)c)) {
                    if (numeroEncontrado) return false;
                    letraEncontrada = true;
                } else if (std::isdigit((unsigned char)c)) {
                    numeroEncontrado = true;
                } else {
                    return false;
                }
            }
        return letraEncontrada && numeroEncontrado;
        }

        bool isNumber(const std::string &token) {
            if (token.empty()) return false;
            int pointCount = 0;
            for (char c : token) {
                if (!std::isdigit((unsigned char)c)) {
                    if (c == '.' && pointCount == 0) {
                        pointCount++;
                    } else {
                        return false;
                    }
                }
            }
            return true;
        }
        
        std::map<std::string, std::function<T(T,T)>> operators = {
            {"+", [](T a, T b){return a+b;} },
            {"-", [](T a, T b){return a-b;} },
            {"*", [](T a, T b){return a*b;} },
            {"/", [](T a, T b){return (b!=0? a/b : T());} }
        }

        // Imprime la cuadrícula actual del Mini-Excel, mostrando los valores evaluados en cada celda o espacios en blanco si están vacías.
        void printGrid() const {
            std::cout << "    ";
            for (char col='A'; col<='J'; ++col) {
                std::cout << std::setw(8)    << col;
            }
            std::cout << "\n";

            // Recorre cada fila y columna de la cuadrícula, obteniendo el valor evaluado de cada celda o dejando en blanco si no está definida.
            for (int row=1; row<=5; ++row) {
                std::cout << std::setw(4) << row;
                for (char col='A'; col<='J'; ++col) {
                    std::string cellName = std::string(1,col) + std::to_string(row);
                    auto it = cellExpressions.find(cellName);
                    if (it == cellExpressions.end() || !it->second) {
                        // Celda no establecida, imprimir en blanco
                        std::cout << std::setw(8) << " ";
                    } else {
                        T val = getCellValue(cellName);
                        std::ostringstream oss;
                        oss << val;
                        std::cout << std::setw(8) << oss.str();
                    }
                }
                std::cout << "\n\n";
            }
        }
};

#endif