# Variáveis de Compilação
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -Iinclude
SRC_DIR = src
OBJ_DIR = obj
BIN = axe

# Caminho de instalação (Padrão para ferramentas locais no Linux)
PREFIX = /usr/local/bin

# Cores para o terminal
GREEN = \033[0;32m
RED   = \033[0;31m
RESET = \033[0m

# Lista de arquivos fonte e objetos
SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(SRCS:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

# Regra padrão: Compila tudo
all: $(BIN)

# Linkagem final do executável
$(BIN): $(OBJS)
	$(CXX) $(OBJS) -o $(BIN)
	@echo "$(GREEN)--- Axe Editor compilado com sucesso! ---$(RESET)"

# Compilação dos arquivos .cpp em .o
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Cria a pasta de objetos se ela não existir
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# --- REGRAS DE SISTEMA (v1.4.2) ---

# Instala o binário no sistema para uso global
install: $(BIN)
	@echo "$(GREEN)--- Instalando Axe no sistema... ---$(RESET)"
	sudo cp $(BIN) $(PREFIX)/$(BIN)
	sudo chmod +x $(PREFIX)/$(BIN)
	@echo "$(GREEN)--- Pronto! Agora você pode usar o comando 'axe' em qualquer lugar. ---$(RESET)"

# Remove o binário do sistema
uninstall:
	@echo "$(RED)--- Removendo Axe do sistema... ---$(RESET)"
	sudo rm -f $(PREFIX)/$(BIN)
	@echo "$(GREEN)--- Desinstalação concluída ---$(RESET)"

# Limpa os arquivos temporários da pasta local
clean:
	rm -rf $(OBJ_DIR) $(BIN)
	@echo "$(GREEN)--- Limpeza concluída ---$(RESET)"

.PHONY: all clean install uninstall