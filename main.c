
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
  int nb_cuts = height / cut_size;

  printf("Loaded the sprite sheet successfully\n");
  printf("Informations : \n");
  printf("\t height : %d \n", height);
  printf("\t width : %d \n", width);
  printf("\t bpp : %d \n",bpp);
  printf("\t cut possible : %d \n", nb_cuts);

  unsigned char* tile = malloc(cut_size * cut_size * sizeof(unsigned char)*bpp);
  char name[10];
  int base = 0;


  for(int k = 0; k < nb_cuts; k++){
    for(int i = 0; i < cut_size; i++)
    {
      for(int j = base; j < base+cut_size*bpp; j++){
        *(tile + (j-base) * sizeof(unsigned char) + i * cut_size * bpp) = *(image_or + j * sizeof(unsigned char) + i * width * bpp);
      }
    }
    base = base + cut_size * bpp;
    sprintf(name,"%d",k);
    stbi_write_jpg(name,cut_size,cut_size,bpp,(void*)tile,100);
  }
  free(tile);

  /*unsigned char* recopie = malloc(height * width * sizeof(unsigned char)*bpp);
  for(int i = 0; i < height; i++)
  {
    for(int j = 0; j < width*bpp; j++){
      *(recopie + j * sizeof(unsigned char) + i * width * bpp) = *(image_or + j * sizeof(unsigned char) + i * width * bpp);
    }
  }

  unsigned char* une_ligne = malloc(width * 300 * sizeof(unsigned char)*bpp);
  for(int j = 0; j < 300; j++){
    for(int i = 0; i < width * bpp; i++)
    {
      *(une_ligne + i + j * width * bpp) = 123;
    }
  }

  stbi_write_jpg("tile.jpg",cut_size,cut_size,bpp,(void*)tile,100);
  stbi_write_jpg("recopie.jpg",width,height,bpp,(void*)recopie,100);
  stbi_write_jpg("une_ligne.jpg",width,300,bpp,(void*)une_ligne,100);*/

  //free(tile);
}
