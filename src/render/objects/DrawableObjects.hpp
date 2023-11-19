class DrawableObjects {
public:
    virtual void getVertexCoordinates(float *array) = 0;
    virtual int numberOfVertexCoordinates() = 0;
};

class Tetrahedron : public DrawableObjects {
public:
    void getVertexCoordinates(float *array);
    int numberOfVertexCoordinates();
};
