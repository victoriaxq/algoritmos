if((f_carga/M) > LMax){
        newM = (2*M)+1;
        Rehash = (Tabela*)malloc(newM * sizeof(Tabela));
        for(int a = 0; a < newM; a++){
          Rehash[a].num = 0;
          Rehash[a].Vector = NULL;
        }
        for(int a = 0; a < M; a++){
          for(int b = 0; b < Hashtable[a].num; b++){
            insert = Hashtable[a].Vector[b].C_timestamp % newM;
            Rehash[insert].Vector = (Cliente*)realloc(Rehash[insert].Vector, (Rehash[insert].num + 1)*sizeof(Cliente));
            if(Rehash[insert].Vector == NULL){
              exit(1);
            }
            Rehash[insert].Vector[Rehash[insert].num].C_timestamp = Hashtable[a].Vector[b].C_timestamp;
            Rehash[insert].Vector[Rehash[insert].num].C_IP = Hashtable[a].Vector[b].C_IP;
            Rehash[insert].num++;
            ordena(Rehash[insert].Vector, 0, Rehash[insert].num);
          }
          free(Hashtable[a].Vector);
        }
        free(Hashtable);
        Hashtable = Rehash;
        Rehash = NULL;
        M = newM;
      }