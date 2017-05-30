#!/bin/bash

#input txt for limits

if [ $# -ne 3 ]
then
    echo "You have to provide name of datacard (EmuSpectrum_datacard_CategoryCombined.txt)
                   
          AND 

          category (-1)
          
          AND

          name of the directory used for the limit calculation (eg. workdir)
          "
    exit 0
fi

echo "MAKE sure that you edited the input datacard correctly, which is used as input for the limit calculation!!!!!"
sleep 5

mass_min=1800
mass_max=4000
mass_binning=200

./create_input_dirs_CategoryCombined.sh $3 ${mass_min} ${mass_max} ${mass_binning} 4

if [ "$1" == "EmuSpectrum_datacard_CategoryCombined.txt" ]
then
    if ! [ -f EmuSpectrum_datacard_CategoryCombined.txt ]
	then
	echo "file EmuSpectrum_datacard_CategoryCombined.txt needed as input is missing. Exiting ..."
	exit 0
    #rm -f EmuSpectrum_datacard.txt
    fi
fi

mass=${mass_min}

while [ $mass -le ${mass_max} ] 
do
    echo " "
    echo "----------------"
    echo "mass $mass .... "
    echo "----------------"
    if [ -d $3/input_masses_comb/Mass_${mass}_input ]
    then
	rm -f $3/input_masses_comb/Mass_${mass}_input/*
    else
	mkdir $3/input_masses_comb/Mass_${mass}_input
    fi
    
    cp EmuSpectrum_datacard_CategoryCombined.txt $3/input_masses_comb/Mass_${mass}_input/tmp1.txt
    cp EmuSpectrum_datacard_CategoryCombined.txt $3/input_masses_comb/Mass_${mass}_input/tmp2.txt
    cp EmuSpectrum_datacard_CategoryCombined.txt $3/input_masses_comb/Mass_${mass}_input/tmp3.txt
    cp EmuSpectrum_datacard_CategoryCombined.txt $3/input_masses_comb/Mass_${mass}_input/tmp4.txt
    
## Copy root file
    if ! [ -f root_out/out_mass_${mass}_Stage1.root ]
	then
	    echo "Did not find root file with histos for mass point: ${mass} and category Stage 1"
	    continue
	else
	    cp root_out/out_mass_${mass}_Stage1.root $3/input_masses_comb/Mass_${mass}_input
	    cp root_out/out_mass_${mass}_Stage1.root $3/output_masses_comb/Mass_${mass}_output
	    
	fi
#
    if ! [ -f root_out/out_mass_${mass}_Stage2.root ]
	then
	    echo "Did not find root file with histos for mass point: ${mass} and category Stage 2"
	    continue
	else
	    cp root_out/out_mass_${mass}_Stage2.root $3/input_masses_comb/Mass_${mass}_input
	    cp root_out/out_mass_${mass}_Stage2.root $3/output_masses_comb/Mass_${mass}_output
	    
	fi
#
    if ! [ -f root_out/out_mass_${mass}_Stage3.root ]
	then
	    echo "Did not find root file with histos for mass point: ${mass} and category Stage 3"
	    continue
	else
	    cp root_out/out_mass_${mass}_Stage3.root $3/input_masses_comb/Mass_${mass}_input
	    cp root_out/out_mass_${mass}_Stage3.root $3/output_masses_comb/Mass_${mass}_output
	    
	fi
#
    if ! [ -f root_out/out_mass_${mass}_Stage4.root ]
	then
	    echo "Did not find root file with histos for mass point: ${mass} and category Stage 4"
	    continue
	else
	    cp root_out/out_mass_${mass}_Stage4.root $3/input_masses_comb/Mass_${mass}_input
	    cp root_out/out_mass_${mass}_Stage4.root $3/output_masses_comb/Mass_${mass}_output
	    
	fi
## copt txt file	
	if ! [ -f txt_out/normalization_Mass_${mass}_Stage1_input_histos.txt ]
	then
	    echo "Did not find normalization txt file with histos for mass point: ${mass} and category Stage 1"
	    continue
	else
	    cp txt_out/normalization_Mass_${mass}_Stage1_input_histos.txt $3/input_masses_comb/Mass_${mass}_input/
	fi  
#
	if ! [ -f txt_out/normalization_Mass_${mass}_Stage2_input_histos.txt ]
	then
	    echo "Did not find normalization txt file with histos for mass point: ${mass} and category Stage 2"
	    continue
	else
	    cp txt_out/normalization_Mass_${mass}_Stage2_input_histos.txt $3/input_masses_comb/Mass_${mass}_input/
	fi  
#
	if ! [ -f txt_out/normalization_Mass_${mass}_Stage3_input_histos.txt ]
	then
	    echo "Did not find normalization txt file with histos for mass point: ${mass} and category Stage 3"
	    continue
	else
	    cp txt_out/normalization_Mass_${mass}_Stage3_input_histos.txt $3/input_masses_comb/Mass_${mass}_input/
	fi  
#
	if ! [ -f txt_out/normalization_Mass_${mass}_Stage4_input_histos.txt ]
	then
	    echo "Did not find normalization txt file with histos for mass point: ${mass} and category Stage 4"
	    continue
	else
	    cp txt_out/normalization_Mass_${mass}_Stage4_input_histos.txt $3/input_masses_comb/Mass_${mass}_input/
	fi  
# Delete datacard if already present	
	if [ -f $3/input_masses_comb/Mass_${mass}_input/EmuSpectrum_datacard_CategoryCombined.txt ]
	then
	    rm -f $3/input_masses_comb/Mass_${mass}_input/EmuSpectrum_datacard_CategoryCombined.txt
	fi
# Nsig and Nobs		
	number_signal_events_S1=$(cat $3/input_masses_comb/Mass_${mass}_input/normalization_Mass_${mass}_Stage1_input_histos.txt | grep "signal $mass" | awk '{print $3}')
	num_observed_events_S1=$(cat $3/input_masses_comb/Mass_${mass}_input/normalization_Mass_${mass}_Stage1_input_histos.txt | grep "data data_obs" | awk '{print $3}')
	echo "number_signal_events_S1 = " $number_signal_events_S1
	echo "num_observed_events_S1  = " $num_observed_events_S1
#
	number_signal_events_S2=$(cat $3/input_masses_comb/Mass_${mass}_input/normalization_Mass_${mass}_Stage2_input_histos.txt | grep "signal $mass" | awk '{print $3}')
	num_observed_events_S2=$(cat $3/input_masses_comb/Mass_${mass}_input/normalization_Mass_${mass}_Stage2_input_histos.txt | grep "data data_obs" | awk '{print $3}')
	echo "number_signal_events_S2 = " $number_signal_events_S2
	echo "num_observed_events_S2  = " $num_observed_events_S2
#
	number_signal_events_S3=$(cat $3/input_masses_comb/Mass_${mass}_input/normalization_Mass_${mass}_Stage3_input_histos.txt | grep "signal $mass" | awk '{print $3}')
	num_observed_events_S3=$(cat $3/input_masses_comb/Mass_${mass}_input/normalization_Mass_${mass}_Stage3_input_histos.txt | grep "data data_obs" | awk '{print $3}')
	echo "number_signal_events_S3 = " $number_signal_events_S3
	echo "num_observed_events_S3  = " $num_observed_events_S3
#
	number_signal_events_S4=$(cat $3/input_masses_comb/Mass_${mass}_input/normalization_Mass_${mass}_Stage4_input_histos.txt | grep "signal $mass" | awk '{print $3}')
	num_observed_events_S4=$(cat $3/input_masses_comb/Mass_${mass}_input/normalization_Mass_${mass}_Stage4_input_histos.txt | grep "data data_obs" | awk '{print $3}')
	echo "number_signal_events_S4 = " $number_signal_events_S4
	echo "num_observed_events_S4  = " $num_observed_events_S4
# Get BKG	
	cat $3/input_masses_comb/Mass_${mass}_input/normalization_Mass_${mass}_Stage1_input_histos.txt | grep 'bkg ' | grep -v Up | grep -v Down > tmp1.txt
      	cat $3/input_masses_comb/Mass_${mass}_input/normalization_Mass_${mass}_Stage2_input_histos.txt | grep 'bkg ' | grep -v Up | grep -v Down > tmp2.txt
	cat $3/input_masses_comb/Mass_${mass}_input/normalization_Mass_${mass}_Stage3_input_histos.txt | grep 'bkg ' | grep -v Up | grep -v Down > tmp3.txt
	cat $3/input_masses_comb/Mass_${mass}_input/normalization_Mass_${mass}_Stage4_input_histos.txt | grep 'bkg ' | grep -v Up | grep -v Down > tmp4.txt
	
# Fill tmp 
	rates_S1=`echo ${number_signal_events_S1}`
	echo "rates_S1 = " $rates_S1
	while read line_S1
	do
	    rates_tmp_S1=$(echo $line_S1 | awk '{print $3}')
	    rates_S1=`echo "${rates_S1} ${rates_tmp_S1}"`
	done < "tmp1.txt"
#
	rates_S2=`echo ${number_signal_events_S2}`
	echo "rates_S2 = " $rates_S2
	while read line_S2
	do
	    rates_tmp_S2=$(echo $line_S2 | awk '{print $3}')
	    rates_S2=`echo "${rates_S2} ${rates_tmp_S2}"`
	done < "tmp2.txt"
#
	rates_S3=`echo ${number_signal_events_S3}`
	echo "rates_S3 = " $rates_S3
	while read line_S3
	do
	    rates_tmp_S3=$(echo $line_S3 | awk '{print $3}')
	    rates_S3=`echo "${rates_S3} ${rates_tmp_S3}"`
	done < "tmp3.txt"
#
	rates_S4=`echo ${number_signal_events_S4}`
	echo "rates_S4 = " $rates_S4
	while read line_S4
	do
	    rates_tmp_S4=$(echo $line_S4 | awk '{print $3}')
	    rates_S4=`echo "${rates_S4} ${rates_tmp_S4}"`
	done < "tmp4.txt"
#	
	#rm -f tmp.txt
	echo " ( "
	cat tmp1.txt
	cat tmp2.txt
	cat tmp3.txt
	cat tmp4.txt
	echo " ) "

	rm -f tmp1.txt
	rm -f tmp2.txt
	rm -f tmp3.txt
	rm -f tmp4.txt
	echo "Now do sed... mass : ${mass} "
	
#	sed -e s/@root_input_file_S1@/out_mass_${mass}_Stage1.root/g  -e  s/@rate_signal_S1@/"${number_signal_events_S1}"/g -e  s/@num_obs_S1@/"${num_observed_events_S1}"/g -e  s/@rates_S1@/"${rates_S1}"/g $3/input_masses_comb/Mass_${mass}_input/tmp1.txt -e s/@root_input_file_S2@/out_mass_${mass}_Stage2.root/g -e  s/@rate_signal_S2@/"${number_signal_events_S2}"/g -e  s/@num_obs_S2@/"${num_observed_events_S2}"/g -e  s/@rates_S2@/"${rates_S2}"/g $3/input_masses_comb/Mass_${mass}_input/tmp2.txt  -e s/@root_input_file_S3@/out_mass_${mass}_Stage3.root/g -e  s/@rate_signal_S3@/"${number_signal_events_S3}"/g -e  s/@num_obs_S3@/"${num_observed_events_S3}"/g -e  s/@rates_S3@/"${rates_S3}"/g $3/input_masses_comb/Mass_${mass}_input/tmp3.txt -e s/@root_input_file_S4@/out_mass_${mass}_Stage4.root/g -e  s/@rate_signal_S4@/"${number_signal_events_S4}"/g -e  s/@num_obs_S4@/"${num_observed_events_S4}"/g -e  s/@rates_S4@/"${rates_S4}"/g  $3/input_masses_comb/Mass_${mass}_input/tmp4.txt >> $3/input_masses_comb/Mass_${mass}_input/EmuSpectrum_datacard_CategoryCombined.txt

	sed -e s/@root_input_file_S1@/out_mass_${mass}_Stage1.root/g  -e  s/@rate_signal_S1@/"${number_signal_events_S1}"/g -e  s/@num_obs_S1@/"${num_observed_events_S1}"/g -e  s/@rates_S1@/"${rates_S1}"/g  -e s/@root_input_file_S2@/out_mass_${mass}_Stage2.root/g -e  s/@rate_signal_S2@/"${number_signal_events_S2}"/g -e  s/@num_obs_S2@/"${num_observed_events_S2}"/g -e  s/@rates_S2@/"${rates_S2}"/g   -e s/@root_input_file_S3@/out_mass_${mass}_Stage3.root/g -e  s/@rate_signal_S3@/"${number_signal_events_S3}"/g -e  s/@num_obs_S3@/"${num_observed_events_S3}"/g -e  s/@rates_S3@/"${rates_S3}"/g  -e s/@root_input_file_S4@/out_mass_${mass}_Stage4.root/g -e  s/@rate_signal_S4@/"${number_signal_events_S4}"/g -e  s/@num_obs_S4@/"${num_observed_events_S4}"/g -e  s/@rates_S4@/"${rates_S4}"/g $3/input_masses_comb/Mass_${mass}_input/tmp4.txt >> $3/input_masses_comb/Mass_${mass}_input/EmuSpectrum_datacard_CategoryCombined.txt

	
#
	cp $3/input_masses_comb/Mass_${mass}_input/EmuSpectrum_datacard_CategoryCombined.txt $3/output_masses_comb/Mass_${mass}_output/EmuSpectrum_datacard_CategoryCombined.txt
       
    if [ $mass -le $mass_max ]
    then
        let mass=$mass+${mass_binning}           
    fi
    
done

if [ -f nohup.out ]
then
    rm -f nohup.out
fi

rm -rf $3/input_masses_comb/

exit