
#include <unordered_map>
#include <stdexcept>

#include "rate_container.hpp"

using namespace std;

namespace mythical {

  void Rate_Container::addRate(int siteId, int neighId, double * rate){
    if(rates_.count(siteId)){
      if(rates_[siteId].count(neighId)){
        throw invalid_argument("Error the rate has already been added.");
      }
    }
    rates_[siteId][neighId]=rate;
  }

  void Rate_Container::addRates(Rate_Map rates){
    if(rates_.size()==0){
      rates_ = rates;
    }else{
      for( auto site : rates ){
        for ( auto neigh : site.second ){
          addRate(site.first,neigh.first,neigh.second); 
        }
      }
    }

  }

  double * Rate_Container::getRate(int siteId, int neighId) {
    if(rates_.count(siteId)==0){
      if(rates_[siteId].count(neighId)==0){
        throw invalid_argument("Cannot retrieve rate as it has not been added.");
      }
    }
    return rates_[siteId][neighId];
  }

  size_t Rate_Container::incomingRateCount(int siteId) {
    size_t count = 0;
    for( auto site : rates_ ) if(site.second.count(siteId)) ++count;
    return count;
  }

  size_t Rate_Container::outgoingRateCount(int siteId) {
    return rates_[siteId].size();
  }

  Rate_Map Rate_Container::getIncomingRates(int siteId) {
    Rate_Map rates; 
    for( auto site : rates_ ){
      for ( auto neigh : site.second ){
        if( neigh.first == siteId ){
          rates[site.first][neigh.first] = neigh.second;
        }
      }
    }
    return rates; 
  }

  Rate_Map Rate_Container::getOutgoingRates(int siteId) {
    Rate_Map rates;
    if(rates_.count(siteId)==1){
      rates[siteId] = rates_[siteId];
    }
    return rates;
  }

  vector<int> Rate_Container::getSourceSiteIds() {
    auto site_ids_outgoing = getSiteIdsWithOutgoingRates_();
    auto site_ids_incoming = getSiteIdsWithIncomingRates_();

    vector<int> source_site_ids;
    for( auto siteId : site_ids_outgoing ){
      if( site_ids_incoming.count(siteId)==0){
        source_site_ids.push_back(siteId);
      }
    }
    return source_site_ids;
  }

  unordered_set<int> Rate_Container::getSiteIdsWithOutgoingRates_(){
    unordered_set<int> siteIds;
    for( auto site : rates_ ) siteIds.insert(site.first);
    return siteIds;
  }

  vector<int> Rate_Container::getSinkSiteIds() {
    auto site_ids_outgoing = getSiteIdsWithOutgoingRates_();
    auto site_ids_incoming = getSiteIdsWithIncomingRates_();

    vector<int> sink_site_ids;
    for( auto siteId : site_ids_incoming ){
      if( site_ids_outgoing.count(siteId)==0){
        sink_site_ids.push_back(siteId);
      }
    }
    return sink_site_ids;
  }

  unordered_set<int> Rate_Container::getSiteIdsWithIncomingRates_(){
    unordered_set<int> siteIds;
    for( auto site : rates_ ) {
      for( auto neigh : site.second ){
        siteIds.insert(neigh.first);
      }
    }
    return siteIds;
  }

}

