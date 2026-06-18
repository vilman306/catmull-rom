extends SplineVisualizer2D


# Called when the node enters the scene tree for the first time.
func _enter_tree() -> void: # runs before the child's _enter_tree
	var worm_head: Node2D = get_node("WormHead")
	worm_head.connect("on_position_sampled", on_head_position_sampled) # runs before the child's emit

func on_head_position_sampled(new_position_samples: PackedVector2Array):
	points = new_position_samples
