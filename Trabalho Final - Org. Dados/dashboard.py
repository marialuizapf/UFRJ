import streamlit as st
import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns

# Configurar a página do Streamlit
st.set_page_config(page_title="Dashboard Netflix", layout="wide")

# Função para carregar o dataset
@st.cache_data
def carregar_dados():
    df = pd.read_csv('netflix_titles.csv')
    return df

# Carregar o dataset
df = carregar_dados()

# Título do Dashboard
#st.title("Dashboard Interativo - Netflix Dataset")
st.title("Análise de Dados da Netflix: Tendências e Características")

# Exibir as primeiras linhas do dataset
st.sidebar.header("Configurações do Dashboard")
if st.sidebar.checkbox('Mostrar as primeiras linhas do dataset'):
    st.subheader("Primeiras Linhas do Dataset")
    st.write(df.head())

# Estatísticas descritivas
if st.sidebar.checkbox('Mostrar estatísticas descritivas'):
    st.subheader("Estatísticas Descritivas")
    st.write(df.describe(include="all").transpose())

# Análise de valores ausentes
if st.sidebar.checkbox('Mostrar valores ausentes'):
    st.subheader("Análise de Valores Ausentes")
    valores_ausentes = pd.DataFrame({
        "Valores Nulos": df.isnull().sum(),
        "Percentual (%)": (df.isnull().sum() / len(df)) * 100
    })
    st.write(valores_ausentes)

# Análise de tipos de conteúdo (Filmes e Séries)
st.subheader("Distribuição de Tipos de Conteúdo")
if st.sidebar.checkbox('Mostrar gráfico de Tipos de Conteúdo'):
    fig, ax = plt.subplots(figsize=(8, 6))
    sns.countplot(data=df, x='type', ax=ax, palette="viridis")
    ax.set_title("Distribuição de Tipos de Conteúdo")
    ax.set_xlabel("Tipo de Conteúdo")
    ax.set_ylabel("Quantidade")
    st.pyplot(fig)

# Análise de lançamento por ano
st.subheader("Quantidade de Lançamentos por Ano")
df['release_year'] = pd.to_datetime(df['release_year'], format='%Y', errors='coerce').dt.year

if st.sidebar.checkbox('Mostrar gráfico de lançamentos por ano'):
    lançamentos_por_ano = df['release_year'].value_counts().sort_index()
    fig, ax = plt.subplots(figsize=(10, 6))
    ax.plot(lançamentos_por_ano.index, lançamentos_por_ano.values, marker='o', color='b')
    ax.set_title("Quantidade de Lançamentos por Ano")
    ax.set_xlabel("Ano")
    ax.set_ylabel("Quantidade de Lançamentos")
    st.pyplot(fig)

# Análise de Duração (Filmes e Séries)
st.subheader("Análise de Duração")

# Tratando os dados de duração
df['duration_num'] = df['duration'].str.extract(r'(\d+)').astype(float)
df['duration_type'] = df['duration'].str.extract(r'([a-zA-Z]+)').fillna('Desconhecido')

# Gráfico para filmes
if st.sidebar.checkbox('Mostrar gráfico de duração de filmes'):
    filmes_df = df[df['duration_type'] == 'min']
    fig, ax = plt.subplots(figsize=(8, 6))
    sns.histplot(filmes_df['duration_num'].dropna(), kde=True, bins=30, ax=ax, color="purple")
    ax.set_title("Distribuição da Duração dos Filmes (em Minutos)")
    ax.set_xlabel("Duração (Minutos)")
    ax.set_ylabel("Frequência")
    st.pyplot(fig)

# Filtros para explorar dados
st.sidebar.subheader("Filtros Interativos")

# Filtro de Tipo de Conteúdo
tipo_conteudo = st.sidebar.selectbox("Escolha o Tipo de Conteúdo", options=df['type'].dropna().unique())
if tipo_conteudo:
    st.subheader(f"Conteúdo do Tipo: {tipo_conteudo}")
    st.write(df[df['type'] == tipo_conteudo])

# Conclusão
st.sidebar.write("Explore os gráficos e os filtros para obter insights do dataset!")
