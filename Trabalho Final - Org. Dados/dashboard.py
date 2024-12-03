import streamlit as st
import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns
import plotly.express as px

# Configurar a página do Streamlit
st.set_page_config(
    page_title="Dashboard Netflix", 
    page_icon="https://raw.githubusercontent.com/marialuizapf/UFRJ/main/Trabalho%20Final%20-%20Org.%20Dados/Imagens/icon.png", 
    layout="wide"
)

# Função para carregar o dataset
@st.cache_data
def carregar_dados():
    df = pd.read_csv('netflix_titles.csv')
    df.fillna('Desconhecido', inplace=True)  
    return df

# Carregar o dataset
df = carregar_dados()

# Título do Dashboard
st.markdown('<h3 style="text-align: left; font-size:32px;">Catálogo Netflix: Estatísticas e Tendências</h3>', unsafe_allow_html=True)
st.text("") 
st.text("") 

#-----------------------------------------------------------------------------------

# Estatísticas Descritivas 
col1, col2, col3, col4, col5 = st.columns(5)

with col1:
    df['duration_num'] = df['duration'].str.extract(r'(\d+)').astype(float)
    df_filmes = df[df['type'] == 'Movie']  
    moda_duracao = df_filmes['duration_num'].mode().iloc[0]  
    st.metric(label="Moda da Duração (Filmes)", value=f"{moda_duracao:.0f}", help="Valor mais frequente de duração entre os filmes.")

with col2:
    mean_duration = df['duration'].str.extract(r'(\d+)').astype(float).mean()[0]
    st.metric(label="Duração Média (min)", value=f"{mean_duration:.2f}", help="Qual é a duração média dos filmes registrados?")

with col3:
    std_duration = df['duration'].str.extract(r'(\d+)').astype(float).std()[0]
    st.metric(label="Desvio Padrão (min)", value=f"{std_duration:.2f}", help="Qual é o desvio padrão das durações dos filmes?")

with col4:
    moda_ano = df['release_year'].mode().iloc[0]
    st.metric(label="Moda do Ano", value=f"{int(moda_ano)}", help="Ano de lançamento mais frequente registrado no dataset.")

with col5:
    mean_year = df['release_year'].mean()
    st.metric(label="Média do Ano", value=f"{mean_year:.1f}", help="Média dos anos de lançamento registrados no dataset.")

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

#-----------------------------------------------------------------------------------

# Recursos Interativos Adicionais
st.sidebar.image("https://raw.githubusercontent.com/marialuizapf/UFRJ/main/Trabalho%20Final%20-%20Org.%20Dados/Imagens/icon_big.png")
st.text("") 
st.text("") 
st.sidebar.header("Filtre os dados")

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
st.write(df_filtrado) 

st.markdown("---")
#-----------------------------------------------------------------------------------

# Distribuição de Tipos de Conteúdo
st.markdown('<h4 style="text-align: left; font-size:24px;">Distribuição de Tipos de Conteúdo</h4>', unsafe_allow_html=True)
fig_pizza = px.pie(df, names='type', title='', color_discrete_sequence=px.colors.sequential.Viridis)
st.plotly_chart(fig_pizza)

st.markdown("---")
#-----------------------------------------------------------------------------------

col13, col14 = st.columns(2)

with col13:
     # Tendências de Lançamento por Ano
    st.markdown('<h4 style="text-align: left; font-size:24px;">Quantidade de Lançamentos por Ano</h4>', unsafe_allow_html=True)
    df['release_year'] = pd.to_datetime(df['release_year'], format='%Y', errors='coerce').dt.year
    lancamentos_por_ano = df['release_year'].value_counts().sort_index()
    fig, ax = plt.subplots(figsize=(10, 6))
    ax.plot(lancamentos_por_ano.index, lancamentos_por_ano.values, marker='o', color='purple')
    ax.set_title("")
    ax.set_xlabel("Ano")
    ax.set_ylabel("Quantidade de Lançamentos")
    st.pyplot(fig)

#-----------------------------------------------------------------------------------

with col14:
    # Sazonalidade de Adições ao Catálogo 
    st.markdown('<h4 style="text-align: left; font-size:24px;">Sazonalidade de Adições ao Catálogo</h4>', unsafe_allow_html=True)
    df['date_added'] = pd.to_datetime(df['date_added'], errors='coerce')
    df['month_added'] = df['date_added'].dt.month
    meses_adicoes = df['month_added'].value_counts().sort_index()
    meses = ["Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"]
    fig, ax = plt.subplots(figsize=(10, 6))
    sns.barplot(x=meses[:len(meses_adicoes)], y=meses_adicoes.values, palette="viridis", ax=ax)  
    ax.set_title("")
    ax.set_xlabel("Mês")
    ax.set_ylabel("Quantidade de Adições")
    st.pyplot(fig)

st.markdown("---")

#-----------------------------------------------------------------------------------

# Distribuição de Classificação 
st.markdown('<h4 style="text-align: left; font-size:24px;">Distribuição de Classificação</h4>', unsafe_allow_html=True)


ratings_validos = [
    'G', 'PG', 'PG-13', 'R', 'NC-17', 'TV-Y', 'TV-Y7', 'TV-G', 
    'TV-PG', 'TV-14', 'TV-MA', 'NR', 'UR', 'TV-Y7-FV'
]

df_rating_limpo = df[df['rating'].isin(ratings_validos)]

ratings = df_rating_limpo['rating'].value_counts()

ratings_percent = (ratings / ratings.sum()) * 100

ratings_principais = ratings[ratings_percent >= 1]
outros = ratings[ratings_percent < 1].sum()

dados_ratings = pd.concat([ratings_principais, pd.Series({'Outros': outros})])

fig = px.pie(
    names=dados_ratings.index,
    values=dados_ratings.values,
    title="",
    hole=0.4,  # Criar o "buraco" no centro para formato de rosca
    color_discrete_sequence=px.colors.sequential.Viridis
)
st.plotly_chart(fig)

st.markdown("---")
#-----------------------------------------------------------------------------------
col15, col16 = st.columns(2)

with col15:
    # Gêneros Populares
    st.markdown('<h4 style="text-align: left; font-size:24px;">Gêneros Mais Populares</h4>', unsafe_allow_html=True)

    generos_mais_frequentes = generos_filtrados.value_counts()
    fig, ax = plt.subplots(figsize=(10, 6))
    sns.barplot(x=generos_mais_frequentes.head(10).values, y=generos_mais_frequentes.head(10).index, palette="viridis", ax=ax)
    ax.set_title("")
    ax.set_xlabel("Frequência")
    ax.set_ylabel("Gêneros")
    st.pyplot(fig)

#-----------------------------------------------------------------------------------

with col16:
    # Diretores com Mais Lançamentos
    st.markdown('<h4 style="text-align: left; font-size:24px;">Diretores com Mais Lançamentos</h4>', unsafe_allow_html=True)


    top_diretores = df[df['director'] != 'Desconhecido']['director'].dropna().value_counts().head(10)

    fig, ax = plt.subplots(figsize=(10, 6))
    sns.barplot(x=top_diretores.values, y=top_diretores.index, palette='viridis', ax=ax)

    ax.set_title("")
    ax.set_xlabel("Quantidade de Lançamentos")
    ax.set_ylabel("Diretor")

    st.pyplot(fig)

st.markdown("---")

#-----------------------------------------------------------------------------------

# Dispersão Simples com Linha de Tendência
st.markdown('<h4 style="text-align: left; font-size:24px;">Correlação entre Ano de Lançamento e Duração</h4>', unsafe_allow_html=True)


if 'duration_num' not in df.columns:
    df['duration_num'] = df['duration'].str.extract(r'(\d+)').astype(float)

df_corr = df[['release_year', 'duration_num']].dropna()

fig, ax = plt.subplots(figsize=(8, 6))

ax.scatter(df_corr['release_year'], df_corr['duration_num'], alpha=0.5, color='purple', label='Dados')

sns.regplot(x='release_year', y='duration_num', data=df_corr, scatter=False, color='#3b9f7a', label='Tendência', ax=ax)

ax.set_title("")
ax.set_xlabel("Ano de Lançamento")
ax.set_ylabel("Duração (min)")
ax.legend()
ax.grid(True, linestyle='--', alpha=0.5)
st.pyplot(fig)
st.markdown("---")

#-----------------------------------------------------------------------------------
col17, col18 = st.columns(2)

with col17:
    # Países com Mais Lançamentos
    st.markdown('<h4 style="text-align: left; font-size:24px;">Países com Mais Lançamentos</h4>', unsafe_allow_html=True)

    pais_lancamentos = df[df['country'] != 'Desconhecido']['country'].value_counts().head(10)
    fig, ax = plt.subplots(figsize=(10, 6))
    sns.barplot(x=pais_lancamentos.values, y=pais_lancamentos.index, palette="viridis", ax=ax)
    ax.set_title("")
    ax.set_xlabel("Quantidade de Lançamentos")
    ax.set_ylabel("País")
    st.pyplot(fig)

#-----------------------------------------------------------------------------------

with col18:
# Distribuição da Duração (Filmes)
    st.markdown('<h4 style="text-align: left; font-size:24px;">Distribuição da Duração (Filmes)</h4>', unsafe_allow_html=True)

    df['duration_num'] = df['duration'].str.extract(r'(\d+)').astype(float)
    df['duration_type'] = df['duration'].str.extract(r'([a-zA-Z]+)').fillna('Desconhecido')
    duração_filmes = df[df['duration_type'].str.contains('min', case=False, na=False)]
    fig, ax = plt.subplots(figsize=(10, 6))
    sns.histplot(duração_filmes['duration_num'].dropna(), kde=True, bins=30, color="#4B0082", ax=ax)
    ax.set_title("")
    ax.set_xlabel("Duração (min)")
    ax.set_ylabel("Frequência")
    st.pyplot(fig)
