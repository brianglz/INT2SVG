#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include <sstream>


#include "Poligonal.h"
#include "LectorINT.h"
#include "EscalaP.hpp"
#include "SalidaSVG.hpp"
#include "GenCU.h"
#include "LectorRes.h"


#define SPATH "./salidas"

using namespace std;

/**
 *
 */
int main(int argc, char *argv[]) {

    //campos y valor para filtro
    int c1 = 0;
    int c2 = 0;
    int cv;

    //dimensiones para el mapa
    int dimx = 0;
    int dimy = 0;


    if (argc < 3) {

        cout << "Falta lista con archivo a procesar: polígonos-INT c1 c2 cv dimx dimy PATH_SALIDA RESTRICCIONES" << endl;
        return 1;
    }

    c1 = atoi(argv[2]);
    c2 = atoi(argv[3]);

    cv = atoi(argv[4]);

    dimx = atoi(argv[5]);
    dimy = atoi(argv[6]);


    //leemos el archivo INT 
    cout << "Archivo INT: " << argv[1] << endl;

    LectorINT lint(string(argv[1]), c1, c2, cv);

    cout << "Cantidad de poligonos recuperados: " << lint.vPol.size() << endl;

    //determinamos las restricciones para los poligonos solo caso municipal
    if (c1 != c2) {
        LectorRes lres(string(argv[8]), cv);
        if (lres.bposeeR) {
            cout << "Posee restricciones: " << cv << endl;

            lres.eliminaPolRes(&lint.vPol);

            cout << "Cantidad de poligonos eliminados: " << lres.numPolElim << endl;
        }
    }

    //escalamos las poligonales
    cout << "Escalamos poligonos" << endl;
    EscalaP escala(&lint.vPol, dimx, dimy);
    escala.impParametrosE(string(SPATH) + string(argv[5]) + string("/") + string(argv[4]) + string(".pesc"));


    //generamos la clave unica para poligonos
    cout << "Generamos claves unicas para poligonos" << endl;

    GenCU mgencu(string(SPATH) + string(argv[5]) + string("/") + string(argv[4]) + string(".bdrep"), c1, c2);
    mgencu.generaCUPol(&lint.vPol);
    mgencu.escribeArchivo();



    //generamos la salida
    cout << "Generamos SVG" << endl;
    SalidaSVG ssvg(string(argv[7]), cv);
    ssvg.dimX = dimx;
    ssvg.dimY = dimy;

    ssvg.imprimeSVG(lint.vPol);


    return 0;
}