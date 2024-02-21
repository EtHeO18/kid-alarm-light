<script setup lang="ts">
import {computed, toRef} from "vue";

	const props = defineProps(['modelValue'])
	const modelValue = toRef(props, 'modelValue')

	const emit =defineEmits(['delete'])

	const time = computed({
		get(){
			const date = new Date();

			const hour = (''+modelValue.value.hour).padStart(2, '0')
			const minute = (''+modelValue.value.minute).padStart(2, '0')
			const second = (''+modelValue.value.second).padStart(2, '0')

			return `${hour}:${minute}:${second}`;
		},
		set(val: string) {
			const parts = val.split(/:/);

			console.log(parts);
			modelValue.value.hour = parseInt(parts[0]);
			modelValue.value.minute = parseInt(parts[1]);
			modelValue.value.second = parseInt(parts[2]);
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
		const r = parseInt(modelValue.value.r);
		const g = parseInt(modelValue.value.g);
		const b = parseInt(modelValue.value.b);
		return `#${componentToHex(r)}${componentToHex(g)}${componentToHex(b)}`;
	},

	set(val){

		const parsed = hexToRgb(val);

		if(parsed){
			modelValue.value.r = parsed.r;
			modelValue.value.g = parsed.g;
			modelValue.value.b = parsed.b;
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
</script>

<template>
    <li v-if="modelValue" class="row">
			<fieldset class="col">
				<select v-model="modelValue.weekday" class="form-select">
					<option
							v-for="(day,index) in daysOfWeek"
							:value="index"
					>
						{{day}}
					</option>
				</select>
			</fieldset>

			<fieldset class="col">
				<input type="time" v-model="time" step="1" class="form-control" />
			</fieldset>

			<fieldset class="col">
				<input type="color" v-model="color" class="form-control form-control-color"/>
			</fieldset>

      <div class="col">
        <button @click="emit('delete')" class="btn btn-danger">Delete</button>
      </div>
		</li>
</template>

<style>
  input[type=color] {
    width: 100%;
  }
</style>