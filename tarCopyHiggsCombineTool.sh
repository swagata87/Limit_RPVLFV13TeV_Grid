cd $CMSSW_BASE/src
tar -cvf HiggsAnalysis.tar HiggsAnalysis/
sleep 10
srmcp file:////$CMSSW_BASE/src/HiggsAnalysis.tar   srm://grid-srm.physik.rwth-aachen.de:8443/pnfs/physik.rwth-aachen.de/cms/store/user/swmukher/EMU2016/HiggsAnalysis.tar
