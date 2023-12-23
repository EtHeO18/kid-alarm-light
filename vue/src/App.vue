<script setup lang="ts">

import { ref, watch } from 'vue';
const program = ref([]);

fetch('/program').then(response => response.json()).then(json => {
  console.log(json);
  program.value = json;
})

watch(program, val => {
  fetch('/program', {
    method: "POST",
    headers: {
      "Content-Type": "application/json",
    },
    body: JSON.stringify(program.value),
  });
});
</script>

<template>
  {{ program }}
  <main>
    <Configurator />
  </main>
</template>

<style scoped>

</style>
