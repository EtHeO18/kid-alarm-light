<script setup lang="ts">
import {type Ref, toRef, watch} from 'vue';
import ConfiguratorLine from "@/components/ConfiguratorLine.vue";

const props = defineProps(['modelValue']);



const lines = toRef(props, "modelValue") as Ref<Array<ScheduleLine>>;

const emits = defineEmits(['update:modelValue']);

watch(lines, () => {
	emits("update:modelValue", lines.value);
})

const addNew = function(){
	lines.value.push({
		"weekday": 1,
		"hour": 7,
		"minute": 30,
		"second": 0,
		"r": 255,
		"g": 64,
		"b": 0,
	} as ScheduleLine);
}

</script>

<template>
		<ul>
			<ConfiguratorLine
					v-for="(line, index) in lines"
					v-model="lines[index]"
					@delete="lines.splice(index, 1)"
			/>
      <li class="row">
        <div class="col-4">
          <button @click="addNew()" class="btn btn-primary">Add</button>
        </div>

      </li>
		</ul>

</template>

<style>
ul {
	list-style: none;
	margin: 0;
	padding: 0;
}

fieldset {
	border: 0;
	display: inline;
}

</style>