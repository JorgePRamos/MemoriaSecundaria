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
    int found=0;
    //abrirArchivoFichero
    f = fopen(fichero,"rb");
    rewind(f);
    //dni a int
    seed = atoi(dni);
    //obtenemos cubo del dato
    bloq = seed % CUBOS;
    //buscamos cubo
    fseek( f, sizeof(tipoCubo)*seed, SEEK_SET );
    fread( &cubo, sizeof(tipoCubo), 1, f );

    if(cubo.numRegAsignados<=C){//no existe desborde
    for(y=0;y<C;y++){
        if(!strcmp(cubo.reg[y].dni, dni)){
            memcpy(&cubo.reg[y].provincia, provincia , sizeof(provincia));
            return bloq;
        }
    }
    return -1;//al no haber desvorde termiona la busqueda
    }else if(cubo.numRegAsignados>C){//exixte desborde

    while(found==0){
        fseek( f, sizeof(tipoCubo)*(CUBOS+x), SEEK_SET );
        fread( &cubo, sizeof(tipoCubo), 1, f );
        for(y=0;y<C;y++){
            if(!strcmp(cubo.reg[y].dni, dni)){
                memcpy(&cubo.reg[y].provincia, provincia , sizeof(provincia));
                return bloq;
            }
        }
        if(CUBOS+x>CUBOS+CUBOSDESBORDE){
            return-1;
        }
        x++;
    }

    }




fclose(f);
return 0; 
}