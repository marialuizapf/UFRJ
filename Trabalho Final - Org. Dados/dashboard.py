import streamlit as st
import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns
import plotly.express as px

# Configurar a página do Streamlit
st.set_page_config(page_title="Dashboard Netflix", layout="wide")

# Função para carregar o dataset
@st.cache_data
def carregar_dados():
    df = pd.read_csv('netflix_titles.csv')
    df.fillna('Desconhecido', inplace=True)  # Preencher valores nulos com "Desconhecido"
    return df

# Carregar o dataset
df = carregar_dados()

# Título do Dashboard
st.title("Dashboard Interativo - Netflix Dataset")

# Estatísticas Descritivas no Formato Personalizado
st.subheader("Estatísticas Descritivas")
col1, col2, col3, col4, col5 = st.columns(5)

with col1:
    count = df['duration'].count()
    st.metric(label="Contagem de Duração", value=f"{count}", help="Quantos filmes têm uma duração registrada?")

with col2:
    mean_duration = df['duration'].str.extract(r'(\d+)').astype(float).mean()[0]
    st.metric(label="Duração Média (min)", value=f"{mean_duration:.2f}", help="Qual é a duração média dos filmes registrados?")

with col3:
    std_duration = df['duration'].str.extract(r'(\d+)').astype(float).std()[0]
    st.metric(label="Desvio Padrão (min)", value=f"{std_duration:.2f}", help="Qual é o desvio padrão das durações dos filmes?")

with col4:
    min_year = df['release_year'].min()
    st.metric(label="Ano Mais Antigo", value=f"{int(min_year)}", help="Qual é o ano mais antigo de lançamento registrado?")

with col5:
    max_year = df['release_year'].max()
    st.metric(label="Ano Mais Recente", value=f"{int(max_year)}", help="Qual é o ano mais recente de lançamento registrado?")

col6, col7, col8, col9, col10 = st.columns(5)

with col6:
    total_movies = len(df[df['type'] == "Movie"])
    st.metric(label="Total de Filmes", value=f"{total_movies}", help="Quantos filmes estão registrados no dataset?")

with col7:
    total_shows = len(df[df['type'] == "TV Show"])
    st.metric(label="Total de Séries", value=f"{total_shows}", help="Quantas séries estão registradas no dataset?")

with col8:
    generos_filtrados = df['listed_in'].dropna().str.split(',').explode().str.strip()
    generos_filtrados = generos_filtrados[~generos_filtrados.isin(["International Movies", "International TV Shows"])]
    unique_genres = generos_filtrados.nunique()
    st.metric(label="Total de Gêneros", value=f"{unique_genres}", help="Quantos gêneros diferentes estão registrados no dataset (exceto 'International')?")

with col9:
    unique_countries = df['country'].nunique()
    st.metric(label="Total de Países", value=f"{unique_countries}", help="De quantos países diferentes são os lançamentos registrados?")

with col10:
    total_directors = df['director'].nunique()
    st.metric(label="Total de Diretores", value=f"{total_directors}", help="Quantos diretores diferentes estão registrados?")

# Distribuição de Tipos de Conteúdo
st.subheader("Distribuição de Tipos de Conteúdo")
fig_pizza = px.pie(df, names='type', title='Distribuição de Filmes e Séries', color_discrete_sequence=px.colors.sequential.Viridis)
st.plotly_chart(fig_pizza)

# Tendências de Lançamento por Ano
st.subheader("Quantidade de Lançamentos por Ano")
df['release_year'] = pd.to_datetime(df['release_year'], format='%Y', errors='coerce').dt.year
lancamentos_por_ano = df['release_year'].value_counts().sort_index()
fig, ax = plt.subplots(figsize=(10, 6))
ax.plot(lancamentos_por_ano.index, lancamentos_por_ano.values, marker='o', color='purple')
ax.set_title("Quantidade de Lançamentos por Ano")
ax.set_xlabel("Ano")
ax.set_ylabel("Quantidade de Lançamentos")
st.pyplot(fig)

# Gêneros Populares
st.subheader("Gêneros Mais Populares")
generos_mais_frequentes = generos_filtrados.value_counts()

# Gráfico de Barras dos Gêneros
fig, ax = plt.subplots(figsize=(10, 6))
sns.barplot(x=generos_mais_frequentes.head(10).values, y=generos_mais_frequentes.head(10).index, palette="viridis", ax=ax)
ax.set_title("Top 10 Gêneros Mais Frequentes")
ax.set_xlabel("Frequência")
ax.set_ylabel("Gêneros")
st.pyplot(fig)

# Países com Mais Lançamentos
st.subheader("Países com Mais Lançamentos")
pais_lancamentos = df['country'].value_counts().head(10)
fig, ax = plt.subplots(figsize=(10, 6))
sns.barplot(x=pais_lancamentos.values, y=pais_lancamentos.index, palette="viridis", ax=ax)
ax.set_title("Top 10 Países com Mais Lançamentos")
ax.set_xlabel("Quantidade de Lançamentos")
ax.set_ylabel("País")
st.pyplot(fig)

# Distribuição da Duração (Filmes)
st.subheader("Distribuição da Duração (Filmes)")
df['duration_num'] = df['duration'].str.extract(r'(\d+)').astype(float)
df['duration_type'] = df['duration'].str.extract(r'([a-zA-Z]+)').fillna('Desconhecido')

duração_filmes = df[df['duration_type'].str.contains('min', case=False, na=False)]
fig, ax = plt.subplots(figsize=(10, 6))
sns.histplot(duração_filmes['duration_num'].dropna(), kde=True, bins=30, color='purple', ax=ax)
ax.set_title("Distribuição da Duração (Filmes - Minutos)")
ax.set_xlabel("Duração (min)")
ax.set_ylabel("Frequência")
st.pyplot(fig)

# Recursos Interativos Adicionais
st.sidebar.header("Filtros Interativos")

# Filtro por Tipo de Conteúdo
tipo = st.sidebar.selectbox(
    "Selecione o Tipo de Conteúdo", 
    options=["Todos", "Movie", "TV Show"]
)

# Filtro por Ano de Lançamento
anos = st.sidebar.slider("Selecione o Ano de Lançamento", int(df['release_year'].min()), int(df['release_year'].max()), (2000, 2020))

# Filtro por Gênero
genero = st.sidebar.multiselect("Escolha Gêneros", options=generos_filtrados.unique())

# Filtro por País
pais = st.sidebar.multiselect("Escolha Países", options=df['country'].dropna().unique())

# Busca por Título
st.sidebar.subheader("Busca por Título")
titulo_busca = st.sidebar.text_input("Digite um Título para Buscar")
if titulo_busca:
    resultados = df[df['title'].str.contains(titulo_busca, case=False, na=False)]
    st.write(resultados)

# Busca por Diretor
st.sidebar.subheader("Busca por Diretor")
diretor = st.sidebar.text_input("Digite o Nome do Diretor")

# Busca por Elenco
st.sidebar.subheader("Busca por Elenco")
elenco = st.sidebar.text_input("Digite o Nome do Ator/Atriz")

# Aplicar Filtros
df_filtrado = df[
    ((df['type'] == tipo) if tipo != "Todos" else True) &
    (df['release_year'].between(anos[0], anos[1])) &
    (df['country'].isin(pais) if pais else True) &
    (df['listed_in'].str.contains('|'.join(genero), na=False) if genero else True) &
    (df['director'].str.contains(diretor, case=False, na=False) if diretor else True) &
    (df['cast'].str.contains(elenco, case=False, na=False) if elenco else True)
]

# Renomear colunas para português
colunas_traduzidas = {
    'show_id': 'ID',
    'type': 'Tipo',
    'title': 'Título',
    'director': 'Diretor',
    'cast': 'Elenco',
    'country': 'País',
    'date_added': 'Data de Adição',
    'release_year': 'Ano de Lançamento',
    'rating': 'Classificação',
    'duration': 'Duração',
    'listed_in': 'Gêneros',
    'description': 'Descrição',
    'duration_num': 'Tempo de Duração',
    'duration_type': 'Tipo de Duração'
}

df_filtrado.rename(columns=colunas_traduzidas, inplace=True)

# Exibir tabela com cabeçalhos traduzidos
st.subheader("Tabela de Dados Personalizável")
st.write(df_filtrado)
