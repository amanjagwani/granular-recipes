# Usage with Vitis IDE:
# In Vitis IDE create a Single Application Debug launch configuration,
# change the debug type to 'Attach to running target' and provide this 
# tcl script in 'Execute Script' option.
# Path of this script: /home/aman/granular-recipes/examples/zynq-spectral/spectral_granular_vitis_app_system/_ide/scripts/systemdebugger_spectral_granular_vitis_app_system_standalone.tcl
# 
# 
# Usage with xsct:
# To debug using xsct, launch xsct and run below command
# source /home/aman/granular-recipes/examples/zynq-spectral/spectral_granular_vitis_app_system/_ide/scripts/systemdebugger_spectral_granular_vitis_app_system_standalone.tcl
# 
connect -url tcp:127.0.0.1:3121
targets -set -nocase -filter {name =~"APU*"}
rst -system
after 3000
targets -set -filter {jtag_cable_name =~ "Digilent Zybo Z7 210351B402AFA" && level==0 && jtag_device_ctx=="jsn-Zybo Z7-210351B402AFA-23727093-0"}
fpga -file /home/aman/granular-recipes/examples/zynq-spectral/spectral_granular_vitis_app/_ide/bitstream/v7_spectral_granular_pvsblur.bit
targets -set -nocase -filter {name =~"APU*"}
loadhw -hw /home/aman/granular-recipes/examples/zynq-spectral/v7_spectral_granular_pvsblur/export/v7_spectral_granular_pvsblur/hw/v7_spectral_granular_pvsblur.xsa -mem-ranges [list {0x40000000 0xbfffffff}] -regs
configparams force-mem-access 1
targets -set -nocase -filter {name =~"APU*"}
source /home/aman/granular-recipes/examples/zynq-spectral/spectral_granular_vitis_app/_ide/psinit/ps7_init.tcl
ps7_init
ps7_post_config
targets -set -nocase -filter {name =~ "*A9*#0"}
dow /home/aman/granular-recipes/examples/zynq-spectral/spectral_granular_vitis_app/Debug/spectral_granular_vitis_app.elf
configparams force-mem-access 0
targets -set -nocase -filter {name =~ "*A9*#0"}
con
