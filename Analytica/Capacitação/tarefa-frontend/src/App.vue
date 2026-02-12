<template>
  <v-app>
    <v-app-bar app color="primary" dark>
      <v-toolbar-title>Países</v-toolbar-title>
      <v-spacer></v-spacer>

      <v-btn text to="/">Home</v-btn>
      <v-btn text to="/brasil">Brasil</v-btn>
      <v-btn text to="/argentina">Argentina</v-btn>
      <v-btn text to="/venezuela">Venezuela</v-btn>
    </v-app-bar>

    <v-main>
      <router-view />
    </v-main>
  </v-app>
</template>

<script>
export default {
  name: 'App'
}
</script>

<style scoped>
.v-toolbar-title {
 
  font-size: 32px;
  text-transform: uppercase;
  letter-spacing: 2.4px;
}
</style>
