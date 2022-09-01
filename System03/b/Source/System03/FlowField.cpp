// Fill out your copyright notice in the Description page of Project Settings.


#include "FlowField.h"

FlowField::FlowField()
{
   
    
    float xoff = FMath::FRand();
    for (int i = 0; i < cols; i++) {
        float yoff = FMath::FRand();
        for (int j = 0; j < cols; j++) { 
            float noise = (FMath::PerlinNoise2D(FVector2D(xoff,yoff))+1.0f)*2* Pi; // mapping  0 - 2Pi
            field.Add(FVector(FMath::Cos(noise),FMath::Sin(noise),0.0f));
            yoff += 0.01f;
            }
        xoff += 0.01f;
    }   


}

FlowField::~FlowField()
{

}

FVector FlowField::GetCellItem(FVector position)
{
   // FVector Item = ((int)position.X)/cols*cols+((int)position.Y)/cols;
    int i = (int)(position.X*cols/8000);
    int j = (int)(position.Y*cols/8000);  

    if (i<0 || i >cols-1 || j<0 || j >cols-1 ){
        return FVector(0.0f,0.0f,0.0f);
    } 
    
    return field[i*cols + j];
}