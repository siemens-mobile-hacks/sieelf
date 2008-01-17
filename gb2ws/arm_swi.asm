
    RSEG    CODE
    PUBLIC  CutWSTRT
    CODE32
CutWSTRT:
    STMFD   SP!, {LR}
    SWI     0x126 //CutWSTR
    LDMFD   SP!, {PC}
    END