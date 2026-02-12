import { createRouter, createWebHistory } from 'vue-router'
import Home from '../views/Home.vue'
import Paises from '../views/Paises.vue'

const routes = [
  { path: '/', component: Home }, 
  { path: '/brasil',  component: Paises, props: { pais: 'Brazil' } },
  { path: '/argentina', component: Paises, props: { pais: 'Argentina' } },
  { path: '/venezuela',   component: Paises, props: { pais: 'Venezuela'  } },
]

const router = createRouter({
  history: createWebHistory(),
  routes,
})

export default router

