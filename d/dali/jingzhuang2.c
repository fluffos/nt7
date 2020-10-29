//Room: /d/dali/jingzhuang2.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","第二层");
        set("long", @LONG
为四神坐像，各有表情，衣褶隆起，筋节毕现，肌肉暴起，极富
立体感。
LONG );
        set("outdoors", "dalic");
        set("exits",([ /* sizeof() == 1 */
            "up"    : "/d/dali/jingzhuang3",
            "down"  : "/d/dali/jingzhuang1",
        ]));
        set("no_clean_up", 0);
	set("coor/x", -19091);
	set("coor/y", -6871);
	set("coor/z", 19);
	setup();
        replace_program(ROOM);
}