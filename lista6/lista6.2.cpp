#include <iostream>
#include <string>

int main(){
    
    int m = 0, n = 0, max = 0, aux = 0, e = 0;

    while((scanf("%d %d", &m, &n) != EOF)){
        int v[m], c[n];
        int mat[m+1][n+1];
        int aux = n;
        int path[n];

        for(int i = 0; i < m; i++){
            scanf("%d", &v[i]);
        }

        for(int j = 0; j < n; j++){
            scanf("%d", &c[j]);
        }

        for(int i = 0; i < m+1; i++){
            for(int j = 0; j < n+1; j++){
                if(i == 0 || j == 0 || j > i){
                    mat[i][j] =  -(__INT_MAX__);
                }else{
                    if(mat[i][j-1] == -(__INT_MAX__) && mat[i-1][j] == -(__INT_MAX__)){
                        e = c[i-1]*v[j-1];
                        mat[i][j] = e;
                    }
                    if(mat[i-1][j] != -(__INT_MAX__) && mat[i][j-1] == -(__INT_MAX__)){
                        e = c[j-1]*v[i-1];
                        if(e > mat[i-1][j]){
                            mat[i][j] = e;
                        }else{
                            mat[i][j] = mat[i-1][j];
                        }
                    } 
                    if(mat[i-1][j] == -(__INT_MAX__) && mat[i][j-1] != -(__INT_MAX__)){ // vizinho horizontal esquerda vazio
                        if(mat[i-1][j-1] != -(__INT_MAX__)){
                            e = mat[i-1][j-1] + c[j-1]*v[i-1];
                        }else{
                            e = c[j-1]*v[i-1];
                        }
                        mat[i][j] = e;
                    }
                    if(mat[i-1][j] != -(__INT_MAX__) && mat[i][j-1] != -(__INT_MAX__)){
                        if(mat[i-1][j-1] != -(__INT_MAX__)){
                            e = mat[i-1][j-1] + c[j-1]*v[i-1];
                        }else{
                            e = c[j-1]*v[i-1];
                        }

                        if(e > mat[i-1][j]){
                            mat[i][j] = e;
                        }else{
                            mat[i][j] = mat[i-1][j];
                        }
                    }
                }
            }
            max = mat[m][n];
        }
        printf("%d\n", max);
        for(int i = m; i >= 0; i--){
            if(aux != 0 && mat[i-1][aux] != mat[i][aux]){
                path[aux-1] = i-1;
                aux--;
            }
        }
        for(int i = 0; i < n; i++){
            if(i== n-1){
                printf("%d", path[i]);
            }else{
                printf("%d ", path[i]);
            }
        }
        printf("\n\n");
    }
    return 0;
}

/* for(int j = 0; j < n+1; j++){
            for(int i = 0; i < m+1; i++){
                printf("%d   ", mat[i][j]);
            }
            printf("\n");
        }  */


/* 
6 3
-11 -4 -9 -6 4 -8
3 -1 2

5 2
3 -5 -4 -8 7
-1 -1
 */
