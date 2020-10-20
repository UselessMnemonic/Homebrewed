#ifndef FLAGS_H_
#define FLAGS_H_

/*
 * A list of flags and tags that may be used
 * throughout the program.
 */

#define ACC_PUBLIC			0x0001
#define ACC_PRIVATE			0x0002
#define ACC_PROTECTED		0x0004
#define ACC_STATIC			0x0008
#define ACC_FINAL			0x0010
#define ACC_SYNCHRONIZED	0x0020
#define ACC_VOLATILE		0x0040
#define ACC_BRIDGE			0x0040
#define ACC_TRANSIENT		0x0080
#define ACC_VARARGS			0x0080
#define ACC_NATIVE			0x0100
#define ACC_ABSTRACT		0x0400
#define ACC_STRICT			0x0800
#define ACC_SYNTEHTIC		0x1000
#define ACC_ENUM			0x4000

#define REF_getField			1
#define REF_getStatic			2
#define REF_putField			3
#define REF_putStatic			4
#define REF_invokeVirtual 		5
#define REF_invokeStatic		6
#define REF_invokeSpecial		7
#define REF_newInvokeSpecial	8
#define REF_invokeInterface		9

#define ITEM_Top				0
#define ITEM_Integer			1
#define ITEM_Float				2
#define ITEM_Long				4
#define ITEM_Double				3
#define ITEM_Null				5
#define ITEM_UninitializedThis	6
#define ITEM_Object				7
#define ITEM_Uninitialized		8

#endif /* FLAGS_H_ */
