#include "catmull_rom.h"
#include <godot_cpp/core/error_macros.hpp>
#include <string>

bool CheckTension(double& Tension)
{
    if (Tension <= 0)
    {
        WARN_PRINT("Did not meet requirement Tension > 0. Defaulting to Tension = 1.");
        Tension = 1.0;
        return true;
    }
    return false;
}

bool tIsInvalid(double t)
{
    if (!(t >= 0 && t <= 1))
    {
        WARN_PRINT("Did not meet requirement 0 <= t <= 1. Returning zero-vector.");
        return true;
    }
    return false;
}

bool PointsSizeIsInvalid(unsigned int PointsSize)
{
    unsigned int MinNrOfPoints = 2;
    if (PointsSize < MinNrOfPoints)
    {
        std::string WarningString = "Did not meet requirement of the list of Points having at least "
                                    + std::to_string(MinNrOfPoints)
                                    + " elements. Returning zero-vector.";
        WARN_PRINT(WarningString.c_str());
        return true;
    }
    return false;
}

bool ArgumentsAreInvalid(double t, const std::vector<godot::Vector2>& Points)
{
    return tIsInvalid(t) || PointsSizeIsInvalid(Points.size());
}

bool ArgumentsAreInvalid(double t, const std::vector<godot::Vector3>& Points)
{
    return tIsInvalid(t) || PointsSizeIsInvalid(Points.size());
}

godot::Vector2 catrom::EvaluateSpline2D(double t, const std::vector<godot::Vector2>& Points, double Tension)
{
    godot::Vector2 Result = {0.0, 0.0};

    if (ArgumentsAreInvalid(t, Points))
    {
        return Result;
    }
    CheckTension(Tension);

    // Calculate Result ...

    return Result;
}

godot::Vector3 catrom::EvaluateSpline3D(double t, const std::vector<godot::Vector3>& Points, double Tension)
{
    godot::Vector3 Result = {0.0, 0.0, 0.0};

    if (ArgumentsAreInvalid(t, Points))
    {
        return Result;
    }
    CheckTension(Tension);

    // Calculate Result ...

    return Result;
}