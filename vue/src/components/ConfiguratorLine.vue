<script setup lang="ts">
import {computed, toRef, watch} from "vue";

	const props = defineProps(['line'])
	const line = toRef(props, 'line')

	const emit = defineEmits(['delete', 'update'])

	const time = computed({
		get(){
			const date = new Date();

			const hour = (''+line.value.hour).padStart(2, '0')
			const minute = (''+line.value.minute).padStart(2, '0')
			const second = (''+line.value.second).padStart(2, '0')

			return `${hour}:${minute}:${second}`;
		},
		set(val: string) {
			const parts = val.split(/:/);

			console.log(parts);
			line.value.hour = parseInt(parts[0]);
			line.value.minute = parseInt(parts[1]);
			line.value.second = parseInt(parts[2]);
		}
	})

function componentToHex(c: number) {
	var hex = c.toString(16);
	return hex.length == 1 ? "0" + hex : hex;
}

function hexToRgb(hex: string) {
	var result = /^#?([a-f\d]{2})([a-f\d]{2})([a-f\d]{2})$/i.exec(hex);
	return result ? {
		r: parseInt(result[1], 16),
		g: parseInt(result[2], 16),
		b: parseInt(result[3], 16)
	} : null;
}

const color = computed({
	get(){
		const r = parseInt(line.value.r);
		const g = parseInt(line.value.g);
		const b = parseInt(line.value.b);
		return `#${componentToHex(r)}${componentToHex(g)}${componentToHex(b)}`;
	},

	set(val){

		const parsed = hexToRgb(val);

		if(parsed){
			line.value.r = parsed.r;
			line.value.g = parsed.g;
			line.value.b = parsed.b;
		}
	}
})

	const daysOfWeek = [
		'sunday',
		'monday',
		'tuesday',
		'wednesday',
		'thursday',
		'friday',
		'saturday',
		'sunday',
	];

	watch(line, () =>{
		emit('update', line);
	})
</script>

<template>
    <li v-if="line" class="row">
		<div class="col-1">
			<img src="../assets/svgviewer-output.svg" width="32" height="32"/>
		</div>
			<fieldset class="col-5">
				<select class="form-select" v-model="line.weekday">
					<option
							v-for="(day,index) in daysOfWeek"
							:value="index"
					>
						{{day}}
					</option>
				</select>
			</fieldset>


			<fieldset class="col-3">
				<input type="time" v-model="time" step="1"/>
			</fieldset>

			<fieldset class="col-2">
				<input type="color" class="form-control form-control-color" v-model="color" />
			</fieldset>

			<div class="col-1">
				<button class="btn btn-danger" @click="emit('delete')">X</button>
			</div>

		</li>
</template>

<style>
  input[type=color] {
    width: 100%;
  }
</style>