/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | Copyright (C) 2011-2015 OpenFOAM Foundation
     \\/     M anipulation  |
-------------------------------------------------------------------------------
License
    This file is part of OpenFOAM.

    OpenFOAM is free software: you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with OpenFOAM.  If not, see <http://www.gnu.org/licenses/>.

Application
    flattenMesh

Description
    Flattens the front and back planes of a 2D cartesian mesh.

\*---------------------------------------------------------------------------*/

#include "argList.H"
#include "Time.H"
#include "polyMesh.H"
#include "emptyPolyPatch.H"
#include "twoDPointCorrector.H"
#include "mathematicalConstants.H"
#include "transformField.H"
#include "transformGeometricField.H"

using namespace Foam;
using namespace Foam::constant::mathematical;

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

int main(int argc, char *argv[])
{
    argList::addOption
    (
        "angle",
        "scalar",
        "make a wedge of the specified angle"
    );

    #include "setRootCase.H"
    #include "createTime.H"
    #include "createPolyMesh.H"

    pointIOField points
    (
        IOobject
        (
            "points",
            runTime.findInstance(polyMesh::meshSubDir, "points"),
            polyMesh::meshSubDir,
            runTime,
            IOobject::MUST_READ,
            IOobject::NO_WRITE,
            false
        )
    );

    boundBox bb(points);

    Info<< "bounding box: min = " << bb.min()
        << " max = " << bb.max() << " metres."
        << endl;


    point midPoint = gAverage(points);

    twoDPointCorrector twoDCorr(mesh);

    scalar v;
    if (args.optionReadIfPresent("angle", v))
    {
        Info<< "Making wedge with angle: " << nl  << v << nl;

        // Convert to radians
        v *= pi/180.0;
        scalar sinus = std::sin(v/2.0);
        scalar cosinus = std::cos(v/2.0);

        forAll(points, pointI)
        {
            if (points[pointI].component(vector::Z) < midPoint.component(vector::Z))
            {
                points[pointI].replace(vector::Z, -sinus*points[pointI].component(vector::X));//first use old x as radius
                points[pointI].replace(vector::X, cosinus*points[pointI].component(vector::X));//then change x
            }
            else
            {
                points[pointI].replace(vector::Z, sinus*points[pointI].component(vector::X));
                points[pointI].replace(vector::X, cosinus*points[pointI].component(vector::X));
            }
        }
    }

    twoDCorr.correctPoints(points);

    // Set the precision of the points data to 10
    IOstream::defaultPrecision(max(10u, IOstream::defaultPrecision()));

    Info<< "Writing points into directory " << points.path() << nl << endl;
    points.write();

    return 0;
}


// ************************************************************************* //
