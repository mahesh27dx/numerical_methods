/*
A tempting way to generate uniformly distributed numbers in a sphere is to generate a uniform distribution of theta and phi, then apply the above transformation to yield points in Cartesian space (x,y,z)
*/
#include<random>
#include<cmath>
#include<chrono>
#include<fstream>

int main(int argc, char *argv[]) {
    // Set up random number generators
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937 generator (seed);
    std::uniform_real_distribution<double> uniform01(0.0, 1.0);

    // generate N random numbers
    int N = 1000;

    // the incorrect way
    std::ofstream incorrectFile("incorrect.txt");
    incorrectFile << "# theta  phi  x  y  z" << std::endl;
    if (incorrectFile.is_open()) {
        for (int i = 0; i < N; i++) {
        // incorrect way
            double theta = 2 * M_PI * uniform01(generator);
            double phi = M_PI * uniform01(generator);
            double x = sin(phi) * cos(theta);
            double y = sin(phi) * sin(theta);
            double z = cos(phi);    
            incorrectFile << i << " " << theta << " " << phi << " "
            << x << " " << y << " " << z << " " << std::endl;
        }
    
    }
    //fclose(incorrect);
}

// std::ofstream fcsFile("/home/mi/mahey90/git/msd/results/simulation_results/lp50/proteins/time_correlation/p1/fcs_p1.txt");

//     fcsFile << "# block  time  FCS_x  ...  FCS_z  err(FCS_x)  ..." << std::endl;
//     if (fcsFile.is_open()) {
//         for (unsigned int i = 0; i < corr.count(); ++i) {
//             auto time = corr.time()[i];
//             auto fcs_correlation_mean_set1 = fcs_correlation_set1->get_mean()[i];
//             auto fcs_correlation_err_set1 = fcs_correlation_set1->get_error()[i];
//             auto fcs_correlation_mean_set2 = fcs_correlation_set2->get_mean()[i];
//             auto fcs_correlation_err_set2 = fcs_correlation_set2->get_error()[i];
//             for (unsigned int j = 0; j < corr.block_size(); ++j) {
//                 fcsFile << i << " " << time[j] << " " << fcs_correlation_mean_set1[j]
//                 << " " << fcs_correlation_err_set1[j] << " " << fcs_correlation_mean_set2[j]
//                 << " " << fcs_correlation_err_set2[j] << " " << std::endl;
//             } 
//         }
//     }