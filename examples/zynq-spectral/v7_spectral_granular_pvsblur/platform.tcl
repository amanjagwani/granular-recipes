# 
# Usage: To re-create this platform project launch xsct with below options.
# xsct /home/aman/granular-recipes/examples/zynq-spectral/v7_spectral_granular_pvsblur/platform.tcl
# 
# OR launch xsct and run below command.
# source /home/aman/granular-recipes/examples/zynq-spectral/v7_spectral_granular_pvsblur/platform.tcl
# 
# To create the platform in a different location, modify the -out option of "platform create" command.
# -out option specifies the output directory of the platform project.

platform create -name {v7_spectral_granular_pvsblur}\
-hw {/home/aman/Desktop/FPGA_Work/hls/tv_conv/float_fft/fftIO_spectral_granular_float/v7_spectral_granular_pvsblur.xsa}\
-out {/home/aman/granular-recipes/examples/zynq-spectral}

platform write
domain create -name {standalone_ps7_cortexa9_0} -display-name {standalone_ps7_cortexa9_0} -os {standalone} -proc {ps7_cortexa9_0} -runtime {cpp} -arch {32-bit} -support-app {empty_application}
platform generate -domains 
platform active {v7_spectral_granular_pvsblur}
domain active {zynq_fsbl}
domain active {standalone_ps7_cortexa9_0}
platform generate -quick
platform generate
platform clean
platform generate
