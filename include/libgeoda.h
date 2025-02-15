#ifndef LIBGEODA_LIBRARY_H
#define LIBGEODA_LIBRARY_H

#ifdef __MSVC__
#include <Windows.h>
#include <Psapi.h>
#endif

#include <list>
#include <vector>
#include <algorithm>
#include <map>
#include <ogrsf_frmts.h>

// forward declaration
namespace gda {
    struct Point;
    struct PolygonContents;
    struct MainMap;
}

class GeoDaColumn {
public:
    enum FieldType { integer_type, string_type, real_type };
    std::string name;
    FieldType field_type;
    int field_length;
    int field_decimals;

    GeoDaColumn(const std::string& nm, FieldType ft, int flen, int fdec)
    : name(nm), field_type(ft), field_length(flen), field_decimals(fdec) {}
    virtual ~GeoDaColumn() {}
};

class GeoDaIntColumn : public GeoDaColumn {
public:
    std::vector<long long> data;

    virtual std::vector<long long>& GetData() { return data;}
    virtual void SetData(const std::vector<long long>& vals) { data = vals; }

    GeoDaIntColumn(const std::string& nm, const std::vector<long long>& vals)
    : GeoDaColumn(nm, integer_type, 20, 0), data(vals) {}
};


class GeoDaStringColumn : public GeoDaColumn {
public:
    std::vector<std::string> data;

    virtual std::vector<std::string>& GetData() { return data;}
    virtual void SetData(const std::vector<std::string>& vals) { data = vals; }

    GeoDaStringColumn(const std::string& nm, const std::vector<std::string>& vals)
            : GeoDaColumn(nm, string_type, 254, 0), data(vals) {}
};

class GeoDaRealColumn : public GeoDaColumn {
public:
    std::vector<double> data;

    virtual std::vector<double>& GetData() { return data;}
    virtual void SetData(const std::vector<double>& vals) { data = vals; }

    GeoDaRealColumn(const std::string& nm, const std::vector<double>& vals)
            : GeoDaColumn(nm, real_type, 35, 15), data(vals) {}
};

class GeoDaTable {
public:
    GeoDaTable(){};
    virtual ~GeoDaTable(){};

    void AddIntColumn(const std::string& nm, const std::vector<long long>& vals) {
        GeoDaColumn* col = new GeoDaIntColumn(nm, vals);
        columns.push_back(col);
    }
    void AddStringColumn(const std::string& nm, const std::vector<std::string>& vals) {
        GeoDaColumn* col = new GeoDaStringColumn(nm, vals);
        columns.push_back(col);
    }
    void AddRealColumn(const std::string& nm, const std::vector<double>& vals) {
        GeoDaColumn* col = new GeoDaRealColumn(nm, vals);
        columns.push_back(col);
    }

    GeoDaColumn* GetColumn(const std::string& col_name) {
        for (size_t i=0; i<columns.size(); ++i) {
            if (col_name.compare(columns[i]->name) == 0) {
                return columns[i];
            }
        }
        return 0;
    }

    GeoDaColumn* GetColumn(int idx) {return columns[idx];}

    int GetNumCols() { return columns.size(); }

protected:
    std::vector<GeoDaColumn*> columns;
};

class GeoDa {
public:
    enum MapType { point_type, polygon_type, line_type, unknown_type };

    // this constructor is for Python
    GeoDa(GeoDaTable* table,
            const std::string& layer_name,
            const std::string& map_type,
            const std::vector<unsigned char> &wkbs,
            const std::vector<int>& wkb_bytes_len,
            const std::string& pszProj4);

	// this constructor is for R
    GeoDa(const std::string& layer_name,
            const std::string& map_type,
            int num_features,
            GeoDaTable* table,
            unsigned char* wkbs,
            const std::vector<int>& wkb_bytes_len,
            const std::string& pszProj4);

    GeoDa(const char* pDsPath, const char* layer_name=NULL);

    virtual ~GeoDa();

    // Layer functions
    int GetNumObs() const;
    int GetNumCols() const;
    std::vector<std::string> GetFieldTypes();
    std::vector<std::string> GetFieldNames();
    std::string GetName();
    OGRLayer* GetOGRLayer();

    // Geometry functions
    std::vector<std::vector<unsigned char> >  GetGeometryWKB();
    std::vector<std::string>  GetGeometryWKT();
    //void SpatialCount(const char* pDSPath);
    int GetMapType();
    const std::vector<gda::Point>& GetCentroids();
    gda::MainMap& GetMainMap();

    // Data functions
    std::vector<double> GetNumericCol(std::string col_name);
    std::vector<long long> GetIntegerCol(std::string col_name);
    std::vector<std::string> GetStringCol(std::string col_name);
    std::vector<bool> GetUndefinesCol(std::string col_name);


protected:
    OGRGeometry* CreateOGRGeomFromWkb(unsigned char* wkb, int n);

    void ReadAllFeatures();

    bool ParseOGRFeatures();

    void CopyEnvelope(OGRPolygon* p, gda::PolygonContents* pc);

	void Init(const std::string& layer_name,
            const std::string& map_type,
            int num_features,
            GeoDaTable* table,
            unsigned char* wkbs,
            const std::vector<int>& wkb_bytes_len,
            const std::string& pszProj4);

    static const std::string DT_STRING;
    static const std::string DT_INTEGER;
    static const std::string DT_NUMERIC;

    GDALDataset *poDS;
    OGRLayer *poLayer;
    OGRSpatialReference *poSpatialRef;
    MapType mapType;

    int numLayers;
    int numObs;
    int numCols;

    std::vector<std::string> fieldNames;
    std::vector<std::string> fieldTypes;
    std::map<std::string, unsigned int> fieldNameIdx;

    std::vector<gda::Point> centroids;
    std::vector<OGRFeature*> features;

    gda::MainMap* main_map;
};

int test();

GeoDaColumn* ToGeoDaColumn(GeoDaStringColumn* col);
GeoDaColumn* ToGeoDaColumn(GeoDaIntColumn* col);
GeoDaColumn* ToGeoDaColumn(GeoDaRealColumn* col);


#endif