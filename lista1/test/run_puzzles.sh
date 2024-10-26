#!/bin/bash
# This file must be inside ./test with 8puzzle_instances.txt and 15puzzle_instances.txt
# Must run inside the ./lista1 folder
# lista1/
# ├── src/
# │   ├── main.cpp
# ├── test/
# │   ├── 8puzzle_instances.txt
# │   ├── 15puzzle_instances.txt
# │   ├── run_puzzles.sh
# ├── main
# ├── Makefile

INPUT8="./test/8puzzle_instances.txt"
INPUT15="./test/15puzzle_instances.txt"
ALGORITHMS=("-bfs" "-idfs" "-gbfs" "-idastar")
EXECUTABLE="./main"
OUTPUT_DIR="./test"

if [[ ! -f "$EXECUTABLE" ]]; then
  echo "Erro: Executável não encontrado em $EXECUTABLE"
  exit 1
fi

run_with_timeout() {
  local algorithm=$1
  local input=$2
  local output_file=$3

  {
    timeout 30 $EXECUTABLE $algorithm $input
    if [[ $? -ne 0 ]]; then
      echo "-,-,-,-,-"
    fi
  } >> "$output_file" 2>&1
}

# Executa todos, menos A*, com INPUT8
for algorithm in "${ALGORITHMS[@]}"; do
  echo "Executando $algorithm com entradas do $INPUT8"
  output_file="${OUTPUT_DIR}/${algorithm#-}_${INPUT8##*/}.txt"
  while IFS= read -r line; do
    run_with_timeout $algorithm "$line" "$output_file"
  done < "$INPUT8"
done

# Executa A* para todas as entradas do INPUT8
echo "Executando -astar com entradas do $INPUT8"
astar_output_file="${OUTPUT_DIR}/astar_${INPUT8##*/}.txt"
while IFS= read -r line; do
  run_with_timeout -astar "$line" "$astar_output_file"
done < "$INPUT8"

# Executa apenas A* para entradas do INPUT15
echo "Executando -astar com entradas do $INPUT15"
astar_output_file="${OUTPUT_DIR}/astar_${INPUT15##*/}.txt"
while IFS= read -r line; do
  run_with_timeout -astar "$line" "$astar_output_file"
done < "$INPUT15"



