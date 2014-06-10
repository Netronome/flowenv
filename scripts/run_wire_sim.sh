#!/bin/sh

set -e

FLOWENV=${FLOWENV:-.}
TOOLS=${FLOWENV}/contrib/simtools
FIRMWARE=${FLOWENV}/me/apps/wire/wire.nffw
NCYCLES=${NCYCLES:-3000}

export LD_LIBRARY_PATH=$SDKHOME/lib

NFLO=$SDKHOME/bin/nflo
STEP=$TOOLS/sim_step
IMBSETUP=$TOOLS/sim_imb_setup
DMASETUP=$TOOLS/sim_nbi_dma_setup
PRESETUP=$TOOLS/sim_nbi_pre_setup
TMSETUP=$TOOLS/sim_nbi_tm_setup
MACSETUP=$TOOLS/sim_mac_setup
PCAPPLAY=$TOOLS/sim_pcap_play
PCAPREC=$TOOLS/sim_pcap_record

OFNBI0=/tmp/wire_nbi0.pcap
OFNBI1=/tmp/wire_nbi1.pcap

[ ! -f $NFLO ] && echo Can\'t find nflo >&1 && exit 1

[ ! -f $STEP ] && echo No sim_step program >&2 && exit 1
[ ! -f $IMBSETUP ] && echo No sim_imb_setup program at $IMBSETUP >&2 && exit 1
[ ! -f $DMASETUP ] && echo No sim_nbi_dma_setup program at $DMASETUP >&2 &&
	exit 1
[ ! -f $PRESETUP ] && echo No sim_nbi_pre_setup program at $PRESETUP >&2 &&
	exit 1
[ ! -f $TMSETUP ] && echo No sim_nbi_tm_setup program at $TMSETUP >&2 && exit 1
[ ! -f $MACSETUP ] && echo No sim_nbi_mac_setup program at $MACSETUP >&2 &&
	exit 1
[ ! -f $PCAPPLAY ] && echo No sim_nbi_pcap_play program at $PCAPPLAY >&2 &&
	exit 1
[ ! -f $PCAPREC ] && echo No sim_pcap_record program at $PCAPREC >&2 && exit 1


kill_nbi_record() {
        echo "    Received Signal!"
        echo "    Killing packet record and exiting"
        killall nbi_record
        exit 1
}


trap kill_nbi_record SIGTERM SIGINT

[ $# -ne 2 ] && echo usage: $0 NBI0_PCAP NBI1_PCAP && exit 1


echo "Running wire"

echo "    Loading firmware"
$NFLO -r $FIRMWARE > /dev/null

echo "    setting up IMB"
$IMBSETUP > /dev/null 2>&1

echo "    setting up NBI0 DMA"
$DMASETUP -n 0 -i 1 > /dev/null 2>&1

echo "    setting up NBI1 DMA"
$DMASETUP -n 1 -i 1 > /dev/null 2>&1

echo "    setting up NBI0 Preclassifier"
$PRESETUP -n 0 > /dev/null 2>&1

echo "    setting up NBI1 Preclassifier"
$PRESETUP -n 1 > /dev/null 2>&1

echo "    setting up NBI0 TM"
$TMSETUP -n 0 > /dev/null 2>&1

echo "    setting up NBI1 TM"
$TMSETUP -n 1 > /dev/null 2>&1

echo "    setting up NBI0 MAC"
$MACSETUP 0 > /dev/null 2>&1

echo "    setting up NBI1 MAC"
$MACSETUP 1 > /dev/null 2>&1

NP0=0
if [ "$1" != "--" ]
then
	NP0=`LD_LIBRARY_PATH= tcpdump -ns 0 -r $1 2>/dev/null | wc -l`
	echo "    Loading NBI0 from $1"
	$PCAPPLAY -n 0 $1
fi


NP1=0
if [ "$2" != "--" ]
then
	NP1=`LD_LIBRARY_PATH= tcpdump -ns 0 -r $2 2>/dev/null | wc -l`
	echo "    Loading NBI1 from $2"
	$PCAPPLAY -n 1 $2
fi


TOTAL=`expr $NP0 \+ $NP1`
echo "    Starting packet record: waiting for $TOTAL packets"
$PCAPREC -m $TOTAL 0:0:$OFNBI0 1:0:$OFNBI1 &

echo "    Running simulation ... will take a while"
$STEP $NCYCLES >/dev/null 2>&1

echo "    Simulation finished running: cleaning up packet capture"
set +e
kill %1 > /dev/null 2>&1
sleep 1
set -e

echo "    Output file: saved in $OFNBI0 and $OFNBI1"
