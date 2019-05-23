//Jorge Perez Ramos
#include "dispersion.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int modificarReg(char *fichero, char *dni, char *provincia){
    FILE *f;
    tipoCubo cubo;
    int y=0,x=0;
    size_t numLee;
    int seed;
    int bloq;
    int bloqActual = 0;
    //abrirArchivoFichero
    f = fopen(fichero,"rb");
    rewind(f);
    //dni a int
    seed = atoi(dni);
    //obtenemos cubo del dato
    bloq = seed % CUBOS;
    //iniciamos lectura
    fread(&cubo,sizeof(cubo),1,f);//cargo el buffer
    while (!feof(f)){//leo hasta final fichero
    if(bloqActual==bloq){
        if(bloq<CUBOS){
            for(y = 0; y<C;y++){
                if(!strcmp(cubo.reg[y].dni, dni)){
                cubo->reg[y].provincia=provincia;//PROBLEMa
                return bloq;
                } 
            }
        }else if(bloq>=CUBOS){
            for(y = 0; y<CUBOSDESBORDE*C;y++){
                if(!strcmp(cubo.reg[y].dni, dni)){
                cubo->reg[y].provincia=provincia;//PROBLEMa
                return bloq;
                }
            }
        }
        if(cubo.numRegAsignados>C){
                bloq=CUBOS;
        }
    }
    
    bloqActual++;
    }


fclose(f);
return -1; 
}