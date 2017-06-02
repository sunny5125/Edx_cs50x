 #include <stdio.h>
#include <stdint.h>

typedef uint8_t BYTE;

int main (void){   

    FILE* rawdata = fopen("card.raw", "r");
    
    if (rawdata == NULL){
        fprintf(stderr, "Cannot create card.raw.\n");
        return 1;
    }

    FILE* output_file = NULL;
    int jpegs = 0;
    
    while (!feof(rawdata)){
        BYTE buffer[512];

        char jpegname[8];
        
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] == 0xe0 || buffer[3] == 0xe1)){
            if (output_file != NULL){
                fclose(output_file);
            }
            sprintf(jpegname, "%03d.jpg", jpegs);
            output_file = fopen(jpegname, "w");
            jpegs++;
            fwrite(buffer, sizeof(buffer), 1, output_file);
        }
        else{
            if (jpegs > 0){
                fwrite(buffer, sizeof(buffer), 1, output_file);            
            }
        }
        fread(buffer, sizeof(buffer), 1, rawdata);
        
    }
    if (jpegs > 0){
        fclose(output_file);
    }
    fclose(rawdata);

    return 0;
}
