<script setup lang="ts">

import {type Ref, ref, watch} from 'vue';
import Configurator from "@/components/Configurator.vue";

const program = ref([]) as Ref<Array<ScheduleLine>>;


const defaultSchedule = [
	{"order": 1, "weekday": 1, "hour": 7, "minute": 30, "second": 0, "r": 255, "g": 64, "b": 0},
	{"order": 2, "weekday": 1, "hour": 19, "minute": 0, "second": 0, "r": 0, "g": 0, "b": 255},
	{"order": 3, "weekday": 2, "hour": 7, "minute": 30, "second": 0, "r": 255, "g": 64, "b": 0},
	{"order": 4, "weekday": 2, "hour": 19, "minute": 0, "second": 0, "r": 0, "g": 0, "b": 255},
	{"order": 5, "weekday": 3, "hour": 7, "minute": 30, "second": 0, "r": 255, "g": 64, "b": 0},
	{"order": 6, "weekday": 3, "hour": 19, "minute": 0, "second": 0, "r": 0, "g": 0, "b": 255},
	{"order": 7, "weekday": 4, "hour": 7, "minute": 30, "second": 0, "r": 255, "g": 64, "b": 0},
	{"order": 8, "weekday": 4, "hour": 19, "minute": 0, "second": 0, "r": 0, "g": 0, "b": 255}
] as Array<ScheduleLine>

const error = ref(false);

fetch('/program').then(response => response.json()).then(json => {
  program.value = json;
}).catch(() => {
	error.value = true;
})

const sortScore = (line: ScheduleLine) => {
	return (line.weekday * 24 * 60 * 60) + (line.hour * 60 * 60) + (line.minute * 60);
}

const save = function(){
	program.value.sort((a: ScheduleLine,b: ScheduleLine) => {
		return sortScore(a) - sortScore(b);
	});

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
  <main v-if="!error" class="container-sm">
    <Configurator v-model="program"/>
		<div>
			<button @click="save()" class="btn btn-primary save">Save program</button>
		</div>
  </main>
	<p v-else>Something went wrong, try reloading.</p>
</template>
