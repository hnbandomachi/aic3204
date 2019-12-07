################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../aic3204_loop_stereo_in1.c \
../aic3204_test.c \
../aic3204_tone_headphone.c \
../main.c 

CMD_SRCS += \
../lnkx.cmd 

OBJS += \
./aic3204_loop_stereo_in1.obj \
./aic3204_test.obj \
./aic3204_tone_headphone.obj \
./main.obj 

C_DEPS += \
./aic3204_loop_stereo_in1.pp \
./aic3204_test.pp \
./aic3204_tone_headphone.pp \
./main.pp 

OBJS__QTD += \
".\aic3204_loop_stereo_in1.obj" \
".\aic3204_test.obj" \
".\aic3204_tone_headphone.obj" \
".\main.obj" 

C_DEPS__QTD += \
".\aic3204_loop_stereo_in1.pp" \
".\aic3204_test.pp" \
".\aic3204_tone_headphone.pp" \
".\main.pp" 

C_SRCS_QUOTED += \
"../aic3204_loop_stereo_in1.c" \
"../aic3204_test.c" \
"../aic3204_tone_headphone.c" \
"../main.c" 


# Each subdirectory must supply rules for building sources it contributes
aic3204_loop_stereo_in1.obj: ../aic3204_loop_stereo_in1.c $(GEN_OPTS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"D:/CCSv4/ccsv4/tools/compiler/c5500/bin/cl55" -vcpu:3.3 -g --include_path="D:/CCSv4/ccsv4/tools/compiler/c5500/include" --include_path="../../../include" --diag_warning=225 --ptrdiff_size=32 --memory_model=large --preproc_with_compile --preproc_dependency="aic3204_loop_stereo_in1.pp" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

aic3204_test.obj: ../aic3204_test.c $(GEN_OPTS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"D:/CCSv4/ccsv4/tools/compiler/c5500/bin/cl55" -vcpu:3.3 -g --include_path="D:/CCSv4/ccsv4/tools/compiler/c5500/include" --include_path="../../../include" --diag_warning=225 --ptrdiff_size=32 --memory_model=large --preproc_with_compile --preproc_dependency="aic3204_test.pp" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

aic3204_tone_headphone.obj: ../aic3204_tone_headphone.c $(GEN_OPTS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"D:/CCSv4/ccsv4/tools/compiler/c5500/bin/cl55" -vcpu:3.3 -g --include_path="D:/CCSv4/ccsv4/tools/compiler/c5500/include" --include_path="../../../include" --diag_warning=225 --ptrdiff_size=32 --memory_model=large --preproc_with_compile --preproc_dependency="aic3204_tone_headphone.pp" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

main.obj: ../main.c $(GEN_OPTS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"D:/CCSv4/ccsv4/tools/compiler/c5500/bin/cl55" -vcpu:3.3 -g --include_path="D:/CCSv4/ccsv4/tools/compiler/c5500/include" --include_path="../../../include" --diag_warning=225 --ptrdiff_size=32 --memory_model=large --preproc_with_compile --preproc_dependency="main.pp" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '


