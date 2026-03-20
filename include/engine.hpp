#ifndef ENGINE_HPP
#define ENGINE_HPP

#include <vector>
#include <string>
#include <fstream>
#include <filesystem>
#include <iostream>
#include <iomanip>

// Namespace para facilitar o uso de caminhos de arquivo
namespace fs = std::filesystem;

// --- ASSINATURAS DAS FUNÇÕES DA ENGINE ---

// 1. Carrega o arquivo do disco para o buffer de RAM (Passagem por referência para performance)
void carregar_para_ram(const std::string& nome, std::vector<std::string>& buffer);

// 2. Mostra o início e o fim do arquivo (Paginação para não travar o processador)
void exibir_paginado(const std::vector<std::string>& buffer);

// 3. O "Coração": Loop de edição, comandos (:q!, :s, :v) e entrada de texto
void processar_edicao(std::vector<std::string>& buffer, std::string& nome_arquivo, bool& modificado);

// 4. A "Saída": Pergunta se quer sobrescrever ou anexar e grava no eMMC/SSD
void salvar_final(std::vector<std::string>& buffer, std::string& nome_arquivo, bool modificado);

#endif