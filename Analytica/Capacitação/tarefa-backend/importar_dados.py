import csv
import sqlite3

import os

# Conectar (ou criar) o banco de dados SQLite
conexao = sqlite3.connect('Database.db')
cursor = conexao.cursor()

# Criar a tabela
criar_tabela = '''
CREATE TABLE IF NOT EXISTS SAT (
    DBN TEXT PRIMARY KEY,
    Nome_Escola TEXT,
    Numero_Candidatos INTEGER,
    Media_Leitura INTEGER,
    Media_Matematica INTEGER,
    Media_Escrita INTEGER
)
'''
cursor.execute("DROP TABLE IF EXISTS SAT")
cursor.execute(criar_tabela)

# Abrir e ler o arquivo CSV
with open('SAT.csv', newline='', encoding='utf-8') as arquivo:
    leitor_csv = csv.reader(arquivo)
    next(leitor_csv) 

    dados_tratados = []
    for linha in leitor_csv:
        if all(linha) and len(linha) == 6:
            try:
                # Converter colunas numéricas
                linha[2] = int(linha[2])  
                linha[3] = int(linha[3])  
                linha[4] = int(linha[4])  
                linha[5] = int(linha[5]) 
                dados_tratados.append(linha)
            except ValueError:
                print(f" Linha ignorada (valores inválidos): {linha}")
        else:
            print(f" Linha incompleta ignorada: {linha}")

# Inserir os dados
inserir_dados = '''
INSERT INTO SAT (
    DBN, Nome_Escola, Numero_Candidatos,
    Media_Leitura, Media_Matematica, Media_Escrita
) VALUES (?, ?, ?, ?, ?, ?)
'''
cursor.executemany(inserir_dados, dados_tratados)

# Mostrar todos os dados inseridos
linhas = cursor.execute("SELECT * FROM SAT").fetchall()
for linha in linhas:
    print(linha)

# Finalizar
conexao.commit()
conexao.close()

print("Dados importados com sucesso!")
