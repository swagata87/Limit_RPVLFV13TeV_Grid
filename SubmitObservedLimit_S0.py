#!/bin/env python

import cesubmit
from gridFunctions import getdcachelist
import binConfig
import checkEnvironment
from datetime import datetime
import optparse,os,time,cPickle,subprocess,shutil,sys,random
import logging
log = logging.getLogger( 'remote' )

def makeExe(user):
    from string import Template
    exe="""
#!/bin/bash -e

echo Copying 1st pack...
  success=false
    for i in {1..2}; do
       if srmcp gsiftp://grid-ftp.physik.rwth-aachen.de:2811/pnfs/physik.rwth-aachen.de/cms/store/user/swmukher/EMU2016/HiggsAnalysis.tar file:///.; then
          success=true
          break
       fi
    done
  if ! $success; then
       echo "srmcp failed"
  fi

echo Copying 2nd pack...
  success=false
    for i in {1..2}; do
       if srmcp gsiftp://grid-ftp.physik.rwth-aachen.de:2811/pnfs/physik.rwth-aachen.de/cms/store/user/swmukher/EMU2016/workdir.tar  file:///.; then                                             
          success=true
          break
       fi
    done
  if ! $success; then
       echo "srmcp failed"
  fi

echo "------------------"
echo "Will extract HiggsAnalysis tar file"
echo "------------------"

mv HiggsAnalysis.tar $CMSSW_BASE/src/
cd $CMSSW_BASE/src/
tar -xvf HiggsAnalysis.tar

cmsenv
scram b clean
scram b -j 4

echo "----------------------"
echo "Inside ->"
echo $PWD
echo "----------------------"

cd ..
cd ..

echo "------------------"
echo "Will extract workdir tar file"
echo "------------------"

tar -xvf workdir.tar
mass=$1

cd workdir/output_masses/Mass_${mass}_Stage_0_output/                                                                                                                
                            
combine -M MarkovChainMC -H ProfileLikelihood EmuSpectrum_datacard.txt --tries 100  -s -1 -m 50 -n observed  --noDefaultPrior 0 


## ONLY for RPV
#if [ "${mass}" -le 200 ] ;
#  then
#  combine -M MarkovChainMC EmuSpectrum_datacard.txt --tries 100  -s -1 -m 50 -n observed --setPhysicsModelParameters r=0.01 --setPhysicsModelParameterRanges r=0,0.03  --noDefaultPrior 0
#elif [[ "${mass}" -gt 200 && "${mass}" -le 300 ]] ;
#  then
#  combine -M MarkovChainMC EmuSpectrum_datacard.txt --tries 100  -s -1 -m 50 -n observed --setPhysicsModelParameters r=0.01 --setPhysicsModelParameterRanges r=0,0.04  --noDefaultPrior 0
#elif [[ "${mass}" -gt 300 && "${mass}" -le 360 ]] ;
#  then
#  combine -M MarkovChainMC EmuSpectrum_datacard.txt --tries 100  -s -1 -m 50 -n observed --setPhysicsModelParameters r=0.01 --setPhysicsModelParameterRanges r=0,0.05  --noDefaultPrior 0
#elif [[ "${mass}" -gt 4900 && "${mass}" -le 5000 ]] ;
#  then
#  combine -M MarkovChainMC EmuSpectrum_datacard.txt --tries 100  -s -1 -m 50 -n observed --setPhysicsModelParameters r=2000 --setPhysicsModelParameterRanges r=1500,3000  --noDefaultPrior 0
#else 
#  combine -M MarkovChainMC -H ProfileLikelihood EmuSpectrum_datacard.txt --tries 100  -s -1 -m 50 -n observed  --noDefaultPrior 0
#fi


## RMAX NOT required for 2016 anymore
#if [ "${mass}" -le 1000 ] ;
#  then
#  combine -M MarkovChainMC -H ProfileLikelihood EmuSpectrum_datacard.txt --tries 100  -s -1 -m 50 -n observed  --noDefaultPrior 0
#elif [[ "${mass}" -gt 1000 && "${mass}" -le 1200 ]] ;
#  then
#  combine -M MarkovChainMC  EmuSpectrum_datacard.txt --tries 100  -s -1 -m 50 -n observed --rMax 0.03  --noDefaultPrior 0
#elif [[ "${mass}" -gt 1200 && "${mass}" -le 1400 ]] ;
#  then
#  combine -M MarkovChainMC  EmuSpectrum_datacard.txt --tries 100  -s -1 -m 50 -n observed --rMax 0.05  --noDefaultPrior 0
#elif [[ "${mass}" -gt 1400 && "${mass}" -le 1600 ]] ;
#  then
#  combine -M MarkovChainMC  EmuSpectrum_datacard.txt --tries 100  -s -1 -m 50 -n observed --rMax 0.09  --noDefaultPrior 0
#elif [[ "${mass}" -gt 1600 && "${mass}" -le 1800 ]] ;
#  then
#  combine -M MarkovChainMC  EmuSpectrum_datacard.txt --tries 100  -s -1 -m 50 -n observed --rMax 0.15  --noDefaultPrior 0
#elif [[ "${mass}" -gt 1800 && "${mass}" -le 2000 ]] ;
#  then
#  combine -M MarkovChainMC  EmuSpectrum_datacard.txt --tries 100  -s -1 -m 50 -n observed --rMax 0.3   --noDefaultPrior 0
#elif [[ "${mass}" -gt 2000 && "${mass}" -le 2200 ]] ;
#  then
#  combine -M MarkovChainMC  EmuSpectrum_datacard.txt --tries 100  -s -1 -m 50 -n observed --rMax 0.5  --noDefaultPrior 0
#elif [[ "${mass}" -gt 2200 && "${mass}" -le 2400 ]] ;
#  then
#  combine -M MarkovChainMC  EmuSpectrum_datacard.txt --tries 100  -s -1 -m 50 -n observed --rMax 0.8  --noDefaultPrior 0
#elif [[ "${mass}" -gt 2400 && "${mass}" -le 2600 ]] ;
#  then
#  combine -M MarkovChainMC  EmuSpectrum_datacard.txt --tries 100  -s -1 -m 50 -n observed --rMax 1.2  --noDefaultPrior 0
#elif [[ "${mass}" -gt 2600 && "${mass}" -le 2800 ]] ;
#  then
#  combine -M MarkovChainMC  EmuSpectrum_datacard.txt --tries 100  -s -1 -m 50 -n observed --rMax 2.0  --noDefaultPrior 0
#elif [[ "${mass}" -gt 2800 && "${mass}" -le 3000 ]] ;
#  then
#  combine -M MarkovChainMC  EmuSpectrum_datacard.txt --tries 100  -s -1 -m 50 -n observed --rMax 3.5  --noDefaultPrior 0
#elif [[ "${mass}" -gt 3000 && "${mass}" -le 3200 ]] ;
#  then
#  combine -M MarkovChainMC  EmuSpectrum_datacard.txt --tries 100  -s -1 -m 50 -n observed --rMax 5.5  --noDefaultPrior 0
#elif [[ "${mass}" -gt 3200 && "${mass}" -le 3400 ]] ;
#  then
#  combine -M MarkovChainMC  EmuSpectrum_datacard.txt --tries 100  -s -1 -m 50 -n observed --rMax 9.5  --noDefaultPrior 0
#elif [[ "${mass}" -gt 3400 && "${mass}" -le 3600 ]] ;
#  then
#  combine -M MarkovChainMC  EmuSpectrum_datacard.txt --tries 100  -s -1 -m 50 -n observed --rMax 14.5  --noDefaultPrior 0
#elif [[ "${mass}" -gt 3600 && "${mass}" -le 3800 ]] ;
#  then
#  combine -M MarkovChainMC  EmuSpectrum_datacard.txt --tries 100  -s -1 -m 50 -n observed --rMax 23.5  --noDefaultPrior 0
#elif [[ "${mass}" -gt 3800 && "${mass}" -le 4000 ]] ;                                                            
#  then                                                                                                          
#  combine -M MarkovChainMC  EmuSpectrum_datacard.txt --tries 100  -s -1 -m 50 -n observed --rMax 40.0  --noDefaultPrior 0
#elif [[ "${mass}" -gt 4000 && "${mass}" -le 5200 ]] ;                                                            
#  then                                                                                                          
#  combine -M MarkovChainMC  EmuSpectrum_datacard.txt --tries 100  -s -1 -m 50 -n observed --rMax 400.0  --noDefaultPrior 0
#else
#  echo "Wrong mass value"
#fi

#combine -M MarkovChainMC -H ProfileLikelihood EmuSpectrum_datacard.txt --tries 100 -s -1  -m 50 -n observed

ls -ltr
mv higgsCombineobserved*.root higgs.root
tar czf outfile.tar.gz higgs.root
cp outfile.tar.gz ../../../                                                                                                     
   
ls -ltr

####lcg-cp file:///`pwd`/higgs_Mass${mass}_observed.root   srm://grid-srm.physik.rwth-aachen.de:8443/pnfs/physik.rwth-aachen.de/cms/store/user/swmukher/LimitRPVTest2015/workdir/output_masses/Mass_${mass}_output/observed.root

"""

    exeFile=open("runtemp.sh","w+")
    exeFile.write(exe)
    exeFile.close()


def main():

    date_time = datetime.now()
    usage = '%prog [options] CONFIG_FILE'
    parser = optparse.OptionParser( usage = usage )
    parser.add_option( '-u', '--user', default = os.getenv( 'LOGNAME' ),
                            help = 'which user on dcache [default = %s]'%(os.getenv( 'LOGNAME' )))
    parser.add_option( '-o', '--Output', default = '%s'%(binConfig.outDir).replace("USER",os.getlogin())+"/TAG", metavar = 'DIRECTORY',
                            help = 'Define the output directory. [default = %default]')
    parser.add_option( '-f', '--force', default = "force the output to overwrite", metavar = 'DIRECTORY',
                            help = 'Define the output directory. [default = %default]')
    parser.add_option( '--debug', metavar = 'LEVEL', default = 'INFO',
                       help= 'Set the debug level. Allowed values: ERROR, WARNING, INFO, DEBUG. [default = %default]' )
    parser.add_option( '-t', '--Tag', default = "output%s_%s_%s_%s_%s"%(date_time.year,
                                                                        date_time.month,
                                                                        date_time.day,
                                                                        date_time.hour,
                                                                        date_time.minute), metavar = 'DIRECTORY',
                        help = 'Define a Tag for the output directory. [default = %default]' )
   # parser.add_option('-j', '--ijob', default='9999', 
   #                     help='Job number')

    ( options, args ) = parser.parse_args()
    #if len( args ) != 1:
        #parser.error( 'Exactly one CONFIG_FILE required!' )
    options.Output=options.Output.replace("TAG",options.Tag)


    format = '%(levelname)s from %(name)s at %(asctime)s: %(message)s'
    date = '%F %H:%M:%S'
    logging.basicConfig( level = logging._levelNames[ options.debug ], format = format, datefmt = date )

    try:
        cmssw_version, cmssw_base, scram_arch = checkEnvironment.checkEnvironment()
    except EnvironmentError, err:
        log.error( err )
        log.info( 'Exiting...' )
        sys.exit( err.errno )


    sampleList={"600","700","800","900","1000","1100","1200","1300","1400","1500","1600","1700","1800","1900","2000","2200","2400","2600","2800","3000","3500","4000","4500","5000"}

#    sampleList={"200","220","240","260","280","300","320","340","360","380","400","420","440","460","480","500","520","540","560","580","600","620","640","660","680","700","720","740","760","780","800","820","840","860","880","900","920","940","960","980","1000","1020","1040","1060","1080","1100","1120","1140","1160","1180","1200","1220","1240","1260","1280","1300","1320","1340","1360","1380","1400","1420","1440","1460","1480","1500","1520","1540","1560","1580","1600","1620","1640","1660","1680","1700","1800","1900","2000","2100","2200","2300","2400","2500","2600","2700","2800","2900","3000","3100","3200","3300","3400","3500","3600","3700","3800","3900","4000","4100","4200","4300","4400","4500","4600","4700","4800","4900","5000"}    

    makeExe(options.user)

    thisdir=os.getcwd()
    if os.path.exists(options.Output) or not options.force:
        log.error("The outpath "+options.Output+" already exists pick a new one or use --force")
        sys.exit(3)
    else:
        os.makedirs(options.Output)
    shutil.copyfile(thisdir+"/runtemp.sh",options.Output+"/runtemp.sh")
    os.remove(thisdir+"/runtemp.sh")


    for sample in sampleList:
     task=cesubmit.Task(sample, options.Output+"/Mass"+sample, scramArch=scram_arch, cmsswVersion=cmssw_version)
     task.executable=options.Output+"/runtemp.sh"
     #### DOES this mean I do not need to send it to dcashe and the working node ?
     task.inputfiles=[]
     task.outputfiles=["outfile.tar.gz"]
    
     standardArg=[sample]
     
#     for f in sampleList[sample]:
     job=cesubmit.Job()
     job.arguments=standardArg
     task.addJob(job)
     log.info("start submitting limits")
     ##### what is 6 ?
     ####task.submit(6,local=True)
     task.submit(6)                                                                                                                            
    log.info("Thanks for zapping in, bye bye")
    log.info("The out files will be in "+options.Output)



if __name__ == '__main__':
    main()
