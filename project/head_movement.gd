extends Node

@export var worm_head: Node2D
const MOVE_SPEED: float = 140.0
const BOOST_SPEED: float = 300.0
var current_speed: float = MOVE_SPEED # pixels per second
var angular_speed: float = 3.0 # radians per second
var current_move_angle: float = 0.0 # in radians, always in interval [-PI, PI[
signal on_update_current_speed(new_current_speed: float)

func _process(delta: float) -> void:
	move(delta)

func update_current_speed(new_current_speed: float):
	current_speed = new_current_speed
	on_update_current_speed.emit(new_current_speed)

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

func move(delta: float) -> void:
	var mouse_pos: Vector2 = worm_head.get_global_mouse_position()
	var head_to_mouse_dir: Vector2 = (mouse_pos - worm_head.global_position).normalized()
	var wanted_move_angle = head_to_mouse_dir.angle()
	current_move_angle = calc_new_move_angle(delta, wanted_move_angle)
	var move_dir: Vector2 = Vector2.from_angle(current_move_angle)
	worm_head.global_position += delta * current_speed * move_dir

func _input(event: InputEvent) -> void:
	if event.is_action_pressed("boost"):
		update_current_speed(BOOST_SPEED)
	elif event.is_action_released("boost"):
		update_current_speed(MOVE_SPEED)
