extends Node

@export var worm: Node2D
@export var worm_head: Node2D
@export var head_movement: Node

signal on_position_sampled(new_position_samples: PackedVector2Array)
const SAMPLE_TIME_CURRENT_SPEED_PRODUCT: float = Worm.BASE_LENGTH # = current_speed * position_sample_time when nr_of_position_samples < max_nr_of_position_samples. allowable values are 2^(-n) * base_length, n: int >= 0 (1, 0.5, 0.25 etc. * base_length).
@onready var position_sample_time: float = SAMPLE_TIME_CURRENT_SPEED_PRODUCT / head_movement.current_speed # seconds
var position_samples: PackedVector2Array = [] # earliest position at index 0, latest position at index (nr_of_position_samples - 1)
var position_sample_timer: float = position_sample_time
@onready var nr_of_position_samples: int = worm.length / SAMPLE_TIME_CURRENT_SPEED_PRODUCT
const max_nr_of_position_samples: int = Worm.BASE_LENGTH * 10

func _ready() -> void:
	assert(nr_of_position_samples < max_nr_of_position_samples, "nr_of_position_samples has to not be greater than or equal to %d (maximum) at start." % [max_nr_of_position_samples])
	assert(max_nr_of_position_samples % Worm.BASE_LENGTH == 0, "max_nr_of_position_samples has to be multiple of base_length.")
	worm.connect("on_growth", on_growth)
	head_movement.connect("on_update_current_speed", on_update_current_speed)
	for i in range(-nr_of_position_samples + 1, 1):
		position_samples.append(worm_head.global_position)
	on_position_sampled.emit(position_samples)

# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta: float) -> void:
	position_sample_timer -= delta
	if position_sample_timer <= 0:
		sample_position()

func sample_position() -> void:
	position_samples.remove_at(0) # clear oldest position
	position_samples.append(worm_head.global_position) # add latest position
	position_sample_timer = position_sample_time # reset timer
	on_position_sampled.emit(position_samples) # emit signal

func update_position_sample_time() -> void:
	var old_position_sample_time = position_sample_time
	if nr_of_position_samples == max_nr_of_position_samples: # caused by growth
		position_sample_time = worm.length / (max_nr_of_position_samples * head_movement.current_speed)
	else: # caused by changing current_speed
		position_sample_time = SAMPLE_TIME_CURRENT_SPEED_PRODUCT / head_movement.current_speed
	position_sample_timer *= position_sample_time / old_position_sample_time # keep timer progress "proportions"
	print("position_sample_time: %f" % [position_sample_time])

func on_growth(delta_length: int):
	# grow visually
	for i in range(0, delta_length / Worm.BASE_LENGTH):
		if nr_of_position_samples < max_nr_of_position_samples:
			# grow visually by adding more position samples
			var oldest_sampled_position: Vector2 = position_samples[0]
			position_samples.insert(0, oldest_sampled_position)
			nr_of_position_samples += Worm.BASE_LENGTH / SAMPLE_TIME_CURRENT_SPEED_PRODUCT
		else: # nr_of_position_samples == max_nr_of_position_samples
			# grow visually by increasing position_sample_time
			update_position_sample_time() # different visual delta lengths!!! true?
			break
	print("nr_of_position_samples: %d" % [nr_of_position_samples])

func on_update_current_speed(new_current_speed: float):
	update_position_sample_time()
