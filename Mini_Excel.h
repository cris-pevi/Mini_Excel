#ifndef __MINI_EXCEL_H__
#define __MINI_EXCEL_H__

#include <iostream>
#include "Node.h"

template<typename T>
class MiniExcel {
    public:
        MiniExcel() {}

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

        std::map<std::string, std::function<T(T,T)>> operators = {
            {"+", [](T a, T b){return a+b;} },
            {"-", [](T a, T b){return a-b;} },
            {"*", [](T a, T b){return a*b;} },
            {"/", [](T a, T b){return (b!=0? a/b : T());} }
        };
};

#endif