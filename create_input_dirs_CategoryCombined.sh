#!/bin/bash

if [ $# -ne 5 ]
then
    echo "Please give the name of the directory and input for the mass settings ..."
    exit 0
fi

step_size=$4

massStart=$2
massMax=$3

catMax=$5

echo "catMax = $catMax"

if ! [ -d $1 ]
then
    echo "create $1"
    mkdir $1
    echo "create input_masses_comb"
    mkdir $1/input_masses_comb
    echo "create output_masses_comb"
    mkdir $1/output_masses_comb
else
    if [ -d $1/input_masses_comb ]
    then
	echo "$1/input_masses_comb already exists! Check if this is o.k."
#	      rm -rf $1/input_masses/*
    else
	echo "create input_masses_comb"
	mkdir $1/input_masses_comb
    fi
    if [ -d $1/output_masses_comb ]
    then
	echo "$1/output_masses_comb already exists! Check if this is o.k."
#	      rm -rf $1/output_masses/*
    else
	echo "create output_masses_comb"
	mkdir $1/output_masses_comb
    fi
fi


while [ $massStart -le $massMax ]
do
    catStart=1    
  #create in-out-directories
    echo "mass : $massStart  ...."
    if ! [ -d $1/input_masses_comb/Mass_${massStart}_input ]
    then
	mkdir $1/input_masses_comb/Mass_${massStart}_input 
	
    fi    
    if ! [ -d $1/output_masses_comb/Mass_${massStart}_output ]
    then
	mkdir $1/output_masses_comb/Mass_${massStart}_output
#      mkdir $1/output_masses/Mass_${massStart}_output/condor
    fi    
    
    while [ $catStart -le $catMax ]
    do    
	echo "category $catStart .... "
	cp root_out/out_mass_${massStart}_Stage${catStart}.root $1/input_masses_comb/Mass_${massStart}_input/
	cp txt_out/normalization_Mass_${massStart}_Stage${catStart}_input_histos.txt $1/input_masses_comb/Mass_${massStart}_input/  
	
	cp root_out/out_mass_${massStart}_Stage${catStart}.root $1/output_masses_comb/Mass_${massStart}_output/
	cp txt_out/normalization_Mass_${massStart}_Stage${catStart}_input_histos.txt $1/output_masses_comb/Mass_${massStart}_output/
	
	let catStart=catStart+1
    done
    let massStart=$massStart+${step_size}
    
done

exit 0