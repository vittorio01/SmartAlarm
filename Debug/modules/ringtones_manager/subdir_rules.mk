################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
modules/ringtones_manager/%.obj: ../modules/ringtones_manager/%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"/home/vittorio/ti/ccs1210/ccs/tools/compiler/ti-cgt-arm_20.2.7.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="/home/vittorio/ti/ccs1210/ccs/ccs_base/arm/include" --include_path="/home/vittorio/workspace_v12/driverlib/source" --include_path="/home/vittorio/ti/ccs1210/ccs/ccs_base/arm/include/CMSIS" --include_path="/home/vittorio/github/SmartAlarm" --include_path="/home/vittorio/ti/ccs1210/ccs/tools/compiler/ti-cgt-arm_20.2.7.LTS/include" --advice:power=all --define=__MSP432P401R__ --define=ccs -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="modules/ringtones_manager/$(basename $(<F)).d_raw" --obj_directory="modules/ringtones_manager" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: "$<"'
	@echo ' '


