@REM This bat file has been generated by the IAR Embeddded Workbench
@REM C-SPY interactive debugger,as an aid to preparing a command
@REM line for running the cspybat command line utility with the
@REM appropriate settings.
@REM
@REM After making some adjustments to this file, you can launch cspybat
@REM by typing the name of this file followed by the name of the debug
@REM file (usually an ubrof file). Note that this file is generated
@REM every time a new debug session is initialized, so you may want to
@REM move or rename the file before making changes.
@REM
@REM Note: some command line arguments cannot be properly generated
@REM by this process. Specifically, the plugin which is responsible
@REM for the Terminal I/O window (and other C runtime functionality)
@REM comes in a special version for cspybat, and the name of that
@REM plugin dll is not known when generating this file. It resides in
@REM the $TOOLKIT_DIR$\bin folder and is usually called XXXbat.dll or
@REM XXXlibsupportbat.dll, where XXX is the name of the corresponding
@REM tool chain. Replace the '<libsupport_plugin>' parameter
@REM below with the appropriate file name. Other plugins loaded by
@REM C-SPY are usually not needed by, or will not work in, cspybat
@REM but they are listed at the end of this file for reference.


"D:\Program Files\IAR\Embedded Workbench 4.0 Evaluation\common\bin\cspybat" "D:\Program Files\IAR\Embedded Workbench 4.0 Evaluation\ARM\bin\armproc.dll" "D:\Program Files\IAR\Embedded Workbench 4.0 Evaluation\ARM\bin\armsim.dll"  %1 --plugin "D:\Program Files\IAR\Embedded Workbench 4.0 Evaluation\ARM\bin\<libsupport_plugin>" --backend -B "--endian" "little" "--cpu" "ARM926EJ-S" "--fpu" "VFP9-S" "--proc_driver" "sim" 


@REM Loaded plugins:
@REM    armlibsupport.dll
