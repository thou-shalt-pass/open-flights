#include <fstream>

#include "tests_utilities.h"

#include "data.h"
#include "type.h"

#include "filename_def.h"

#include "importance.h"

TEST_CASE("mutal test actual data scc", "[mutual_actual]") {
    Data data = ReadData(kFilenameInputDataAirportDefault, kFilenameInputDataAirlineDefault);
    const AdjList& adj_list = data.GetAdjList();
    std::vector<double> it_result = ImportanceIteration(adj_list, 5000);
    std::vector<double> lu_result = ImportanceEigenvectorByLU(adj_list);
    std::vector<double> gaussian_result = ImportanceEigenvectorByGaussian(adj_list);
    double diff_peak_lu_gaussian, diff_peak_lu_it, diff_peak_gaussian_it;
    diff_peak_lu_gaussian = CheckVectorDoubleWithScalarMultiple(lu_result, gaussian_result, 5e-5);
    diff_peak_lu_it = CheckVectorDoubleWithScalarMultiple(lu_result, it_result, 5e-5);
    diff_peak_gaussian_it = CheckVectorDoubleWithScalarMultiple(gaussian_result, it_result, 5e-5);
    printf("diff_peak_lu_gaussian = %f\ndiff_peak_lu_it = %f\ndiff_peak_gaussian_it = %f\n", 
        diff_peak_lu_gaussian, diff_peak_lu_it, diff_peak_gaussian_it);
}
