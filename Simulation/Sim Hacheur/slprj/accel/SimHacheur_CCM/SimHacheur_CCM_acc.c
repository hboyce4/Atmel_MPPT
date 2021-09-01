#include "__cf_SimHacheur_CCM.h"
#include <math.h>
#include "SimHacheur_CCM_acc.h"
#include "SimHacheur_CCM_acc_private.h"
#include <stdio.h>
#include "simstruc.h"
#include "fixedpoint.h"
#define CodeFormat S-Function
#define AccDefine1 Accelerator_S-Function
real_T look1_binlxpw ( real_T u0 , const real_T bp0 [ ] , const real_T table
[ ] , uint32_T maxIndex ) { real_T frac ; uint32_T iRght ; uint32_T iLeft ;
uint32_T bpIdx ; if ( u0 <= bp0 [ 0U ] ) { iLeft = 0U ; frac = ( u0 - bp0 [
0U ] ) / ( bp0 [ 1U ] - bp0 [ 0U ] ) ; } else if ( u0 < bp0 [ maxIndex ] ) {
bpIdx = maxIndex >> 1U ; iLeft = 0U ; iRght = maxIndex ; while ( iRght -
iLeft > 1U ) { if ( u0 < bp0 [ bpIdx ] ) { iRght = bpIdx ; } else { iLeft =
bpIdx ; } bpIdx = ( iRght + iLeft ) >> 1U ; } frac = ( u0 - bp0 [ iLeft ] ) /
( bp0 [ iLeft + 1U ] - bp0 [ iLeft ] ) ; } else { iLeft = maxIndex - 1U ;
frac = ( u0 - bp0 [ maxIndex - 1U ] ) / ( bp0 [ maxIndex ] - bp0 [ maxIndex -
1U ] ) ; } return ( table [ iLeft + 1U ] - table [ iLeft ] ) * frac + table [
iLeft ] ; } static void mdlOutputs ( SimStruct * S , int_T tid ) { real_T
o33zqjjt5d ; real_T currentTime ; n3qi1whofz * _rtB ; loikxjbxjg * _rtP ;
ew10rzwqr2 * _rtDW ; _rtDW = ( ( ew10rzwqr2 * ) ssGetRootDWork ( S ) ) ; _rtP
= ( ( loikxjbxjg * ) ssGetDefaultParam ( S ) ) ; _rtB = ( ( n3qi1whofz * )
_ssGetBlockIO ( S ) ) ; if ( ssIsSampleHit ( S , 2 , 0 ) ) { _rtB ->
cvkeszmnjq [ 0 ] = _rtP -> P_5 [ 0 ] ; _rtB -> cvkeszmnjq [ 1 ] = _rtP -> P_5
[ 1 ] ; _rtB -> cvkeszmnjq [ 2 ] = _rtP -> P_5 [ 2 ] ; _rtB -> cvkeszmnjq [ 3
] = _rtP -> P_5 [ 3 ] ; _rtB -> je1asji303 = _rtP -> P_6 ; _rtB -> k3taxnr0ym
= _rtP -> P_7 ; _rtB -> em1vtxpfzv = _rtP -> P_8 ; _rtB -> gh4tissgyw = _rtP
-> P_9 ; ssCallAccelRunBlock ( S , 1 , 5 , SS_CALL_MDL_OUTPUTS ) ; }
o33zqjjt5d = ssGetT ( S ) ; _rtB -> fdkghnhej4 = ssGetTStart ( S ) ;
o33zqjjt5d -= _rtB -> fdkghnhej4 ; if ( ssIsSampleHit ( S , 1 , 0 ) ) { _rtB
-> mdyadk04ie = _rtP -> P_10 ; } o33zqjjt5d = muDoubleScalarRem ( o33zqjjt5d
, _rtB -> mdyadk04ie ) ; o33zqjjt5d = look1_binlxpw ( o33zqjjt5d , _rtP ->
P_12 , _rtP -> P_11 , 1U ) ; _rtB -> f10ve052uj = muDoubleScalarFloor ( _rtP
-> P_13 * o33zqjjt5d ) ; _rtB -> i0htfp3fk2 = _rtP -> P_14 * _rtB ->
f10ve052uj ; if ( ssIsMajorTimeStep ( S ) ) { _rtDW -> p4xqdips0v = _rtB ->
i0htfp3fk2 >= _rtP -> P_15 ? 1 : _rtB -> i0htfp3fk2 > _rtP -> P_16 ? 0 : - 1
; } _rtB -> da0dudg0f4 = _rtDW -> p4xqdips0v == 1 ? _rtP -> P_15 : _rtDW ->
p4xqdips0v == - 1 ? _rtP -> P_16 : _rtB -> i0htfp3fk2 ; o33zqjjt5d = ssGetT (
S ) ; _rtB -> ch4s12p1rz = ssGetTStart ( S ) ; o33zqjjt5d -= _rtB ->
ch4s12p1rz ; if ( ssIsSampleHit ( S , 1 , 0 ) ) { _rtB -> koatzglqdb = _rtP
-> P_17 ; } o33zqjjt5d = muDoubleScalarRem ( o33zqjjt5d , _rtB -> koatzglqdb
) ; _rtB -> ahsodbcljv = look1_binlxpw ( o33zqjjt5d , _rtP -> P_19 , _rtP ->
P_18 , 1U ) ; if ( ssIsSampleHit ( S , 1 , 0 ) ) { if ( ssIsMajorTimeStep ( S
) ) { _rtDW -> erjsjr2qzo = ( _rtB -> da0dudg0f4 >= _rtB -> ahsodbcljv ) ; }
_rtB -> abvu3xxawz = _rtDW -> erjsjr2qzo ; _rtB -> h4juj30xqw = ! _rtDW ->
erjsjr2qzo ; } if ( ssIsSampleHit ( S , 2 , 0 ) ) { _rtB -> lnqo4llq1n = _rtP
-> P_20 * _rtB -> pvbm0keh00 [ 5 ] ; _rtB -> lr01utbclh = _rtP -> P_21 * _rtB
-> pvbm0keh00 [ 7 ] ; _rtB -> pffpndsfee = _rtP -> P_22 * _rtB -> pvbm0keh00
[ 4 ] ; } ssCallAccelRunBlock ( S , 1 , 56 , SS_CALL_MDL_OUTPUTS ) ; if (
ssIsSampleHit ( S , 1 , 0 ) ) { currentTime = ssGetTaskTime ( S , 1 ) ; if (
ssIsMajorTimeStep ( S ) ) { _rtDW -> dtdkrg2r4l = ( currentTime >= _rtP ->
P_25 ) ; } } UNUSED_PARAMETER ( tid ) ; }
#define MDL_UPDATE
static void mdlUpdate ( SimStruct * S , int_T tid ) { n3qi1whofz * _rtB ;
ew10rzwqr2 * _rtDW ; _rtDW = ( ( ew10rzwqr2 * ) ssGetRootDWork ( S ) ) ; _rtB
= ( ( n3qi1whofz * ) _ssGetBlockIO ( S ) ) ; if ( ssIsSampleHit ( S , 2 , 0 )
) { ssCallAccelRunBlock ( S , 0 , 0 , SS_CALL_MDL_UPDATE ) ; }
UNUSED_PARAMETER ( tid ) ; }
#define MDL_DERIVATIVES
static void mdlDerivatives ( SimStruct * S ) { loikxjbxjg * _rtP ; f1xhd02yjc
* _rtX ; pqmvzr1kvu * _rtXdot ; _rtXdot = ( ( pqmvzr1kvu * ) ssGetdX ( S ) )
; _rtX = ( ( f1xhd02yjc * ) ssGetContStates ( S ) ) ; _rtP = ( ( loikxjbxjg *
) ssGetDefaultParam ( S ) ) ; _rtXdot -> nt5ykhctxg = 0.0 ; _rtXdot ->
nt5ykhctxg += _rtP -> P_23 * _rtX -> nt5ykhctxg ; _rtXdot -> nt5ykhctxg +=
0.0 ; }
#define MDL_ZERO_CROSSINGS
static void mdlZeroCrossings ( SimStruct * S ) { n3qi1whofz * _rtB ;
loikxjbxjg * _rtP ; d15n1ti4kq * _rtZCSV ; _rtZCSV = ( ( d15n1ti4kq * )
ssGetSolverZcSignalVector ( S ) ) ; _rtP = ( ( loikxjbxjg * )
ssGetDefaultParam ( S ) ) ; _rtB = ( ( n3qi1whofz * ) _ssGetBlockIO ( S ) ) ;
_rtZCSV -> gy2fs33ian = _rtB -> i0htfp3fk2 - _rtP -> P_15 ; _rtZCSV ->
nvizxvries = _rtB -> i0htfp3fk2 - _rtP -> P_16 ; _rtZCSV -> dboqxib4va = _rtB
-> da0dudg0f4 - _rtB -> ahsodbcljv ; _rtZCSV -> itos2u5pt2 = ssGetT ( S ) -
_rtP -> P_25 ; } static void mdlInitializeSizes ( SimStruct * S ) {
ssSetChecksumVal ( S , 0 , 2734680498U ) ; ssSetChecksumVal ( S , 1 ,
2999698602U ) ; ssSetChecksumVal ( S , 2 , 1056798251U ) ; ssSetChecksumVal (
S , 3 , 2021679211U ) ; { mxArray * slVerStructMat = NULL ; mxArray *
slStrMat = mxCreateString ( "simulink" ) ; char slVerChar [ 10 ] ; int status
= mexCallMATLAB ( 1 , & slVerStructMat , 1 , & slStrMat , "ver" ) ; if (
status == 0 ) { mxArray * slVerMat = mxGetField ( slVerStructMat , 0 ,
"Version" ) ; if ( slVerMat == NULL ) { status = 1 ; } else { status =
mxGetString ( slVerMat , slVerChar , 10 ) ; } } mxDestroyArray ( slStrMat ) ;
mxDestroyArray ( slVerStructMat ) ; if ( ( status == 1 ) || ( strcmp (
slVerChar , "8.3" ) != 0 ) ) { return ; } } ssSetOptions ( S ,
SS_OPTION_EXCEPTION_FREE_CODE ) ; if ( ssGetSizeofDWork ( S ) != sizeof (
ew10rzwqr2 ) ) { ssSetErrorStatus ( S ,
"Unexpected error: Internal DWork sizes do "
"not match for accelerator mex file." ) ; } if ( ssGetSizeofGlobalBlockIO ( S
) != sizeof ( n3qi1whofz ) ) { ssSetErrorStatus ( S ,
"Unexpected error: Internal BlockIO sizes do "
"not match for accelerator mex file." ) ; } { int ssSizeofParams ;
ssGetSizeofParams ( S , & ssSizeofParams ) ; if ( ssSizeofParams != sizeof (
loikxjbxjg ) ) { static char msg [ 256 ] ; sprintf ( msg ,
"Unexpected error: Internal Parameters sizes do "
"not match for accelerator mex file." ) ; } } _ssSetDefaultParam ( S , (
real_T * ) & o2iu0a2jke ) ; rt_InitInfAndNaN ( sizeof ( real_T ) ) ; } static
void mdlInitializeSampleTimes ( SimStruct * S ) { } static void mdlTerminate
( SimStruct * S ) { }
#include "simulink.c"
