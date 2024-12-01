import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns

# Carregar o dataset
df = pd.read_csv('netflix_titles.csv')

### VISUALIZAÇÃO INICIAL
# Visualizar as primeiras linhas do dataset
print("Primeiras linhas do dataset:")
print(df.head())

# Informações gerais sobre o dataset
print("Informações gerais sobre o dataset:")
print(df.info())

# Estatísticas descritivas
print("Estatísticas descritivas:")
print(df.describe())

### CORREÇÃO DO DATASET
# Preencher valores nulos com 'Desconhecido'
df.fillna('Desconhecido', inplace=True)

# Verificar valores nulos 
print("Valores nulos por coluna:")
print(df.isnull().sum())

### ESTATÍSTICAS
# Distribuição de categorias 
print("Distribuição de tipos de conteúdo:")
print(df['type'].value_counts())

# Estatísticas de colunas numéricas
print("Estatísticas gerais:")
print(df.describe())

### FIGURA 1: Distribuição de Tipos de Conteúdo
sns.countplot(data=df, x='type', palette='viridis')
plt.title("Distribuição de Tipos de Conteúdo")
plt.xlabel("Tipo")
plt.ylabel("Quantidade")
plt.show()

### FIGURA 2: Tendência de Lançamentos por Ano
# Converter release_year para numérico
df['release_year'] = pd.to_datetime(df['release_year'], format='%Y', errors='coerce').dt.year

# Agrupar lançamentos por ano
conteudo_por_ano = df['release_year'].value_counts().sort_index()

plt.plot(conteudo_por_ano.index, conteudo_por_ano.values, marker='o', color='purple')
plt.title("Quantidade de Conteúdo por Ano")
plt.xlabel("Ano")
plt.ylabel("Quantidade")
plt.grid()
plt.show()

### FIGURA 3: Gêneros Mais Populares
# Separar e contar os gêneros
generos_filtrados = df['listed_in'].str.split(',').explode().str.strip()
generos_mais_frequentes = generos_filtrados.value_counts()

sns.barplot(x=generos_mais_frequentes.head(10).values, y=generos_mais_frequentes.head(10).index, palette='viridis')
plt.title("Top 10 Gêneros Mais Populares")
plt.xlabel("Frequência")
plt.ylabel("Gênero")
plt.show()

### FIGURA 4: Países com Mais Lançamentos
# Contar os países
pais_lancamentos = df['country'].value_counts().head(10)

sns.barplot(x=pais_lancamentos.values, y=pais_lancamentos.index, palette='viridis')
plt.title("Top 10 Países com Mais Lançamentos")
plt.xlabel("Quantidade de Lançamentos")
plt.ylabel("País")
plt.show()

### FIGURA 5: Distribuição da Duração (Filmes)
# Separar valores numéricos da coluna 'duration'
df['duration_num'] = df['duration'].str.extract('(\d+)').astype(float)
df['duration_type'] = df['duration'].str.extract('([a-zA-Z]+)').fillna('Desconhecido')

# Filtrar apenas filmes
duração_filmes = df[df['duration_type'].str.contains('min', case=False, na=False)]

sns.histplot(duração_filmes['duration_num'].dropna(), kde=True, bins=30, color='blue')
plt.title("Distribuição da Duração (Filmes - Minutos)")
plt.xlabel("Duração (min)")
plt.ylabel("Frequência")
plt.show()

### FIGURE 6: Distribuição de Anos de Lançamento
sns.histplot(df['release_year'].dropna(), bins=20, kde=False, color='green')
plt.title("Distribuição de Anos de Lançamento")
plt.xlabel("Ano")
plt.ylabel("Frequência")
plt.show()
