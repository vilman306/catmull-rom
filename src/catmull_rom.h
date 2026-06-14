#pragma once

#include <vector>
#include <godot_cpp/variant/vector2.hpp>
#include <godot_cpp/variant/vector3.hpp>

// https://andrewhungblog.wordpress.com/2017/03/03/catmull-rom-splines-in-plain-english/
// https://www.desmos.com/calculator/pltzhbje6x
namespace catrom
{
    // Returns the point at "step" t (0<=t<=1) along the spline interpolation of the Points.
    // Requirements: 
    // 0 <= t <= 1
    // Tension > 0
    godot::Vector2 EvaluateSpline2D(double t, const std::vector<godot::Vector2>& Points, double Tension);

    // Returns the point at "step" t (0<=t<=1) along the spline interpolation of the Points.
    // Requirements: 
    // 0 <= t <= 1
    // Tension > 0
    godot::Vector3 EvaluateSpline3D(double t, const std::vector<godot::Vector3>& Points, double Tension);
}