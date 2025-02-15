#ifndef __JSGEODSA_GDA_WEIGHTS__
#define __JSGEODSA_GDA_WEIGHTS__

#include <string>

#ifdef __JSGEODA__
class GdaGeojson;
#define GEODA_WRAPPER GdaGeojson
#else
class GeoDa;
#define GEODA_WRAPPER GeoDa
#endif

class GeoDaWeight;

// APIs of weights creation
/**
 *
 * @param geoda
 * @param polyid
 * @param order
 * @param include_lower_order
 * @param precision_threshold
 * @return
 */
GeoDaWeight* gda_queen_weights(GEODA_WRAPPER* geoda,
                               unsigned int order=1,
                               bool include_lower_order = false,
                               double precision_threshold = 0);

GeoDaWeight* gda_rook_weights(GEODA_WRAPPER* geoda,
                               unsigned int order=1,
                               bool include_lower_order = false,
                               double precision_threshold = 0);

GeoDaWeight* gda_knn_weights(GEODA_WRAPPER* geoda, unsigned int k,
                             double power = 1.0,
                             bool is_inverse = false,
                             bool is_arc = false,
                             bool is_mile = true,
                             const std::string& kernel = "",
                             double bandwidth = 0,
                             bool adaptive_bandwidth = false,
                             bool use_kernel_diagnals = false,
                             const std::string& polyid = "");

double gda_min_distthreshold(GEODA_WRAPPER* geoda, bool is_arc = false,
                             bool is_mile = true);

GeoDaWeight* gda_distance_weights(GEODA_WRAPPER* geoda, double dist_thres,
                                  const std::string& polyid = "",
                                  double power = 1.0,
                                  bool is_inverse = false,
                                  bool is_arc = false,
                                  bool is_mile = true,
                                  const std::string& kernel = "",
                                  bool use_kernel_diagonals = false);
#endif
