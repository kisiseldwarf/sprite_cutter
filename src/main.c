
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#define NAME_BUF 10
#include "../lib/stb_image.h"
#include "../lib/stb_image_write.h"

int is_number(char* s)
{
  char* ptr = s;
  while(*ptr != '\0'){
    if(!isdigit(*ptr))
      return 0;
    ptr++;
  }

  return 1;
}

int usage()
{
  printf("Usage : ./sprite_cutter [Source Sheet] [Sprite size]\n");
  printf("\t Source sheet : The sprite sheet to cut from, an jpg or png file.\n");
  printf("\t Sprite size : The size of the sprites to be cut from the source sheet, usually a power of 2. In pixels.\n");
}

int main(int argc, char* argv[]){
  //load an image
  int width, height, bpp;

  if(argc < 2){
    usage();
    return 1;
  }

  unsigned char* image_or = stbi_load(argv[1],&width,&height,&bpp,0);
  if(image_or == NULL){
    printf("Failed to load the sprite sheet.\n");
    return 1;
  }

  if(argv[2] == NULL){
    usage();
    return 3;
  }

  if(!is_number(argv[2])){
    usage();
    return 2;
  }

  int cut_size = atoi(argv[2]);
  int surface = width * height;
  int nb_cuts = surface / (cut_size * cut_size);
  int nb_col = width / cut_size;
  int nb_row = height / cut_size;

  if(cut_size > width || cut_size > height){
    printf("Sprite size is too big for the source sheet.\n");
    return 3;
  }

  printf("Loaded the sprite sheet successfully\n");
  printf("Informations : \n");
  printf("\t height : %d \n", height);
  printf("\t width : %d \n", width);
  printf("\t bpp : %d \n",bpp);
  printf("\t sprites possible : %d \n", nb_cuts);
  printf("\t number of columns : %d \n", nb_col);
  printf("\t number of rows : %d \n", nb_row);

  unsigned char* tile = malloc(cut_size * cut_size * sizeof(unsigned char)*bpp);
  char name[NAME_BUF];
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
      sprintf(name,"%d-%d.png",l,k);
      stbi_write_png(name,cut_size,cut_size,bpp,(void*)tile,cut_size*bpp);
    }
    base_k = 0;
    base_l = base_l + cut_size;
  }
  free(tile);

  printf("Done ! The sprites are in the directory you called sprite_cutter. \n");
}
