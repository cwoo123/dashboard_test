
// script to analyse all performance data at once.


#include "Dashboard_Analysis.h"

void Analysis(int run_num){

  Analysis_FastEfficiencyTable(run_num);
  Analysis_VFATEfficiencyTable(run_num);
  Analysis_HotStripsTable(run_num);
  Analysis_DeadStripsTable(run_num);

}
