//Room: /d/dali/heisenlin.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","黑森林");
        set("long", @LONG
迎面一大片黑压压的森林，高大的古松参天而立。左首一排九株
大松树，看起来有些特别。
LONG );
// 万劫谷 here.
// wait to be done in future.
        set("outdoors", "dalic");
        set("exits",([ /* sizeof() == 1 */
            "south"      : "/d/dali/dasenlin",
            "northeast"  : "/d/kunming/htroad3", 
        ]));
        set("no_clean_up", 0);
	set("coor/x", -19080);
	set("coor/y", -6840);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}