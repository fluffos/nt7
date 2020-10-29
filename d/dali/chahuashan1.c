//Room: /d/dali/chahuashan1.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","茶花山");
        set("long", @LONG
你站在一座小山西面脚下，大理盛产茶花，好品种的茶花遍地生
长，东面的这片小山林也长满了好茶。西边不远就是大理城的北门了。
LONG );
        set("outdoors", "dalic");
        set("exits",([ /* sizeof() == 1 */
            "west"      : "/d/dali/northgate",
            "eastup"    : "/d/dali/chahuashan2",
        ]));
        set("no_clean_up", 0);
	set("coor/x", -19150);
	set("coor/y", -6860);
	set("coor/z", 20);
	setup();
        replace_program(ROOM);
}