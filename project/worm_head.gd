extends Node2D

# movement
const move_speed: float = 140.0
const boost_speed: float = 300.0
var current_speed: float = move_speed # pixels per second
var angular_speed: float = 3.0 # radians per second
var current_move_angle: float = 0.0 # in radians, always in interval [-PI, PI[
# body
const base_length: int = 10 # base "unit" that length has to be an integer multiple of.
var length: int = base_length * 16 # pixels (in base resolution)    # head should not store body length!
# position sampling
signal on_position_sampled(new_position_samples: PackedVector2Array)
const sample_time_current_speed_product: float = base_length # = current_speed * position_sample_time when nr_of_position_samples < max_nr_of_position_samples. allowable values are 2^(-n) * base_length, n: int >= 0 (1, 0.5, 0.25 etc. * base_length).
var position_sample_time: float = sample_time_current_speed_product / current_speed # seconds
var position_samples: PackedVector2Array = [] # earliest position at index 0, latest position at index (nr_of_position_samples - 1)
var position_sample_timer: float = position_sample_time
var nr_of_position_samples: int = length / sample_time_current_speed_product
const max_nr_of_position_samples: int = base_length * 10
# test
const grow_time: float = 2.0
var grow_timer: float = grow_time
var grow_amount: int = base_length * 4 # delta length

# Called when the node enters the scene tree for the first time.
func _enter_tree() -> void:
	#assert(current_speed * position_sample_time == 1, "current_speed * position_sample_time != 1. The whole game relies on it being 1 (because it makes nr_of_position_samples int).")
	assert(nr_of_position_samples < max_nr_of_position_samples, "nr_of_position_samples has to not be greater than or equal to %d (maximum) at start." % [max_nr_of_position_samples])
	assert(max_nr_of_position_samples % base_length == 0, "max_nr_of_position_samples has to be multiple of base_length.")
	for i in range(-nr_of_position_samples + 1, 1):
		position_samples.append(global_position)
	on_position_sampled.emit(position_samples)

# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta: float) -> void:
	# movement
	move(delta)
	# position sampling
	position_sample_timer -= delta
	if position_sample_timer <= 0:
		sample_position()
	# test
	#grow_timer -= delta
	#if grow_timer <= 0:
		#grow(grow_amount)

func update_current_speed(new_current_speed: float):
	current_speed = new_current_speed
	update_position_sample_time()

func grow(delta_length: int) -> void:
	grow_timer = grow_time # reset timer
	# increase length
	assert(delta_length > 0, "delta_length has to be greater than zero in function grow().")
	assert(delta_length % base_length == 0, "delta_length has to be integer multiple of base_length in function grow().")
	length += delta_length
	print("length: %d" % [length])
	# grow visually
	for i in range(0, delta_length / base_length):
		if nr_of_position_samples < max_nr_of_position_samples:
			# grow visually by adding more position samples
			var oldest_sampled_position: Vector2 = position_samples[0]
			position_samples.insert(0, oldest_sampled_position)
			nr_of_position_samples += base_length / sample_time_current_speed_product
		else: # nr_of_position_samples == max_nr_of_position_samples
			# grow visually by increasing position_sample_time
			update_position_sample_time() # different visual delta lengths!!! true?
			break
	print("nr_of_position_samples: %d" % [nr_of_position_samples])

func update_position_sample_time() -> void:
	var old_position_sample_time = position_sample_time
	if nr_of_position_samples == max_nr_of_position_samples: # caused by growth
		position_sample_time = length / (max_nr_of_position_samples * current_speed)
	else: # caused by changing current_speed
		position_sample_time = sample_time_current_speed_product / current_speed
	position_sample_timer *= position_sample_time / old_position_sample_time # keep timer progress "proportions"
	print("position_sample_time: %f" % [position_sample_time])

func calc_new_move_angle(delta: float, wanted_move_angle: float) -> float:
	var angle_diff: float = current_move_angle - wanted_move_angle
	if angle_diff == 0:
		return current_move_angle
	var rot_dir: int = 1 # 1 => clockwise, -1 => counterclockwise
	if angle_diff > 0 and angle_diff < PI:
		rot_dir = -1
	elif angle_diff < -PI:
		rot_dir = -1
	var new_move_angle: float = wrapf(current_move_angle + rot_dir * delta * angular_speed, -PI, PI)
	return new_move_angle

func sample_position() -> void:
	position_samples.remove_at(0) # clear oldest position
	position_samples.append(global_position) # add latest position
	position_sample_timer = position_sample_time # reset timer
	on_position_sampled.emit(position_samples) # emit signal

func move(delta: float) -> void:
	var mouse_pos: Vector2 = get_global_mouse_position()
	var head_to_mouse_dir: Vector2 = (mouse_pos - global_position).normalized()
	var wanted_move_angle = head_to_mouse_dir.angle()
	current_move_angle = calc_new_move_angle(delta, wanted_move_angle)
	var move_dir: Vector2 = Vector2.from_angle(current_move_angle)
	global_position += delta * current_speed * move_dir

func _input(event: InputEvent) -> void:
	if event.is_action_pressed("boost"):
		update_current_speed(boost_speed)
	elif event.is_action_released("boost"):
		update_current_speed(move_speed)
	if event.is_action_pressed("grow"):
		grow(grow_amount)
