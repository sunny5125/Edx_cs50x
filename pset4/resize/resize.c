#include <stdio.h>
#include <stdlib.h>
#include "bmp.h"

int main(int argc, char* argv[]){
    if (argc != 4){
        printf("Usage: copy infile outfile\n");
        return 1;
    }

    int multiplier = atoi(argv[1]);
    
    if (multiplier > 100 || multiplier <= 0){
        printf("Number must be positive and less than 100");
    }

    char* infile = argv[2];
    char* outfile = argv[3];

    FILE* input_file = fopen(infile, "r");
    if (input_file == NULL){
        printf("Cannot open %s.\n", infile);
        return 2;
    }

    FILE* output_file = fopen(outfile, "w");
    if (output_file == NULL){
        fclose(input_file);
        fprintf(stderr, "Cannot create %s.\n", outfile);
        return 3;
    }

    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, input_file);

    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, input_file);

    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || 
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(output_file);
        fclose(input_file);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }

    int old_width = bi.biWidth;
    int old_height = bi.biHeight;
    bi.biWidth = old_width * multiplier;
    bi.biHeight = old_height * multiplier;

    int old_padding = (4 - (old_width * sizeof(RGBTRIPLE)) % 4) % 4;
    int padding =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    bi.biSizeImage = (bi.biWidth * sizeof(RGBTRIPLE) + padding) * abs(bi.biHeight);
    bf.bfSize = (bi.biSizeImage) + 54; 

    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, output_file);

    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, output_file);
    int old_height2 = abs(old_height);
        
    for (int i = 0; i < old_height2; i++){
        for (int l = 0; l < multiplier; l++){   
            fseek(input_file, (54 + ((old_width*3 + old_padding) * i)), SEEK_SET);
            for (int j = 0; j < old_width; j++){
                RGBTRIPLE triple;

                fread(&triple, sizeof(RGBTRIPLE), 1, input_file);

                for (int k = 0; k < multiplier; k++)
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, output_file);                   
            }
            for (int m = 0; m < padding; m++)
                fputc(0x00, output_file);
        }
    }
    fclose(input_file);

    fclose(output_file);
    return 0;
}
