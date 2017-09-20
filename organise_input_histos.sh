#!/bin/bash

#input txt for limits

if [ $# -ne 3 ]
then
    echo "You have to provide name of datacard:
          EmuSpectrum_datacard_S0.txt / EmuSpectrum_datacard_S1.txt / EmuSpectrum_datacard_S2.txt / EmuSpectrum_datacard_S3.txt /
          EmuSpectrum_datacard_S4.txt 
                   
          AND 

          category (0,1,2,3,4)
          
          AND

          name of the directory used for the limit calculation (eg. workdir)
          "
    exit 0
fi

echo "MAKE sure that you edited the input datacard correctly, which is used as input for the limit calculation!!!!!"
sleep 5

mass_min=600
mass_max=1000
mass_binning=200
cat=$2
./create_input_dirs.sh $3 ${mass_min} ${mass_max} ${mass_binning} ${cat}

if [ "$1" == "EmuSpectrum_datacard_S0.txt" ]
then
    if ! [ -f EmuSpectrum_datacard_S0.txt ]
	then
	echo "file EmuSpectrum_datacard_S0.txt needed as input is missing. Exiting ..."
	exit 0
    #rm -f EmuSpectrum_datacard.txt
    fi
fi

if [ "$1" == "EmuSpectrum_datacard_S1.txt" ]
then
    if ! [ -f EmuSpectrum_datacard_S1.txt ]
	then
	echo "file EmuSpectrum_datacard_S1.txt needed as input is missing. Exiting ..."
	exit 0
    #rm -f EmuSpectrum_datacard.txt
    fi
fi

if [ "$1" == "EmuSpectrum_datacard_S2.txt" ]
then
    if ! [ -f EmuSpectrum_datacard_S2.txt ]
	then
	echo "file EmuSpectrum_datacard_S2.txt needed as input is missing. Exiting ..."
	exit 0
    #rm -f EmuSpectrum_datacard.txt
    fi
fi

if [ "$1" == "EmuSpectrum_datacard_S3.txt" ]
then
    if ! [ -f EmuSpectrum_datacard_S3.txt ]
	then
	echo "file EmuSpectrum_datacard_S3.txt needed as input is missing. Exiting ..."
	exit 0
    #rm -f EmuSpectrum_datacard.txt
    fi
fi

if [ "$1" == "EmuSpectrum_datacard_S4.txt" ]
then
    if ! [ -f EmuSpectrum_datacard_S4.txt ]
	then
	echo "file EmuSpectrum_datacard_S4.txt needed as input is missing. Exiting ..."
	exit 0
    #rm -f EmuSpectrum_datacard.txt
    fi
fi

mass=${mass_min}

while [ $mass -le ${mass_max} ] 
do
    
    echo $mass
    
    if [ -d $3/input_masses/Mass_${mass}_Stage_${cat}_input ]
    then
	rm -f $3/input_masses/Mass_${mass}_Stage_${cat}_input/*
    else
	mkdir $3/input_masses/Mass_${mass}_Stage_${cat}_input
    fi
    
    
    if ! [ -f root_out/out_mass_${mass}_Stage${cat}.root ]
    then
	  echo "Did not find root file with histos for mass point: ${mass} and category Stage ${cat}"
	  continue
    else
	cp root_out/out_mass_${mass}_Stage${cat}.root $3/input_masses/Mass_${mass}_Stage_${cat}_input
	cp root_out/out_mass_${mass}_Stage${cat}.root $3/output_masses/Mass_${mass}_Stage_${cat}_output
	
    fi
    
    if ! [ -f txt_out/normalization_Mass_${mass}_Stage${cat}_input_histos.txt ]
    then
	echo "Did not find normalization txt file with histos for mass point: ${mass} and category Stage ${cat}"
	continue
    else
	cp txt_out/normalization_Mass_${mass}_Stage${cat}_input_histos.txt $3/input_masses/Mass_${mass}_Stage_${cat}_input/normalization.txt
    fi  
    
    if [ -f $3/input_masses/Mass_${mass}_Stage_${cat}_input/EmuSpectrum_datacard.txt ]
    then
	rm -f $3/input_masses/Mass_${mass}_Stage${cat}_input/EmuSpectrum_datacard.txt
    fi
    
    cp EmuSpectrum_datacard_S${cat}.txt $3/input_masses/Mass_${mass}_Stage_${cat}_input/tmp.txt
    
    number_signal_events=$(cat $3/input_masses/Mass_${mass}_Stage_${cat}_input/normalization.txt | grep "signal $mass" | awk '{print $3}')
    num_observed_events=$(cat $3/input_masses/Mass_${mass}_Stage_${cat}_input/normalization.txt | grep "data data_obs" | awk '{print $3}')
    
    echo "number_signal_events = " $number_signal_events
    echo "num_observed_events  = " $num_observed_events
    
    cat $3/input_masses/Mass_${mass}_Stage_${cat}_input/normalization.txt | grep 'bkg ' | grep -v Up | grep -v Down > tmp.txt
    
  #rates=`echo @rate_signal@`
    rates=`echo ${number_signal_events}`
    echo "rates = " $rates
    while read line
    do
	
    #echo "name bkg: $line" 
	
	rates_tmp=$(echo $line | awk '{print $3}')
	rates=`echo "${rates} ${rates_tmp}"`
	
    done < "tmp.txt"
    
#    rm -f tmp.txt
    echo "Now do sed"
    sed -e s/@root_input_file@/out_mass_${mass}_Stage${cat}.root/g -e  s/@rate_signal@/"${number_signal_events}"/g -e  s/@num_observed_events@/"${num_observed_events}"/g -e  s/@rates@/"${rates}"/g  $3/input_masses/Mass_${mass}_Stage_${cat}_input/tmp.txt >> $3/input_masses/Mass_${mass}_Stage_${cat}_input/EmuSpectrum_datacard.txt
    
    cp $3/input_masses/Mass_${mass}_Stage_${cat}_input/EmuSpectrum_datacard.txt $3/output_masses/Mass_${mass}_Stage_${cat}_output/EmuSpectrum_datacard.txt
    
#    rm -f $3/input_masses/Mass_${mass}_Stage_${cat}_input/tmp.txt
    
#      if [ $mass -lt $mass_int_1 ]
#	  then
#	  let mass=$mass+${mass_binning}
#      elif [ $mass -ge $mass_int_1 ] && [ $mass -lt $mass_int_2 ]
#	  then
#	  let mass=$mass+${mass_binning_2}
#      elif [ $mass -ge $mass_int_2 ]
#	  then
#	  let mass=$mass+${mass_binning_3}
#      fi      
    
    
    if [ $mass -le $mass_max ]
    then
        let mass=$mass+${mass_binning}           
    fi
    
done

if [ -f nohup.out ]
then
    rm -f nohup.out
fi

rm -rf $3/input_masses/

exit