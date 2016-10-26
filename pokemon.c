#include <stdio.h>
#include <string.h>
#include "pokemon.h"

/* Gera a Primary Key com os dados do Pokemon */
void gerarPrimaryKey(Pokemon *p){
  p->primaryKey[0] = p->teamName[0];
  p->primaryKey[1] = p->coachName[0];
  p->primaryKey[2] = p->pokeName[0];
  p->primaryKey[3] = p->pokeName[1];
  p->primaryKey[4] = p->catchDate[0];
  p->primaryKey[5] = p->catchDate[1];
  p->primaryKey[6] = p->catchDate[3];
  p->primaryKey[7] = p->catchDate[4];
  p->primaryKey[8] = p->catchHour[0];
  p->primaryKey[9] = p->catchHour[1];
  p->primaryKey[10] = p->catchHour[3];
  p->primaryKey[11] = p->catchHour[4];
  p->primaryKey[12] = '\0';
}

/* Verificando se existe um arquivo */
int arquivoExiste(char *str){
  FILE *fp = fopen(str, "r");
  if(fp == NULL) return 0;
  else return 1;
}

/* Escreve dados do Pokemon em pokemon.dat */
void escreverArquivoDat(Pokemon *p, FILE *fp){
  int offset;
  int tam, count;
  /* Tamanho das palavras variaveis */
  tam = strlen(p->pokeName) + strlen(p->pokeType) + strlen(p->coachName) + strlen(p->teamName);
  /* Para saber quantos # serão escritos */
  offset = 192-44-tam;
  fprintf(fp,"%s@%s@%s@%s@%s@%s@%s@%s@%s@",p->primaryKey, p->pokeName, p->pokeType, p->combatPoints, p->catchDate, p->catchHour, p->coachName, p->coachLevel, p->teamName);
  /* Pritando os # */
  for(count = 0 ; count < offset ; count++){
    fprintf(fp, "#");
  }
}

/* Escreve Primary KeY + Registro em Iprimary.idx */
void escreverArquivoIpr(IprimaryIdx *p, FILE *fp, int tam){
  int count;
  int atualizado = 1;

  fprintf(fp,"%d", atualizado); //Atualizado
  fprintf(fp,"\n");
  /* Pritando os valores */
  for(count = 0 ; count < tam ; count++){
    fprintf(fp, "%s %d",p[count].primaryKey, p[count].rrn+1);
    fprintf(fp,"\n");
  }
}

/* Escreve Primary KeY + Nome do Pokemon em Ipokemon.idx */
void escreverArquivoIpk(IpokemonIdx *p, FILE *fp, int tam){
  int count;
  int atualizado = 1;

  fprintf(fp,"%d", atualizado); //Atualizado
  fprintf(fp,"\n");
  /* Pritando os valores */
  for(count = 0 ; count < tam ; count++){
    fprintf(fp, "%s %s",p[count].primaryKey, p[count].pokeName);
    fprintf(fp,"\n");
  }
}

/* Escreve Primary KeY + Nome do Time em Iteam.idx */
void escreverArquivoItm(IteamIdx *p, FILE *fp, int tam){
  int count;
  int atualizado = 1;

  fprintf(fp,"%d", atualizado); //Atualizado
  fprintf(fp,"\n");
  /* Pritando os valores */
  for(count = 0 ; count < tam ; count++){
    fprintf(fp, "%s %s",p[count].primaryKey, p[count].teamName);
    fprintf(fp,"\n");
  }
}

/* Escreve todas as strings em UPERCASE */
void toUpperString(char str[]){
  int count;
  char c;

  for(count = 0 ; count < strlen(str); count++){
    c = str[count];
    str[count]= toupper(c);
  }
}

/* Busca por indice através da Chave Primaria dentro do Vetor */
int buscaPrimaryIndice(char pKey[], IprimaryIdx vet[], int tam){
  int count;
  for(count = 0 ; count < tam ; count ++){
    if (!strcmp(vet[count].primaryKey, pKey)){
      return count;
    }
  }
return -1;
}

/* Altera o Combat Points no arquivo pokemon.dat */
void alterarCombatPoints(int rrn, FILE *fp, char newCp[]){
  int idx = rrn*192;
  int count = 0 ;
  char letra;
  fseek(fp, idx, SEEK_SET);

  /* Contando até numero de @ < 3 em um intervalo de [0-3]*/
  while(count < 3){
    letra = fgetc(fp);
    if(letra == '@'){
      count++;
    }
  }
  /* Verificar o CP antes de imprimir*/
  fprintf(fp, "%s", newCp);
  rewind(fp);
}

/* Remove o Pokemon do arquivo pokemon.dat colocando *| no inicio*/
void removerPokemon(int rrn, FILE *fp){
  int idx = rrn*192;
  fseek(fp, idx, SEEK_SET);
  fprintf(fp, "*|");
  rewind(fp);
}

void buscarPokemonPkey(int rrn, FILE *fp){
  Pokemon aux;
  int idx = rrn*192;
  char auxC;
  fseek(fp, idx, SEEK_SET);
  fscanf(fp, "%[^@]s", aux.primaryKey);
  fseek(fp, 1, SEEK_CUR);
  fscanf(fp, "%[^@]s", aux.pokeName);
  printf("%s\n%s", aux.primaryKey, aux.pokeName);
}
