//Room: /d/dali/zhengdian.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","正殿");
        set("long", @LONG
这里是大理国皇宫的正殿，大理皇帝通常都在这里处理国事，但
现在皇帝不在，所以显得不那么拘谨，往南是长廊。
LONG );
        set("exits",([ /* sizeof() == 1 */
            "south"  : "/d/dali/hualang",
        ]));
        set("no_clean_up", 0);
	set("coor/x", -19140);
	set("coor/y", -6820);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}