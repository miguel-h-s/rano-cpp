# 1. Versão mínima e Nome do Projeto
cmake_minimum_required(VERSION 3.14)
project(AxeEditor LANGUAGES CXX)

# 2. Configurações de Compilação 
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 3. Coletar os arquivos fonte 
file(GLOB_RECURSE SOURCES "src/*.cpp")

# 4. Criar o Executável 
add_executable(axe ${SOURCES})

# 5. Onde estão os Headers 
target_include_directories(axe PRIVATE include)

# 6. Flags de Aviso 
target_compile_options(axe PRIVATE -Wall -Wextra)

# --- REGRAS DE INSTALAÇÃO  ---

# Define que o executável 'axe' vai para /usr/local/bin
install(TARGETS axe DESTINATION /usr/local/bin)

# Mensagem de sucesso ao configurar
message(STATUS "Axe Editor: Configuração para Linux concluída com sucesso!")