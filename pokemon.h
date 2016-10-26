#ifndef POKEMON_H
#define POKEMON_H

#include <stdio.h>
#include <string.h>

typedef struct pokemon{
  char pokeName[35];
  char pokeType[35];
  char combatPoints[8];
  char catchDate[9];
  char catchHour[6];
  char coachName[35];
  char coachLevel[4];
  char teamName[35];
  char primaryKey[13];
}Pokemon;

/*--  Iprimary.idx --*/
typedef struct iprimary{
  char primaryKey[13];
  int rrn;
}IprimaryIdx;

/*-- Ipokemon.idx --*/
typedef struct ipokemon{
  char pokeName[35];
  char primaryKey[13];
}IpokemonIdx;

/*-- Iteam.idx -- */
typedef struct iteam{
  char teamName[35];
  char primaryKey[13];
}IteamIdx;

/* Gera a Primary Key com os dados do Pokemon */
void gerarPrimaryKey(Pokemon *p);

/* Verificando se existe um arquivo */
int arquivoExiste(char *str);

void verificaPrimaryKey(Pokemon *p);

/* Escreve dados do Pokemon em pokemon.dat */
void escreverArquivoDat(Pokemon *p, FILE *fp);

/* Escreve Primary KeY + Nome do Pokemon em Ipokemon.idx */
void escreverArquivoIpr(IprimaryIdx *p, FILE *fp, int tam);

/* Escreve Primary KeY + Nome do Time em Iteam.idx */
void escreverArquivoItm(IteamIdx *p, FILE *fp, int tam);

/* Escreve todas as strings em UPERCASE */
void toUpperString(char str[]);

/* Busca por indice através da Chave Primaria dentro do Vetor */
int buscaPrimaryIndice(char pKey[], IprimaryIdx *vet, int tam);

/* Remove o Pokemon do arquivo pokemon.dat colocando *| no inicio*/
void removerPokemon(int rrn, FILE *fp);

void buscarPokemonPkey(int rrn, FILE *fp);

/* Altera o Combat Points no arquivo pokemon.dat */
void alterarCombatPoints(int rrn, FILE *fp, char newRrn[]);
#endif
