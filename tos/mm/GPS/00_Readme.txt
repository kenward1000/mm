GPSmonitor - v1.1 - State Machine

The GPSmonitor is responsible for top level control of the gps subsystem.

Initially this is tightly coupled to the GSD4e chip and reflects its
weirdnesses.


1) Major States

The GPSmonitor has the following major states:

The major mode is determined when the MajorTimer fires.  If we have been
asleep (currently MinorState is MPM), then we will determine the next
MajorState based on current needs.

    (in order of priority)

    IDLE            no major activity selected/in progress.  Choose and
                    start a major cycle.

    CYCLE           take fixes for CYCLE_TIME.  ~30secs which seems to keep
                    MPM happy.

                    After a CYCLE completes, we will put the gps back to sleep
                    ie. MPM.  If MPM fails (mpm_error) then we will try gather
                    more satellite information (MPM_COLLECT).  This might help.

    MPM_COLLECT     Stabilizing MPM.  Collect enough fixes to help MPM
                    stablize.  (~2 mins).

    SATS_STARTUP    after booting, we may or may not have lost everything
                    (Power On Reset, POR).  SATS_STARTUP is used to get
                    the GPS satellite state into a more reasonable state
                    before starting normal operation.

    SATS_COLLECT    collecting almanac/ephemeri so the gps behaves better.
                    during this collection one needs to leave the gps up.
                    we turn off messages we don't want to receive while in
                    this mode to not yank the processor's chain.

                    If we don't have sufficient gps state ie. can't see
                    enough satellites with strong enough signal strength,
                    we sleep in SATS_COLLECT.  We choose a long enough duty
                    cycle to conserve power and wake up once in a while
                    to try again.

                    This is where a decision can be made to give up for a
                    time if sufficient forward progress isn't possible.
                    (looking at satellite Cno signals in the NavTrack
                    message).

    TIME_COLLECT    collecting time fixes, the timing system has a feature
                    (auto-cal), which needs a series of high quality gps
                    time stamps.


2) Minor State machine...

OFF             Boot.booted
                    retry_count = 1
                    -> GMS_BOOTING
                    GPSControl.turnOn

FAIL

BOOTING         GPSControl.gps_booted
                    msg_count   = 0
                    retry_count = 1
                    send(swver)
                    MinorT.startOneShot(SWVER_TO)
                    -> CONFIG

                GPSControl.gps_boot_fail
                    too many tries ... -> FAIL  (retry_count)
                    2nd try:
                        GPSControl.reset
                        GPSControl.turnOn
                    3rd try:
                        GPSControl.powerOff
                        GPSControl.powerOn
                        GPSControl.turnOn

CONFIG          SWVER seen              purpose is to make sure we know the
                                        swver on first boot.

                    major_event(EV_STARTUP)
                        (SATS_STARTUP, MajorTimer)
                    MinorT.startOneShot(GPS_MON_COLLECT_DEADMAN)
                    -> COLLECT

                MinorT.fired
                    retrys++
                    too many trys?:  (retry count)
                        give up?
                        /* not seeing msgs, try one more time */
                        pulse
                        MinorT.startOneShot(SWVER_TO)
                        -> CONFIG
                        return
                    if (!msg_count)     not seeing any messages
                        pulse
                    msg_count = 0
                    send(swver)
                    MinorT.startOneShot(SWVER_TO)
                    -> CONFIG

                any msg
                    msg_count++         count any msgs seen.

                ots_no
                    pulse
                    -> CONFIG

COMM_CHECK      any msg
                    if major_state == IDLE
                        retry_count = 1
                        send(mpm)
                        MinorT.startOneShot(MPM_RSP_TIMEOUT)
                        -> MPM_WAIT
                    else
                        MinorTimer.startOneShot(GPS_MON_COLLECT_DEADMAN)
                        -> COLLECT

                MinorT.fired
                    too many trys? (retry_count)
                        -> FAIL

                    retry_count++
                    pulse
                    MinorT.startOneShot(LONG_COMM_TO)

                ots_no
                    pulse
                    MinorT.startOneShot(SHORT_COMM_TO)
                    -> COMM_CHECK

will want to start a longer timer for proper duty cycle, want to watch
navTrack to see if we have a reasonable chance. The timer needs to be
set up on entry to COLLECT/CYCLE, etc.

got_lock records current_time - cycle_start if cycle_start != 0

COLLECT         MinorT_timeout          (didn't see any messages, oops)
                    pulse
                    MinorT.startOneShot(SHORT_COMM_TO)
                    -> COMM_CHECK

                msg
                    MinorT.startOneShot(COLLECT_MSG_DEADMAN)

                ots_no
                    pulse (to wake up)
                    MinorT.startOneShot(SHORT_COMM_TO)
                    -> COMM_CHECK

                lock_pos
                    lock_seen = TRUE

                lock_time
                    lock_seen = TRUE
                    major_event(lock_time)

                major_changed
                   MinorT.startOneShot(SHORT_COMM_TO)
                   -> COMM_CHECK

MPM_WAIT        mpm_error (not 0010)
                    major_event(mpm_error)
                    MinorT.startOneShot(GPS_MON_MPM_RESTART_WAIT)
                    -> MPM_RESTART

                mpm_good
                    MinorT.stop()
                    -> GMS_MPM

                MinorT.fired
                    if (retry_count > 5)
                        fail
                        major_event(MON_EV_MPM_ERROR)
                        pulse
                        MinorT.startOneStart(SHORT_COMM_TO)
                        -> COMM_CHECK
                    retry_count++
                    send(mpm)
                    MinorT.startOneShot(MPM_RSP_TIMEOUT)
                    -> MPM_WAIT

                ots_no
                    pulse (to wake up)
                    MinorT.startOneShot(SHORT_COMM_TO)
                    -> COMM_CHECK


MPM_RESTART     ots_no
                    pulse (to wake up)
                    MinorT.startOneShot(SHORT_COMM_TO)
                     -> COMM_CHECK

                MinorT.fired
                    pulse (to wake up)
                    MinorT.startOneShot(SHORT_COMM_TO)
                    -> COMM_CHECK

MPM             got_lock                can happen during NavDataCycles(MPM).
                    ignore

                ots_no
                    pulse (to wake up)
                    MinorT.startOneShot(SHORT_COMM_TO)
                    -> COMM_CHECK

                major_changed
                    cycle_start = current_time
                    lock_seen = False
                    pulse (to wake up)
                    MinorT.startOneShot(SHORT_COMM_TO)
                    -> COMM_CHECK


3) Major state transitions

IDLE            Boot.booted
                    major_state -> IDLE

                ev_startup
                    major_state = SATS_STARTUP
                    MajorTimer.startOneShot(SATS_STARTUP_TIME)

                MajorTimer.fired
                    MajorTimer.startOneShot(CYCLE_TIME)
                    major_state = CYCLE
                    minor_event(major_changed)

                mpm_error
                    MajorTimer.startOneShot(MPM_COLLECT_TIME)
                    major_state = MPM_COLLECT

CYCLE           MajorTimer.fired
                    MajorTimer.startOneShot(MON_WAKEUP)
                    major_state = IDLE          go to sleep
                    minor_event(major_changed)

MPM_COLLECT     MajorTimer.fired
                    MajorTimer.startOneShot(MON_WAKEUP)
                    major_state = IDLE          go to sleep
                    minor_event(major_changed)

SATS_STARTUP is used to collect satellite information.  It leaves
the GPS up so it can do this.  SATS_STARTUP terminates when we
see lock_seen (from lock_time, geo).

SATS_STARTUP    MajorTimer.fired
                    too many retrys?  ->  sleep for a while, try again.

                    MajorTimer.startOneShot(SATS_STARTUP_TIME)
                    major_state = SATS_STARTUP
                    minor_event(major_changed)

                 lock_time
                    MajorTimer.startOneShot(CYCLE_TIME)
                    major_state = CYCLE
                    minor_event(major_changed)


4) Startup notes - Inside.  2 story wood building
   office @ 60310 Woodside Loop, Bend OR  ~ 8pm PDT

a) on POR, the GPS loses any almanac information.

b) initial sats it tries are:

---                      0.000000 2018/6/7 1:00 (3) UTC
--- @2144          28  873.913848 224  32  GPS_RAW -- MID:   4     (04) <rx> navTrack   [0]
    NAV_TRACK: week10: 638  tow: 1.03s  chans: 12

     20: az:   0.0  el:  0.0  state: 0x0000  cno/s:   0  0  0  0  0  0  0  0  0  0
     10: az:   0.0  el:  0.0  state: 0x0000  cno/s:   0  0  0  0  0  0  0  0  0  0
     22: az:   0.0  el:  0.0  state: 0x0000  cno/s:   0  0  0  0  0  0  0  0  0  0
     18: az:   0.0  el:  0.0  state: 0x0000  cno/s:   0  0  0  0  0  0  0  0  0  0
     31: az:   0.0  el:  0.0  state: 0x0000  cno/s:   0  0  0  0  0  0  0  0  0  0
     27: az:   0.0  el:  0.0  state: 0x0000  cno/s:   0  0  0  0  0  0  0  0  0  0
      9: az:   0.0  el:  0.0  state: 0x0000  cno/s:   0  0  0  0  0  0  0  0  0  0
      8: az:   0.0  el:  0.0  state: 0x0000  cno/s:   0  0  0  0  0  0  0  0  0  0
     19: az:   0.0  el:  0.0  state: 0x0000  cno/s:   0  0  0  0  0  0  0  0  0  0
     29: az:   0.0  el:  0.0  state: 0x0000  cno/s:   0  0  0  0  0  0  0  0  0  0
      6: az:   0.0  el:  0.0  state: 0x0000  cno/s:   0  0  0  0  0  0  0  0  0  0
     17: az:   0.0  el:  0.0  state: 0x0000  cno/s:   0  0  0  0  0  0  0  0  0  0

c) From POR to Initial Boot (communications established)
--- @960            6  871.679595  40   4  EVENT GPS_TURN_ON 1217 0 0 0
--- @1192          11  873.018035  40   4  EVENT GPS_BOOT_TIME 1217 1370 0 0

                       1.334 secs

Baseline.  First startup after POR boot
---                      0.000000 2018/6/7 1:00 (3) UTC
--- @1544          17  873.889678  40   4  EVENT gps/mon (MAJOR),  <startup>        idle -> sats_startup

d) Time from first POR to various NavTrack sats seen
--- @6172          83  878.917205 224  32  GPS_RAW -- MID:   4     (04) <rx> navTrack   [1]  5
--- @73624        821 1076.118499 224  32  GPS_RAW -- MID:   4     (04) <rx> navTrack   [2]  5, 2
--- @122784      1402 1269.310882 224  32  GPS_RAW -- MID:   4     (04) <rx> navTrack   [3]  5, 2, 29
--- @481056      5598 2604.656829 224  32  GPS_RAW -- MID:   4     (04) <rx> navTrack   [3]  5, 2, 29

    saw 56/5 ee50bpsBcast data just before
--- @486108      5658 2621.686218 224  32  GPS_RAW -- MID:   4     (04) <rx> navTrack   [4]  5, 2, 29, 21
--- @486908      5667 2623.677124 224  32  GPS_RAW -- MID:   4     (04) <rx> navTrack   [5]  5, 2, 29, 21, 2
--- @487876      5678 2626.681365 224  32  GPS_RAW -- MID:   4     (04) <rx> navTrack   [6]  5, 2, 29, 21, 2, 20
--- @490148      5706 2634.688415 224  32  GPS_RAW -- MID:   4     (04) <rx> navTrack   [7]  5, 2, 29, 21, 2, 20, 15
--- @493876      5749 2646.704071 224  32  GPS_RAW -- MID:   4     (04) <rx> navTrack   [6]  5, 25, 29, 21x, 2, 20, 15
--- @494988      5760 2649.708435 224  32  GPS_RAW -- MID:   4     (04) <rx> navTrack   [5]  5, 25, 29, 21x, 2, 20, 15x
--- @495992      5772 2654.712707 224  32  GPS_RAW -- MID:   4     (04) <rx> navTrack   [7]  5, 25, 29, 21, 2, 20, 15x, 26
--- @498812      5803 2665.724395 224  32  GPS_RAW -- MID:   4     (04) <rx> navTrack   [6]  5, 25, 29, 21x, 2, 20, 15x, 26
--- @506912      5901 2699.759826 224  32  GPS_RAW -- MID:   4     (04) <rx> navTrack   [7]  5, 25, 29, 21, 2, 20, 15x, 26, 16x
--- @511000      5950 2710.770568 224  32  GPS_RAW -- MID:   4     (04) <rx> navTrack   [7]  5, 25, 29, 21, 2, 20, 15x, 26, 16x

--- @514348      6000 2722.382476 224  32  GPS_RAW -- MID:   4     (04) <rx> navTrack   [6]  5, 25, 29, 21,  2, 20, 15x, 26x, 16x
--- @521068      6102 2740.402648 224  32  GPS_RAW -- MID:   4     (04) <rx> navTrack   [7]  5, 25, 29, 21,  2, 20, 15x, 26x, 16x, 13
--- @531556      6293 3046.625885 224  32  GPS_RAW -- MID:   4     (04) <rx> navTrack   [4]  5, 29, 20, 21,  25x, 2x
--- @533416      6321 3051.731628 224  32  GPS_RAW -- MID:   4     (04) <rx> navTrack   [3]  5, 29, 20, 21x, 25x, 2x
--- @540120      6423 3072.754943 224  32  GPS_RAW -- MID:   4     (04) <rx> navTrack   [5]  5, 29, 20, 21x, 25,  2x, 16x, 13
--- @551040      6621 3378.629486 224  32  GPS_RAW -- MID:   4     (04) <rx> navTrack   [8]  5, 2x, 13, 25,  29,  16, 21,  20, 26

d) Time from first POR boot to first lock - 1838 secs (30 mins)
--- @511384      5954 2712.362640 127  32  GPS_RAW -- MID:  41     (29) <rx> geoData  L [5]
