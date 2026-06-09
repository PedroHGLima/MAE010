#!/bin/bash

SOBRENOME="Lima"
NOME="Pedro"
NOME_ENTREGA="T1_${SOBRENOME}_${NOME}"

if [ -f "relatorio.tex" ]; then
    pdflatex -interaction=batchmode relatorio.tex
    rm -f relatorio.aux relatorio.log relatorio.out relatorio.toc
else
    echo "Erro: relatorio.tex não encontrado!"
    exit 1
fi

rm -rf "$NOME_ENTREGA" "${NOME_ENTREGA}.zip"
mkdir -p "$NOME_ENTREGA"
cp relatorio.pdf "$NOME_ENTREGA/"

EXERCICIOS=("ex1_hello_os" "ex2_trap" "ex3_psum" "ex4_coletivas" "ex5_vecadd" "ex6_derived")

for dir in "${EXERCICIOS[@]}"; do
    if [ -d "$dir" ]; then
        if [ -f "$dir/Makefile" ]; then
            make -C "$dir" clean > /dev/null 2>&1
        fi
        cp -r "$dir" "$NOME_ENTREGA/"
    fi
done

if [ -d "$NOME_ENTREGA" ]; then
    zip -r -q "${NOME_ENTREGA}.zip" "$NOME_ENTREGA"
    rm -rf "$NOME_ENTREGA"
    echo "Arquivo gerado: ${NOME_ENTREGA}.zip"
fi
