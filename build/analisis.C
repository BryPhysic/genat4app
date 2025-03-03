#include <TFile.h>
#include <iostream>

void explorar() {
    // 1️⃣ Abrir el archivo ROOT
    TFile *file = TFile::Open("output.root");
    if (!file || file->IsZombie()) {
        std::cerr << "Error al abrir el archivo ROOT.\n";
        return;
    }

    // 2️⃣ Listar el contenido del archivo
    std::cout << "Contenido del archivo ROOT:\n";
    file->ls();  // Lista los objetos dentro del archivo

    // 3️⃣ Cerrar el archivo
    file->Close();
}
