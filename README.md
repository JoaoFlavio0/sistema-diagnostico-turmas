# 📊 Sistema de Diagnóstico de Turmas (EPT)

Sistema em linguagem C para análise de desempenho de turmas, com foco em médias, frequência e registro de evasão escolar.

---

## 🚀 Sobre o projeto

Este sistema realiza o acompanhamento de alunos por meio de:

- Notas teóricas e práticas
- Cálculo de médias individuais e da turma
- Análise de frequência
- Registro de evasão com motivo
- Diagnóstico geral do desempenho da turma

O objetivo é simular um sistema simples de gestão e análise acadêmica usando lógica de programação em C.

---

## ⚙️ Funcionalidades

- Cadastro de alunos
- Inserção de notas (teórica e prática)
- Validação de dados de entrada
- Cálculo automático de médias
- Cálculo de frequência (horas)
- Identificação do:
  - Melhor aluno
  - Pior aluno
- Diagnóstico da turma:
  - Média geral
  - Status de desempenho
- Registro de evasões com motivo
- Conversão de tempo (minutos → dias/horas/minutos)

---

## 🧠 Tecnologias e conceitos usados

- Linguagem C
- Estruturas de repetição (`while`)
- Vetores (arrays)
- Funções
- Strings (`fgets`, `strlen`)
- Validação de entrada
- Lógica de programação aplicada

---

## 🖥️ Como executar

### 🔹 Requisitos
- GCC (compilador C)

### 🔹 Compilação
```bash
gcc main.c -o sistema
🔹 Execução
./sistema

📋 Menu do sistema
1. Adicionar notas
2. Visualizar diagnostico
3. Registrar evasao
4. Encerrar
📈 Exemplo de análise

O sistema gera:

Médias da turma
Frequência média
Aluno com maior e menor desempenho
Status da turma:
✅ Turma destaque
⚠️ Turma com problemas
🚨 Turma com defasagem
📂 Estrutura do projeto
📁 sistema-diagnostico-turmas
 ├── main.c
 └── README.md

👥 Integrantes
João Flavio Pedroso do Carmo
Kerlon Ramirez Oliveria Rodrigues                                                   
Arthur Jose Araujo Mota                             
Victor Rafael Bezerra Sampaio                             
Francisco Yuri Diogenes Gomes                          
Jose Ernesto Carvalho Oliveira 
