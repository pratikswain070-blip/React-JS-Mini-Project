import { defineConfig } from 'vite'
import react from '@vitejs/plugin-react'

// Support both Vercel (serves from '/') and GitHub Pages (serves from '/React-JS-Mini-Project/')
export default defineConfig({
  base: process.env.VERCEL ? '/' : '/React-JS-Mini-Project/',
  plugins: [react()],
})
