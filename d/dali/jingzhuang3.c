//Room: /d/dali/jingzhuang3.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","第三层");
        set("long", @LONG
雕绕绫坐像四座，坐像间之四面各雕佛及菩萨一组。识者谓北面
多臂观音，南面为地藏菩萨。合神佛面目和蔼，雕刻精细，造形优美。
LONG );
        set("outdoors", "dalic");
        set("exits",([ /* sizeof() == 1 */
            "up"    : "/d/dali/jingzhuang4",
            "down"  : "/d/dali/jingzhuang2",
        ]));
        set("no_clean_up", 0);
	set("coor/x", -19091);
	set("coor/y", -6871);
	set("coor/z", 29);
	setup();
        replace_program(ROOM);
}