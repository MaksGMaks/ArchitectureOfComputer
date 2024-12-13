.code
        lw      r1      idn1
        lw      r2      idn2 
        lw      r3      idn3
        cmpe    r1      r2      r4
        cmpe    r1      r3      r5
        bez     r5      bezJM
        inc     r6
        inc     r6
bezJM:  bnz     r4      bnezJM
        dec     r6
        dec     r6
bnezJM: jma     r3      r1      jmaJM
        inc     r6
jmaJM:  jmb     r3      r1      jmbJM
        inc     r6
jmbJM:  jmae    r1      r1      jmaeJM
        dec     r6
jmaeJM: jmbe    r1      r3      jmbeJM
        inc     r7
jmbeJM: jmp     end
        dec     r7
end:    swp     r7      r1
        halt

.data
idn1:   10
idn2:   10
idn3:   11
