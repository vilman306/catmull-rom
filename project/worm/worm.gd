class_name Worm
extends Node2D

const BASE_LENGTH: int = 10 # base "unit" that length has to be an integer multiple of. increasing this allows for greater position_sample_time when nr_of_position_samples < max_nr_of_position_samples.
var length: int = BASE_LENGTH * 16 # pixels (in base resolution)

signal on_growth(delta_length: int)
const grow_time: float = 2.0
var grow_timer: float = grow_time
var grow_amount: int = BASE_LENGTH * 4 # delta length

func grow(delta_length: int) -> void:
	grow_timer = grow_time # reset timer
	# increase length
	assert(delta_length > 0, "delta_length has to be greater than zero in function grow().")
	assert(delta_length % BASE_LENGTH == 0, "delta_length has to be integer multiple of base_length in function grow().")
	length += delta_length
	print("length: %d" % [length])
	on_growth.emit(delta_length)

func _input(event: InputEvent) -> void:
	if event.is_action_pressed("grow"):
		grow(grow_amount)
