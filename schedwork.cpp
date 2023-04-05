#ifndef RECCHECK
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#endif

// add or remove necessary headers as you please
#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;

bool helper(const AvailabilityMatrix& avail, const size_t dailyNeed, const size_t maxShifts, DailySchedule& sched, size_t day, size_t slot, vector<int>& scheduled_workers)
{
    // // Check if there are enough workers available on this day
    // size_t available_workers = 0;
    // for (size_t i = 0; i < avail.size(); ++i) {
    //     if (avail[i][day] && !scheduled_workers[i]) {
    //         ++available_workers;
    //     }
    // }
    // if (available_workers < dailyNeed) {
    //     return false;
    // }

    //base case
    //filled the schedule for all days, return true
    if (day == sched.size()) {
        return true;
    }

    //try to schedule each worker for the current day
    for (size_t i = 0; i < avail[0].size(); i++) {
        //check if worker available and has not reached maxShifts
        if (avail[day][i] && scheduled_workers[i] < maxShifts) {
            //schedule the worker for the current day
            //sched[day].push_back(i);
            sched[day][slot] = i;
            
            //increment the worker's shift count
            scheduled_workers[i]++;

            //recursively try to fill the rest of the schedule
            bool valid;
            if (slot == dailyNeed-1){
                valid = helper(avail, dailyNeed, maxShifts, sched, day + 1, 0, scheduled_workers);
                return valid;
            } 
            else {
                valid = helper(avail, dailyNeed, maxShifts, sched, day, slot+1, scheduled_workers);
                return valid;
            }
            
            /*
            if slot == dailyNeed:
                helper(avail, dailyNeed, maxShifts, sched, day + 1, 0, sched_workers)
            else:
                helper(avail, dailyNeed, maxShifts, sched, day, slot + 1, sched_workers)

            */
            

            //unmark the worker as scheduled
            scheduled_workers[i]--;
            //remove the worker from the current day's schedule
            sched[day].pop_back();
        }
    }

    //tried all workers and none worked
    return false;
}

bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{
    //check for invalid inputs
    if (avail.empty() || dailyNeed <= 0 || dailyNeed > avail.size() || maxShifts <= 0) {
        return false;
    }

    //initialize the schedule to the correct dimensions
    sched = DailySchedule(avail.size());
    for (size_t i = 0; i < sched.size(); i++){
         sched[i].resize(dailyNeed);
    }

    // //make sure the avail matrix has the correct dimensions
    // for (const auto& row : avail) {
    //     if (row.size() != sched.size()) {
    //         return false;
    //     }
    // }

    //initialize the vector of scheduled workers to all false
    vector<int> scheduled_workers(avail[0].size(), 0);

    //start the recursive search to fill the schedule
    return helper(avail, dailyNeed, maxShifts, sched, 0, 0, scheduled_workers);
}







/*
// Add prototypes for any helper functions here


// Add your implementation of schedule() and other helper functions here

bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{
    // Add your code below




}
*/
