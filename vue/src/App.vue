<script setup lang="ts">

import {type Ref, ref, watch} from 'vue';
import Configurator from "@/components/Configurator.vue";

const program = ref([]) as Ref<Array<ScheduleLine>>;


const defaultSchedule = [
	{"weekday": 1, "hour": 7, "minute": 30, "second": 0, "r": 255, "g": 64, "b": 0},
	{"weekday": 1, "hour": 19, "minute": 0, "second": 0, "r": 0, "g": 0, "b": 255},
	{"weekday": 2, "hour": 7, "minute": 30, "second": 0, "r": 255, "g": 64, "b": 0},
	{"weekday": 2, "hour": 19, "minute": 0, "second": 0, "r": 0, "g": 0, "b": 255},
	{"weekday": 3, "hour": 7, "minute": 30, "second": 0, "r": 255, "g": 64, "b": 0},
	{"weekday": 3, "hour": 19, "minute": 0, "second": 0, "r": 0, "g": 0, "b": 255},
	{"weekday": 4, "hour": 7, "minute": 30, "second": 0, "r": 255, "g": 64, "b": 0},
	{"weekday": 4, "hour": 19, "minute": 0, "second": 0, "r": 0, "g": 0, "b": 255}
] as Array<ScheduleLine>

const error = ref(false);

fetch('/program').then(response => response.json()).then(json => {
  program.value = json;
}).catch(() => {
	error.value = true;
})

const save = function(){
  fetch('/program', {
    method: "POST",
    headers: {
      "Content-Type": "application/json",
    },
    body: JSON.stringify(program.value),
  });
}

</script>

<template>
  <main v-if="!error">
    <Configurator v-model="program"/>
		<div>

			<button @click="save()" class="save">Save program</button>
		</div>
  </main>
	<p v-else>Something went wrong, try reloading.</p>
</template>

<style>
.save {
	float: right;
	margin: 1em
}
</style>
