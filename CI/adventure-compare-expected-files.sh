#!/bin/bash

level_alive_LC=$(cat level_alive | wc -l)
level_dead_LC=$(cat level_dead | wc -l)
level_alive_WC=$(cat level_alive | wc -w)
level_dead_WC=$(cat level_dead | wc -w)
level_alive_CC=$(cat level_alive | wc -c)
level_dead_CC=$(cat level_dead | wc -c)

power_alive_LC=$(cat power_alive | wc -l)
power_dead_LC=$(cat power_dead | wc -l)
power_alive_WC=$(cat power_alive | wc -w)
power_dead_WC=$(cat power_dead | wc -w)
power_alive_CC=$(cat power_alive | wc -c)
power_dead_CC=$(cat power_dead | wc -c)

charm_alive_LC=$(cat charm_alive | wc -l)
charm_dead_LC=$(cat charm_dead | wc -l)
charm_alive_WC=$(cat charm_alive | wc -w)
charm_dead_WC=$(cat charm_dead | wc -w)
charm_alive_CC=$(cat charm_alive | wc -c)
charm_dead_CC=$(cat charm_dead | wc -c)

strategy_alive_LC=$(cat strategy_alive | wc -l)
strategy_dead_LC=$(cat strategy_dead | wc -l)
strategy_alive_WC=$(cat strategy_alive | wc -w)
strategy_dead_WC=$(cat strategy_dead | wc -w)
strategy_alive_CC=$(cat strategy_alive | wc -c)
strategy_dead_CC=$(cat strategy_dead | wc -c)

subtlety_alive_LC=$(cat subtlety_alive | wc -l)
subtlety_dead_LC=$(cat subtlety_dead | wc -l)
subtlety_alive_WC=$(cat subtlety_alive | wc -w)
subtlety_dead_WC=$(cat subtlety_dead | wc -w)
subtlety_alive_CC=$(cat subtlety_alive | wc -c)
subtlety_dead_CC=$(cat subtlety_dead | wc -c)

#level
if [ $level_alive_LC -ne 109 ]; then
	printf "Your level_alive is not uwuing.\n"
	exit 100
fi

if [ $level_dead_LC -ne 191 ]; then
	printf "Your level_dead is not uwuing.\n"
	exit 101
fi

if [ $level_alive_LC -ne 109 ]; then
	printf "Your level_alive is not uwuing.\n"
	exit 100
fi

if [ $level_dead_LC -ne 191 ]; then
	printf "Your level_dead is not uwuing.\n"
	exit 101
fi

if [ $level_alive_LC -ne 109 ]; then
	printf "Your level_alive is not uwuing.\n"
	exit 100
fi

if [ $level_dead_LC -ne 191 ]; then
	printf "Your level_dead is not uwuing.\n"
	exit 101
fi


#power
if [ $power_alive_LC -ne 154 ]; then
	printf "Your power_alive is not uwuing.\n"
	exit 100
fi

if [ $power_dead_LC -ne 146 ]; then
	printf "Your power_dead is not uwuing.\n"
	exit 101
fi

if [ $power_alive_WC -ne 992 ]; then
	printf "Your power_alive is not uwuing.\n"
	exit 100
fi

if [ $power_dead_WC -ne 1587 ]; then
	printf "Your power_dead is not uwuing.\n"
	exit 101
fi

if [ $power_alive_CC -ne 6387 ]; then
	printf "Your power_alive is not uwuing.\n"
	exit 100
fi

if [ $power_dead_CC -ne 9385 ]; then
	printf "Your power_dead is not uwuing.\n"
	exit 101
fi


#charm
if [ $charm_alive_LC -ne 130 ]; then
	printf "Your charm_alive is not uwuing.\n"
	exit 100
fi

if [ $charm_dead_LC -ne 170 ]; then
	printf "Your charm_dead is not uwuing.\n"
	exit 101
fi

if [ $charm_alive_WC -ne 843 ]; then
	printf "Your charm_alive is not uwuing.\n"
	exit 100
fi

if [ $charm_dead_WC -ne 1964 ]; then
	printf "Your charm_dead is not uwuing.\n"
	exit 101
fi

if [ $charm_alive_CC -ne 5414 ]; then
	printf "Your charm_alive is not uwuing.\n"
	exit 100
fi

if [ $charm_dead_CC -ne 10910 ]; then
	printf "Your charm_dead is not uwuing.\n"
	exit 101
fi


#strategy
if [ $strategy_alive_LC -ne 134 ]; then
	printf "Your strategy_alive is not uwuing.\n"
	exit 100
fi

if [ $strategy_dead_LC -ne 166 ]; then
	printf "Your strategy_dead is not uwuing.\n"
	exit 101
fi

if [ $strategy_alive_WC -ne 867 ]; then
	printf "Your strategy_alive is not uwuing.\n"
	exit 100
fi

if [ $strategy_dead_WC -ne 1933 ]; then
	printf "Your strategy_dead is not uwuing.\n"
	exit 101
fi

if [ $strategy_alive_CC -ne 5530 ]; then
	printf "Your strategy_alive is not uwuing.\n"
	exit 100
fi

if [ $strategy_dead_CC -ne 11237 ]; then
	printf "Your strategy_dead is not uwuing.\n"
	exit 101
fi


#subtlety
if [ $subtlety_alive_LC -ne 118 ]; then
	printf "Your subtlety_alive is not uwuing.\n"
	exit 100
fi

if [ $subtlety_dead_LC -ne 182 ]; then
	printf "Your subtlety_dead is not uwuing.\n"
	exit 101
fi

if [ $subtlety_alive_WC -ne 772 ]; then
	printf "Your subtlety_alive is not uwuing.\n"
	exit 100
fi

if [ $subtlety_dead_WC -ne 2153 ]; then
	printf "Your subtlety_dead is not uwuing.\n"
	exit 101
fi

if [ $subtlety_alive_CC -ne 4925 ]; then
	printf "Your subtlety_alive is not uwuing.\n"
	exit 100
fi

if [ $subtlety_dead_CC -ne 12043 ]; then
	printf "Your subtlety_dead is not uwuing.\n"
	exit 101
fi
