#include "calculate.h"

void preMultiply(ARRAY_2D *vector,ARRAY_2D *matrix,ARRAY_2D *result){
    if(vector->cols + matrix->rows == 2){
        setSizeArray2D(result,vector->rows,matrix->cols);
        for(int i=0;i<vector->rows;i++)
            for(int j=0;j<matrix->cols;j++)
                result->index[i][j] = vector->index[i][0] * matrix->index[0][j];
    }else printf("preMultiply: Incorrect rule !!!\n");
}

void postMultiply(ARRAY_2D *vector,ARRAY_2D *matrix,ARRAY_2D *result){
    if(vector->rows + matrix->cols == 2){
        setSizeArray2D(result,vector->rows,matrix->cols);
            for(int i=0;i<vector->rows;i++)
                for(int j=0;j<matrix->cols;j++)
                    for(int k=0;k<vector->cols;k++)
                        result->index[i][j] += vector->index[i][k] * matrix->index[i][j];
    }else printf("prostMultiply: Incorrect rule !!!\n");
}

void negateVector(ARRAY_2D *vector){
    for (int i=0;i<vector->rows;i++){
        for(int j=0;j<vector->cols;j++){
            vector->index[i][j] = vector->index[i][j] * -1;
        }
    }
}

void multiplySclarWithVector(ARRAY_2D *vector,ARRAY_2D *matrix,ARRAY_2D *result){
    int r,c;
    ARRAY_2D *vec1,*vec2;
    r = (vector->rows >= matrix->rows) ? vector->rows : matrix->rows;
    c = (vector->cols >= matrix->cols) ? vector->cols : matrix->cols;
    setSizeArray2D(result,r,c);
    if(vector->rows+vector->cols>matrix->rows+matrix->cols){
        vec1 = matrix;
        vec2 = vector;
    }else{
        vec1 = vector;
        vec2 = matrix;
    }
    if(vec1->rows+vec1->cols == 2){
        for (int i=0;i<vec2->rows;i++){
            for(int j=0;j<vec2->cols;j++){
                result->index[i][j] = vec2->index[i][j] * vec1->index[0][0];
            }
        }
    }
    else if (vec1->rows == vec2->rows && vec1->cols == 1){
        for (int i=0;i<vec2->rows;i++){
            for(int j=0;j<vec2->cols;j++){
                result->index[i][j] = vec2->index[i][j] * vec1->index[i][0];
            }
        }
    }
    else if(vec1->rows == vec2->rows && vec1->cols == vec2->cols){
        for (int i=0;i<vec2->rows;i++){
            for(int j=0;j<vec2->cols;j++){
                result->index[i][j] = vec2->index[i][j] * vec1->index[i][j];
            }
        }
    }
    else if(vec1->rows + vec2->cols == 2){
        for (int i=0;i<vec2->rows;i++)
            for(int j=0;j<vec1->cols;j++)
                result->index[i][j] = vec2->index[i][0] * vec1->index[0][j];
    }
    else if(vec1->cols + vec2->rows == 2){
        for (int i=0;i<vec1->rows;i++)
            for(int j=0;j<vec2->cols;j++)
                result->index[i][j] = vec2->index[0][j] * vec1->index[i][0];
    }
    else{
        setSizeArray2D(result,0,0);
        printf("multiplySclarWithVector: Incorrect rule !!!\n");
    }
}

void addVector(ARRAY_2D *vector1,ARRAY_2D *vector2,ARRAY_2D *result){
    ARRAY_2D *vec1,*vec2;
    if(vector1->rows+vector1->cols>vector2->rows+vector2->cols){
        vec1 = vector2;
        vec2 = vector1;
    }else{
        vec1 = vector1;
        vec2 = vector2;
    }
    setSizeArray2D(result,vec2->rows,vec2->cols);
    if(vec1->rows + vec1->cols == 2){
        for(int i=0;i<vec2->rows;i++)
            for(int j=0;j<vec2->cols;j++){
                result->index[i][j] = vec1->index[0][0] + vec2->index[i][j]; 
            }
    }else if(vec1->rows == vec2->rows && vec1->cols == 1){
        for(int i=0;i<vec2->rows;i++)
            for(int j=0;j<vec2->cols;j++){
                result->index[i][j] = vec1->index[i][0] + vec2->index[i][j]; 
            }
    }else if(vec1->cols == vec2->cols && vec1->rows == 1){
        for(int i=0;i<vec2->rows;i++)
            for(int j=0;j<vec2->cols;j++){
                result->index[i][j] = vec1->index[0][j] + vec2->index[i][j]; 
            }
    }else if(vec1->rows == vec2->rows && vec1->cols == vec2->cols){
        for(int i=0;i<vec2->rows;i++)
            for(int j=0;j<vec2->cols;j++){
                result->index[i][j] = vec1->index[i][j] + vec2->index[i][j]; 
            }
    }else{
        setSizeArray2D(result,0,0);
        printf("addVector: Incorrect rule !!!\n");
    }
}

void substractVector(ARRAY_2D *vector,ARRAY_2D *matrix,ARRAY_2D *result){
    negateVector(matrix);
    addVector(vector,matrix,result);
    negateVector(matrix);
}

void normalize(ARRAY_2D *vector,ARRAY_2D *result){
    float norm = computeMagnitude(vector);
    if(norm){
    setSizeArray2D(result,vector->rows,vector->cols);
    for(int i=0;i<vector->rows;i++)
        for(int j=0;j<vector->cols;j++)
            result->index[i][j] = vector->index[i][j]/norm;
    }else printf("normalize: Incorrect rule !!!\n");
}

float dotProduct(ARRAY_2D *vector1,ARRAY_2D *vector2){
    float result = 0;
    if(vector1->cols == vector2->cols && vector1->rows == vector2->rows){
        for(int i=0;i<vector2->rows;i++)
            for(int j=0;j<vector2->cols;j++){
                result += vector2->index[i][j] * vector1->index[i][j];
            }                
    }else printf("dotProuct: Incorrect rule !!!\n");
    return result;
} 

void transpose(ARRAY_2D *matrix){
    ARRAY_2D result;
    setSizeArray2D(&result,matrix->cols,matrix->rows);
    for(int i=0;i<result.rows;i++)
        for(int j=0;j<result.cols;j++)
             result.index[i][j] = matrix->index[j][i];
    matrix = &result;
}

float computeMagnitude(ARRAY_2D *vector){
    float norm = 0;
    if(vector->cols == 1 || vector->rows == 1){
        for(int i=0;i<vector->rows;i++)
            for(int j=0;j<vector->cols;j++)
                if(vector->index[i][j]) norm += pow(vector->index[i][j],2);
                else goto RETURN;
        norm = sqrt(norm);
    }
    RETURN:
    return norm;
}

void crossProduct(ARRAY_2D *vector1,ARRAY_2D *vector2,ARRAY_2D *result){
    if(vector1->rows + vector2->rows == 2 && vector2->cols + vector2->cols == 6){
        setSizeArray2D(result,1,3);
        result->index[0][0] = vector1->index[0][1]*vector2->index[0][2] - vector1->index[0][2]*vector2->index[0][1]; 
        result->index[0][1] = vector1->index[0][0]*vector2->index[0][2] - vector1->index[0][2]*vector2->index[0][0]; 
        result->index[0][2] = vector1->index[0][0]*vector2->index[0][1] - vector1->index[0][1]*vector2->index[0][0]; 
    }else printf("crossProduct: Incorrect rule !!!\n");
}