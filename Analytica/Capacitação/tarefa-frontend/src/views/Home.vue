<template>
  <v-container class="text-center py-12">
    <v-row justify="center">
      <v-col cols="12" md="8">
        <h1 class="display-2 font-weight-bold mb-4">
          🌍 Análise Populacional por País
        </h1>
        <p class="text-subtitle-1">
          Explore os dados demográficos de diferentes países a partir de um arquivo CSV. Clique em um país para ver detalhes!
        </p>
      </v-col>
    </v-row>

    <v-row justify="center">
      <v-col cols="12" md="6">
        <v-card class="pa-4" elevation="5">
          <v-card-title class="text-h5 font-weight-bold">
            Sobre o projeto
          </v-card-title>
          <v-card-text>
            Este projeto foi desenvolvido com Vue.js e Vuetify para treinar leitura de dados de arquivos CSV e visualização organizada por país
          </v-card-text>
        </v-card>
      </v-col>
    </v-row>
  </v-container>
</template>

<script setup>
</script>

<style scoped>
h1 {
  font-family: 'Poppins', sans-serif;
}
</style>
