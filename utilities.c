#include "header.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// global constants
const char *prefix_title = ":RT:--    ";
const char *prefix_body = ":-----       ";
const char *plane_key[6] = {"NEAR","LEFT","RIGHT","BOTTOM","TOP"}; 
const char *res_key = "RES";
const char *sphere_key = "SPHERE";
const char *light_key = "LIGHT";
const char *background_key = "BACK";
const char *ambient_key = "AMBIENT";
const char *output_key = "OUTPUT";

// structs
struct Sphere {
    char name[20+1];
    float position[3];
    float scale[3];
    float color[3];
    float whatever[4];
    int specular_exponent; 
};

struct Light {
    char name[20+1];
    float position[3];
    float intensity[3];
};

void druck(char *string){
    char *prefix_title = ":RT:--    ";
    printf("%s%s\n", prefix_title, string);
}


int processFile(char *filename){
    FILE* file;
    int i;

    file = fopen(filename, "r");

    if (NULL == file) {
        printf("%sProblem with file [%s], cannot be opened.\n", prefix_title, filename);
        exit(0);
    }

    printf("%sFile Contents:\n",prefix_title);

    char *line = NULL;
    size_t len = 0;

    char *token;
    const char space[2] = " ";
    const char newline[2] = "\n";

    float planes[5];
    int res[2];
    struct Sphere spheres[15];
    int numSpheres = 0;
    struct Light lights[10];
    int numLights = 0;
    float background_color[3]; // [r,g,b] each between 0,1
    float ambient[3];
    char *out_filename;

    int key_found;

    while (getline(&line, &len, file) != -1) {
        key_found = 0;

        token = strtok(line, space);

        for(i=0;i<5;i++){
            if(!key_found && !strcmp(token,plane_key[i])){
                planes[i] = atof(strtok(NULL, newline));
                key_found = 1;
            } 
        }
        if(!key_found && !strcmp(token,res_key)){
            res[0] = atoi(strtok(NULL, space));
            res[1] = atoi(strtok(NULL, space));
            key_found = 1;
        }
        else if(!key_found && !strcmp(token,sphere_key)){ 
            token = strtok(NULL, space);
            strcpy(spheres[numSpheres].name, strdup(token));
            spheres[numSpheres].position[0] = atof(strtok(NULL, space));
            spheres[numSpheres].position[1] = atof(strtok(NULL, space));
            spheres[numSpheres].position[2] = atof(strtok(NULL, space));
            spheres[numSpheres].scale[0] = atof(strtok(NULL, space));
            spheres[numSpheres].scale[1] = atof(strtok(NULL, space));
            spheres[numSpheres].scale[2] = atof(strtok(NULL, space));
            spheres[numSpheres].color[0] = atof(strtok(NULL, space));
            spheres[numSpheres].color[1] = atof(strtok(NULL, space));
            spheres[numSpheres].color[2] = atof(strtok(NULL, space));
            spheres[numSpheres].whatever[0] = atof(strtok(NULL, space));
            spheres[numSpheres].whatever[1] = atof(strtok(NULL, space));
            spheres[numSpheres].whatever[2] = atof(strtok(NULL, space));
            spheres[numSpheres].whatever[3] = atof(strtok(NULL, space));
            spheres[numSpheres].specular_exponent = atoi(strtok(NULL, space));

            numSpheres++;
            key_found = 1;
        }
        else if(!key_found && !strcmp(token,light_key)){
            token = strtok(NULL, space);
            strcpy(lights[numLights].name, strdup(token));
            lights[numLights].position[0] = atof(strtok(NULL,space));
            lights[numLights].position[1] = atof(strtok(NULL,space));
            lights[numLights].position[2] = atof(strtok(NULL,space));
            lights[numLights].intensity[0] = atof(strtok(NULL,space));
            lights[numLights].intensity[1] = atof(strtok(NULL,space));
            lights[numLights].intensity[2] = atof(strtok(NULL,space));

            numLights++;
            key_found = 1;
        }
        else if(!key_found && !strcmp(token,background_key)){
            background_color[0] = atof(strtok(NULL, space));
            background_color[1] = atof(strtok(NULL, space));
            background_color[2] = atof(strtok(NULL, space));
            key_found = 1;
        }
        else if(!key_found && !strcmp(token,ambient_key)){
            ambient[0] = atof(strtok(NULL, space));
            ambient[1] = atof(strtok(NULL, space));
            ambient[2] = atof(strtok(NULL, space));
            key_found = 1;
        }
        else if(!key_found && !strcmp(token,output_key)){ // to process string
            token = strtok(NULL, newline);
            out_filename = strdup(token);
            key_found = 1;
        }
    }

    printf("%sVariables processed from file: \n", prefix_title);
    printf("%sPlanes:       -%.1f- -%.1f- -%.1f- -%.1f- -%.1f-\n",prefix_body, planes[0],planes[1],planes[2],planes[3],planes[4]);
    printf("%sResolution:   -%d- -%d-\n",prefix_body, res[0], res[1]);
    for(i=0;i<numSpheres;i++){
        printf("%sSphere:       -%s- -%.1f- -%.1f- -%.1f- -%.1f- -%.1f- -%.1f- -%.1f- -%.1f- -%.1f- -%.1f- -%.1f- -%.1f- -%.1f- -%i-\n",prefix_body, spheres[i].name, spheres[i].position[0], spheres[i].position[1], spheres[i].position[2], spheres[i].scale[0], spheres[i].scale[1], spheres[i].scale[2], spheres[i].color[0], spheres[i].color[1], spheres[i].color[2], spheres[i].whatever[0], spheres[i].whatever[1], spheres[i].whatever[2], spheres[i].whatever[3], spheres[i].specular_exponent);
    }
    for(i=0;i<numLights;i++){
        printf("%sLight:        -%s- -%.1f- -%.1f- -%.1f- -%.1f- -%.1f- -%.1f-\n",prefix_body, lights[i].name, lights[i].position[0], lights[i].position[1], lights[i].position[2], lights[i].intensity[0], lights[i].intensity[1], lights[i].intensity[2]);
    }
    printf("%sBackground:   -%.1f- -%.1f- -%.1f-\n",prefix_body, background_color[0], background_color[1], background_color[2]);
    printf("%sAmbient:      -%.1f- -%.1f- -%.1f-\n",prefix_body, ambient[0], ambient[1], ambient[2]);
    printf("%sOutput File:  -%s-\n",prefix_body, out_filename);

    fclose(file);
}