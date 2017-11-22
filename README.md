# wedgePlease

This is an OpenFOAM-3.0.1 utility for converting a 2D mesh to axisymmetric.
It is a modification of the flattenMesh utility distributed with OpenFOAM.
The cases are a modification of the more elaborate utility [makeAxialMesh](http://openfoamwiki.net/index.php/Contrib/MakeAxialMesh).
One case uses the wedgePlease to convert a blockMesh to an OpenFOAM axialMesh.
One case uses it to convert a fluentMesh.

See the official website [openfoam.org](https://openfoam.org/), unofficial wiki
[openfoamwiki.net](https://openfoamwiki.net/index.php/Main_Page) and the community forum
[cfd-online.com](https://www.cfd-online.com/Forums/openfoam/).

## Getting Started

An OpenFOAM 3.0.1 installation is required to run the code. This code was run on Centos 6.6 (Rocks 6.2 Sidewinder).

Run `Allwmake` in the utility directory to compile it.

Run `Allmesh` in the [`caseBM`](/caseBM) or [`caseFM`](/caseFM) directory to convert the mesh. Then run `paraFoam` in the case directory to view the results.

## Functionality

* Assumes a 2D mesh in the XY plane.
* The Y axis becomes the axis of symmetry.
* The command `wedgePlease -angle 5` only reshapes the points to form the wedge.

## Feedback

Any feedback is apreciated - krebeljk()gmail.com.

## Author

* **Kristjan Krebelj**

## License

This project is licensed under the GPU License - see the [LICENSE.md](LICENSE.md) file for details.

## Acknowledgments

* The work was supported by the [Laboratory for Numerical Modelling and Simulation - LNMS](http://lab.fs.uni-lj.si/lnms/).

## Demo case
![Demo geometry](/tutorials/demo/demo_geom.png)
![Pressure evolution](/tutorials/demo/plot.png)
