#pragma once

#include <godot_cpp/classes/node2d.hpp>
#include <godot_cpp/variant/vector2.hpp>
#include <vector>

class SplineVisualizer2D : public godot::Node2D
{
    GDCLASS(SplineVisualizer2D, godot::Node2D);

private:
    godot::PackedVector2Array knot_points;
    double tension = 0.0;

protected:
    static void _bind_methods();

public:
    SplineVisualizer2D();
    ~SplineVisualizer2D();

    void set_points(const godot::PackedVector2Array& p_points);
    godot::PackedVector2Array get_points();

    void set_tension(double p_tension);
    double get_tension();

    void _draw() override;
};