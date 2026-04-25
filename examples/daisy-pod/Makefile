# Project Name
TARGET = granular-recipes

USE_DAISYSP_LGPL = 1

# Sources
CPP_SOURCES = \
	main.cpp \
	hardware.cpp \
	../../src/engine.cpp \
	../../src/granular_processor.cpp \
	../../src/grain_pool.cpp \
	../../src/window_lut.cpp \
	../../src/circular_buffer_stereo.cpp \
	../../src/fourPole.cpp \
	../../src/recipes/lush.cpp \
	../../src/recipes/sprinkle.cpp \
	../../src/recipes/cloud.cpp \
	../../src/recipes/stutter.cpp \

# Library Locations
LIBDAISY_DIR = libs/libDaisy/
DAISYSP_DIR = libs/DaisySP/

C_INCLUDES += -I../../include

# Core location, and generic Makefile.
SYSTEM_FILES_DIR = $(LIBDAISY_DIR)/core
include $(SYSTEM_FILES_DIR)/Makefile
