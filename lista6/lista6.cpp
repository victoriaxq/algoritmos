#include <iostream>
#include <string>
#define vazio -(__INT_MAX__);

int main(){
    
    int m = 0, n = 0, max = 0, aux = 0, flag = 0;
    int e = 0;

    while((scanf("%d %d", &m, &n) != EOF)){
        
        int v[m], c[n];
        int mat[m+1][n+1];

        for(int i = 0; i < m; i++){
            scanf("%d", &v[i]);
        }

        for(int j = 0; j < n; j++){
            scanf("%d", &c[j]);
        }

        for(int i = 0; i < m+1; i++){
            for(int j = 0; j < n+1; j++){ 
                if(i == 0 || j == 0 || i > j){ //OK
                    mat[i][j] =  -(__INT_MAX__);
                }else{
                    if(mat[i-1][j-1] == -(__INT_MAX__) && mat[i][j-1] == -(__INT_MAX__)){ //OK
                        e = c[i-1]*v[j-1];
                        mat[i][j] = e;
                    }
                    
                    if(mat[i][j-1] == -(__INT_MAX__) && mat[i-1][j-1] != -(__INT_MAX__)){ //ok
                        e = mat[i-1][j-1] + c[j-1]*v[i-1];

                        if(e > mat[i][j-1]){
                            mat[i][j] = e;
                        }else{
                            mat[i][j] = mat[i][j-1];
                        }
                    } 

                    if(mat[i][j-1] != -(__INT_MAX__) && mat[i-1][j-1] == -(__INT_MAX__)){  //ok
                        e = c[j-1]*v[i-1];
                        
                        if(e > mat[i][j-1]){
                            mat[i][j] = e;
                        }else{
                            mat[i][j] = mat[i][j-1];
                        }
                    }

                    if(mat[i][j-1] != -(__INT_MAX__) && mat[i-1][j-1] != -(__INT_MAX__)){
                        if(mat[i-1][j-1] != -(__INT_MAX__)){
                            e = mat[i-1][j-1] + c[j-1]*v[i-1];
                        }else{
                            e = c[j-1]*v[i-1];
                        }

                        if(e > mat[i][j-1]){
                            mat[i][j] = e;
                        }else{
                            mat[i][j] = mat[i][j-1];
                        }
                    }
                }

            }
            //max = mat[m][n];
        }

        printf("%d\n", max);

        for(int i = 0; i < m+1; i++){
            for(int j = 0; j < n+1; j++){
                printf("%d   ", mat[i][j]);
            }
            printf("\n");
        } 

        
    }
    return 0;
}




/* 
6 3
-11 -4 -9 -6 4 -8
3 -1 2

5 2
3 -5 -4 -8 7
-1 -1
 */
