#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct node{

    struct node* father;
    int height;
    uint32_t contagious;
    uint32_t x;
    uint32_t y;

} node;

node* initNode(uint32_t x, uint32_t y){

    node* main = (node*)malloc(sizeof(node));
    main->father = main;
    main->height = 0;
    main->contagious = 0;
    main->x = x;
    main->y = y;

    return main;

}

uint32_t myrand(){

    static uint32_t next = 1;
    next = next * 1103515245 + 12345;
    return next;

}

uint32_t propagation(uint32_t x){

    return x + (-1 + myrand() % 3);

}

int main(int argc, char const *argv[])
{
    
    FILE* input = fopen(argv[1], "r");
	FILE* output = fopen(argv[2], "w");

    uint32_t numbRegion = 0, width = 0, height = 0, x = 0, y = 0;
    
    fscanf(input, "%d", &numbRegion);

    for(int i = 0; i < numbRegion; i++){

        fscanf(input, "%d %d %d %d", &width, &height, &x, &y);
        
        uint32_t xR = x;
        uint32_t yR = y;

        node*** region = (node***)malloc(width*sizeof(node**));

        for(int z = 0; z < width; z++){
            region[z] = (node**)malloc(height*sizeof(node*));
            for(int x = 0; x < height; x++){
                region[z][x] = (node*)malloc(sizeof(node));
                region[z][x] = initNode(z,x);
            }
        }

        region[x][y]->contagious = 1;

        fprintf(output,"%d:", i+1);
        fprintf(output,"(%d,%d);", region[x][y]->x, region[x][y]->y);

        for(int i = 0; i < (width*height) - 1; i++){
           
            while(1){
                
                x = propagation(xR);
                while(x >= width){
                    x = propagation(xR);
                }
                

                y = propagation(yR);
                while(y >= height){
                    y = propagation(yR);
                }

                if(region[x][y]->contagious == 0){
                    xR = x;
                    yR = y;
                    break;
                }
                else if(region[x][y]->contagious == 1){
                    xR = x;
                    yR = y;
                }
            }
            region[x][y]->contagious = 1;
            if(i+1 == width*height - 1){
                fprintf(output,"(%d,%d)", region[x][y]->x, region[x][y]->y); 
            }
            else{
                fprintf(output,"(%d,%d);", region[x][y]->x, region[x][y]->y); 
            }
        }
        fprintf(output,"\n");
        
    }

    fclose(input);
	fclose(output);

    return 0;
}
