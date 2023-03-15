################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
modules/ringtones_manager/%.obj: ../modules/ringtones_manager/%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"C:/ti/ccs1220/ccs/tools/compiler/ti-cgt-arm_20.2.7.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="C:/ti/ccs1220/ccs/ccs_base/arm/include" --include_path="C:/Users/Filippo Castellan/Desktop/SmartAlarm/driverlib/source/ti/grlib/" --include_path="C:/ti/ccs1220/ccs/ccs_base/arm/include/CMSIS" --include_path="C:/Users/Filippo Castellan/Desktop/SmartAlarm/driverlib/source" --include_path="C:/Users/Filippo Castellan/Desktop/SmartAlarm" --include_path="C:/ti/ccs1220/ccs/tools/compiler/ti-cgt-arm_20.2.7.LTS/include" --advice:power="all" --define=__MSP432P401R__ --define=ccs -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="modules/ringtones_manager/$(basename $(<F)).d_raw" --include_path="C:/Users/Filippo Castellan/Desktop/SmartAlarm/Debug/syscfg" --obj_directory="modules/ringtones_manager" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


