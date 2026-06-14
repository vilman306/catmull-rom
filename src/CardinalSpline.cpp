#include "CardinalSpline.h"
#include <godot_cpp/core/error_macros.hpp>
#include <string>

// bool CheckTension(double& Tension)
// {
//     if (Tension <= 0)
//     {
//         WARN_PRINT("Did not meet requirement Tension > 0. Defaulting to Tension = 1.");
//         Tension = 1.0;
//         return true;
//     }
//     return false;
// }

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

// godot::Vector2 cardinal::EvaluateSpline2D(double t, const std::vector<godot::Vector2>& Points, double Tension)
// {
//     godot::Vector2 Result = {0.0, 0.0};

//     if (ArgumentsAreInvalid(t, Points))
//     {
//         return Result;
//     }
//     CheckTension(Tension);

//     // Calculate Result ...

//     return Result;
// }

// godot::Vector3 cardinal::EvaluateSpline3D(double t, const std::vector<godot::Vector3>& Points, double Tension)
// {
//     godot::Vector3 Result = {0.0, 0.0, 0.0};

//     // Check arguments
//     if (ArgumentsAreInvalid(t, Points))
//     {
//         return Result;
//     }
//     CheckTension(Tension);

//     // Calculate Result ...
    


//     return Result;
// }




bool NrOfSegmentPointsIsInvalid(unsigned int NrOfPoints)
{
    unsigned int NrOfPointsOpt1 = 2;
    unsigned int NrOfPointsOpt2 = 4;
    if (!(NrOfPoints == NrOfPointsOpt1 || NrOfPoints == NrOfPointsOpt2))
    {
        std::string WarningString = "Did not meet requirement of the list of Points having exactly "
                                    + std::to_string(NrOfPointsOpt1)
                                    + " or " + std::to_string(NrOfPointsOpt2)
                                    + " elements. Returning zero-vector.";
        WARN_PRINT(WarningString.c_str());
        return true;
    }
    return false;
}

bool SegmentArgumentsAreInvalid(double t, unsigned int NrOfSegmentPoints)
{
    return tIsInvalid(t) || NrOfSegmentPointsIsInvalid(NrOfSegmentPoints);
}



// godot::Vector2 cardinal::EvaluateSplineSegment2D(double t, const std::vector<godot::Vector2>& SegmentPoints, double Tension)
// {
//     godot::Vector2 Result = {0.0, 0.0};
    
//     // Check arguments
//     unsigned int NrOfSegmentPoints = SegmentPoints.size();
//     if (SegmentArgumentsAreInvalid(t, NrOfSegmentPoints))
//     {
//         return Result;
//     }
//     // CheckTension(Tension);
    
//     // Calculate Result
//     godot::Vector2 P0, P1, P2, P3;
//     bool HasGhostPoints = (NrOfSegmentPoints == 4);
//     if (HasGhostPoints)
//     {
//         P0 = SegmentPoints[0];
//         P1 = SegmentPoints[1];
//         P2 = SegmentPoints[2];
//         P3 = SegmentPoints[3];
//     }
//     else
//     {
//         P0 = P1 = SegmentPoints[0];
//         P2 = P3 = SegmentPoints[1];
//     }

//     Result = cardinal::CalculateCardinalSplinePoint(P0, P1, P2, P3, t, Tension);
//     return Result;
// }

// godot::Vector3 cardinal::EvaluateSplineSegment3D(double t, const std::vector<godot::Vector3>& SegmentPoints, double Tension)
// {
//     godot::Vector3 Result = {0.0, 0.0, 0.0};

//     // Check arguments
//     unsigned int NrOfSegmentPoints = SegmentPoints.size();
//     if (SegmentArgumentsAreInvalid(t, NrOfSegmentPoints))
//     {
//         return Result;
//     }
//     // CheckTension(Tension);

//     // Calculate Result ...
//     godot::Vector3 P0, P1, P2, P3;
//     bool HasGhostPoints = (NrOfSegmentPoints == 4);
//     if (HasGhostPoints)
//     {
//         P0 = SegmentPoints[0];
//         P1 = SegmentPoints[1];
//         P2 = SegmentPoints[2];
//         P3 = SegmentPoints[3];
//     }
//     else
//     {
//         P0 = P1 = SegmentPoints[0];
//         P2 = P3 = SegmentPoints[1];
//     }

//     Result = cardinal::CalculateCardinalSplinePoint(P0, P1, P2, P3, t, Tension);
//     return Result;
// }