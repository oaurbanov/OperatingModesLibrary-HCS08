################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/MCUinit.c" \
"../Sources/main.c" \
"../Sources/operating_modes.c" \

C_SRCS += \
../Sources/MCUinit.c \
../Sources/main.c \
../Sources/operating_modes.c \

OBJS += \
./Sources/MCUinit_c.obj \
./Sources/main_c.obj \
./Sources/operating_modes_c.obj \

OBJS_QUOTED += \
"./Sources/MCUinit_c.obj" \
"./Sources/main_c.obj" \
"./Sources/operating_modes_c.obj" \

C_DEPS += \
./Sources/MCUinit_c.d \
./Sources/main_c.d \
./Sources/operating_modes_c.d \

C_DEPS_QUOTED += \
"./Sources/MCUinit_c.d" \
"./Sources/main_c.d" \
"./Sources/operating_modes_c.d" \

OBJS_OS_FORMAT += \
./Sources/MCUinit_c.obj \
./Sources/main_c.obj \
./Sources/operating_modes_c.obj \


# Each subdirectory must supply rules for building sources it contributes
Sources/MCUinit_c.obj: ../Sources/MCUinit.c
	@echo 'Building file: $<'
	@echo 'Executing target #1 $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Sources/MCUinit.args" -ObjN="Sources/MCUinit_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '

Sources/%.d: ../Sources/%.c
	@echo 'Regenerating dependency file: $@'
	
	@echo ' '

Sources/main_c.obj: ../Sources/main.c
	@echo 'Building file: $<'
	@echo 'Executing target #2 $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Sources/main.args" -ObjN="Sources/main_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '

Sources/operating_modes_c.obj: ../Sources/operating_modes.c
	@echo 'Building file: $<'
	@echo 'Executing target #3 $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Sources/operating_modes.args" -ObjN="Sources/operating_modes_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '


