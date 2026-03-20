#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <filesystem>
#include <limits>

#include "axe.hpp"
#include "assets.hpp"
#include "messages.hpp"
#include "engine.hpp"

namespace fs =  std::filesystem;

void menu() {
    std::cout << "1 - criar e escrever em um arquivo\n";
    std::cout << VERMELHO << "0 - sair\n" << RESET;
}

void apresentacao() {
    std::cout << VERMELHO << AXE_LOGO << RESET << "\n";
    std::cout << DIAMANTE << NEGRITO << "Axe Editor - v1.4.0 | The Diamond Axe Update" << RESET << "\n";
}

void criar_escrever(const std::string& nome_fornecido) {
    // 1. CONFIGURAÇÃO INICIAL
    std::string nome_arquivo = nome_fornecido;
    std::vector<std::string> buffer;
    bool modificado = false;

    // 2. ENTRADA DE DADOS (Se não veio pelo terminal)
    if (nome_arquivo.empty()) {
        std::cout << "\n" << AMARELO << "File name: " << RESET;
        std::cin >> nome_arquivo;
        // Limpa o buffer do teclado para o getline não bugar depois
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    // 3. ORQUESTRAÇÃO DA ENGINE (O fluxo de trabalho)
    
    // Passo A: Tenta carregar o arquivo se ele existir
    carregar_para_ram(nome_arquivo, buffer);

    // Passo B: Mostra o que foi carregado (Paginação inteligente)
    exibir_paginado(buffer);

    // Passo C: Abre o modo de edição (Loop de comandos e texto)
    // Passamos o 'modificado' por referência para saber se algo mudou lá dentro
    processar_edicao(buffer, nome_arquivo, modificado);

    // Passo D: Finalização (Só pergunta se quer salvar se 'modificado' for true)
    salvar_final(buffer, nome_arquivo, modificado);
    
    std::cout << "\n" << CINZA << "[Axe] Retornando ao menu principal..." << RESET << "\n";
}
