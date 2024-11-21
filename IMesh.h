/*#ifndef IMESH_H
#define IMESH_H

class IMesh {
public:
    virtual ~IMesh() = default;
    virtual double getXMin() const = 0;
    virtual double getXMax() const = 0;
    virtual int getNumPoints() const = 0;
    virtual double getDeltaX() const = 0;
    virtual double getPosition(int index) const = 0;
};

#endif // IMESH_H
*/
#ifndef IMESH_H
#define IMESH_H

class IMesh {
public:
    virtual ~IMesh() = default;
    virtual double getXMin() const = 0;
    virtual double getXMax() const = 0;
    virtual int getNumPoints() const = 0;
    virtual double getDeltaX() const = 0;
    virtual double getPosition(int index) const = 0;

    // Nouvelle méthode pour obtenir la taille du maillage
    virtual int x_size() const = 0;

    // Méthode pour obtenir la position x_i d'un point donné
    virtual double x_i(int i) const = 0;
};

#endif // IMESH_H
