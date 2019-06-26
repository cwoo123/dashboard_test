import os, sys, io
import matplotlib.pyplot # is this portable/useful

def Analyse_FastEfficiencyTable(run_num):

    # by reading csv file, obtain mean, std of fasteff values - using some python package

    

    # plot on histogram [   x_axis: efficiency 1:100:10 , y_axis: chamber multiplicity  ] ??


    pass

if __name__ == '__main__':
    runNumber = sys.argv[1]
    AnalysisType = sys.argv[2]
    if AnalysisType == "FastEfficiencyTable":
        Analyse_FastEfficiencyTable(runNumber)
    else:
        print "Wrong name for a table!"
