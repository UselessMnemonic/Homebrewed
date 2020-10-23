#include "util/print/ClassPrinter.h"
#include "classfile/attributes/Unknown.h"
#include "vm/Opcodes.h"
#include <stdio.h>
#include <string.h>

void _PrintAttributes(u2 attributes_count, ATTRIBUTE **attributes, CONSTANT **constant_pool, size_t indent);

void _PrintIndent(size_t indent)
{
	while(indent-- != 0) putchar('\t');
}

void _PrintConstantPool(u2 constant_pool_count, CONSTANT **constant_pool, size_t indent)
{
	for (int i = 0; i < constant_pool_count - 1; i++)
	{
		CONSTANT *cp_info = constant_pool[i];
		if (cp_info) switch (cp_info->tag)
		{
		case CONSTANT_Integer_info:
		{
			CONSTANT_Integer *int_info = (CONSTANT_Integer *)cp_info;
			_PrintIndent(indent); printf("[#%d] Integer Constant: %d\n", i+1, (int)int_info->value);
			break;
		}
		case CONSTANT_Float_info:
		{
			CONSTANT_Float *float_info = (CONSTANT_Float *)cp_info;
			_PrintIndent(indent); printf("[#%d] Float Constant: %f\n", i+1, (float)float_info->value);
			break;
		}
		case CONSTANT_Long_info:
		{
			CONSTANT_Long *long_info = (CONSTANT_Long *)cp_info;
			uint64_t temp = long_info->high;
			temp <<= 32;
			temp |= long_info->low;
			_PrintIndent(indent); printf("[#%d] Long Constant: %ld\n", i+1, (long)temp);
			break;
		}
		case CONSTANT_Double_info:
		{
			CONSTANT_Double *long_info = (CONSTANT_Double *)cp_info;
			uint64_t temp = long_info->high;
			temp <<= 32;
			temp |= long_info->low;
			_PrintIndent(indent); printf("[#%d] Double Constant: %lf\n", i+1, (double)temp);
			break;
		}
		case CONSTANT_String_info:
		{
			CONSTANT_String *string_info = (CONSTANT_String *)cp_info;
			_PrintIndent(indent); printf("[#%d] String Reference:\n", i+1);
			_PrintIndent(indent+1); printf("Name @ %u\n", string_info->string_index);
			break;
		}
		case CONSTANT_Class_info:
		{
			CONSTANT_Class *class_info = (CONSTANT_Class *)cp_info;
			_PrintIndent(indent); printf("[#%d] Class Reference:\n", i+1);
			_PrintIndent(indent+1); printf("Name @ %u\n", class_info->name_index);
			break;
		}
		case CONSTANT_Fieldref_info:
		{
			CONSTANT_Fieldref *field_info = (CONSTANT_Fieldref *)cp_info;
			_PrintIndent(indent); printf("[#%d] Field Reference:\n", i+1);
			_PrintIndent(indent+1); printf("Class @ %u\n", field_info->class_index);
			_PrintIndent(indent+1); printf("Name and Type @ %u\n", field_info->name_and_type_index);
			break;
		}
		case CONSTANT_Methodref_info:
		{
			CONSTANT_Methodref *method_info = (CONSTANT_Methodref *)cp_info;
			_PrintIndent(indent); printf("[#%d] Method Reference:\n", i+1);
			_PrintIndent(indent+1); printf("Class @ %u\n", method_info->class_index);
			_PrintIndent(indent+1); printf("Name and Type @ %u\n", method_info->name_and_type_index);
			break;
		}
		case CONSTANT_InterfaceMethodref_info:
		{
			CONSTANT_InterfaceMethodref *interface_info = (CONSTANT_InterfaceMethodref *)cp_info;
			_PrintIndent(indent); printf("[#%d] Interface Method Reference:\n", i+1);
			_PrintIndent(indent+1); printf("Class @ %u\n", interface_info->class_index);
			_PrintIndent(indent+1); printf("Name and Type @ %u\n", interface_info->name_and_type_index);
			break;
		}
		case CONSTANT_NameAndType_info:
		{
			CONSTANT_NameAndType *name_and_type_info = (CONSTANT_NameAndType *)cp_info;
			_PrintIndent(indent); printf("[#%d] Name and Type:\n", i+1);
			_PrintIndent(indent+1); printf("Name @ %u\n", name_and_type_info->name_index);
			_PrintIndent(indent+1); printf("Descriptor @ %u\n", name_and_type_info->descriptor_index);
			break;
		}
		case CONSTANT_Utf8_info:
		{
			CONSTANT_Utf8 *utf8_info = (CONSTANT_Utf8 *)cp_info;
			_PrintIndent(indent); printf("[#%d] UTF-8 Constant: \"%s\"\n", i+1, utf8_info->runes);
			break;
		}
		}
	}
}

void _PrintAttribute_ConstantValue(ATTRIBUTE_ConstantValue *attribute, CONSTANT **constant_pool, size_t indent)
{
	_PrintIndent(indent); printf("Constant Value @ #%u\n", attribute->constantvalue_index);
}

void _PrintAttribute_Code(ATTRIBUTE_Code *attribute, CONSTANT **constant_pool, size_t indent)
{
	_PrintIndent(indent); printf("Max Stack: %u\n", attribute->max_stack);
	_PrintIndent(indent); printf("Max Locals: %u\n", attribute->max_locals);

	_PrintIndent(indent); printf("Code (%lu bytes) {\n", attribute->code_length);
	bytecode *c = attribute->code;
	for (int i = 0; i < attribute->code_length; ) {
		_PrintIndent(indent+1); printf("%d: ", i);
		switch (c[i]) {
		case op_nop: printf("nop\n"); i++; break;

		case op_aconst_null: printf("aconst null\n"); i++; break;
		case op_aload: printf("aload locals[%u]\n", c[i+1]); i+=2 ; break;
		case op_aload_0: printf("aload locals[0]\n"); i++; break;
		case op_aload_1: printf("aload locals[1]\n"); i++; break;
		case op_aload_2: printf("aload locals[2]\n"); i++; break;
		case op_aload_3: printf("aload locals[3]\n"); i++; break;
		case op_aaload: printf("aaload\n"); i++; break;
		case op_astore: printf("astore locals[%u]\n", c[i+1]); i+=2 ; break;
		case op_astore_0: printf("astore locals[0]\n"); i++; break;
		case op_astore_1: printf("astore locals[1]\n"); i++; break;
		case op_astore_2: printf("astore locals[2]\n"); i++; break;
		case op_astore_3: printf("astore locals[3]\n"); i++; break;
		case op_aastore: printf("aastore\n"); i++; break;
		case op_athrow: printf("athrow\n"); i++; break;
		case op_areturn: printf("areturn\n"); i++; break;

		case op_dconst_0: printf("dconst #0.0\n"); i++; break;
		case op_dconst_1: printf("dconst #1.0\n"); i++; break;
		case op_dload: printf("dload locals[%u]\n", c[i+1]); i+=2; break;
		case op_dload_0: printf("dload locals[1]\n"), i++; break;
		case op_dload_1: printf("dload locals[2]\n"); i++; break;
		case op_dload_2: printf("dload locals[3]\n"); i++; break;
		case op_dload_3: printf("dload locals[4]\n"); i++; break;
		case op_daload: printf("daload\n"); i++; break;
		case op_dstore: printf("dstore locals[%u]\n", c[i+1]); i+=2; break;
		case op_dstore_0: printf("dstore locals[0]\n"); i++; break;
		case op_dstore_1: printf("dstore locals[1]\n"); i++; break;
		case op_dstore_2: printf("dstore locals[2]\n"); i++; break;
		case op_dstore_3: printf("dstore locals[3]\n"); i++; break;
		case op_dastore: printf("dastore\n"); i++; break;
		case op_dadd: printf("dadd\n"); i++; break;
		case op_dsub: printf("dsub\n"); i++; break;
		case op_dmul: printf("dmul\n"); i++; break;
		case op_ddiv: printf("ddiv\n"); i++; break;
		case op_drem: printf("drem\n"); i++; break;
		case op_dneg: printf("dneg\n"); i++; break;
		case op_dcmpg: printf("dcmp<g>\n"); i++; break;
		case op_dcmpl: printf("dcmp<l>\n"); i++; break;
		case op_d2f: printf("d2f\n"); i++; break;
		case op_d2i: printf("d2i\n"); i++; break;
		case op_d2l: printf("d2l\n"); i++; break;
		case op_dreturn: printf("dreturn\n"); i++; break;

		case op_fconst_0: printf("fconst #0.0f\n"); i++; break;
		case op_fconst_1: printf("fconst #1.0f\n"); i++; break;
		case op_fconst_2: printf("fconst #2.0f\n"); i++; break;
		case op_fload: printf("fload locals[%u]\n", c[i+1]); i+=2; break;
		case op_fload_0: printf("fload locals[0]\n"); i++; break;
		case op_fload_1: printf("fload locals[1]\n"); i++; break;
		case op_fload_2: printf("fload locals[2]\n"); i++; break;
		case op_fload_3: printf("fload locals[3]\n"); i++; break;
		case op_faload: printf("faload\n"); i++; break;
		case op_fstore: printf("fstore locals[%u]\n", c[i+1]); i+=2; break;
		case op_fstore_0: printf("fstore locals[0]\n"); i++; break;
		case op_fstore_1: printf("fstore locals[1]\n"); i++; break;
		case op_fstore_2: printf("fstore locals[2]\n"); i++; break;
		case op_fstore_3: printf("fstore locals[3]\n"); i++; break;
		case op_fastore: printf("fastore\n"); i++; break;
		case op_fadd: printf("fadd\n"); i++; break;
		case op_fsub: printf("nop\n"); i++; break;
		case op_fmul: printf("fmul\n"); i++; break;
		case op_fdiv: printf("fdiv\n"); i++; break;
		case op_frem: printf("frem\n"); i++; break;
		case op_fneg: printf("fneg\n"); i++; break;
		case op_fcmpg: printf("fcmp<g>\n"); i++; break;
		case op_fcmpl: printf("fcmp<l>\n"); i++; break;
		case op_f2d: printf("f2d\n"); i++; break;
		case op_f2i: printf("f2i\n"); i++; break;
		case op_f2l: printf("f2l\n"); i++; break;
		case op_freturn: printf("freturn\n"); i++; break;

		case op_iconst_m1: printf("iconst #-1\n"); i++; break;
		case op_iconst_0: printf("iconst #0\n"); i++; break;
		case op_iconst_1: printf("iconst #1\n"); i++; break;
		case op_iconst_2: printf("iconst #2\n"); i++; break;
		case op_iconst_3: printf("iconst #3\n"); i++; break;
		case op_iconst_4: printf("iconst #4\n"); i++; break;
		case op_iconst_5: printf("iconst #5\n"); i++; break;
		case op_iload: printf("iload locals[%u]\n", c[i+1]); i+=2; break;
		case op_iload_0: printf("iload locals[0]\n"); i++; break;
		case op_iload_1: printf("iload locals[1]\n"); i++; break;
		case op_iload_2: printf("iload locals[2]\n"); i++; break;
		case op_iload_3: printf("iload locals[3]\n"); i++; break;
		case op_iaload: printf("iaload\n"); i++; break;
		case op_istore: printf("istore locals[%u]\n", c[i+1]); i+=2; break;
		case op_istore_0: printf("istore locals[0]\n"); i++; break;
		case op_istore_1: printf("istore locals[1]\n"); i++; break;
		case op_istore_2: printf("istore locals[2]\n"); i++; break;
		case op_istore_3: printf("istore locals[3]\n"); i++; break;
		case op_iastore: printf("iastore\n"); i++; break;
		case op_iinc: printf("iinc locals[%u] += #%u\n", c[i+1], c[i+2]); i+=3; break;
		case op_iadd: printf("iadd\n"); i++; break;
		case op_isub: printf("isub\n"); i++; break;
		case op_imul: printf("imul\n"); i++; break;
		case op_idiv: printf("idiv\n"); i++; break;
		case op_irem: printf("irem\n"); i++; break;
		case op_ineg: printf("ineg\n"); i++; break;
		case op_iand: printf("iand\n"); i++; break;
		case op_ior: printf("ior\n"); i++; break;
		case op_ixor: printf("ixor\n"); i++; break;
		case op_iushr: printf("iushr\n"); i++; break;
		case op_ishr: printf("ishr\n"); i++; break;
		case op_ishl: printf("ishl\n"); i++; break;
		case op_i2b: printf("i2b\n"); i++; break;
		case op_i2c: printf("i2c\n"); i++; break;
		case op_i2d: printf("i2d\n"); i++; break;
		case op_i2f: printf("i2f\n"); i++; break;
		case op_i2l: printf("i2l\n"); i++; break;
		case op_i2s: printf("i2s\n"); i++; break;
		case op_ireturn: printf("ireturn\n"); i++; break;

		case op_lconst_0: printf("lconst #0L\n"); i++; break;
		case op_lconst_1: printf("lconst #1L\n"); i++; break;
		case op_lload: printf("lload locals[%u]\n", c[i+1]); i+=2; break;
		case op_lload_0: printf("lload locals[0]\n"); i++; break;
		case op_lload_1: printf("lload locals[1]\n"); i++; break;
		case op_lload_2: printf("lload locals[2]\n"); i++; break;
		case op_lload_3: printf("lload locals[3]\n"); i++; break;
		case op_laload: printf("laload\n"); i++; break;
		case op_lstore: printf("lstore locals[%u]\n", c[i+1]); i+=2; break;
		case op_lstore_0: printf("lstore locals[0]\n"); i++; break;
		case op_lstore_1: printf("lstore locals[1]\n"); i++; break;
		case op_lstore_2: printf("lstore locals[2]\n"); i++; break;
		case op_lstore_3: printf("lstore locals[3]\n"); i++; break;
		case op_lastore: printf("lastore\n"); i++; break;
		case op_ladd: printf("ladd\n"); i++; break;
		case op_lsub: printf("lsub\n"); i++; break;
		case op_lmul: printf("lmul\n"); i++; break;
		case op_ldiv: printf("ldiv\n"); i++; break;
		case op_lrem: printf("lrem\n"); i++; break;
		case op_lneg: printf("lneg\n"); i++; break;
		case op_land: printf("land\n"); i++; break;
		case op_lor: printf("lor\n"); i++; break;
		case op_lxor: printf("lxor\n"); i++; break;
		case op_lushr: printf("lushr\n"); i++; break;
		case op_lshr: printf("lshr\n"); i++; break;
		case op_lshl: printf("lshl\n"); i++; break;
		case op_l2d: printf("l2d\n"); i++; break;
		case op_l2f: printf("l2f\n"); i++; break;
		case op_l2i: printf("l2i\n"); i++; break;
		case op_lcmp: printf("lcmp\n"); i++; break;
		case op_lreturn: printf("lreturn\n"); i++; break;

		case op_saload: printf("saload\n"); i++; break;
		case op_sastore: printf("sastore\n"); i++; break;
		case op_sipush: printf("sipush #%u\n", c[i+1]); i+=2; break;

		case op_baload: printf("baload\n"); i++; break;
		case op_bastore: printf("bastore\n"); i++; break;
		case op_bipush: printf("bipush #%u\n", c[i+1]); i+=2; break;

		case op_caload: printf("caload\n"); i++; break;
		case op_castore: printf("castore\n"); i++; break;

		case op_pop: printf("pop\n"); i++; break;
		case op_pop2: printf("pop2\n"); i++; break;
		case op_swap: printf("swap\n"); i++; break;

		case op_dup: printf("dup\n"); i++; break;
		case op_dup_x1: printf("dup_x1\n"); i++; break;
		case op_dup_x2: printf("dup_x2\n"); i++; break;

		case op_dup2: printf("dup\n"); i++; break;
		case op_dup2_x1: printf("dup_x1\n"); i++; break;
		case op_dup2_x2: printf("dup_x2\n"); i++; break;

		case op_ldc: printf("ldc constant_pool[%u]\n", c[i+1]); i+=2; break;
		case op_ldc_w: printf("ldc_w constant_pool[%u]\n", Append2U1(c[i+1], c[i+2])); i+=3; break;
		case op_ldc2_w: printf("ldc2_w constant_pool[%u]\n", Append2U1(c[i+1], c[i+2])); i+=3; break;

		case op_if_acmpeq: printf("if_acmp<eq> goto code[%u]\n", Append2U1(c[i+1], c[i+2])); i+=3; break;
		case op_if_acmpne: printf("if_acmp<ne> goto code[%u]\n", Append2U1(c[i+1], c[i+2])); i+=3; break;
		case op_if_icmpeq: printf("if_icmp<eq> goto code[%u]\n", Append2U1(c[i+1], c[i+2])); i+=3; break;
		case op_if_icmpge: printf("if_icmp<ge> goto code[%u]\n", Append2U1(c[i+1], c[i+2])); i+=3; break;
		case op_if_icmpgt: printf("if_icmp<gt> goto code[%u]\n", Append2U1(c[i+1], c[i+2])); i+=3; break;
		case op_if_icmple: printf("if_icmp<le> goto code[%u]\n", Append2U1(c[i+1], c[i+2])); i+=3; break;
		case op_if_icmplt: printf("if_icmp<lt> goto code[%u]\n", Append2U1(c[i+1], c[i+2])); i+=3; break;
		case op_if_icmpne: printf("if_icmp<ne> goto code[%u]\n", Append2U1(c[i+1], c[i+2])); i+=3; break;
		case op_ifeq: printf("if<eq> goto code[%u]\n", Append2U1(c[i+1], c[i+2])); i+=3; break;
		case op_ifge: printf("if<ge> goto code[%u]\n", Append2U1(c[i+1], c[i+2])); i+=3; break;
		case op_ifgt: printf("if<gt> goto code[%u]\n", Append2U1(c[i+1], c[i+2])); i+=3; break;
		case op_ifle: printf("if<le> goto code[%u]\n", Append2U1(c[i+1], c[i+2])); i+=3; break;
		case op_iflt: printf("if<lt> goto code[%u]\n", Append2U1(c[i+1], c[i+2])); i+=3; break;
		case op_ifne: printf("if<ne> goto code[%u]\n", Append2U1(c[i+1], c[i+2])); i+=3; break;
		case op_ifnonnull: printf("if<nonnull> goto code[%u]\n", Append2U1(c[i+1], c[i+2])); i+=3; break;
		case op_ifnull: printf("if<null> goto code[%u]\n", Append2U1(c[i+1], c[i+2])); i+=3; break;
		case op_goto: printf("goto code[%u]\n", Append2U1(c[i+1], c[i+2])); i+=3; break;
		case op_goto_w: printf("goto_w code[%lu]\n", Append4U1(c[i+1], c[i+2], c[i+3], c[i+4])); i+=5; break;
		case op_jsr: printf("jsr code[%u]\n", Append2U1(c[i+1], c[i+2])); i+=3; break;
		case op_jsr_w: printf("jsr_w code[%lu]\n", Append4U1(c[i+1], c[i+2], c[i+3], c[i+4])); i+=5; break;
		case op_ret: printf("ret frame[%u]\n", c[i+1]); i+=2; break;
		case op_return: printf("return\n"); i++; break;

		case op_invokedynamic: {
			u2 dynamic_ref_index = Append2U1(c[i+1],c[i+2]);
			CONSTANT_InvokeDynamic *dynamic_info = constant_pool[dynamic_ref_index - 1];

			u2 bootstrap_index = dynamic_info->bootstrap_method_attr_index;

			CONSTANT_NameAndType *name_and_type_info = constant_pool[dynamic_info->name_and_type_index - 1];
			CONSTANT_Utf8 *method_name = constant_pool[name_and_type_info->name_index - 1];
			CONSTANT_Utf8 *descriptor = constant_pool[name_and_type_info->descriptor_index - 1];

			printf("invokedynamic %s %s | Bootstrap @ %u\n", method_name->runes, descriptor->runes, bootstrap_index); i+=3; break;
		}
		case op_invokeinterface: {
			u2 method_ref_index = Append2U1(c[i+1],c[i+2]);
			CONSTANT_InterfaceMethodref *method_info = constant_pool[method_ref_index - 1];

			CONSTANT_Class *class_info = constant_pool[method_info->class_index - 1];
			CONSTANT_Utf8 *class_name = constant_pool[class_info->name_index - 1];

			CONSTANT_NameAndType *name_and_type_info = constant_pool[method_info->name_and_type_index - 1];
			CONSTANT_Utf8 *method_name = constant_pool[name_and_type_info->name_index - 1];
			CONSTANT_Utf8 *descriptor = constant_pool[name_and_type_info->descriptor_index - 1];

			printf("invokeinterface %s::%s %s\n", class_name->runes, method_name->runes, descriptor->runes); i+=3; break;
		}
		case op_invokespecial: {
			u2 method_ref_index = Append2U1(c[i+1],c[i+2]);
			CONSTANT_Methodref *method_info = constant_pool[method_ref_index - 1];

			CONSTANT_Class *class_info = constant_pool[method_info->class_index - 1];
			CONSTANT_Utf8 *class_name = constant_pool[class_info->name_index - 1];

			CONSTANT_NameAndType *name_and_type_info = constant_pool[method_info->name_and_type_index - 1];
			CONSTANT_Utf8 *method_name = constant_pool[name_and_type_info->name_index - 1];
			CONSTANT_Utf8 *descriptor = constant_pool[name_and_type_info->descriptor_index - 1];

			printf("invokespecial %s::%s %s\n", class_name->runes, method_name->runes, descriptor->runes); i+=3; break;
		}
		case op_invokestatic: {
			u2 method_ref_index = Append2U1(c[i+1],c[i+2]);
			CONSTANT_Methodref *method_info = constant_pool[method_ref_index - 1];

			CONSTANT_Class *class_info = constant_pool[method_info->class_index - 1];
			CONSTANT_Utf8 *class_name = constant_pool[class_info->name_index - 1];

			CONSTANT_NameAndType *name_and_type_info = constant_pool[method_info->name_and_type_index - 1];
			CONSTANT_Utf8 *method_name = constant_pool[name_and_type_info->name_index - 1];
			CONSTANT_Utf8 *descriptor = constant_pool[name_and_type_info->descriptor_index - 1];

			printf("invokestatic %s::%s %s\n", class_name->runes, method_name->runes, descriptor->runes); i+=3; break;
		}
		case op_invokevirtual: {
			u2 method_ref_index = Append2U1(c[i+1],c[i+2]);
			CONSTANT_Methodref *method_info = constant_pool[method_ref_index - 1];

			CONSTANT_Class *class_info = constant_pool[method_info->class_index - 1];
			CONSTANT_Utf8 *class_name = constant_pool[class_info->name_index - 1];

			CONSTANT_NameAndType *name_and_type_info = constant_pool[method_info->name_and_type_index - 1];
			CONSTANT_Utf8 *method_name = constant_pool[name_and_type_info->name_index - 1];
			CONSTANT_Utf8 *descriptor = constant_pool[name_and_type_info->descriptor_index - 1];

			printf("invokevirtual %s::%s %s\n", class_name->runes, method_name->runes, descriptor->runes); i+=3; break;
		}

		case op_newarray: printf("newarray %s[]\n", c[1] == 4 ? "boolean"
				                                  : c[1] == 5 ? "char"
				                                  : c[1] == 6 ? "float"
				                                  : c[1] == 7 ? "double"
				                                  : c[1] == 8 ? "byte"
				                                  : c[1] == 9 ? "short"
				                                  : c[1] == 10 ? "int"
				                                  : c[1] == 11 ? "long" : "?"); i+=2; break;

		case op_new: {
			u2 class_info_index = Append2U1(c[i+1], c[i+2]);
			CONSTANT_Class *class_info = constant_pool[class_info_index - 1];
			CONSTANT_Utf8 *utf8_info = constant_pool[class_info->name_index - 1];
			printf("new %s\n", utf8_info->runes); i+=3; break;
		}
		case op_multianewarray: {
			u2 class_info_index = Append2U1(c[i+1], c[i+2]);
			CONSTANT_Class *class_info = constant_pool[class_info_index - 1];
			CONSTANT_Utf8 *utf8_info = constant_pool[class_info->name_index - 1];
			printf("multianewarray %s\n", utf8_info->runes); i+=3; break;
		}
		case op_anewarray: {
			u2 class_info_index = Append2U1(c[i+1], c[i+2]);
			CONSTANT_Class *class_info = constant_pool[class_info_index - 1];
			CONSTANT_Utf8 *utf8_info = constant_pool[class_info->name_index - 1];
			printf("anewarray %s\n", utf8_info->runes); i+=3; break;
		}
		case op_checkcast: {
			u2 class_info_index = Append2U1(c[i+1], c[i+2]);
			CONSTANT_Class *class_info = constant_pool[class_info_index - 1];
			CONSTANT_Utf8 *utf8_info = constant_pool[class_info->name_index - 1];
			printf("checkcast %s\n", utf8_info->runes); i+=3; break;
		}
		case op_instanceof: {
			u2 class_info_index = Append2U1(c[i+1], c[i+2]);
			CONSTANT_Class *class_info = constant_pool[class_info_index - 1];
			CONSTANT_Utf8 *utf8_info = constant_pool[class_info->name_index - 1];
			printf("instanceof %s\n", utf8_info->runes); i+=3; break;
		}

		case op_getfield: {
			u2 field_ref_index = Append2U1(c[i+1], c[i+2]);
			CONSTANT_Fieldref *field_info = constant_pool[field_ref_index - 1];

			CONSTANT_Class *class_info = constant_pool[field_info->class_index - 1];
			CONSTANT_Utf8 *class_name = constant_pool[class_info->name_index - 1];

			CONSTANT_NameAndType *name_and_type_info = constant_pool[field_info->name_and_type_index - 1];
			CONSTANT_Utf8 *field_name = constant_pool[name_and_type_info->name_index - 1];
			CONSTANT_Utf8 *field_descriptor = constant_pool[name_and_type_info->descriptor_index - 1];

			printf("getfield %s.%s (%s)\n", class_name->runes, field_name->runes, field_descriptor->runes); i+=3; break;
		}
		case op_getstatic: {
			u2 field_ref_index = Append2U1(c[i+1], c[i+2]);
			CONSTANT_Fieldref *field_info = constant_pool[field_ref_index - 1];

			CONSTANT_Class *class_info = constant_pool[field_info->class_index - 1];
			CONSTANT_Utf8 *class_name = constant_pool[class_info->name_index - 1];

			CONSTANT_NameAndType *name_and_type_info = constant_pool[field_info->name_and_type_index - 1];
			CONSTANT_Utf8 *field_name = constant_pool[name_and_type_info->name_index - 1];
			CONSTANT_Utf8 *field_descriptor = constant_pool[name_and_type_info->descriptor_index - 1];

			printf("getstatic %s.%s (%s)\n", class_name->runes, field_name->runes, field_descriptor->runes); i+=3; break;
		}
		case op_putfield: {
			u2 field_ref_index = Append2U1(c[i+1], c[i+2]);
			CONSTANT_Fieldref *field_info = constant_pool[field_ref_index - 1];

			CONSTANT_Class *class_info = constant_pool[field_info->class_index - 1];
			CONSTANT_Utf8 *class_name = constant_pool[class_info->name_index - 1];

			CONSTANT_NameAndType *name_and_type_info = constant_pool[field_info->name_and_type_index - 1];
			CONSTANT_Utf8 *field_name = constant_pool[name_and_type_info->name_index - 1];
			CONSTANT_Utf8 *field_descriptor = constant_pool[name_and_type_info->descriptor_index - 1];

			printf("putfield %s.%s (%s)\n", class_name->runes, field_name->runes, field_descriptor->runes); i+=3; break;
		}
		case op_putstatic: {
			u2 field_ref_index = Append2U1(c[i+1], c[i+2]);
			CONSTANT_Fieldref *field_info = constant_pool[field_ref_index - 1];

			CONSTANT_Class *class_info = constant_pool[field_info->class_index - 1];
			CONSTANT_Utf8 *class_name = constant_pool[class_info->name_index - 1];

			CONSTANT_NameAndType *name_and_type_info = constant_pool[field_info->name_and_type_index - 1];
			CONSTANT_Utf8 *field_name = constant_pool[name_and_type_info->name_index - 1];
			CONSTANT_Utf8 *field_descriptor = constant_pool[name_and_type_info->descriptor_index - 1];

			printf("putstatic %s.%s (%s)\n", class_name->runes, field_name->runes, field_descriptor->runes); i+=3; break;
		}

		case op_wide: {
			if (c[i+1] == op_iinc) {
				printf("wide-iinc locals[%u] += #%u\n", Append2U1(c[i+2], c[i+3]), Append2U1(c[i+4], c[i+5]));
				i+=6; break;
			}
			else if (c[i+1] == op_iload)
			{
				printf("wide-iload locals[%u]\n", Append2U1(c[i+2], c[i+3]));
				i+=4; break;
			}
			else if (c[i+1] == op_fload)
			{
				printf("wide-fload locals[%u]\n", Append2U1(c[i+2], c[i+3]));
				i+=4; break;
			}
			else if (c[i+1] == op_aload)
			{
				printf("wide-aload locals[%u]\n", Append2U1(c[i+2], c[i+3]));
				i+=4; break;
			}
			else if (c[i+1] == op_lload)
			{
				printf("wide-lload locals[%u]\n", Append2U1(c[i+2], c[i+3]));
				i+=4; break;
			}
			else if (c[i+1] == op_dload)
			{
				printf("wide-dload locals[%u]\n", Append2U1(c[i+2], c[i+3]));
				i+=4; break;
			}
			else if (c[i+1] == op_istore)
			{
				printf("wide-istore locals[%u]\n", Append2U1(c[i+2], c[i+3]));
				i+=4; break;
			}
			else if (c[i+1] == op_fstore)
			{
				printf("wide-fstore locals[%u]\n", Append2U1(c[i+2], c[i+3]));
				i+=4; break;
			}
			else if (c[i+1] == op_astore)
			{
				printf("wide-astore locals[%u]\n", Append2U1(c[i+2], c[i+3]));
				i+=4; break;
			}
			else if (c[i+1] == op_lstore)
			{
				printf("wide-lstore locals[%u]\n", Append2U1(c[i+2], c[i+3]));
				i+=4; break;
			}
			else if (c[i+1] == op_dstore)
			{
				printf("wide-dstore locals[%u]\n", Append2U1(c[i+2], c[i+3]));
				i+=4; break;
			}
			else if (c[i+1] == op_ret)
			{
				printf("wide-ret frame[%u]\n", Append2U1(c[i+2], c[i+3]));
				i+=4; break;
			}
			break;
		}

		case op_arraylength: printf("arraylength\n"); i++; break;
		case op_monitorenter: printf("monitorenter\n"); i++; break;
		case op_monitorexit: printf("monitorexit\n"); i++; break;

		case op_breakpoint: printf("breakpoint\n"); i++; break;
		case op_impdep1: printf("impdep1\n"); i++; break;
		case op_impdep2: printf("impdep2\n"); i++; break;

		case op_lookupswitch: printf("lookupswitch\n"); i++; break;
		case op_tableswitch: printf("tableswitch\n"); i++; break;
		}
	}
	_PrintIndent(indent); printf("}\n");

	_PrintIndent(indent); printf("Exception Count: %u\n", attribute->exception_table_length);
	for (int i = 0; i < attribute->exception_table_length; i++)
	{
		struct ExceptionEntry *e = &attribute->exception_table[i];
		_PrintIndent(indent+1); printf("Exception {");
		_PrintIndent(indent+2); printf("Start PC: %u\n", e->catch_type);
		_PrintIndent(indent+2); printf("End PC: %u\n", e->catch_type);
		_PrintIndent(indent+1); printf("Handler PC: %u\n", e->catch_type);
		_PrintIndent(indent+1); if (e->catch_type) printf("Catch Type @ %u\n", e->catch_type); else printf("No Catch Type\n");
		_PrintIndent(indent+1); printf("}\n");
	}

	_PrintIndent(indent); printf("Attributes Count: %u\n", attribute->attributes_count);
	_PrintAttributes(attribute->attributes_count, attribute->attributes, constant_pool, indent+1);
}

void _PrintAttribute_StackMapTable(ATTRIBUTE_StackMapTable *attribute, CONSTANT **constant_pool, size_t indent)
{
}

void _PrintAttribute_BootstrapMethods(ATTRIBUTE_BootstrapMethods *attribute, CONSTANT **constant_pool, size_t indent)
{
	_PrintIndent(indent); printf("Number of Bootstrap Methods: %u\n", attribute->num_bootstrap_methods);
	for (int i = 0; i < attribute->num_bootstrap_methods; i++)
		{
			struct BootstrapMethod *method = attribute->bootstrap_methods[i];
			_PrintIndent(indent); printf("Bootstrap Method {\n");
			_PrintIndent(indent+1); printf("Method Reference @ #%u", method->bootstrap_method_ref);
			for (int k = 0; k < method->num_bootstrap_arguments; k++)
			{
				_PrintIndent(indent+2); printf("Argument @ #%u", method->bootstrap_arguments[k]);
			}
			_PrintIndent(indent); printf("}\n");
		}
}

void _PrintAttribute_NestHost(ATTRIBUTE_NestHost *attribute, CONSTANT **constant_pool, size_t indent)
{
	_PrintIndent(indent); printf("Host Class @ #%u\n", attribute->host_class_index);
}

void _PrintAttribute_NestMembers(ATTRIBUTE_NestMembers *attribute, CONSTANT **constant_pool, size_t indent)
{
	for (int i = 0; i < attribute->number_of_classes; i++)
	{
		_PrintIndent(indent); printf("Member Class @ #%u\n", attribute->classes[i]);
	}
}

void _PrintAttributes(u2 attributes_count, ATTRIBUTE **attributes, CONSTANT **constant_pool, size_t indent)
{
	for (int i = 0; i < attributes_count; i++)
	{
		// resolve attribute name and check if supported
		// TODO replace with Modified-UTF8-safe code
		u2 name_index = attributes[i]->attribute_name_index;
		const char *attribute_name =
				(const char *)((CONSTANT_Utf8*) constant_pool[name_index - 1])->runes;

		void (*_PrintAttributeFunction)(ATTRIBUTE*, CONSTANT**, size_t) = NULL;

		// find which attribute is being read
		if (strcmp(attribute_name, "ConstantValue") == 0)
		{
			_PrintAttributeFunction = (void *)_PrintAttribute_ConstantValue;
		}
		else if (strcmp(attribute_name, "Code") == 0)
		{
			_PrintAttributeFunction = (void *)_PrintAttribute_Code;
		}
		else if (strcmp(attribute_name, "StackMapTable") == 0)
		{
			_PrintAttributeFunction = (void *)_PrintAttribute_StackMapTable;
		}
		else if (strcmp(attribute_name, "BootstrapMethods") == 0)
		{
			_PrintAttributeFunction = (void *)_PrintAttribute_BootstrapMethods;
		}
		else if (strcmp(attribute_name, "NestHost") == 0)
		{
			_PrintAttributeFunction = (void *)_PrintAttribute_NestHost;
		}
		else if (strcmp(attribute_name, "NestMembers") == 0)
		{
			_PrintAttributeFunction = (void *)_PrintAttribute_NestMembers;
		}
		else
		{
			_PrintAttributeFunction = NULL;
			ATTRIBUTE_Unknown *unk = (ATTRIBUTE_Unknown *)attributes[i];
			_PrintIndent(indent); printf("Unknown Attribute \"%s\" (%d bytes)\n", attribute_name, unk->attribute_length);
		}

		if (_PrintAttributeFunction != NULL)
		{
			_PrintIndent(indent); printf("%s Attribute {\n", attribute_name);
			_PrintAttributeFunction(attributes[i], constant_pool, indent+1);
			_PrintIndent(indent); printf("}\n");
		}
	}
}

void _PrintFields(u2 fields_count, FIELD *fields, CONSTANT **constant_pool, size_t indent)
{
	for (int i = 0; i < fields_count; i++)
	{
		FIELD *field = &fields[i];
		CONSTANT_Utf8 *name = constant_pool[field->name_index - 1];
		CONSTANT_Utf8 *descriptor = constant_pool[field->descriptor_index - 1];
		_PrintIndent(indent); printf("Field \"%s\" %s {\n", name->runes, descriptor->runes);
		_PrintIndent(indent+1); printf("Access Flags: 0x%02X\n", field->access_flags);
		_PrintIndent(indent+1); printf("Attributes Count: %u\n", field->attributes_count);
		_PrintAttributes(field->attributes_count, field->attributes, constant_pool, indent+2);
		_PrintIndent(indent); printf("}\n");
	}
}

void _PrintMethods(u2 methods_count, METHOD *methods, CONSTANT **constant_pool, size_t indent)
{
	for (int i = 0; i < methods_count; i++)
	{
		METHOD *method = &methods[i];
		CONSTANT_Utf8 *name = constant_pool[method->name_index - 1];
		CONSTANT_Utf8 *descriptor = constant_pool[method->descriptor_index - 1];
		_PrintIndent(indent); printf("Method \"%s\" %s {\n", name->runes, descriptor->runes);
		_PrintIndent(indent+1); printf("Access Flags: 0x%02X\n", method->access_flags);
		_PrintIndent(indent+1); printf("Attributes Count: %u\n", method->attributes_count);
		_PrintAttributes(method->attributes_count, method->attributes, constant_pool, indent+2);
		_PrintIndent(indent); printf("}\n");
	}
}

void _PrintClass(CLASS *clazz, size_t indent)
{
	CONSTANT_Class *class_info = clazz->constant_pool[clazz->this_class_ref_index - 1];
	CONSTANT_Utf8 *class_name = clazz->constant_pool[class_info->name_index - 1];

	CONSTANT_Class *superclass_info = clazz->constant_pool[clazz->super_class_ref_index - 1];
	CONSTANT_Utf8 *superclass_name = clazz->constant_pool[superclass_info->name_index - 1];

	_PrintIndent(indent); printf("class \"%s\" extends \"%s\" {\n", class_name->runes, superclass_name->runes);
	_PrintIndent(indent+1); printf("Access Flags: 0x%02X\n", clazz->access_flags);

	_PrintIndent(indent+1); printf("Constant Pool Count: %u\n", clazz->constant_pool_count);
	_PrintConstantPool(clazz->constant_pool_count, clazz->constant_pool, indent+2);

	_PrintIndent(indent+1); printf("Interfaces Count: %u\n", clazz->interfaces_count);
	for (int i = 0; i < clazz->interfaces_count; i++)
	{
		CONSTANT_Class *interface_info = clazz->constant_pool[clazz->interface_ref_indices[i] - 1];
		CONSTANT_Utf8 *interface_name = clazz->constant_pool[interface_info->name_index - 1];
		_PrintIndent(indent+2); printf("Interface %s", interface_name->runes);
	}

	_PrintIndent(indent+1); printf("Fields Count: %u\n", clazz->fields_count);
	_PrintFields(clazz->fields_count, clazz->fields, clazz->constant_pool, indent+2);

	_PrintIndent(indent+1); printf("Methods Count: %u\n", clazz->methods_count);
	_PrintMethods(clazz->methods_count, clazz->methods, clazz->constant_pool, indent+2);

	_PrintIndent(indent+1); printf("Attributes Count: %u\n", clazz->attributes_count);
	_PrintAttributes(clazz->attributes_count, clazz->attributes, clazz->constant_pool, indent+1);
	_PrintIndent(indent); printf("}\n");
}

void PrintClass(CLASS *clazz)
{
	_PrintClass(clazz, 0);
}
