# dashboard_test

FIXME: Change absolute paths in C++ files

For FastEff, VFATEff, HotStrips, DeadStrips

Data-pulling functions can
1. Pull specific data for specific runs
2. Pull all data for specific runs
3. Pull Hot Strips data for all runs
4. Pull Dead Strips data for all runs

Analysis functions can
1. Analyse (and pull) specific data for specific runs
2. Analyse (and pull) all data for specific runs
3. Analyse (and pull) Hot Strips data for all runs
4. Analyse (and pull) Dead Strips data for all runs

Analyse data: write command line arguments as given in bottom of "Analyse.py"
- for AnalyseHotStripsTable/AnalyseDeadStripsTable, if sys.argv[1] is given as "a", Hot/Dead strips data across all runs will be taken and analysed.
- for PullAll/AnalyseAll, if sys.argv[1] is given as "n", all data (FastEff,VFATeff, etc) for run "n" will be pulled/analysed.
- All data is saved in /Data/CSVs and root files are output into /Data/Roots
