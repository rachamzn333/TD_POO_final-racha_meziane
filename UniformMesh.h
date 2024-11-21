/*#ifndef UNIFORMMESH_H
#define UNIFORMMESH_H

#include "IMesh.h"
#include <vector>

class UniformMesh : public IMesh {
public:
    UniformMesh(double x_min, double x_max, double dx);
    double getXMin() const override;
    double getXMax() const override;
    int getNumPoints() const override;
    double getDeltaX() const override;
    double getPosition(int index) const override;

private:
    double x_min, x_max, dx;
    std::vector<double> points;
};

#endif // UNIFORMMESH_H */
#ifndef UNIFORMMESH_H
#define UNIFORMMESH_H

#include "IMesh.h"
#include <vector>

class UniformMesh : public IMesh {
public:
    UniformMesh(double x_min, double x_max, double dx);
    double getXMin() const override;
    double getXMax() const override;
    int getNumPoints() const override;
    double getDeltaX() const override;
    double getPosition(int index) const override;

    // declaration  x_size()
   int x_size() const override;
   double x_i(int i) const override;


private:
    double x_min, x_max, dx;
    std::vector<double> points;
};

#endif // UNIFORMMESH_H

