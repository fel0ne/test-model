// формула лепестка  ρ = a · cos(k · φ) 

// Параметр a определяет размер: вся кривая будет лежать внутри круга радиуса a. 

// Параметр k задаёт количество лепестков и их форму:

// Если k — целое число: при нечётном k получится k лепестков, при чётном — 2k лепестков. 

// Если k — рациональное число (можно записать как дробь m/n), количество лепестков тоже будет зависеть от m и n: при нечётных m и n — m лепестков 
//(они могут частично перекрываться), при чётном m или чётном n — 2m лепестков (тоже с перекрытием). 

// Если k — иррациональное число, роза превратится в ажурную, бесконечно развивающуюся структуру с бесконечным множеством частично перекрывающихся лепестков. 
#pragma once


#include <stdlib.h>
#include <math.h>





class Model {
    public:
        double* r;
        double* f;
        int current_resolution;
    
    
    void start_math(float L, float m, float n){
        
        double current_angle;

        for(int i = 0; i < current_resolution; i++){
            current_angle = (180.0/(double)current_resolution) * i;
            current_angle = current_angle * M_PI / 180;
            
            f[i] = current_angle;
            r[i] = L * pow(fabsf(cosf(current_angle/2)), m) * pow(fabsf(sinf(current_angle/2)), n);
        }   
    };
    


    Model(int RESOLUTION_MODEL){
        current_resolution = RESOLUTION_MODEL;

        // r = new double[RESOLUTION_MODEL];
        // f = new double[RESOLUTION_MODEL];
        r = (double*)malloc(sizeof(double) * RESOLUTION_MODEL);
        f = (double*)malloc(sizeof(double) * RESOLUTION_MODEL);
    }


    
    

};