//Jorge Perez Ramos
#include "dispersion.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int modificarReg(char *fichero, char *dni, char *provincia){
    FILE *f;
    tipoCubo cubo;
    int y=0,x=0,bloqActual=0,found=0;
    int seed;
    int bloq;
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
    for(y=0;y<C;y++){
        if(!strcmp(cubo.reg[y].dni, dni)){
            memcpy(&cubo.reg[y].provincia, provincia , sizeof(provincia));
            fclose(f);
            return bloq;
        }
    }
    if(cubo.numRegAsignados>C){//exixte desborde
        while(found==0){
            fseek( f, sizeof(tipoCubo)*(CUBOS+x), SEEK_SET );
            fread( &cubo, sizeof(tipoCubo), 1, f );
            for(y=0;y<C;y++){
                if(!strcmp(cubo.reg[y].dni, dni)){
                    memcpy(&cubo.reg[y].provincia, provincia , sizeof(provincia));
                    fclose(f);
                    return bloq;
                }
            }
            if(cubo.numRegAsignados<=C ) break;//No hay más desborde.

            if(CUBOS+x>CUBOS+CUBOSDESBORDE){
                fclose(f);
                return-1;
            }
            x++;
        }
    }
fclose(f);
return -1; //al no haber desvorde termiona la busqueda sin exito
}