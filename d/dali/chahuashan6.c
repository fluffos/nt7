//Room: /d/dali/chahuashan6.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","茶花山南");
        set("long", @LONG
这儿是茶花山的南面，仍然有大量的茶花盛开着。但显然不如山
上的品种好了，都是凡品。
LONG );
        set("outdoors", "dalic");
        set("exits",([ /* sizeof() == 1 */
            "westup"     : "/d/dali/chahuashan5",
            "southeast"  : "/d/dali/dadieshui",
        ]));
        set("no_clean_up", 0);
	set("coor/x", -19120);
	set("coor/y", -6860);
	set("coor/z", 20);
	setup();
        replace_program(ROOM);
}