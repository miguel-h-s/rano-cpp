#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <filesystem>
#include <limits>
#include <sys/ioctl.h>
#include <unistd.h> 

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
    imprimir_logo_gradiente();
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    
    std::string info = "Axe Editor v1.5.1 | The Polished Edge";
    int espacos = (w.ws_col - info.length()) / 2;
    if (espacos < 0) espacos = 0;

    std::cout << std::string(espacos, ' ') << VERMELHO << NEGRITO << info << RESET << "\n\n";
}

// VIBE CODING :(
void imprimir_logo_gradiente() {
    // 1. Pega a largura do terminal
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    int largura_terminal = w.ws_col;

    // 2. Cores do Gradiente (Vermelho -> Ciano)
    int r1 = 100, g1 = 0, b1 = 0;
    // Fim: RGB(255, 50, 50) - Vermelho vivo/brilhante
    int r2 = 255, g2 = 50, b2 = 50;

    std::vector<std::string> linhas = {
        "  ,  /\\  .  ",
        " //`-||-'\\\\ ",
        "(| -=||=- |)",
        " \\\\,-||-.// ",
        "  `  ||  '  ",
        "     ||     ",
        "     ||     ",
        "     ()     "
    };

    int total_linhas = linhas.size();

    for (int i = 0; i < total_linhas; ++i) {
        // 3. Calcula a centralização
        int largura_texto = linhas[i].length();
        int espacos = (largura_terminal - largura_texto) / 2;
        if (espacos < 0) espacos = 0; // Evita erro se o terminal for micro

        // 4. Calcula a cor
        int r = r1 + (r2 - r1) * i / (total_linhas - 1);
        int g = g1 + (g2 - g1) * i / (total_linhas - 1);
        int b = b1 + (b2 - b1) * i / (total_linhas - 1);

        // 5. Imprime (Espaços + Cor + Texto)
        std::cout << std::string(espacos, ' ') 
                  << "\033[38;2;" << r << ";" << g << ";" << b << "m" 
                  << linhas[i] << RESET << "\n";
    }
}

void criar_escrever(const std::string& nome_fornecido) {
    // 1. CONFIGURAÇÃO INICIAL
    std::string nome_arquivo = nome_fornecido;
    std::vector<std::string> buffer;
    bool modificado = false;

    // 2. ENTRADA DE DADOS (Se não veio pelo terminal)
    if (nome_arquivo.empty()) {
        std::cout << "\n" << Msg::prompt_filename;
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
    
    std::cout << "\n" << Msg::voltando_menu << "\n";
}
