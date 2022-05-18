#include <getopt.h>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "util.hpp"
#include "lz78.h"
#include "sufixArray.h"

struct option long_options[] = { //opções por extenso para getopt_long
	{ "pattern", required_argument, NULL, 'p' },
	{ "help", no_argument, NULL, 'h' },
    { "count", no_argument, NULL, 'c' },
	{ 0, 0, 0, 0 }
};

void display_help(){
	printf("ipmt [{index, search, zip, unzip}] [-p ARQUIVO] [-c] PADRAO ARQUIVO\n");
    printf("PADRAO só é necessário ser passado no modo busca \n");
	printf("Modos do sistema\n\n");
	printf("Indexação | index\n");
    printf("Busca exata | search\n");
    printf("Compressão de arquivo | zip\n");
    printf("Descompressão de arquivo | unzip\n");
    printf("Para indexação e busca foi usado o algoritmo sufix array\n");
    printf("Para compressão e descompressão foi usado o algoritmo LZ78\n");
	printf("\n");
    printf("\t\t--help -h\t\tExibe as opções da CLI\n");
    printf("\t\tOpções abaixo são permitidas apenas para o modo busca \n");
	printf("\t\t--pattern -p ARQUIVO\t\tfaz a busca com os padrões em ARQUIVO, um por linha\n");
    printf("\t\t--count -c\t\texibe somente a quantidade de padrões encontrados\n");
}


int main( int argc, char* argv[] ){
    bool showOnlyCountOfPatterns = false;
    std::vector<char*> patterns;
    std::string fileName;
	char* patternFile = nullptr;
	char option;
	std::string algorithmMode = argv[1];
    
	while ( ( option = getopt_long( argc, argv, "p:ha:c", long_options, NULL ) ) != -1 ){
		if(option == 'h'){
			display_help();
			return 0;
		} else if(option == 'p'){
			patternFile = copyString( optarg ); 
		} else if(option == 'c'){
            showOnlyCountOfPatterns = true;
        }
    }
    //optind eh o indice que a lib getopt usa pra saber o indice em que esta checando os argumentos
    //quando o while ai de cima acaba, quer dizer que parou de ler os comandos -alguma_coisa
    //logo o que vier depois nao eh comando que tem - antes
    optind++;
    if (algorithmMode == "search") {
        if(optind < argc){
            patterns.push_back(copyString(argv[optind]));
            optind++;
        } else{
            printf("missing pattern\n");
            exit(1);
            fflush(stdout);
        }
    }

    if (optind < argc) {
        fileName = argv[optind];
    }else{
        printf("missing file\n");
        exit(1);
        fflush(stdout);
    }

    //lê os padrões dos arquivos e passa pra um vector de strings
    if( patternFile ){
        std::ifstream pat_file( patternFile, std::ifstream::in );

        if( !pat_file ){
            if( patternFile ) delete patternFile;
            printf( "can't read from file\n" );
            exit( 1 );
        }

        std::string line;

        while( getline( pat_file, line ) ){
            char* pat = copyString(line.c_str());
			int size = strlen(pat);
            if(pat[size-1] == '\n') pat[size - 1 ] = '\0';
            patterns.push_back(pat);
        }
    }
    if(algorithmMode == "index"){
        createSufix(fileName);
    } else if (algorithmMode == "search"){
        findPattern(fileName, patterns, showOnlyCountOfPatterns);
    } else if(algorithmMode == "zip"){
        lz78Compress(fileName);
    } else if(algorithmMode == "unzip"){
        lz78Decompress(fileName);
    }
	return 0;
}


