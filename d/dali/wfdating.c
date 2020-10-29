//Room: /d/dali/wfdating.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","镇南王府大厅");
        set("long", @LONG
进了大厅，放眼看那大厅，只见正中一块，横匾，写着‘邦国柱
石’四个大字，下首署着‘丁卯御笔’四个小字，楹柱中堂悬满了字
画，一时也看不了这许多。向北是镇南王总理国务见人办公之处，西
边是帐房，往东是一条石径通往内宅。
LONG );
        set("objects",([
            "/d/dali/npc/jiading": 1,
        ]));
        set("exits",([ /* sizeof() == 1 */
            "west"   : "/d/dali/zhangfang",
            "east"   : "/d/dali/shijing",
            "north"  : "/d/dali/zonglichu",
            "out"    : "/d/dali/wangfugate",
        ]));
	set("coor/x", -19121);
	set("coor/y", -6861);
	set("coor/z", -1);
	setup();
        replace_program(ROOM);
}