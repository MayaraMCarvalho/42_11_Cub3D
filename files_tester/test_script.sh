#!/bin/bash

# Caminho para o executável do seu programa em C
PROGRAM="./cub3D"

comp="make re && clear"

# Inicializar contadores
total_tests=0
successful_tests=0

# Inicializar número do teste
test_number=0

# Função para executar um teste
run_test() {
    # Incrementar o número do teste
    ((test_number++))

    # Incrementar o contador total de testes
    ((total_tests++))

    # Entrada de teste
    input="$1"

    # Saída esperada
    expected_output="$2"

    # Executar o programa com a entrada do teste e capturar a saída
    full_output="$($PROGRAM "$input" 2>&1)"

    if [ "$full_output" = "$expected_output" ]; then
        # Incrementar o contador de testes bem-sucedidos
        ((successful_tests++))
        echo -e "\n\e[32mTeste $test_number: OK\e[0]\nEntrada=\"$PROGRAM $input\"\n\n"
    else
        echo -e "\e[31m\nTeste $test_number: X\e[0m\nEntrada=\"$input\"\n\nSaída Obtida=\n\"$full_output\"\n\nSaída Esperada=\n\"$expected_output\"\n"
    fi
}

$comp
clear
echo -e "Iniciando os testes..."

# Testes
#1
run_test "" "Enter a valid file

Usage: ./cub3D [*.cub]
Args: a map in format *.cub"

#2
chmod 000 maps/lock.cub
run_test "lock.cub" "lock.cub: Permission denied

Usage: ./cub3D [*.cub]
Args: a map in format *.cub"
chmod 777 maps/lock.cub

#3
run_test "text.txt" "text.txt: Extension not supported

Usage: ./cub3D [*.cub]
Args: a map in format *.cub"

#4
run_test "test" "test: Extension not supported

Usage: ./cub3D [*.cub]
Args: a map in format *.cub"

#5
run_test "no_exist.cub" "no_exist.cub: No such file or directory

Usage: ./cub3D [*.cub]
Args: a map in format *.cub"

# Calcular porcentagem de acertos
percentage=$(echo "scale=2; $successful_tests / $total_tests * 100" | bc)

# Imprimir resultados com cores
echo -e "\n\e[33mTestes realizados: \e[94m$total_tests\e[0m\n\e[33mTestes OK: \e[94m$successful_tests\e[0m\n\e[33mPorcentagem de acertos: \e[94m$percentage%\e[0m\n"

# Limpar recursos, se necessário
# ...

echo -e "Testes concluídos.\n"
# make fclean > /dev/null

