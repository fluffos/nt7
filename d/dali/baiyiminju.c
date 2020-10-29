//Room: /d/dali/baiyiminju.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","摆夷民居");
        set("long", @LONG
摆夷是大理第一大族，大多散布在苍山洱海附近。摆夷民居是以
石块垒成，别局风格。朝花节那天，家家户户都把盆栽花木摆在门口，
摆搭成一座座的『花山』，招引四野乡村的人来观花街。
LONG );
        set("objects", ([
           "/d/dali/npc/oldman": 1,
           "/d/dali/npc/girl1": 2,
        ]));
        set("exits",([ /* sizeof() == 1 */
            "north"  : "/d/dali/dahejieeast",
        ]));
     set("no_fight",0);
	set("coor/x", -19120);
	set("coor/y", -6910);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}