extends SplineVisualizer2D

@export var head_position_sampler: Node

func _ready() -> void:
	head_position_sampler.connect("on_position_sampled", on_head_position_sampled)

func on_head_position_sampled(new_position_samples: PackedVector2Array):
	points = new_position_samples
