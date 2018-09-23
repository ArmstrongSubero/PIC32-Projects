#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/18_USB_Host.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/18_USB_Host.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=-mafrlcsj
else
COMPARISON_BUILD=
endif

ifdef SUB_IMAGE_ADDRESS

else
SUB_IMAGE_ADDRESS_COMMAND=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=Main.c usb_config.c usb_host_msd_scsi.c usb_host_msd.c usb_host.c FSIO.c PIC32MX270_USB.c usb_event_handler.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/Main.o ${OBJECTDIR}/usb_config.o ${OBJECTDIR}/usb_host_msd_scsi.o ${OBJECTDIR}/usb_host_msd.o ${OBJECTDIR}/usb_host.o ${OBJECTDIR}/FSIO.o ${OBJECTDIR}/PIC32MX270_USB.o ${OBJECTDIR}/usb_event_handler.o
POSSIBLE_DEPFILES=${OBJECTDIR}/Main.o.d ${OBJECTDIR}/usb_config.o.d ${OBJECTDIR}/usb_host_msd_scsi.o.d ${OBJECTDIR}/usb_host_msd.o.d ${OBJECTDIR}/usb_host.o.d ${OBJECTDIR}/FSIO.o.d ${OBJECTDIR}/PIC32MX270_USB.o.d ${OBJECTDIR}/usb_event_handler.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/Main.o ${OBJECTDIR}/usb_config.o ${OBJECTDIR}/usb_host_msd_scsi.o ${OBJECTDIR}/usb_host_msd.o ${OBJECTDIR}/usb_host.o ${OBJECTDIR}/FSIO.o ${OBJECTDIR}/PIC32MX270_USB.o ${OBJECTDIR}/usb_event_handler.o

# Source Files
SOURCEFILES=Main.c usb_config.c usb_host_msd_scsi.c usb_host_msd.c usb_host.c FSIO.c PIC32MX270_USB.c usb_event_handler.c


CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/18_USB_Host.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=32MX270F256D
MP_LINKER_FILE_OPTION=
# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assembleWithPreprocess
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/Main.o: Main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Main.o.d 
	@${RM} ${OBJECTDIR}/Main.o 
	@${FIXDEPS} "${OBJECTDIR}/Main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -MMD -MF "${OBJECTDIR}/Main.o.d" -o ${OBJECTDIR}/Main.o Main.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/usb_config.o: usb_config.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/usb_config.o.d 
	@${RM} ${OBJECTDIR}/usb_config.o 
	@${FIXDEPS} "${OBJECTDIR}/usb_config.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -MMD -MF "${OBJECTDIR}/usb_config.o.d" -o ${OBJECTDIR}/usb_config.o usb_config.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/usb_host_msd_scsi.o: usb_host_msd_scsi.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/usb_host_msd_scsi.o.d 
	@${RM} ${OBJECTDIR}/usb_host_msd_scsi.o 
	@${FIXDEPS} "${OBJECTDIR}/usb_host_msd_scsi.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -MMD -MF "${OBJECTDIR}/usb_host_msd_scsi.o.d" -o ${OBJECTDIR}/usb_host_msd_scsi.o usb_host_msd_scsi.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/usb_host_msd.o: usb_host_msd.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/usb_host_msd.o.d 
	@${RM} ${OBJECTDIR}/usb_host_msd.o 
	@${FIXDEPS} "${OBJECTDIR}/usb_host_msd.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -MMD -MF "${OBJECTDIR}/usb_host_msd.o.d" -o ${OBJECTDIR}/usb_host_msd.o usb_host_msd.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/usb_host.o: usb_host.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/usb_host.o.d 
	@${RM} ${OBJECTDIR}/usb_host.o 
	@${FIXDEPS} "${OBJECTDIR}/usb_host.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -MMD -MF "${OBJECTDIR}/usb_host.o.d" -o ${OBJECTDIR}/usb_host.o usb_host.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/FSIO.o: FSIO.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/FSIO.o.d 
	@${RM} ${OBJECTDIR}/FSIO.o 
	@${FIXDEPS} "${OBJECTDIR}/FSIO.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -MMD -MF "${OBJECTDIR}/FSIO.o.d" -o ${OBJECTDIR}/FSIO.o FSIO.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/PIC32MX270_USB.o: PIC32MX270_USB.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/PIC32MX270_USB.o.d 
	@${RM} ${OBJECTDIR}/PIC32MX270_USB.o 
	@${FIXDEPS} "${OBJECTDIR}/PIC32MX270_USB.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -MMD -MF "${OBJECTDIR}/PIC32MX270_USB.o.d" -o ${OBJECTDIR}/PIC32MX270_USB.o PIC32MX270_USB.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/usb_event_handler.o: usb_event_handler.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/usb_event_handler.o.d 
	@${RM} ${OBJECTDIR}/usb_event_handler.o 
	@${FIXDEPS} "${OBJECTDIR}/usb_event_handler.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -MMD -MF "${OBJECTDIR}/usb_event_handler.o.d" -o ${OBJECTDIR}/usb_event_handler.o usb_event_handler.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
else
${OBJECTDIR}/Main.o: Main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Main.o.d 
	@${RM} ${OBJECTDIR}/Main.o 
	@${FIXDEPS} "${OBJECTDIR}/Main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -MMD -MF "${OBJECTDIR}/Main.o.d" -o ${OBJECTDIR}/Main.o Main.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/usb_config.o: usb_config.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/usb_config.o.d 
	@${RM} ${OBJECTDIR}/usb_config.o 
	@${FIXDEPS} "${OBJECTDIR}/usb_config.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -MMD -MF "${OBJECTDIR}/usb_config.o.d" -o ${OBJECTDIR}/usb_config.o usb_config.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/usb_host_msd_scsi.o: usb_host_msd_scsi.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/usb_host_msd_scsi.o.d 
	@${RM} ${OBJECTDIR}/usb_host_msd_scsi.o 
	@${FIXDEPS} "${OBJECTDIR}/usb_host_msd_scsi.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -MMD -MF "${OBJECTDIR}/usb_host_msd_scsi.o.d" -o ${OBJECTDIR}/usb_host_msd_scsi.o usb_host_msd_scsi.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/usb_host_msd.o: usb_host_msd.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/usb_host_msd.o.d 
	@${RM} ${OBJECTDIR}/usb_host_msd.o 
	@${FIXDEPS} "${OBJECTDIR}/usb_host_msd.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -MMD -MF "${OBJECTDIR}/usb_host_msd.o.d" -o ${OBJECTDIR}/usb_host_msd.o usb_host_msd.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/usb_host.o: usb_host.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/usb_host.o.d 
	@${RM} ${OBJECTDIR}/usb_host.o 
	@${FIXDEPS} "${OBJECTDIR}/usb_host.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -MMD -MF "${OBJECTDIR}/usb_host.o.d" -o ${OBJECTDIR}/usb_host.o usb_host.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/FSIO.o: FSIO.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/FSIO.o.d 
	@${RM} ${OBJECTDIR}/FSIO.o 
	@${FIXDEPS} "${OBJECTDIR}/FSIO.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -MMD -MF "${OBJECTDIR}/FSIO.o.d" -o ${OBJECTDIR}/FSIO.o FSIO.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/PIC32MX270_USB.o: PIC32MX270_USB.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/PIC32MX270_USB.o.d 
	@${RM} ${OBJECTDIR}/PIC32MX270_USB.o 
	@${FIXDEPS} "${OBJECTDIR}/PIC32MX270_USB.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -MMD -MF "${OBJECTDIR}/PIC32MX270_USB.o.d" -o ${OBJECTDIR}/PIC32MX270_USB.o PIC32MX270_USB.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/usb_event_handler.o: usb_event_handler.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/usb_event_handler.o.d 
	@${RM} ${OBJECTDIR}/usb_event_handler.o 
	@${FIXDEPS} "${OBJECTDIR}/usb_event_handler.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -MMD -MF "${OBJECTDIR}/usb_event_handler.o.d" -o ${OBJECTDIR}/usb_event_handler.o usb_event_handler.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/18_USB_Host.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -g -mdebugger -D__MPLAB_DEBUGGER_ICD3=1 -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/18_USB_Host.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)   -mreserve=data@0x0:0x1FC -mreserve=boot@0x1FC00490:0x1FC00BEF  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-D=__DEBUG_D,--defsym=__MPLAB_DEBUGGER_ICD3=1,--defsym=_min_heap_size=8192,--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/18_USB_Host.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/18_USB_Host.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=_min_heap_size=8192,--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml
	${MP_CC_DIR}\\xc32-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/18_USB_Host.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} 
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/default
	${RM} -r dist/default

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
