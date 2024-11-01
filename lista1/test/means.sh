#!/bin/bash
# This file must be inside ./lista1/test with outputs
# Must run inside the ./lista1/test folder

soma_nodos=0
soma_comprimento=0
soma_tempo=0
soma_heuristica_media=0
soma_heuristica_inicial=0
contador=0

while IFS=, read -r nodos comprimento tempo heuristica_media heuristica_inicial; do
    # Ignora a linha se todos os campos forem '-'
    if [[ "$nodos" == "-" && "$comprimento" == "-" && "$tempo" == "-" && "$heuristica_media" == "-" && "$heuristica_inicial" == "-" ]]; then
        continue
    fi

    soma_nodos=$((soma_nodos + nodos))
    soma_comprimento=$((soma_comprimento + comprimento))
    soma_tempo=$(echo "$soma_tempo + $tempo" | bc)
    soma_heuristica_media=$(echo "$soma_heuristica_media + $heuristica_media" | bc)
    soma_heuristica_inicial=$((soma_heuristica_inicial + heuristica_inicial))
    contador=$((contador + 1))
done < astar_8puzzle_instances.txt.txt
# HERE alterar arquivo

media_nodos=$((soma_nodos / contador))
media_comprimento=$((soma_comprimento / contador))
media_tempo=$(echo "scale=6; $soma_tempo / $contador" | bc)
media_heuristica_media=$(echo "scale=6; $soma_heuristica_media / $contador" | bc)
media_heuristica_inicial=$((soma_heuristica_inicial / contador))

echo "Média: $media_nodos, $media_comprimento, $media_tempo, $media_heuristica_media, $media_heuristica_inicial"