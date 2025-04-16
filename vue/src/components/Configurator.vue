<script setup lang="ts">
import {computed, type Ref, toRef, watch} from 'vue';
import ConfiguratorLine from "@/components/ConfiguratorLine.vue";
import draggable from 'vuedraggable'


const props = defineProps(['modelValue']);
const emit = defineEmits(['update:modelValue']);


const lines = toRef(props, "modelValue") as Ref<Array<ScheduleLine>>;

	const sortableLines = computed({
		
		get() {
			return lines.value
		},

		set(value){
			console.log('sortableLines.set', value)
			emit('update:modelValue', value);
		}
		
	});

// const emits = defineEmits(['update:modelValue']);

// watch(lines, () => {
// 	emits("update:modelValue", lines.value);
// })

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

//not necessary?!
const update = (line: ScheduleLine, newLine: ScheduleLine) => {
	// console.log({line, newLine})
}

</script>

<template>
	<div class="container-sm">
		<ul>
			<draggable v-model="sortableLines" item-key="id">
				<template #item="{element: line}">
					<ConfiguratorLine
					:line="line"
					@update="update"
					@delete="lines.splice(lines.indexOf(line), 1)"
				/>
				</template>
			</draggable>
			
		</ul>
	</div>
	<div>
		<button @click="addNew()" class="btn btn-secondary add-new">+</button>
	</div>
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