import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns
#import numpy as np

# Carregar o dataset
df = pd.read_csv('netflix_titles.csv')

### VISUALIZAÇÃO INICIAL
print("Primeiras linhas do dataset:")
print(df.head())

print("Informações gerais sobre o dataset:")
print(df.info())

print("Estatísticas descritivas:")
print(df.describe())

### CORREÇÃO DO DATASET
# Preencher valores nulos com 'Desconhecido'
df.fillna('Desconhecido', inplace=True)

# Verificar valores nulos após correção
print("Valores nulos por coluna após correção:")
print(df.isnull().sum())

# Separar valores numéricos e tipos de duração
df['duration_num'] = df['duration'].str.extract('(\d+)').astype(float)
df['duration_type'] = df['duration'].str.extract('([a-zA-Z]+)').fillna('Desconhecido')

### ESTATÍSTICAS
# Medidas estatísticas adicionais
print("\nMédia, Mediana e Moda da duração (min):")
print(f"Média: {df['duration_num'].mean():.2f}")
print(f"Mediana: {df['duration_num'].median():.2f}")
print(f"Moda: {df['duration_num'].mode().iloc[0]:.2f}")

### INSIGHTS
print("\nInsights e Padrões Identificados:")
print("- Filmes têm maior variabilidade de duração comparado a séries.")
print("- Certos países, como os EUA e Índia, dominam os lançamentos.")
print("- Gêneros mais populares incluem Drama, Comédia e Ação.")
print("- A maioria dos lançamentos ocorreu nos últimos 20 anos, refletindo a expansão do streaming.")

### FIGURA 1: Distribuição de Tipos de Conteúdo
sns.countplot(data=df, x='type', palette='viridis')
plt.title("Distribuição de Tipos de Conteúdo")
plt.xlabel("Tipo")
plt.ylabel("Quantidade")
plt.show()

### FIGURA 2: Tendência de Lançamentos por Ano
df['release_year'] = pd.to_datetime(df['release_year'], format='%Y', errors='coerce').dt.year
conteudo_por_ano = df['release_year'].value_counts().sort_index()
plt.plot(conteudo_por_ano.index, conteudo_por_ano.values, marker='o', color='purple')
plt.title("Tendência de Lançamentos por Ano")
plt.xlabel("Ano")
plt.ylabel("Quantidade")
plt.grid()
plt.show()

### FIGURA 3: Gêneros Mais Populares (Sem International Movies/TV Shows)
generos_filtrados = df['listed_in'].str.split(',').explode().str.strip()
generos_filtrados = generos_filtrados[~generos_filtrados.isin(['International Movies', 'International TV Shows'])]
generos_mais_frequentes = generos_filtrados.value_counts()
sns.barplot(x=generos_mais_frequentes.head(10).values, y=generos_mais_frequentes.head(10).index, palette='viridis')
plt.title("Top 10 Gêneros Mais Populares")
plt.xlabel("Frequência")
plt.ylabel("Gênero")
plt.show()

### FIGURA 4: Países com Mais Lançamentos
pais_lancamentos = df['country'].value_counts().head(10)

sns.barplot(x=pais_lancamentos.values, y=pais_lancamentos.index, palette='viridis')
plt.title("Top 10 Países com Mais Lançamentos")
plt.xlabel("Quantidade de Lançamentos")
plt.ylabel("País")
plt.show()

### FIGURA 5: Distribuição da Duração (Filmes)
duração_filmes = df[df['duration_type'].str.contains('min', case=False, na=False)]

sns.histplot(duração_filmes['duration_num'].dropna(), kde=True, bins=30, color='blue')
plt.title("Distribuição da Duração (Filmes - Minutos)")
plt.xlabel("Duração (min)")
plt.ylabel("Frequência")
plt.show()

# FIGURA 6: Gráfico de Dispersão Simples com Linha de Tendência
df_corr = df[['release_year', 'duration_num']].dropna()

plt.figure(figsize=(8, 6))
plt.scatter(df_corr['release_year'], df_corr['duration_num'], alpha=0.5, color='purple', label='Dados')
sns.regplot(x='release_year', y='duration_num', data=df_corr, scatter=False, color='orange', label='Tendência')

plt.title("Correlação entre Ano de Lançamento e Duração")
plt.xlabel("Ano de Lançamento")
plt.ylabel("Duração (min)")
plt.legend()
plt.grid(True, linestyle='--', alpha=0.5)
plt.show()

# Lista de classificações válidas
ratings_validos = [
    'G', 'PG', 'PG-13', 'R', 'NC-17', 'TV-Y', 'TV-Y7', 'TV-G', 
    'TV-PG', 'TV-14', 'TV-MA', 'NR', 'UR', 'TV-Y7-FV'
]

# Filtrar apenas classificações válidas
df_rating_limpo = df[df['rating'].isin(ratings_validos)]

# FIGURA 7: Distribuição de Classificação 
ratings = df_rating_limpo['rating'].value_counts()

sns.barplot(x=ratings.values, y=ratings.index, palette='viridis')
plt.title("Distribuição de Classificação")
plt.xlabel("Frequência")
plt.ylabel("Classificação")
plt.show()

# FIGURA 8:Diretores com Mais Lançamentos
top_diretores = df[df['director'] != 'Desconhecido']['director'].dropna().value_counts().head(10)

sns.barplot(x=top_diretores.values, y=top_diretores.index, palette='viridis')
plt.title("Top 10 Diretores com Mais Lançamentos")
plt.xlabel("Quantidade de Lançamentos")
plt.ylabel("Diretor")
plt.show()

# FIGURA 9:Sazonalidade de Adições ao Catálogo
df['date_added'] = pd.to_datetime(df['date_added'], errors='coerce')
df['month_added'] = df['date_added'].dt.month
meses_adicoes = df['month_added'].value_counts().sort_index()

meses = ["Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"]
plt.bar(meses, meses_adicoes, color='purple', alpha=0.7)
plt.title("Sazonalidade de Adições ao Catálogo")
plt.xlabel("Mês")
plt.ylabel("Quantidade de Adições")
plt.show()

# FIGURA 10:Medidas estatísticas adicionais para o ano de lançamento
print("\nMédia, Mediana e Moda do ano de lançamento:")
print(f"Média: {df['release_year'].mean():.2f}")
print(f"Mediana: {df['release_year'].median():.2f}")
print(f"Moda: {df['release_year'].mode().iloc[0]:.0f}")

# FIGURA 11:Distribuição de tipos de conteúdo
print("\nDistribuição de tipos de conteúdo:")
print(df['type'].value_counts())

