//
// Created by Xun Li on 9/27/19.
//

#ifndef GEODA_GDA_CLUSTERING_H
#define GEODA_GDA_CLUSTERING_H

#include <vector>

class GeoDaWeight;
class UniLocalMoran;
class UniGeary;
class UniJoinCount;
class UniG;
class UniGstar;
class GeoDa;

// Public APIs

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
GeoDaWeight* gda_queen_weights(GeoDa* geoda, const std::string& polyid="",
                               unsigned int order=1,
                               bool include_lower_order = false,
                               double precision_threshold = 0);

/**
 *
 * @param geoda
 * @param polyid
 * @param order
 * @param include_lower_order
 * @param precision_threshold
 * @return
 */
GeoDaWeight* gda_rook_weights(GeoDa* geoda, const std::string& polyid="",
                               unsigned int order=1,
                               bool include_lower_order = false,
                               double precision_threshold = 0);

/**
 *
 * @param geoda
 * @param is_arc
 * @param is_mile
 * @return
 */
double gda_min_distthreshold(GeoDa* geoda, bool is_arc = false,
                             bool is_mile = true);

/**
 *
 * @param geoda
 * @param is_arc
 * @param is_mile
 * @return
 */
double gda_max_distthreshold(GeoDa* geoda, bool is_arc = false,
                             bool is_mile = true);

/**
 *
 * @param geoda
 * @param dist_thres
 * @param polyid
 * @param power
 * @param is_inverse
 * @param is_arc
 * @param is_mile
 * @param kernel
 * @param use_kernel_diagnals
 * @return
 */
GeoDaWeight* gda_distance_weights(GeoDa* geoda, double dist_thres,
                                  const std::string& polyid = "",
                                  double power = 1.0,
                                  bool is_inverse = false,
                                  bool is_arc = false,
                                  bool is_mile = true,
                                  const std::string& kernel = "",
                                  bool use_kernel_diagnals = false);

/**
 *
 * @param geoda
 * @param k
 * @param polyid
 * @param power
 * @param is_inverse
 * @param is_arc
 * @param is_mile
 * @param kernel
 * @param bandwidth
 * @param adaptive_bandwidth
 * @param use_kernel_diagnals
 * @return
 */
GeoDaWeight* gda_knn_weights(GeoDa* geoda, unsigned int k,
                             double power = 1.0,
                             bool is_inverse = false,
                             bool is_arc = false,
                             bool is_mile = true,
                             const std::string& kernel = "",
                             double bandwidth = 0,
                             bool adaptive_bandwidth = false,
                             bool use_kernel_diagnals = false,
                             const std::string& polyid = "");
// APIs of clustering

/**
 *
 * @param w
 * @param data
 * @param bound_vals
 * @param min_bound
 * @param local_search_method
 * @param initial
 * @param tabu_length
 * @param cool_rate
 * @param seeds
 * @param distance_method
 * @param rand_seed
 * @return
 */
const std::vector<std::vector<int> > gda_maxp(GeoDaWeight *w,
                                const std::vector<std::vector<double> >& data,
                                const std::vector<double>& bound_vals,
                                double min_bound,
                                const std::string& local_search_method = "greedy",
                                int initial = 99,
                                int tabu_length = 85,
                                double cool_rate = 0.85,
                                const std::vector<int>& seeds = std::vector<int>(),
                                const std::string &distance_method = "euclidean",
                                int rand_seed = 123456789);

/**
 *
 * @param k
 * @param w
 * @param data
 * @param redcap_method
 * @param distance_method
 * @param bound_vals
 * @param min_bound
 * @param rand_seed
 * @return
 */
const std::vector<std::vector<int> > gda_redcap(unsigned int k,
                                  GeoDaWeight *w,
                                  const std::vector<std::vector<double> > &data,
                                  const std::string &redcap_method =  "firstorder-singlelinkage",
                                  const std::string &distance_method = "euclidean",
                                  const std::vector<double>& bound_vals = std::vector<double>(),
                                  double min_bound = 0,
                                  int rand_seed = 123456789);

/**
 *
 * @param k
 * @param w
 * @param data
 * @param distance_method
 * @param bound_vals
 * @param min_bound
 * @param rand_seed
 * @return
 */
const std::vector<std::vector<int> > gda_skater(unsigned int k,
                                  GeoDaWeight *w,
                                  const std::vector<std::vector<double> > &data,
                                  const std::string &distance_method = "euclidean",
                                  const std::vector<double>& bound_vals = std::vector<double>(),
                                  double min_bound = -1,
                                  int rand_seed = 123456789);

// APIs of local spatial autocorrelation
/**
 *
 * @param w
 * @param data
 * @param undefs
 * @return
 */
UniLocalMoran* gda_lisa(GeoDaWeight *w,
                  const std::vector<double> &data,
                  const std::vector<bool> &undefs = std::vector<bool>());

/**
 *
 * @param w
 * @param data
 * @param undefs
 * @return
 */
UniGeary* gda_geary(GeoDaWeight *w, const std::vector<double> &data,
                    const std::vector<bool> &undefs = std::vector<bool>());

/**
 *
 * @param w
 * @param data
 * @param undefs
 * @return
 */
UniJoinCount* gda_joincount(GeoDaWeight *w, const std::vector<double> &data,
                            const std::vector<bool> &undefs = std::vector<bool>());

/**
 *
 * @param w
 * @param data
 * @param undefs
 * @return
 */
UniG* gda_localg(GeoDaWeight *w, const std::vector<double> &data,
                            const std::vector<bool> &undefs = std::vector<bool>());

/**
 *
 * @param w
 * @param data
 * @param undefs
 * @return
 */
UniGstar* gda_localgstar(GeoDaWeight *w, const std::vector<double> &data,
                 const std::vector<bool> &undefs = std::vector<bool>());


/*
MultiGeary* gda_multigeary(GeoDaWeight *w,
                           const std::vector<std::vector<double> > &data,
                           const std::vector<std::vector<bool> > &undefs  = std::vector<std::vector<bool> >());


MultiJointCount* gda_multijoincount(GeoDaWeight *w,
                                    const std::vector<std::vector<double> > &data,
                                    const std::vector<std::vector<bool> > &undefs  = std::vector<std::vector<bool> >());
*/

// Data APIs
/**
 *
 * @param vals
 * @return
 */
double gda_sumofsquares(const std::vector<double>& vals);

/**
 *
 * @param vals
 * @return
 */
double gda_totalsumofsquare(const std::vector<std::vector<double> >& vals);

/**
 *
 * @param solution
 * @param vals
 * @return
 */
double gda_withinsumofsquare(const std::vector<std::vector<int> >& solution,
        const std::vector<std::vector<double> >& vals);

/**
 *
 * @param solution
 * @param data
 * @return
 */
double gda_betweensumofsquare(const std::vector<std::vector<int> >& solution,
        const std::vector<std::vector<double> >& data);

#endif //GEODA_GDA_CLUSTERING_H
