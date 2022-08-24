#!/bin/bash

deusex_alive_LC=$(cat deusex_alive | wc -l)
deusex_dead_LC=$(cat deusex_dead | wc -l)
g

if [ $deusex_alive_LC -lt 280 ]; then
	printf "Your deusex_alive is not uwuing\n"
	exit 100
fi

if [ $deusex_dead_LC -gt 20 ]; then
	printf "Your deusex_dead is not uwuing\n"
	exit 100
fi

