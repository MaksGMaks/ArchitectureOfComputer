.code
        lw      r1      idn1
        lw      r2      iDn2 
        lw      r3      idn3
        lw      r4      idn4
        bt      r3      r4
        sal     r1      r4      r5
        sar     r2      r4      r6
        rcl     r1      r4      r7
        rcr     r1      r4      r8
        sw      r5      salRes
        sw      r6      sarRes
        sw      r7      rclRes
        sw      r8      rcrRes
        halt

.data
idn1:   15
iDn2:   -10
idn3:   5
idn4:   2
salRes: 0
sarRes: 0
rclRes: 0
rcrRes: 0
