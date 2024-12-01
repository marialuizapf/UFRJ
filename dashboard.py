import streamlit as st
import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns

# Função para carregar o dataset
@st.cache
def carregar_dados():
    # Substitua pelo caminho do seu dataset real
    df = pd.read_csv('netflix_titles.csv')
    return df

# Carregar o dataset
df = carregar_dados()

# Título do Dashboard
st.title("Dashboard Interativo - Netflix Dataset")

# Exibir as primeiras linhas do dataset
if st.checkbox('Mostrar as primeiras linhas do dataset'):
    st.write(df.head())

# Estatísticas descritivas
if st.checkbox('Mostrar estatísticas descritivas'):
    st.write(df.describe())

# Análise de valores ausentes
if st.checkbox('Mostrar valores ausentes'):
    st.write(df.isnull().sum())
    st.write((df.isnull().sum() / len(df)) * 100)

# Análise de tipos de conteúdo (Filmes e Séries)
st.subheader("Distribuição de Tipos de Conteúdo")
if st.checkbox('Mostrar gráfico de Tipos de Conteúdo'):
    plt.figure(figsize=(8, 6))
    sns.countplot(data=df, x='type')
    plt.title("Distribuição de Tipos de Conteúdo")
    plt.xlabel("Tipo de Conteúdo")
    plt.ylabel("Contagem")
    st.pyplot()

# Análise de lançamento por ano
st.subheader("Quantidade de Lançamentos por Ano")
df['release_year'] = pd.to_datetime(df['release_year'], format='%Y', errors='coerce').dt.year

if st.checkbox('Mostrar gráfico de lançamentos por ano'):
    lançamentos_por_ano = df['release_year'].value_counts().sort_index()
    plt.figure(figsize=(10, 6))
    plt.plot(lançamentos_por_ano.index, lançamentos_por_ano.values, marker='o')
    plt.title("Quantidade de Lançamentos por Ano")
    plt.xlabel("Ano")
    plt.ylabel("Quantidade de Lançamentos")
    st.pyplot()

# Análise de Duração (Filmes e Séries)
st.subheader("Análise de Duração")

# Tratando os dados de duração
df['duration_num'] = df['duration'].str.extract('(\d+)').astype(float)
df['duration_type'] = df['duration'].str.extract('([a-zA-Z]+)').fillna('Desconhecido')

# Gráfico para filmes
if st.checkbox('Mostrar gráfico de duração de filmes'):
    filmes_df = df[df['duration_type'] == 'min']
    plt.figure(figsize=(8, 6))
    sns.histplot(filmes_df['duration_num'].dropna(), kde=True, bins=30)
    plt.title("Distribuição da Duração dos Filmes (em Minutos)")
    plt.xlabel("Duração (Minutos)")
    plt.ylabel("Frequência")
    st.pyplot()

# Filtros para explorar dados
st.sidebar.subheader("Filtros Interativos")

# Filtro de Tipo de Conteúdo
tipo_conteudo = st.sidebar.selectbox("Escolha o Tipo de Conteúdo", options=df['type'].unique())
if tipo_conteudo:
    st.write(f"Conteúdo do tipo: {tipo_conteudo}")
    st.write(df[df['type'] == tipo_conteudo])

# Conclusão
st.sidebar.write("Explore os gráficos e os filtros!")
