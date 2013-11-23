/* 
 * File:   main.cpp
 * Author: Fernando
 *
 * Created on 22 de Novembro de 2013, 17:59
 */

#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <string>
#include <hash_map>
#include <map>

#define FILE_PATH "C:\\Users\\Fernando\\Desktop\\texto.txt"

using namespace std;

typedef map<string, int> mapWord;

void printMap(mapWord& m) {
    for (mapWord::iterator it = m.begin(); it != m.end(); it++) {
        printf("%s => %i\n", it->first.c_str(), it->second);
        //std::cout << it->first << " => " << it->second << '\n';
    }
}

int countWords(char *text, mapWord& result) {
    char word[100]; // Buffer que irá conter a palavra que está sendo formada a partir do texto. Obs.: não deu pra trabalhar diretamente com "string word"
    int tpos = 0; // Contador utilizado para a posição no texto (text).
    int wpos = 0; // Contador utilizado para a posição na palavra (word).

    while (true) {
        //printf("Letra %c \n", text[tpos]);
        if ((text[tpos] >= 65 && text[tpos] <= 90) ||
                text[tpos] >= 97 && text[tpos] <= 122) { // Todos os caracteres que forem forem considerados formadores de palavras deverão ser adicionados aqui.
            word[wpos] = text[tpos];
            wpos++;
            tpos++;
        } else { // Palavra formada.
            word[wpos] = '\0'; // Fecha o array de caracteres.
            result[word] = result[word] + 1; // Acrescenta no mapWord. Caso a palavra ainda não exista, ela será criada.
            word[0] = '\0'; // Reinicia a palavra.
            wpos = 0;
            tpos++;
        }
        if (text[tpos-1] == '\0')
            break;
    }    
    return 0;
}

int main(int argc, char** argv) {
    FILE *fp; // Descritor do arquivo contendo o texto.
    char *text = NULL; // Texto contido no arquivo.
    int fileSize = 0; // Tamanho do arquivo.
    mapWord result; // Mapa contendo o resultado da contagem.

    // Abre o arquivo e verifica se ocorreu algum erro.
    fp = fopen(FILE_PATH, "a+");
    if (fp == NULL) {
        printf("Houve um erro ao abrir o arquivo.\n");
        return 1;
    }
    printf("Arquivo aberto com sucesso\n");

    // Determina o tamanho do arquivo (em bytes).
    fseek(fp, 0, SEEK_END);
    fileSize = ftell(fp);
    printf("Tamanho do arquivo: %i\n", fileSize);
    fseek(fp, 0, SEEK_SET);

    // Carrega todo o conteúdo do arquivo para a memória.
    text = (char*) malloc(fileSize + 1);
    fgets(text, fileSize + 1, fp);
    //printf("%s \n", text);
    
    countWords(text, result);
    printMap(result);

    fclose(fp);
    return 0;
}