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
        echo -e "\n\e[32mTeste $test_number: OK\e[0]\nEntrada=\"$PROGRAM $input\""
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
chmod 000 maps/wrong_maps/lock.cub
run_test "wrong_maps/lock.cub" "wrong_maps/lock.cub: Permission denied

Usage: ./cub3D [*.cub]
Args: a map in format *.cub"
chmod 777 maps/wrong_maps/lock.cub

#3
run_test "wrong_maps/text.txt" "wrong_maps/text.txt: Extension not supported

Usage: ./cub3D [*.cub]
Args: a map in format *.cub"

#4
run_test "wrong_maps/test" "wrong_maps/test: Extension not supported

Usage: ./cub3D [*.cub]
Args: a map in format *.cub"

#5
run_test "no_exist.cub" "no_exist.cub: No such file or directory

Usage: ./cub3D [*.cub]
Args: a map in format *.cub"

#6
run_test "wrong_maps/color_less.cub" "
Error
Invalid Color Settings"

#7
run_test "wrong_maps/color_more.cub" "
Error
Configuration items are more"

#8
run_test "wrong_maps/color_more2.cub" "
Error
Configuration items are more"

#9
run_test "wrong_maps/empty.cub" "
Error
File empty"

#10
run_test "wrong_maps/map_identifier_less.cub" "
Error
Map without identifier"

#11
run_test "wrong_maps/map_more_letter.cub" "
Error
Map with disallowed identifier"

#12
run_test "wrong_maps/map_open.cub" "
Error
Map is open"

#13
run_test "wrong_maps/map_open2.cub" "
Error
Map is open"

#14
run_test "wrong_maps/map_open3.cub" "
Error
Map is open"

#15
run_test "wrong_maps/missing.cub" "
Error
Invalid Settings"

#16
run_test "wrong_maps/repeated_tex.cub" "
Error
Invalid Texture Settings"

#17
run_test "wrong_maps/texture_less.cub" "
Error
Configuration items are missing"

#18
run_test "wrong_maps/texture_more.cub" "
Error
Configuration items are more"

#19
run_test "wrong_maps/map_open4.cub" "
Error
Map is open"

#20
run_test "wrong_maps/repeated_color.cub" "
Error
Invalid Color Settings"

#21
run_test "wrong_maps/color_less2.cub" "
Error
Invalid Color Settings"

#22
run_test "wrong_maps/color_less3.cub" "
Error
Invalid Color Settings"

#23
run_test "wrong_maps/color_more3.cub" "
Error
Configuration items are more"

#24
run_test "wrong_maps/color_more4.cub" "
Error
Configuration items are more"

#25
run_test "wrong_maps/repeated_tex2.cub" "
Error
Invalid Texture Settings"

#26
run_test "wrong_maps/repeated_color2.cub" "
Error
Invalid Color Settings"

#27
run_test "wrong_maps/map_open5.cub" "
Error
Map is open"

#28
run_test "wrong_maps/map_open6.cub" "
Error
Map is open"

#29
run_test "wrong_maps/map_open7.cub" "
Error
Map is open"

#30
run_test "wrong_maps/map_open8.cub" "
Error
More than one map identifier"

#31
run_test "wrong_maps/map_more_letter2.cub" "
Error
Map with disallowed identifier"


# Calcular porcentagem de acertos
percentage=$(echo "scale=2; $successful_tests / $total_tests * 100" | bc)

# Imprimir resultados com cores
echo -e "\n\e[33mTestes realizados: \e[94m$total_tests\e[0m\n\e[33mTestes OK: \e[94m$successful_tests\e[0m\n\e[33mPorcentagem de acertos: \e[94m$percentage%\e[0m\n"

# Limpar recursos, se necessário
# ...

echo -e "Testes concluídos.\n"
# make fclean > /dev/null

