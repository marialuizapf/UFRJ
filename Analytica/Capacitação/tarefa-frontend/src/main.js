import './assets/main.css'

import { createApp } from 'vue'
import App from './App.vue'

import router from './router'

import 'vuetify/styles' 
import { createVuetify } from 'vuetify'
import * as components from 'vuetify/components'
import * as directives from 'vuetify/directives'

const vuetify = createVuetify({
  components,
  directives,
  theme: {
  defaultTheme: 'dark', 
  themes: {
    dark: {
      colors: {
        background: '#0e0216ff', 
        primary: '#6A0DAD',
        secondary: '#331f41ff',
        accent: '#82B1FF'
      }
    }
  }
},
})

createApp(App)
  .use(router)
  .use(vuetify)
  .mount('#app')
