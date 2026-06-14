#pragma once

#include <vector>
#include <godot_cpp/variant/vector2.hpp>
#include <godot_cpp/variant/vector3.hpp>

// https://algorithmist.wordpress.com/2009/09/28/cardinal-splines-part-2/
// https://en.wikipedia.org/wiki/Cubic_Hermite_spline#Cardinal_spline
// https://andrewhungblog.wordpress.com/2017/03/03/catmull-rom-splines-in-plain-english/


namespace cardinal
{
    // // Returns the point at "step" t (0<=t<=1) along the spline interpolation of the Points.
    // // Argument requirements: 
    // // 0 <= t <= 1
    // // No manual "ghost points" at the start and/or end.
    // godot::Vector2 EvaluateSpline2D(double t, const std::vector<godot::Vector2>& Points, double Tension);

    // // Returns the point at "step" t (0<=t<=1) along the spline interpolation of the Points.
    // // Argument requirements: 
    // // 0 <= t <= 1
    // // At least two points
    // // No manual "ghost points" at the start and/or end.
    // godot::Vector3 EvaluateSpline3D(double t, const std::vector<godot::Vector3>& Points, double Tension);


    // Returns the point at "step" t (0<=t<=1) along the spline interpolation of the Points.
    // Argument requirements: 
    // 0 <= t <= 1
    // Either two or four points. Two points will create "default" tangents at start and end.
    godot::Vector2 EvaluateSplineSegment2D(double t, const std::vector<godot::Vector2>& SegmentPoints, double Tension);
    godot::Vector3 EvaluateSplineSegment3D(double t, const std::vector<godot::Vector3>& SegmentPoints, double Tension);

    // https://en.wikipedia.org/wiki/Cubic_Hermite_spline#Cardinal_spline
    template <typename T>
    T CalculateCardinalSplinePoint(T P0, T P1, T P2, T P3, double t, double Tension)
    {
        double t2 = t * t;
        double t3 = t * tSquared;
        double s = (1.0 - T) * 0.5;
        T StartTangent = s * (P2 - P0);
        T EndTangent = s * (P3 - P1);
        T Result = (2*t3 - 3*t2 + 1) * P1 + (t3 - 2*t2 + t) * StartTangent
                 + (-2*t3 + 3*t2) * P2 + (t3 - t2) * EndTangent;
        return Result;
    }
}