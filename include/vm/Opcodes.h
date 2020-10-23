#ifndef VM_OPCODES_H_
#define VM_OPCODES_H_

#define op_nop				0x00
#define op_aconst_null		0x01
#define op_iconst_m1		0x02
#define op_iconst_0			0x03
#define op_iconst_1			0x04
#define op_iconst_2			0x05
#define op_iconst_3			0x06
#define op_iconst_4			0x07
#define op_iconst_5			0x08
#define op_lconst_0			0x09
#define op_lconst_1			0x0a
#define op_fconst_0			0x0b
#define op_fconst_1			0x0c
#define op_fconst_2			0x0d
#define op_dconst_0			0x0e
#define op_dconst_1			0x0f
#define op_bipush			0x10
#define op_sipush			0x11
#define op_ldc				0x12
#define op_ldc_w			0x13
#define op_ldc2_w			0x14
#define op_iload			0x15
#define op_lload			0x16
#define op_fload			0x17
#define op_dload			0x18
#define op_aload			0x19
#define op_iload_0			0x1a
#define op_iload_1			0x1b
#define op_iload_2			0x1c
#define op_iload_3			0x1d
#define op_lload_0			0x1e
#define op_lload_1			0x1f
#define op_lload_2			0x20
#define op_lload_3			0x21
#define op_fload_0			0x22
#define op_fload_1			0x23
#define op_fload_2			0x24
#define op_fload_3			0x25
#define op_dload_0			0x26
#define op_dload_1			0x27
#define op_dload_2			0x28
#define op_dload_3			0x29
#define op_aload_0			0x2a
#define op_aload_1			0x2b
#define op_aload_2			0x2c
#define op_aload_3			0x2d
#define op_iaload			0x2e
#define op_laload			0x2f
#define op_faload			0x30
#define op_daload			0x31
#define op_aaload			0x32
#define op_baload			0x33
#define op_caload			0x34
#define op_saload			0x35
#define op_istore			0x36
#define op_lstore			0x37
#define op_fstore			0x38
#define op_dstore			0x39
#define op_astore			0x3a
#define op_istore_0			0x3b
#define op_istore_1			0x3c
#define op_istore_2			0x3d
#define op_istore_3			0x3e
#define op_lstore_0			0x3f
#define op_lstore_1			0x40
#define op_lstore_2			0x41
#define op_lstore_3			0x42
#define op_fstore_0			0x43
#define op_fstore_1			0x44
#define op_fstore_2			0x45
#define op_fstore_3			0x46
#define op_dstore_0			0x47
#define op_dstore_1			0x48
#define op_dstore_2			0x49
#define op_dstore_3			0x4a
#define op_astore_0			0x4b
#define op_astore_1			0x4c
#define op_astore_2			0x4d
#define op_astore_3			0x4e
#define op_iastore			0x4f
#define op_lastore			0x50
#define op_fastore			0x51
#define op_dastore			0x52
#define op_aastore			0x53
#define op_bastore			0x54
#define op_castore			0x55
#define op_sastore			0x56
#define op_pop				0x57
#define op_pop2				0x58
#define op_dup				0x59
#define op_dup_x1			0x5a
#define op_dup_x2			0x5b
#define op_dup2				0x5c
#define op_dup2_x1			0x5d
#define op_dup2_x2			0x5e
#define op_swap				0x5f
#define op_iadd				0x60
#define op_ladd				0x61
#define op_fadd				0x62
#define op_dadd				0x63
#define op_isub				0x64
#define op_lsub				0x65
#define op_fsub				0x66
#define op_dsub				0x67
#define op_imul				0x68
#define op_lmul				0x69
#define op_fmul				0x6a
#define op_dmul				0x6b
#define op_idiv				0x6c
#define op_ldiv				0x6d
#define op_fdiv				0x6e
#define op_ddiv				0x6f
#define op_irem				0x70
#define op_lrem				0x71
#define op_frem				0x72
#define op_drem				0x73
#define op_ineg				0x74
#define op_lneg				0x75
#define op_fneg				0x76
#define op_dneg				0x77
#define op_ishl				0x78
#define op_lshl				0x79
#define op_ishr				0x7a
#define op_lshr				0x7b
#define op_iushr			0x7c
#define op_lushr			0x7d
#define op_iand				0x7e
#define op_land				0x7f
#define op_ior				0x80
#define op_lor				0x81
#define op_ixor				0x82
#define op_lxor				0x83
#define op_iinc				0x84
#define op_i2l				0x85
#define op_i2f				0x86
#define op_i2d				0x87
#define op_l2i				0x88
#define op_l2f				0x89
#define op_l2d				0x8a
#define op_f2i				0x8b
#define op_f2l				0x8c
#define op_f2d				0x8d
#define op_d2i				0x8e
#define op_d2l				0x8f
#define op_d2f				0x90
#define op_i2b				0x91
#define op_i2c				0x92
#define op_i2s				0x93
#define op_lcmp				0x94
#define op_fcmpl			0x95
#define op_fcmpg			0x96
#define op_dcmpl			0x97
#define op_dcmpg			0x98
#define op_ifeq				0x99
#define op_ifne				0x9a
#define op_iflt				0x9b
#define op_ifge				0x9c
#define op_ifgt				0x9d
#define op_ifle				0x9e
#define op_if_icmpeq		0x9f
#define op_if_icmpne		0xa0
#define op_if_icmplt		0xa1
#define op_if_icmpge		0xa2
#define op_if_icmpgt		0xa3
#define op_if_icmple		0xa4
#define op_if_acmpeq		0xa5
#define op_if_acmpne		0xa6
#define op_goto				0xa7
#define op_jsr				0xa8
#define op_ret				0xa9
#define op_tableswitch		0xaa
#define op_lookupswitch		0xab
#define op_ireturn			0xac
#define op_lreturn			0xad
#define op_freturn			0xae
#define op_dreturn			0xaf
#define op_areturn			0xb0
#define op_return			0xb1
#define op_getstatic		0xb2
#define op_putstatic		0xb3
#define op_getfield			0xb4
#define op_putfield			0xb5
#define op_invokevirtual	0xb6
#define op_invokespecial	0xb7
#define op_invokestatic		0xb8
#define op_invokeinterface	0xb9
#define op_invokedynamic	0xba
#define op_new				0xbb
#define op_newarray			0xbc
#define op_anewarray		0xbd
#define op_arraylength		0xbe
#define op_athrow			0xbf
#define op_checkcast		0xc0
#define op_instanceof		0xc1
#define op_monitorenter		0xc2
#define op_monitorexit		0xc3
#define op_wide				0xc4
#define op_multianewarray	0xc5
#define op_ifnull			0xc6
#define op_ifnonnull		0xc7
#define op_goto_w			0xc8
#define op_jsr_w			0xc9
#define op_breakpoint		0xca
#define op_impdep1			0xfe
#define op_impdep2			0xff

#endif /* VM_OPCODES_H_ */
