struct Vector2D{
    Vector2D(double x, double y) : x(x), y(y) {};
    double x, y;
};

Vector2D add(const Vector2D& l, const Vector2D& r) { return {l.x + r.x, l.y + r.y}; }
Vector2D sub(const Vector2D& l, const Vector2D& r) { return {l.x - r.x, l.y - r.y}; }
double   dot(const Vector2D& l, const Vector2D& r) { return l.x * r.x + l.y * r.y;  }

int main(){

    Vector2D v1(0,0);
    Vector2D v2(1,1);
    Vector2D v3(13, 15);

    double res = dot(v3, add(v1,v2));
}

