#include <fstream>
#include <array>
#include <functional>

using namespace std;
typedef array<double, 3> cartesian;

void writeOut(ofstream&, double, cartesian, cartesian);
cartesian compForce(cartesian, std::function<double(double)>);
double harmOsc(double);

int main()
{
    const double h = 0.01d;
    const int maxit = 1000;

    cartesian r, v, a;
    r.at(0) = 0; r.at(1) = 0; r.at(2) = 1;
    v.at(0) = 0; v.at(1) = 0; v.at(2) = 0;

    a = compForce(r, harmOsc);

    ofstream results;
    results.open("results.txt");
    results << "time, rx, ry, rz, vx, vy, vz" << endl;
    writeOut(results, 0, r, v);

    for (unsigned i = 1; i <= maxit; ++i) {
        for (size_t j = 0; j < a.size(); ++j) {
            v.at(j) += 0.5 * h * a.at(j);
            r.at(j) += h * v.at(j);
        }
        a = compForce(r, harmOsc);
        for (size_t j = 0; j < a.size(); ++j) {
            v.at(j) += 0.5 * h * a.at(j);
        }
        writeOut(results, i*h, r, v);
    }
    results.close();

    return 0;
}

void writeOut(ofstream& destination, double t, cartesian r, cartesian v) {
    destination << t << ",";

    for(size_t j = 0; j < r.size(); ++j) { destination << r.at(j) << ","; }
    for(size_t j = 0; j < v.size(); ++j) { destination << v.at(j) << ","; }
    destination << endl;
}

cartesian compForce(cartesian x, std::function<double(double)> f) {
    cartesian a;
    for(size_t j = 0; j < a.size(); ++j) { a.at(j) = f(x.at(j));}
    return a;
}

double harmOsc(double x){return -x;}