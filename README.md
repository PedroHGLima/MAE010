# Trabalho 1 - Computação de Alto Desempenho (MAE010)

Repositório estruturado para o desenvolvimento do Trabalho 1. Cada pasta interna representa um exercício isolado e auto-suficiente. Os arquivos-fonte do relatório final em LaTeX (`relatorio.tex` e dependências) encontram-se na raiz do projeto.

## Estrutura do Repositório

* `relatorio.tex` - Fonte em LaTeX do relatório final (raiz do projeto)
* `ex1_hello_os/` - Exercício 1: Variantes do Hello World
* `ex2_trap/`     - Exercício 2: Regra do Trapézio, Generalizada
* `ex3_psum/`     - Exercício 3: Soma Paralela
* `ex4_coletivas/`- Exercício 4: Prática de Comunicação Coletiva
* `ex5_vecadd/`   - Exercício 5: Soma Paralela de Vetores (Scatter / Gather)
* `ex6_derived/`  - Exercício 6: Um Tipo de Dado Derivado MPI

## Compilação

Cada diretório possui um `Makefile` configurado com regras genéricas. Para compilar e rodar qualquer exercício, navegue até a pasta desejada e utilize os comandos abaixo:

```bash
# Compilar
make

# Limpar binários e objetos
make clean
```
