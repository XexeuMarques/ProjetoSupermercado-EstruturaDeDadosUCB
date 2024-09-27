#!/bin/bash

# Função para verificar se o último comando foi bem-sucedido
check_error() {
    if [ $? -ne 0 ]; then
        echo "Erro: $1 falhou. Verifique e tente novamente."
        exit 1
    fi
}

# Verifica se o diretório é um repositório Git
if [ ! -d .git ]; then
    echo "Erro: Este diretório não é um repositório Git."
    exit 1
fi

# Obtém a data atual no formato dd/mm/yyyy
DIA=$(date +%d/%m/%Y)

# Exibe o status atual do repositório
echo "Este é o status atual no Git"
echo "-----------------------------------------------"
git status
check_error "git status"
read -p "Pressione Enter para continuar ..."

# Confirma antes de adicionar todos os arquivos ao estágio
read -p "Deseja adicionar todos os arquivos (git add .)? (s/n) " RESP
if [[ "$RESP" == "s" ]]; then
    git add .
    check_error "git add"
else
    echo "Adicione os arquivos manualmente e depois continue."
    exit 1
fi

# Mostra o status atualizado após adicionar os arquivos
echo "Este é o status atualizado (git add)"
echo "-----------------------------------------------"
git status
check_error "git status"
read -p "Pressione Enter para fazer o commit ..."

# Solicita a mensagem de commit
read -p "Digite a mensagem do commit: " COMMIT

# Confirma se deseja adicionar a data ao commit
read -p "Deseja adicionar a data atual à mensagem do commit? (s/n) " ADD_DATE
if [[ "$ADD_DATE" == "s" ]]; then
    git commit -m "$COMMIT -> $DIA"
else
    git commit -m "$COMMIT"
fi
check_error "git commit"
echo "-----------------------------------------------"
echo "Commit realizado com sucesso."

# Verifica se há um repositório remoto configurado antes de tentar o push
REMOTE=$(git remote)
if [[ -z "$REMOTE" ]]; then
    echo "Erro: Nenhum repositório remoto configurado. Configure o repositório remoto e tente novamente."
    exit 1
fi

read -p "Pressione Enter para enviar ao repositório remoto ($REMOTE) ..."

# Envia as alterações para o repositório remoto
git push
check_error "git push"
echo "Push realizado com sucesso."

exit 0
