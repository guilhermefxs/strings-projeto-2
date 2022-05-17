Dupla: Guilherme Xavier e Matheus Felipe 

IPMT
===

Ferramenta que busca padrões em linhas de texto e comprime arquivos de texto.

Sinopse
--------

    ipmt [{index, search, zip, unzip}] [-p ARQUIVO] [-c] PADRAO ARQUIVO
    PADRAO só é necessário ser passado no modo busca

    Modos do sistema

    Indexação | index
    Busca exata | search
    Compressão de arquivo | zip
    Descompressão de arquivo | unzip

    Para indexação e busca foi usado o algoritmo sufix array
    Para compressão e descompressão foi usado o algoritmo LZ78

	    --help      Exibe as opções da CLI
	    Opções abaixo são permitidas apenas para o modo busca
	    --pattern -p ARQUIVO      faz a busca com os padrões em ARQUIVO, um por linha
	    --count -c      exibe somente a quantidade de padrões encontrados

Compilação
----------

Para compilação, deve ser usado o comando `make` e o executável vai para a pasta bin.
