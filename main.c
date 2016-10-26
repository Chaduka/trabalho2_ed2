/*-----------------------------------
UNIVERSIDADE FEDERAL DE SÃO CARLOS - SOROCABA
Nome: Chady Chaito     RA : 613797
Arquivo: main.c
----------------------------------*/
//Bibliotecas
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "pokemon.h"

//Menu
#define MENU "MENU\n1 - Cadastar\n2 - Alterar\n3 - Remover\n4 - Buscar\n5 - Listar\n6- Liberar espaco\n0 - Sair\n"
#define SUBMENU_BUSCAR "1 - Buscar pokemon por codigo\n2- Buscar pokemon por nome\n3- Buscar pokemon por nome da equipe\n"
#define SUBMENU_LISTAR "1 - Buscar pokemon por codigo\n2- Buscar pokemon por nome\n3- Buscar pokemon por nome da equipe\n"

void main(){
  char primaryKeyBusca[13];
  char newCombatPoints[8]; //MUDAR PARA > FLOAT <
  int option, subopt_busca, subopt_listar, retornoIdx, idx;
  int flag, created = 0, isUpdate; //Marcadores
  int count, tamIpr = 0, tamIpk = 0, tamItm = 0; //Contadores
  FILE *fpDat, *fpPrimary, *fpPokemon, *fpTime; //File Pointers
  Pokemon pkm;
  IprimaryIdx vetIpr[1000];
  IpokemonIdx vetIpk[1000];
  IteamIdx vetItm[1000];

  /* Verificar se existe o arquivo de dados. */
  if(arquivoExiste("pokemons.dat")){
    fpDat = fopen("pokemons.dat", "r+");
  }
  else{
    fpDat = fopen("pokemons.dat", "w+");
    created = 1;
  }

  if(arquivoExiste("iprimary.idx"))
    fpPrimary = fopen("iprimary.idx","r+");
  else{
    fpPrimary = fopen("iprimary.idx","w+");
  }

    fpPokemon = fopen("ipokemon.idx","w+");

    fpTime = fopen("iteam.idx","w+");

  do{
    printf(MENU);
    scanf("%d", &option);
    switch(option){
      case 1://Cadastrar
        scanf("%s", pkm.pokeName); toUpperString(pkm.pokeName);
        /* Verificando se o nome é composto apenas por letras */
        for(count = 0 ; count < strlen(pkm.pokeName) ; count++){
          if(isalpha(pkm.pokeName[count])) //Se for
            flag = 0;
          else{ //Se não for
            flag = 1;
            break;
          }//close else
        }//close for
        if(flag){
          printf("Campo inválido! Informe novamente:");
        }
        scanf("%s", pkm.pokeType); toUpperString(pkm.pokeType);
        scanf("%s", pkm.combatPoints);
        scanf("%s", pkm.catchDate);
        scanf("%s", pkm.catchHour);
        scanf("%s", pkm.coachName); toUpperString(pkm.coachName);
        scanf("%s", pkm.coachLevel);
        scanf("%s", pkm.teamName); toUpperString(pkm.teamName);
        gerarPrimaryKey(&pkm);
        //.Dat
        escreverArquivoDat(&pkm, fpDat);

        //iprimary.idx - Escrevendo no vetor
        vetIpr[tamIpr].rrn = tamIpr;
        strcpy(vetIpr[tamIpr].primaryKey, pkm.primaryKey);
        tamIpr++;

        //ipokemon.idx - Escrevendo no vetor
        strcpy(vetIpk[tamIpk].primaryKey, pkm.primaryKey);
        strcpy(vetIpk[tamIpk].pokeName, pkm.pokeName);
        tamIpk++;

        //iteam.idx - Escrevendo no vetor
        strcpy(vetItm[tamItm].primaryKey, pkm.primaryKey);
        strcpy(vetItm[tamItm].teamName, pkm.teamName);
        tamItm++;
      break;

      case 2://Alterar
        scanf("%s", primaryKeyBusca); //Usuario entra com chave primaria

        /* Busca o a primaryKey no Iprimary.idx e retorna a localização da struct no vetor */
        retornoIdx = buscaPrimaryIndice(primaryKeyBusca, vetIpr, tamIpr);
        if(retornoIdx == -1){ // Se não existir
          printf("Registro nao encontrado!");
        }
        else{ //Se existir
          scanf("%s", newCombatPoints);
          /* Altera o Combat Points no arquivo pokemon.dat */
          alterarCombatPoints(vetIpr[retornoIdx].rrn, fpDat, newCombatPoints);
        }
      break;

      case 3://Remover
        scanf("%s", primaryKeyBusca);

        /* Busca o a primaryKey no Iprimary.idx e retorna a localização da struct no vetor */
        retornoIdx = buscaPrimaryIndice(primaryKeyBusca, vetIpr, tamIpr);
        if(retornoIdx == -1){ // Se não existir
          printf("Registro nao encontrado!");
        }
        else{ //Se existir
          removerPokemon(vetIpr[retornoIdx].rrn, fpDat);
          vetIpr[retornoIdx].rrn = -2; //Colocando -1 nos indices
        }
      break;

      case 4://Buscar
        printf(SUBMENU_BUSCAR);
        scanf("%d", &subopt_busca);
        switch(subopt_busca){
          case 1:
            scanf("%s", primaryKeyBusca);

            /* Busca o a primaryKey no Iprimary.idx e retorna a localização da struct no vetor */
            retornoIdx = buscaPrimaryIndice(primaryKeyBusca, vetIpr, tamIpr);
            if(retornoIdx == -1){ // Se não existir
              printf("Registro nao encontrado!");
            }
            else{ //Se existir
              buscarPokemonPkey(retornoIdx, fpDat);
            }
          break;
          case 2:
          break;
            printf("foi2");
          break;
          case 3:
            printf("foi3");
          break;
        }//close switch submenu
      break;

      case 5://Listar
        printf(SUBMENU_LISTAR );
        scanf("%d", &subopt_listar);
        switch(subopt_listar){
          case 1:
            printf("foi1");
          break;
          case 2:
          break;
            printf("foi2");
          break;
          case 3:
            printf("foi3");
          break;
        }//close switch submenu
      break;

      case 6://Liberar espaco
      break;

      case 0: //Sair
        escreverArquivoIpr(vetIpr, fpPrimary, tamIpr);
        escreverArquivoIpk(vetIpk, fpPokemon, tamIpk);
        escreverArquivoItm(vetItm, fpTime, tamItm);
      break;

    }//close switch menu
  }while(option != 0);

fclose(fpTime);
fclose(fpPokemon);
fclose(fpPrimary);
}//close main
