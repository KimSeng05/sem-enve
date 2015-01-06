;==============================================================================
;                Electronic Speed Controller Using PIC10F206
;==============================================================================
;                 Bruce Abbott (bhabbott@paradise.net.nz)
;
;---------------------------------------------------------------------------
;                            Specifications
;
;   - 76 stick positions controlling 38 power levels.
;
;   - Throttle range is 1.2mS to 1.8mS
;
;   - Accepts servo pulse widths as low as 0.9mS, and as high as 2.2mS
;
;   - Reverse Exponential function for smooth power control.
;
;   - 2.7KHz PWM switching frequency.
;
;
;-----------------------------------------------------------------------------
;
; changes:
;
; V1.0   Created from Speed508.asm
;

                PROCESSOR PIC10F206
                INCLUDE   <P10F206.inc>

	__CONFIG  _MCLRE_OFF&_CP_OFF&_WDT_ON

        radix     dec

        errorlevel 0,-305,-302


version  = 1
revision = 0


;DEFINE NO_OSCCAL         0               ; enable if osccal has been erased!

; Bit definitions for the GPIO register and the TRIS register

RunBit		EQU       2               ; Turns on motor
ServoBit	EQU       3               ; servo pulse input
BattSenseBit	EQU       0               ; + input to comparator
GreenLedBit	EQU       1               ; Status LED

TrisBits	EQU       ((1<<BattSenseBit)|(1<<ServoBit))


; Bits to be set with the OPTION instruction
;   No wake up
;   No weak pullups
;   Timer 0 source internal
;   Which edge is don't care
;   Prescaler to watchdog, set to give 16*17 ms timeout

OptionBits      EQU       B'11011100'

; ==========================================================================
; Algorithm constants

PWM_Period      EQU       47              ; Number of 8-instr code cycles
PWM_Start       EQU       4               ; Lowest cycle count
ArmPulsesReqd   EQU       13              ; consecutive in-range servo pulses
BrakeDelay      EQU       50              ; delay before braking on low throttle
LoBattDelay     EQU       45              ; delay before braking on low battery
MaxBadPulses    EQU       25	          ; delay before stopping due to noise


;===========================================================================
; Macro to create offsets for general purpose registers in RAM
;
ByteAddress     SET 8     ; general purpose registers start here

BYTE            MACRO     ByteName
ByteName        EQU       ByteAddress
ByteAddress     SET       ByteAddress+1
                ENDM

; ==========================================================================
; General Purpose Register Definitions.
;

	BYTE       Flags           ; Various boolean flags
	BYTE       PwmCount        ; Counts down to zero during PWM output
	BYTE       PwmWidth        ; PWM loop counter
	BYTE       ServoCount      ; servo pulse count 0-255 * 8uS
	BYTE       HiCycles        ; count PWM cycles while servo pulse is hi
	BYTE	   LoCycles	   ;                  ''                   lo
	BYTE       PrevCount       ; Previous servo pulse width (averaged)
	BYTE       Index           ; Indexes into table of PWM widths (0-75)
	BYTE       ArmPulseCount   ; Arming pulses required (counts down)
	BYTE       BrakeDelayCount ; Number of servo pulses until brake engages
	BYTE       PwmPeriod       ; Number of 8uS loops in one PWM cycle
	BYTE	   BadPulseCount   ; number of bad servo pulses detected

; Bits in Flags

BattLow         EQU       0	   ; Low Battery Voltage Detected
PriorServoBit   EQU       1	   ; previous state of servo pulse (hi/lo)
BadPulseBit     EQU       2        ; bad servo pulse detected
PlayTune	EQU	  4        ; initial arming sequence

; =========================================================================
; Helper for making strings of no-op instructions
;
NO_OP           MACRO     count
NO_OP_COUNT     SET       count
                WHILE     NO_OP_COUNT
                nop
NO_OP_COUNT     SET       NO_OP_COUNT - 1
                ENDW
                ENDM

; =========================================================================
; Macro to set the initial state of the motor fet.  W contains the count
; on exit. The code in this Macro uses 5 clocks.
;
DoRunBit        MACRO
                movf      PwmWidth, W
                skpz
                bsf       GPIO, RunBit
                skpnz
                bcf       GPIO, RunBit
                ENDM

; =========================================================================
; Macro to keep up with the servo pulse duration
; The code in this Macro uses 2 clocks.
;
DoServoCount    MACRO
                btfsc     GPIO, ServoBit
                incf      ServoCount, F
                ENDM

; =========================================================================
; =========================================================================
; =========================================================================
;
; Now for some code
;
; Critical instruction timings are shown in brackets
; eg. ;(2) = 2 microseconds (with 4Mhz oscillator).
;
Coldstart:      ORG       0
		goto	  Start

		org	  8
		dt	  "========"
                dt        "Speed206"
                dt        "--V"
                dw        version+48
                dt        "."
                dw        revision+48
                dt        "--"
                dt        "bhabbott@paradise.net.nz"
		dt	  "========"

Start:
	movwf	OSCCAL			; set oscillator calibration

; Move prescaler from tmr0 to the watchdog, without causing accidental reset!

        clrwdt
        clrf	TMR0
        movlw	OptionBits | 7
        OPTION
        clrwdt
        movlw	OptionBits
        OPTION
        clrwdt

; initialise I/O registers

        clrf	GPIO			; all outputs low
        movlw	TrisBits
        TRIS    GPIO			; set I/O pin directions

	movlw	b'01111011'
        movwf	CMCON0			; Comparator + = pin 1, - = 0.6V

; CPU specific stuff done, now we can start the main program!

	bsf	Flags,PlayTune		; play tune after 1st arming

        goto	Rearm

; ==========================================================================
; Servo pulse to PWM width table read.  Returns with width in W.
; This routine takes 5 clocks to execute (including call and retlw).
;
ServoLookup:
        addwf   PCL    ;   (1) goto W
	retlw	0      ; 0 (2) Motor stopped at 1.2mS
	retlw   5      ; 1
	retlw   7      ; 2
        retlw   8      ; 3
        retlw   10     ; 4
        retlw   11     ; 5
        retlw   12     ; 6
        retlw   13     ; 7
        retlw   14     ; 8
        retlw   15     ; 9
        retlw   16     ;10
        retlw   16     ;11
        retlw   17     ;12
        retlw   18     ;13
        retlw   19     ;14
        retlw   19     ;15
        retlw   20     ;16
        retlw   20     ;17
        retlw   21     ;18
        retlw   22     ;19
        retlw   22     ;20
        retlw   23     ;21
        retlw   23     ;22
        retlw   24     ;23
        retlw   24     ;24
        retlw   25     ;25
        retlw   25     ;26
        retlw   26     ;27
        retlw   26     ;28
        retlw   27     ;29
        retlw   27     ;30
        retlw   28     ;31
        retlw   28     ;32
        retlw   29     ;33
        retlw   29     ;34
        retlw   30     ;35
        retlw   30     ;36
        retlw   30     ;37
        retlw   31     ;38
        retlw   31     ;39
        retlw   32     ;40
        retlw   32     ;41
        retlw   32     ;42
        retlw   33     ;43
        retlw   33     ;44
        retlw   34     ;45
        retlw   34     ;46
        retlw   34     ;47
        retlw   35     ;48
        retlw   35     ;49
        retlw   35     ;50
        retlw   36     ;51
        retlw   36     ;52
        retlw   36     ;53
        retlw   37     ;54
        retlw   37     ;55
        retlw   38     ;56
        retlw   38     ;57
        retlw   38     ;58
        retlw   39     ;59
        retlw   39     ;60
        retlw   39     ;61
        retlw   40     ;62
        retlw   40     ;63
        retlw   40     ;64
        retlw   40     ;65
        retlw   41     ;66
        retlw   41     ;67
        retlw   41     ;68
        retlw   42     ;69
        retlw   42     ;70
        retlw   42     ;72
        retlw   43     ;72
        retlw   43     ;73
        retlw   43     ;74
	retlw   44     ;75  full throttle at 1.8mS


; ==========================================================================
; PWM pulse subroutine.  On entry, the motor may be on or off. If the motor
; is off, it will never be turned on.  However, it will be turned OFF when
; (if) the PWM_Count register reaches zero.
;
; takes 350 clocks to execute
;
DoPwmPulse:     movlw     PWM_Period-PWM_Start  ;(1)
                movwf     PwmPeriod             ;(1) set PWM period count
pwmloop:        decf      PwmCount,F            ;(1)
                skpnz                           ;(1) end of PWM hi pulse?
                bcf       GPIO, RunBit          ;(1) yes, then turn off motor
		btfss     CMCON0,CMPOUT         ;(2) Battery low ?
                goto	  BattLoShutdown	;
                decfsz    PwmPeriod,F           ;(2)
                goto      pwmloop               ;(+1)
                retlw     0                     ;(2)


;===========================================================================
;                     Make the motor 'Beep'
;
; input: W = period
;
Beep:		movwf	  PwmWidth
                clrf      PwmCount
		NO_OP	  4
beep1:          bsf       GPIO,RunBit          ; motor on
                movlw     8
                movwf     PwmPeriod
beep2:          clrwdt                         ; for 32uS
                decfsz    PwmPeriod,F
                goto      beep2
                bcf       GPIO,RunBit          ; motor off
                movf	  PwmWidth,w
                movwf     PwmPeriod
beep3:          clrwdt
                decfsz    PwmPeriod,F
                goto      beep3                ; for period*4uS
                decfsz    PwmCount,F
                goto      beep1                ; 256 cycles
		retlw	  0

;============================================================================
;             Wait for Valid (low throttle) Servo Signal
;
Rearm:		bcf	  GPIO, RunBit   ; stop the motor
;
; Hunt for a whole servo pulse before looking for arm pulses
;
RaLoop1:	clrwdt
	        btfss     CMCON0,CMPOUT
                goto      Rearm
                btfss     GPIO, ServoBit
                goto      RaLoop1
RaLoop2:        clrwdt
		btfss     CMCON0,CMPOUT
                goto      Rearm
                btfsc     GPIO, ServoBit
                goto      RaLoop2

RaStartCount:   movlw     ArmPulsesReqd
                movwf     ArmPulseCount

RaNextPulse:    clrf      ServoCount
                bcf       Flags,BadPulseBit
;
; Measure length of next servo pulse.
;
RaLoop3:	clrwdt
	        btfss     CMCON0,CMPOUT
                goto      Rearm
                btfss     GPIO, ServoBit       ; wait for start of pulse
                goto      RaLoop3
RaLoop4:	NO_OP	  1		       ;(1)
		clrwdt			       ;(1)
	        incf      ServoCount, F        ;(1) NOTE: loop must be 8uS
                skpnz                          ;(2)
                goto      Rearm                ;    bad if pulse width > 2mS
                btfsc     GPIO, ServoBit       ;(1) wait for end of pulse
                goto      RaLoop4              ;(2)

;
;   0-112  = bad
;  113-150 = brake
;  151-236 = PWM
;  237-255 = Full On
;  256+    = bad
;
                movlw     113
                subwf     ServoCount,F
                skpc
                bsf       Flags,BadPulseBit
                movlw     38
                subwf     ServoCount,F         ; pulse in arming range?
                skpnc
                bsf       Flags,BadPulseBit
                btfsc     Flags,BadPulseBit
                goto      RaStartCount

                decfsz    ArmPulseCount,F      ; Do we have enough arm pulses?
                goto      RaNextPulse          ; Not yet.

		btfss	  Flags, PlayTune
		goto	  Rearm_Beep	       ; short beep if re-arming
;
; Play a tune to indicate successful arming (uses the motor as a speaker!)
;
		movlw	  200
		call	  Beep
		movlw	  150
		call	  Beep
Rearm_Beep:
		movlw	  125
		call	  Beep
;
; wait for end of next servo pulse
;
servo_hi:       btfss     GPIO, ServoBit
                goto      servo_hi
servo_lo:       btfsc     GPIO, ServoBit
                goto      servo_lo

; ready to go! Initialise all variables.

Armed:          clrf      PwmWidth
                clrf      Flags
		clrf	  LoCycles
		clrf	  HiCycles
                movlw     BrakeDelay
                movwf     BrakeDelayCount
                movlw     -113
                movwf     ServoCount
                clrf      PrevCount
		clrf	  BadPulseCount

;
; Fall into the main PWM loop.  The motor is off and will stay
; off until the next servo pulse.

; ===========================================================
; The main PWM loop
;
; Two timing loops have to be simultaneously maintained:-
;
; 1/ Count servo pulse width every 8 clocks. DoServoCount takes 2
;    clocks, thus 6 clocks are available between each instance.
;
; 2/ DoRunBit + 18 clocks + DoPwmPulse + 4 clocks etc. This creates
;    a PWM cycle time of 376 clocks, which corresponds to a frequency
;    of 2.7Khz.
;
MainPwmLoop:    DoServoCount                   ;(2) measure servo pulse width
                clrwdt                         ;(1)
                movlw     PWM_Period-PWM_Start ;(1)  do PWM pulse loop 43 times
                movwf     PwmPeriod            ;(1)
pwmpulseloop:   decf      PwmCount,F           ;(1)  > count down PWM on-time
                skpnz                          ;(1)  > end of PWM pulse?
                bcf       GPIO, RunBit         ;(1)  > yes, then turn off motor
                DoServoCount                   ;(2)  > measure servo pulse
                decfsz    PwmPeriod,F          ;(2)  >
                goto      pwmpulseloop         ;(+1) > 8 clocks in PWM loop
		NO_OP	  2		       ;(2)
                btfss     CMCON0,CMPOUT        ;(2)  Battery low ?
                goto	  BattLoShutdown
                DoServoCount                   ;(2)
MainPwmEntry:   DoRunBit                       ;(5)
                movwf     PwmCount             ;(1)
                DoServoCount                   ;(2) measure servo pulse width
                btfsc     GPIO, ServoBit       ;(2)
                goto      ServoIsHigh          ;(+1) Is servo pulse High ?
                btfsc     Flags, PriorServoBit ;(2)  servo pulse is now Low...
                goto      EndOfPulse           ;(+1) ...but was it High ?
                movlw     -113		       ;(1)
                movwf     ServoCount           ;(1) precharge ServoCount
                NO_OP     1                    ;(1)
                DoServoCount                   ;(2) measure servo pulse width
                clrf      HiCycles             ;(1)
		NO_OP     2		       ;(2)
		incfsz	  LoCycles	       ;(1)
                goto      MainPwmLoop          ;(2)
		goto	  Rearm		       ;    Servo pulse stuck low!

ServoIsHigh:    bsf       Flags, PriorServoBit ;(1) servo pulse is high
                NO_OP     2                    ;(2)
                DoServoCount                   ;(2) measure servo pulse width
                incf      HiCycles,F           ;(1) count PWM cycles
                skpnz                          ;(2)
                goto	  Rearm                ;    Servo pulse stuck high!
                clrf	  LoCycles	       ;(1)
                goto      MainPwmLoop          ;(2)


; ============================================================================
; End of Servo Pulse. We don't have to count servo pulses now, but we still
; have to maintain the PWM loop cycle:-
;
;   DoRunBit + 18 clocks + DoPwmPulse + 4 clocks etc.
;
;
; Starting 8 clocks after DoRunBit

EndOfPulse:     bcf       Flags, PriorServoBit  ;(1) servo pulse finished
                movlw     2                     ;(1)
                subwf     HiCycles,W            ;(1) less than 2 PWM cycles?
                skpc                            ;(1)
                bsf       Flags,BadPulseBit     ;(1)
                movlw     7                     ;(1)
                subwf     HiCycles,W            ;(1) more than 6 PWM cycles?
                skpnc                           ;(1)
                bsf       Flags,BadPulseBit     ;(1)
                nop				;(1)
                call      DoPwmPulse            ;(350)
                movlw     163                   ;(1)
                subwf     ServoCount, W         ;(1) servo pulse out of range?
                skpnc                           ;(1)
                bsf       Flags,BadPulseBit     ;(1)
                DoRunBit                        ;(5)
                movwf     PwmCount              ;(1)
                btfsc     Flags,BadPulseBit     ;(2)  ignore bad pulse!
                goto      BadPulse              ;(+1)
		movf	  ServoCount,w		;(1)
		movwf	  Index			;(1)
                movf      PrevCount,w           ;(1)
                addwf     Index                 ;(1)
                rrf       Index                 ;(1) Index = Average(count+prev)
                movlw     38                    ;(1)
                subwf     Index                 ;(1) index = 0~75 (1.2mS~1.8mS)
                skpc                            ;(1) if minimum throttle
                clrf      Index                 ;(1) then Index = 0
		NO_OP	  6			;(6)
                call      DoPwmPulse            ;(350)
                NO_OP     4                     ;(4)
                DoRunBit                        ;(5)
                movwf     PwmCount              ;(1)
                movlw     75                    ;(1)
                subwf     Index,w               ;(1) Max Index = 75
                skpnc                           ;(1)
                subwf     Index                 ;(1)
                movf      Index,w               ;(1) get index (0-75)
                call      ServoLookup           ;(5) do table lookup
                movwf     PwmWidth              ;(1) set PWM width (0-43)
		NO_OP	  6			;(6)
GoodPulse:      call      DoPwmPulse            ;(350)
                NO_OP     4                     ;(4)
                DoRunBit                        ;(5)
                movwf     PwmCount              ;(1)
                movf      ServoCount,w          ;(1) remember last servo pulse
                movwf     PrevCount             ;(1)
		tstf	  BadPulseCount		;(1)
		skpz				;(1)
		decf	  BadPulseCount		;(1) good pulse 25% weighting
		NO_OP	  6			;(6)
		bsf	  GPIO,GreenLedBit	;(1) show good signal indicator
		goto	  NextPulse		;(2)

BadPulse:	bcf	  GPIO,GreenLedBit	;(1) NOT a good signal!
		movlw	  3  			;(1) 
		addwf	  BadPulseCount		;(1) bad pulse 75% weighting
		movlw	  MaxBadPulses*3	;(1)
		subwf	  BadPulseCount,w	;(1)
		skpnc				;(2) too many bad pulses ?
		goto	  Rearm

NextPulse:      clrwdt				;(1) reset the watchdog timer
		movlw	  (15000/377)-1		;(1)
		movwf	  HiCycles		;(1) PWM only for next 15mS
DelayNext:	clrwdt				;(1)
		NO_OP	  2			;(3)
		call	  DoPwmPulse		;(350)
		NO_OP	  4			;(4)
		DoRunBit			;(5)
		movwf	  PwmCount		;(1)
		NO_OP	  10			;(10)
		decfsz	  HiCycles		;(2)
		goto	  DelayNext		;+1)
		nop				;(1)
		bcf       Flags,BadPulseBit     ;(1)
                movlw     -113                  ;(1)
                movwf     ServoCount            ;(1) precharge ServoCount
                call      DoPwmPulse            ;(350)
                NO_OP     2                     ;(2)
                goto      MainPwmEntry          ;(2) measure next servo pulse
;
; Low battery - shutdown and wait for arming.
;
BattLoShutdown: bcf       GPIO, RunBit          ;(1) Stop the motor
                goto      Rearm


                END

