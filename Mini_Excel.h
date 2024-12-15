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

        void run() {
            // // Ejecuta el bucle interactivo para procesar operaciones y actualizar la cuadrícula de Mini-Excel.
            //std::cout << "Mini-Excel Inicial:\n";
            printGrid();
            std::cout << "\nOperación (Ejemplo: C2 = A1 + B1), o 'exit' para salir:\n";

            std::string line;
            while (true) {
                std::cout << ">>> ";
                if (!std::getline(std::cin, line)) break;
                if (line == "exit") break;
                if (line.empty()) continue;
                processLine(line);
                printGrid();
            }
        }

    private:
        // // Mapa que almacena las expresiones de cada celda, asociando el nombre de la celda con su nodo raíz.
        std::map<std::string, std::unique_ptr<Node<T>>> cellExpressions;

        // Procesa una línea de entrada y actualiza el mapa de expresiones de celdas.
        void processLine(const std::string &line) {
            // Parsear una asignación básica: "C2 = A1 + B1"
            size_t eqPos = line.find('=');
            if (eqPos == std::string::npos) return;

            std::string cellName = trim(line.substr(0, eqPos));
            std::string expression = trim(line.substr(eqPos + 1));

            // Procesar expresión (ej: "A1 + B1" o "10 + 20")
            size_t opPos = expression.find_first_of("+-*/");
            if (opPos != std::string::npos) {
                std::string left = trim(expression.substr(0, opPos));
                std::string right = trim(expression.substr(opPos + 1));
                char op = expression[opPos];

                auto leftNode = createNode(left);
                auto rightNode = createNode(right);

                if (leftNode && rightNode) {
                    cellExpressions[cellName] = std::make_unique<OpNode<T>>(
                        std::move(leftNode),
                        std::move(rightNode),
                        operators[std::string(1, op)]
                    );
                }
            } else {
                // Asignar un número o una referencia directa a celda
                cellExpressions[cellName] = createNode(expression);
            }
        }

        // Crea un nodo (NumberNode o CellNode) según el token proporcionado.
        std::unique_ptr<Node<T>> createNode(const std::string &token) {
            if (isNumber(token)) {
                return std::make_unique<NumberNode<T>>(std::stod(token));
            } else if (isCellRef(token)) {
                return std::make_unique<CellNode<T>>(token);
            }
            return nullptr;
        }

        // Verifica si el token es una referencia válida a una celda (ej: "A1").
        bool isCellRef(const std::string &token) {
            return !token.empty() && std::isalpha(token[0]) && std::isdigit(token[1]);
        }

        // Verifica si el token es un número válido (ej: "123" o "45.67").
        bool isNumber(const std::string &token) {
            try {
                std::stod(token);
                return true;
            } catch (...) {
                return false;
            }
        }

        // Elimina los espacios en blanco al inicio y al final de una cadena.
        std::string trim(const std::string &str) {
            size_t start = str.find_first_not_of(" ");
            size_t end = str.find_last_not_of(" ");
            return (start == std::string::npos) ? "" : str.substr(start, end - start + 1);
        }

        // Mapa que asocia operadores matemáticos con sus funciones correspondientes.
        std::map<std::string, std::function<T(T, T)>> operators = {
            {"+", [](T a, T b) { return a + b; }},
            {"-", [](T a, T b) { return a - b; }},
            {"*", [](T a, T b) { return a * b; }},
            {"/", [](T a, T b) { return (b != 0 ? a / b : T()); }}
        };

        // Imprime la cuadrícula del Mini-Excel mostrando los valores evaluados de cada celda.
        void printGrid() const {
            std::cout << "    ";
            for (char col = 'A'; col <= 'I'; ++col) {
                std::cout << std::setw(8) << col;
            }
            std::cout << "\n";

            for (int row = 1; row <= 5; ++row) {
                std::cout << std::setw(4) << row;
                for (char col = 'A'; col <= 'I'; ++col) {
                    std::string cellName = std::string(1, col) + std::to_string(row);
                    auto it = cellExpressions.find(cellName);
                    if (it == cellExpressions.end() || !it->second) {
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

        // Obtiene el valor evaluado de una celda, o un valor por defecto si la celda está vacía.
        T getCellValue(const std::string &cellName) const {
            auto it = cellExpressions.find(cellName);
            if (it != cellExpressions.end() && it->second) {
                return it->second->evaluate(cellExpressions);
            }
            return T();
        }
};

#endif