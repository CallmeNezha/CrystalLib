//
// Created by admin on 2016/12/15.
//

#ifndef __CRYSTALLIB_DBSCAN_H__
#define __CRYSTALLIB_DBSCAN_H__

#include <vector>
#include <queue>
#include <set>
#include <functional>
#include <Eigen/Core>

namespace Crystal {

/**
* README **
* This is a DBSCAN clustering method implemented by nezha
*/
typedef unsigned int uint;

template<typename T, typename Float>
class DBSCAN final {

    enum ERROR_TYPE {
        SUCCESS = 0
        , FAILED
        , COUNT
    };

    typedef std::vector<T> TVector;
    typedef std::function<Float(const T&, const T&)> DistanceFunc;

public:
    DBSCAN() { }
    ~DBSCAN() { }

    int Run(TVector& V, const Float eps, const uint min, const DistanceFunc& disfunc) {
        
        // Validate
        if (V.size() < 1) return ERROR_TYPE::FAILED;

        // initialization
        this->_datalen = V.size();
        this->_visited = std::vector<bool>(this->_datalen, false);
        this->_assigned = std::vector<bool>(this->_datalen, false);
        this->Clusters.clear();
        this->Noise.clear();
        this->_minpts = min;
        this->_data = V;
        this->_disfunc = disfunc;
        this->_epsilon = eps;

        //

        for (uint pid = 0; pid < this->_datalen; ++pid) {
            // Check if point forms a cluster
            if (!this->_visited[pid]) {
                this->_visited[pid] = true;
                
                // it maybe noise or on the border of one cluster
                const std::vector<uint> neightbors = this->regionQuery(pid);
                if (neightbors.size() < this->_minpts) {
                    continue;
                }
                else {
                    uint cid = this->Clusters.size();
                    this->Clusters.push_back(std::vector<uint>());
                    // first blood
                    this->addToBorderSet(pid);
                    this->addToCluster(pid, cid);  
                    this->expandCluster(cid, neightbors);
                }
            }
        }

        for (uint pid = 0; pid < this->_datalen; ++pid) {
            if (!this->_assigned[pid]) this->Noise.push_back(pid);
        }

    }

private:
    std::vector<uint> regionQuery(const uint pid) const;
    void              addToCluster(const uint pid, const uint cid);
    void              expandCluster(const uint cid, const std::vector<uint>& neighbors);
    void              addToBorderSet(const uint pid) { this->_borderset.insert(pid); }
    void              addToBorderSet(const std::vector<uint>& pids) { for (uint pid : pids) this->_borderset.insert(pid); }
    bool              isInBorderSet(const uint pid) const { return this->_borderset.end() != this->_borderset.find(pid); }

public:
    std::vector<std::vector<uint>>  Clusters;
    std::vector<uint>               Noise;
    
private:
    //temporary variables used during computation
    std::vector<bool>   _visited;
    std::vector<bool>   _assigned;
    std::set<uint>      _borderset;
    uint                _datalen;
    uint                _minpts;
    Float               _epsilon;

    //TODO: replace it by kd-tree later
    std::vector<T>      _data;
    DistanceFunc        _disfunc;
};

template<typename T, typename Float>
std::vector<uint> DBSCAN<T, Float>::regionQuery(const uint pid) const {
    //TODO: replace it by kd-tree later , but... now brute force  O(n^2)
    std::vector<uint> neighbors;
    for (uint i = 0; i < this->_data.size(); ++i)
        if (i != pid &&  this->_disfunc(this->_data[pid], this->_data[i]) < this->_epsilon)
            neighbors.push_back(i);
    
    return neighbors;
}

template<typename T, typename Float>
void DBSCAN<T, Float>::expandCluster(const uint cid, const std::vector<uint>& neighbors) {

    std::queue<uint> border; // it has unvisited , visited unassigned pts. visited assigned will not appear
    for (uint pid : neighbors) border.push(pid); 
    this->addToBorderSet(neighbors);
    
    while(border.size() > 0) { 
        const uint pid = border.front(); border.pop();

        if (!this->_visited[pid]) {

            // not been visited, great! , hurry to mark it visited and assigned
            this->_visited[pid] = true;
            this->addToCluster(pid, cid);
            
            const std::vector<uint> pidneighbors = this->regionQuery(pid);

            // Core point, the neighbors will be expanded
            if (pidneighbors.size() >= this->_minpts) { 
                for (uint pidnid : pidneighbors) { 
                    if (!this->isInBorderSet(pidnid)) { 
                        border.push(pidnid); 
                        this->addToBorderSet(pidnid);
                    }
                }
            }
            
        }
        else {
            // if visited and not assgined implies it cant be a core point
            if (!this->_assigned[pid]) {
                // Not core points (just at the border of cluster)
                this->addToCluster(pid, cid);
            }
        }
    }
   
}

template<typename T, typename Float>
void DBSCAN<T, Float>::addToCluster(const uint pid, const uint cid) {
    this->Clusters[cid].push_back(pid);
    this->_assigned[pid] = true;
}





} // !namespace Crystal
#endif //CRYSTALLIB_DBSCAN_H
