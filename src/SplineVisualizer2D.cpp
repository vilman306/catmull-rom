#include "SplineVisualizer2D.h"
#include "CardinalSpline.h"
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/color.hpp>


SplineVisualizer2D::SplineVisualizer2D()
{

}

SplineVisualizer2D::~SplineVisualizer2D()
{

}


void SplineVisualizer2D::_bind_methods()
{
    godot::ClassDB::bind_method(godot::D_METHOD("set_points", "p_points"), &SplineVisualizer2D::set_points);
    godot::ClassDB::bind_method(godot::D_METHOD("get_points"), &SplineVisualizer2D::get_points);
    ADD_PROPERTY(godot::PropertyInfo(godot::Variant::PACKED_VECTOR2_ARRAY, "points"), "set_points", "get_points");
    
    godot::ClassDB::bind_method(godot::D_METHOD("set_tension", "p_tension"), &SplineVisualizer2D::set_tension);
    godot::ClassDB::bind_method(godot::D_METHOD("get_tension"), &SplineVisualizer2D::get_tension);
    ADD_PROPERTY(godot::PropertyInfo(godot::Variant::FLOAT, "tension"), "set_tension", "get_tension");

    godot::ClassDB::bind_method(godot::D_METHOD("set_lines_per_segment", "p_lines_per_segment"), &SplineVisualizer2D::set_lines_per_segment);
    godot::ClassDB::bind_method(godot::D_METHOD("get_lines_per_segment"), &SplineVisualizer2D::get_lines_per_segment);
    ADD_PROPERTY(godot::PropertyInfo(godot::Variant::INT, "lines_per_segment", godot::PROPERTY_HINT_RANGE, "1,500,1"), "set_lines_per_segment", "get_lines_per_segment");
}


void SplineVisualizer2D::set_points(const godot::PackedVector2Array& p_points)
{
    knot_points = p_points;
    queue_redraw();
}

godot::PackedVector2Array SplineVisualizer2D::get_points()
{
    return knot_points;
}

void SplineVisualizer2D::set_tension(double p_tension)
{
    tension = p_tension;
    queue_redraw();
}

double SplineVisualizer2D::get_tension()
{
    return tension;
}

void SplineVisualizer2D::set_lines_per_segment(unsigned int p_lines_per_segment)
{
    lines_per_segment = p_lines_per_segment;
    queue_redraw();
}

unsigned int SplineVisualizer2D::get_lines_per_segment()
{
    return lines_per_segment;
}

void SplineVisualizer2D::_draw()
{
    unsigned int NrOfPoints = knot_points.size();
    if (NrOfPoints < 2)
        return;

    // store lines_per_segment locally so don't have to get it every time
    const unsigned int LinesPerSegment = lines_per_segment;

    godot::Vector2 P[4]; //= {{0.0, 0.0}, {0.0, 0.0}, {0.0, 0.0}, {0.0, 0.0}};
    for (int i = 0; i < NrOfPoints-1; i++) // Runs for every segment to interpolate
    {
        P[1] = knot_points[i];
        P[2] = knot_points[i+1];

        // Handle first point
        P[0] = (i == 0) ? P[1] : knot_points[i-1];
        // Handle end point
        P[3] = (i == NrOfPoints-2) ? P[2] : knot_points[i+2];
        
        // Draw the interpolated segment with lines
        godot::Vector2 PreviousPoint = knot_points[i];
        for (unsigned int j = 1; j <= LinesPerSegment; j++) // Runs for every line to draw
        { 
            double t = double(j) / LinesPerSegment;
            godot::Vector2 Point = cardinal::CalculateCardinalSplinePoint(P[0],
                P[1], P[2], P[3], t, tension);
            draw_line(PreviousPoint, Point, godot::Color(1, 0, 0), 2.0f);
            PreviousPoint = Point;
        }
    }
}
