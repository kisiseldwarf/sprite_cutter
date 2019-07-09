
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image.h"
#include "stb_image_write.h"

int main(int argc, char* argv[]){
  //load an image
  int width, height, bpp;
  unsigned char* image_or = stbi_load(argv[1],&width,&height,&bpp,0);
  if(image_or == NULL){
    printf("Failed to load the sprite\n");
    return 1;
  }

  int cut_size = atoi(argv[2]);
  int surface = width * height;
  int nb_cuts = surface / (cut_size * cut_size);
  int nb_col = width / cut_size;
  int nb_row = height / cut_size;

  printf("Loaded the sprite sheet successfully\n");
  printf("Informations : \n");
  printf("\t height : %d \n", height);
  printf("\t width : %d \n", width);
  printf("\t bpp : %d \n",bpp);
  printf("\t cut possible : %d \n", nb_cuts);
  printf("\t number of columns : %d \n", nb_col);
  printf("\t number of rows : %d \n", nb_row);

  unsigned char* tile = malloc(cut_size * cut_size * sizeof(unsigned char)*bpp);
  char name[10];
  int base_k = 0;
  int base_l = 0;

  for(int l = 0; l < nb_row; l++){

    //cut an entire row of sprites
    for(int k = 0; k < nb_col; k++){

      //cut a single sprite
      for(int i = base_l; i < base_l+cut_size; i++)
      {
        for(int j = base_k; j < base_k+cut_size*bpp; j++){
          *(tile + (j-base_k) * sizeof(unsigned char) + (i-base_l) * cut_size * bpp) = *(image_or + j * sizeof(unsigned char) + i * width * bpp);
        }
      }
      base_k = base_k + cut_size * bpp;
      sprintf(name,"%d-%d.jpg",l,k);
      stbi_write_jpg(name,cut_size,cut_size,bpp,(void*)tile,100);
    }
    base_k = 0;
    base_l = base_l + cut_size;
  }
  free(tile);

  printf("Done ! The sprites are in the directory you called sprite_cutter. \n");
}
