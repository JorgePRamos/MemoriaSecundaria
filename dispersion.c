#include "dispersion.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// Crea un fichero hash inicialmente vacio seg�n los criterios especificados en la pr�ctica
// Primera tarea a realizar para  crear un fichero organizado mediante DISPERSI�N
void creaHvacio(char *fichHash)
{ FILE *fHash;
  tipoCubo cubo;
  int j;
  int numCubos =CUBOS+CUBOSDESBORDE;

  memset(&cubo,0,sizeof(cubo));

  fHash = fopen(fichHash,"wb");
  for (j=0;j<numCubos;j++) fwrite(&cubo,sizeof(cubo),1,fHash);
  fclose(fHash);
}
// Lee el contenido del fichero hash organizado mediante el m�todo de DISPERSI�N seg�n los criterios
// especificados en la pr�ctica. Se leen todos los cubos completos tengan registros asignados o no. La
// salida que produce esta funci�n permite visualizar el m�todo de DISPERSI�N

int leeHash(char *fichHash)
{ FILE *f;
  tipoCubo cubo;
  int j,i=0;
  size_t numLee;

   f = fopen(fichHash,"rb");
   rewind(f);
   fread(&cubo,sizeof(cubo),1,f);
   while (!feof(f)){
	for (j=0;j<C;j++) {
        if (j==0)    	printf("Cubo %2d (%2d reg. ASIGNADOS)",i,cubo.numRegAsignados);
        else  	printf("\t\t\t");
	if (j < cubo.numRegAsignados) 
		    printf("\t%s %s %s %s %s\n",
	    		cubo.reg[j].dni,
			cubo.reg[j].nombre,
			cubo.reg[j].ape1,
		  	cubo.reg[j].ape2,
  	                cubo.reg[j].provincia);
	else printf ("\n");
        }
       i++;
       fread(&cubo,sizeof(cubo),1,f);
   }
   fclose(f);
   return i;
}

int creaHash(char *fichEntrada,char *fichHash){
	FILE *fEntrada, *fHash;
	tipoAlumno reg;
	tipoCubo cubo, cuboDES;
	fpos_t pos;
	int cubos, escrito;
	int numCubo, i, numDesb=0;

	int numRegistros;
	creaHvacio("alumnos.hash");
	fEntrada= fopen(fichEntrada,"rb");
	fHash=fopen(fichHash, "r+b");

	fread(&reg,sizeof(reg), 1, fEntrada);
	while(!feof(fEntrada)){

		numCubo=atoi(reg.dni)%CUBOS;
		fseek(fHash,numCubo*sizeof(cubo),SEEK_SET);
		fread(&cubo,sizeof(cubo),1,fHash);
		i=cubo.numRegAsignados;
		if(i>=C){
			numDesb++;
			cubo.numRegAsignados++;
			cubos=desborde(fHash, &reg);			
				
		}else{
			cubo.reg[i]=reg;
			cubo.numRegAsignados++;
			}
		fseek(fHash,numCubo*sizeof(cubo),SEEK_SET);
		fwrite(&cubo, sizeof(cubo),1,fHash);

		fread(&reg,sizeof(reg),1,fEntrada);
		
	}
		fclose(fEntrada);
		fclose(fHash);
		return numDesb;
}

int desborde(FILE *fHash, tipoAlumno *reg){
		int i;
		tipoCubo cuboDES;
		fpos_t pos;
		memset(&cuboDES,0,sizeof(cuboDES));
		int cubos=CUBOS;
			
			while(cubos<CUBOS+CUBOSDESBORDE){
				fseek(fHash, cubos*sizeof(cuboDES),SEEK_SET);
				fgetpos(fHash,&pos);
				fread(&cuboDES, sizeof(cuboDES),1,fHash);
				i=cuboDES.numRegAsignados;
			if(i<C){
				cuboDES.reg[i]=*reg;
				cuboDES.numRegAsignados++;
				fsetpos(fHash,&pos);
				fwrite(&cuboDES, sizeof(cuboDES),1,fHash);
				return 1;}
			else{
				cuboDES.numRegAsignados++;
				fsetpos(fHash,&pos);
				fwrite(&cuboDES, sizeof(cuboDES),1,fHash);//Para escribir en memoria secundaria
				cubos++;}

			}
		return cuboDES.numRegAsignados++;
}
