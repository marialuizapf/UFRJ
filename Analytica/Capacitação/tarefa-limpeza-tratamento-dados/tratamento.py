import pandas as pd
import numpy as np

bus = pd.read_csv('bus_data.csv', sep='|', decimal=',')
company = pd.read_csv('company_data.csv', sep=';')

#Substituindo valores nulos da coluna 'driver_name' por "motorista não atribuído" e 'bus_route' para "rota não atribuída"
print(bus.isna().sum())
print(company.isna().sum())

bus["bus_integrity"] = bus["bus_integrity"].replace({"-": None})
bus["bus_integrity"] = pd.to_numeric(bus["bus_integrity"])
bus['bus_integrity'] = bus['bus_integrity'].interpolate()

bus = bus.fillna(value={'driver_name': 'motorista não atribuído', 'bus_route': 'rota não atribuída'})

print(bus.isna().sum())

#Trocando a data pelo formato adequado (formato de data)
bus['bus_built_date'] = pd.to_datetime(bus['bus_built_date'], format="%m/%d/%Y")

print('Data após tratamento de dados:')
print(bus['bus_built_date'].head())

#Merge do dataframe 'bus_data' com o dataframe 'company_data'
merged_df = pd.merge(left=bus, right=company, left_on="bus_line_id", right_on="id", how="inner")
merged_df = merged_df.drop(columns=['id']) 

print('Dataframe após merge:')
print(merged_df.head())

#Criação de um mini dataframe agrupando 4 rotas de ônibus 
rotas = ['Urca-Lapa', 'Jardim Botânico-Ipanema', 'Copacabana-Leblon', 'Barra da Tijuca-Centro']
mini_df = merged_df[merged_df['bus_route'].isin(rotas)]

print('Mini dataframe com 4 rotas de ônibus:')
print(mini_df.head())

#Exportando o dataframe tratado para um arquivo CSV
merged_df.to_csv("dados_tratados.csv", index=False)
