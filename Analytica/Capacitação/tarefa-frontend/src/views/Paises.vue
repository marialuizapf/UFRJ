<template>
  <v-card :title="`População - ${pais}`" flat>
    <template v-slot:text>
      <v-text-field
        v-model="search"
        label="Buscar"
        prepend-inner-icon="mdi-magnify"
        variant="outlined"
        hide-details
        single-line
      ></v-text-field>
    </template>

    <v-data-table
      :headers="headers"
      :items="pessoasDoPais"
      :search="search"
      class="elevation-1"
    />
  </v-card>
</template>

<script>
import Papa from 'papaparse'

export default {
  props: {
    pais: String
  },
  data() {
    return {
      dados: [],
      search: '', // ← Adicionado aqui
      headers: [
        { text: 'Nome', value: 'nome' },
        { text: 'Sobrenome', value: 'sobrenome' },
        { text: 'Idade', value: 'idade' },
        { text: 'Gênero', value: 'genero' },
        { text: 'Salário', value: 'salario' },
        { text: 'Cidade', value: 'cidade' }
      ]
    }
  },
  computed: {
    pessoasDoPais() {
      return this.dados.filter(p => p.pais.toLowerCase() === this.pais.toLowerCase())
    }
  },
  mounted() {
    fetch('/dados-flask-treino.csv')
      .then(res => res.text())
      .then(csv => {
        Papa.parse(csv, {
          header: true,
          skipEmptyLines: true,
          complete: result => {
            this.dados = result.data.map(pessoa => {
              delete pessoa.id
              return pessoa
            })
          }
        })
      })
  }
}
</script>
