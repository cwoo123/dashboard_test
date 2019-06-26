# remove test

import cx_Oracle
import os, sys, io

def getFastEfficiencyTable(run_num):
    print "\nDownloading FastEfficiencyTable for run {0}".format(run_num)

    db = cx_Oracle.connect('GEM_904_COND/904CondDB@INT2R')
    cur = db.cursor()

    query = "select * from CMS_GEM_MUON_VIEW.QC8_GEM_QUICK_EFFICIENCY_V_RH where RUN_NUMBER="+str(run_num) # ???
    cur.execute(query)

    configTablesPath = os.path.abspath("dumpDBtables.py").split('QC8Test')[0] + 'dashboard_test/Dashboard/Data/CSVs/' #???
    outfile_name = configTablesPath + "Test_FastEfficiencyTable_run{0}.csv".format(run_num) # ???

    with open(outfile_name,"w+") as outfile:
        line = "CHAMBER_NAME,OVERALL_EFFICIENCY,ERROR_EFFICIENCY,RUN_NUMBER\n"
        outfile.write(line)
        for result in cur:
            chamber_name           = result[0]
            overall_efficiency     = result[1]
            error_efficiency       = result[2]
            run_number             = result[3]
            line = str(chamber_name) + "," + str(overall_efficiency) + "," + str(error_efficiency) + "," + str(run_number)  + "\n"
            outfile.write(line)

    print "\nSuccesfully done!\n"

def getVFATTable(run_num):
    print "\nDownloading VFATEfficiencyTable for run {0}".format(run_num)

    db = cx_Oracle.connect('GEM_904_COND/904CondDB@INT2R')
    cur = db.cursor()

    query = "select * from CMS_GEM_MUON_VIEW.QC8_GEM_CH_VFAT_EFF_VIEW_RH where RUN_NUMBER="+str(run_num) # ???
    cur.execute(query)

    configTablesPath = os.path.abspath("dumpDBtables.py").split('QC8Test')[0] + 'dashboard_test/Dashboard/Data/CSVs/' #???
    outfile_name = configTablesPath + "Test_VFATEfficiencyTable_run{0}.csv".format(run_num) # ???

    with open(outfile_name,"w+") as outfile:
        line = "CHAMBER_NAME,VFAT_POSN,EFFICIENCY,EFFICIENCY_ERROR,CLUSTER_SIZE_AVG,CLUSTER_SIZE_SIGMA,PERCENT_MASKED,RUN_NUMBER,RUN_BEGIN,RUN_END\n"
        outfile.write(line)
        for result in cur:
            chamber_name        = result[0]
            vfat_posn           = result[1]
            efficiency          = result[2]
            efficiency_error    = result[3]
            cluster_size_avg    = result[4]
            cluster_size_sigma  = result[5]
            percent_masked      = result[6]
            run_number          = result[7]
            run_begin           = result[8]
            run_end             = result[9]
            line = str(chamber_name) + "," + str(vfat_posn) + "," + str(efficiency) + "," + str(efficiency_error)  + "," + str(cluster_size_avg) + \
                    "," + str(cluster_size_sigma) + "," + str(percent_masked) + "," + str(run_number) + "," + str(run_begin) + "," + str(run_end) + "\n"
            outfile.write(line)

    print "\nSuccesfully done!\n"

def getHotStripsTable(run_num):
    print "\nDownloading HotStripsTable for run {0}".format(run_num)

    db = cx_Oracle.connect('GEM_904_COND/904CondDB@INT2R')
    cur = db.cursor()

    query = "select * from CMS_GEM_MUON_VIEW.QC8_GEM_MASKED_STRIPS_HOT_V_RH where RUN_NUMBER="+str(run_num)
    cur.execute(query)

    hotStripsTablesPath = os.path.abspath("dumpDBtables.py").split('QC8Test')[0] + 'dashboard_test/Dashboard/Data/CSVs/'
    outfile_name = hotStripsTablesPath + "Test_HotStrips_run{0}.csv".format(run_num)

    with open(outfile_name,"w+") as outfile:
        line = "CH_SERIAL_NUMBER,GEM_NUMBER,POSITION,VFAT,CHANNEL,STRIP,RUN_NUMBER\n"
        outfile.write(line)
        for result in cur:
            chamber_name = result[0]
            gem_num      = result[1]
            position     = result[2]
            vfat         = result[3]
            channel      = result[4]
            strip        = result[5]
            run_number   = result[6]
            line = str(chamber_name) + "," + str(gem_num) + "," + str(position) + "," + str(vfat) + "," + str(channel) + "," + str(strip) + "," + str(run_number) + "\n"
            outfile.write(line)

    print "\nSuccesfully done!\n"

def getDeadStripsTable(run_num):
    print "\nDownloading DeadStripsTable for run {0}".format(run_num)

    db = cx_Oracle.connect('GEM_904_COND/904CondDB@INT2R')
    cur = db.cursor()

    query = "select * from CMS_GEM_MUON_VIEW.QC8_GEM_MASKED_STRIPS_DEAD_RH where RUN_NUMBER="+str(run_num)
    cur.execute(query)

    deadStripsTablesPath = os.path.abspath("dumpDBtables.py").split('QC8Test')[0] + 'dashboard_test/Dashboard/Data/CSVs/'
    outfile_name = deadStripsTablesPath + "Test_DeadStrips_run{0}.csv".format(run_num)

    with open(outfile_name,"w+") as outfile:
        line = "CH_SERIAL_NUMBER,GEM_NUMBER,POSITION,VFAT,CHANNEL,STRIP,RUN_NUMBER\n"
        outfile.write(line)
        for result in cur:
            chamber_name = result[0]
            gem_num      = result[1]
            position     = result[2]
            vfat         = result[3]
            channel      = result[4]
            strip        = result[5]
            run_number   = result[6]
            line = str(chamber_name) + "," + str(gem_num) + "," + str(position) + "," + str(vfat) + "," + str(channel) + "," + str(strip) + "," + str(run_number) + "\n"
            outfile.write(line)

    print "\nSuccesfully done!\n"


if __name__ == '__main__':
    runNumber = sys.argv[1]
    tableType = sys.argv[2]
    if tableType == "FastEfficiencyTable":
        getFastEfficiencyTable(runNumber)
    elif tableType == "VFATEfficiencyTable":
        getVFATTable(runNumber)
    elif tableType == "HotStripsTable":
        getHotStripsTable(runNumber)
    elif tableType == "DeadStripsTable":
        getDeadStripsTable(runNumber)
    else:
        print "Wrong name for a table!"
