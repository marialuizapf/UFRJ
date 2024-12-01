import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns

### VISUALIZAÇÃO
# Carregar o dataset
df = pd.read_csv('netflix_titles.csv')

# Visualizar as primeiras linhas do dataset
print(df.head())

# Informações gerais sobre o dataset
print(df.info())

# Estatísticas descritivas
print(df.describe())


### CORREÇÃO DO DATASET
# Verificar valores nulos
print("Valores nulos por coluna:")
print(df.isnull().sum())

# Percentual de valores ausentes
print((df.isnull().sum() / len(df)) * 100)


### ESTATÍSTICA 
# Estatísticas de colunas numéricas
print("Estatísticas gerais:")
print(df.describe())

# Distribuição de categorias, por exemplo, o tipo (filmes ou séries)
print("Distribuição de tipos de conteúdo:")
print(df['type'].value_counts())


### FIGURE 1
# Gráfico de barras para tipos de conteúdo
sns.countplot(data=df, x='type')
plt.title("Distribuição de Tipos de Conteúdo")
plt.show()

### FIGURE 2
# Gráfico de linha do tempo (exemplo: quantidade de lançamentos por ano)
df['release_year'] = pd.to_datetime(df['release_year'], format='%Y', errors='coerce')
conteudo_por_ano = df.groupby('release_year').size()

plt.plot(conteudo_por_ano.index, conteudo_por_ano.values)
plt.title("Quantidade de Conteúdo por Ano")
plt.xlabel("Ano")
plt.ylabel("Quantidade")
plt.show()


### CORREÇÃO
# Substituir valores nulos com 'Desconhecido' ou apagar linhas
df['director'].fillna('Desconhecido', inplace=True)

# Apagar linhas com muitos valores ausentes (opcional)
df.dropna(subset=['cast', 'country'], inplace=True)

# Conferir se os valores ausentes foram tratados
print(df.isnull().sum())


### FIGURE 3
# Verificar as primeiras linhas da coluna 'duration'
print(df['duration'].head())

# Identificar valores únicos na coluna 'duration'
print("Valores únicos na coluna 'duration':")
print(df['duration'].unique())

# Separar valores numéricos da duração
# Criar duas novas colunas: uma para o número e outra para o tipo de duração (minutos ou temporadas)
df['duration_num'] = df['duration'].str.extract('(\d+)').astype(float)  # Extrai números
df['duration_type'] = df['duration'].str.extract('([a-zA-Z]+)').fillna('Desconhecido')  # Extrai o texto

# Visualizar como ficou a transformação
print(df[['duration', 'duration_num', 'duration_type']].head())

# Verificar estatísticas apenas para filmes (minutos)
print("Estatísticas para duração em minutos:")
print(df[df['duration_type'] == 'min']['duration_num'].describe())

# Gráfico de distribuição de duração (filmes)
sns.histplot(df[df['duration_type'] == 'min']['duration_num'].dropna(), kde=True, bins=30)
plt.title("Distribuição da Duração (Filmes - Minutos)")
plt.xlabel("Duração (min)")
plt.ylabel("Frequência")
plt.show()


### FIGURE 4
# Verificar a frequência de temporadas (séries) 
print("Frequência de Temporadas:")
print(df[df['duration_type'] == 'Season']['duration_num'].value_counts())

sns.histplot(df['release_year'], bins=20, kde=False)
plt.title("Distribuição de Anos de Lançamento")
plt.xlabel("Ano")
plt.ylabel("Frequência")
plt.show()
