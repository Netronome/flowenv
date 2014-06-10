#!/bin/sh
#
#  Copyright (C) 2010 Netronome Systems, Inc.  All rights reserved.
#
#  Debug utility to view MicroEngine signalled events,
#  wakeup it events and Context current program counter
#

isl="$1"
me="$2"
if [ -z "$me" ] || [ -z "$isl" ]; then
        cat <<EOF 1>&2
Usage:

$0 <isl#> <me#>
EOF
        exit 1
fi

nfpreg() {
        $SDKHOME/bin/nfp-reg "$1" | sed -e 's/[^=]*=//'
}

val=`nfpreg mecsr:i32.me0.ActCtxStatus.ActiveContextNo`
echo -n "i"$isl".me"$me":  Active context = "
printf "%d\n" $val

echo "      SIG_EVENTS WAKE_EVENT CTX_STS READY"
for i in 0 1 2 3 4 5 6 7 ;
do
        echo -n "CTX${i}: "
        val=`nfpreg mecsr:i${isl}.me${me}.ctx${i}.IndCtxSglEvt.Signals`
        printf "0x%08x " $(( ($val << 1) | 1 ))
        val=`nfpreg mecsr:i${isl}.me${me}.ctx${i}.IndCtxWkpEvt.WakeupEvents`
        val2=`nfpreg mecsr:i${isl}.me${me}.ctx${i}.IndCtxWkpEvt.Voluntary`
        printf "0x%08x " $(( ($val << 1) | $val2 ))
        val=`nfpreg mecsr:i${isl}.me${me}.ctx${i}.IndCtxStatus.ContextPC`
        printf "%7d " $val
        val=`nfpreg mecsr:i${isl}.me${me}.ctx${i}.IndCtxStatus.ReadyToRun`
        printf "%5d\n" $val
done
