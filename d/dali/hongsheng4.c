//Room: /d/dali/hongsheng4.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","宏圣寺塔");
        set("long", @LONG
这里是宏圣寺塔内部，四面墙壁上都辟有佛龛，龛内置佛像。西
面塔壁由模印砖所砌，上面用梵，汉文刻了阴形文的『阿众佛灭正保
咒』。
LONG );
        set("exits",([ /* sizeof() == 1 */
            "down"     : "/d/dali/hongsheng3",
        ]));
        set("no_clean_up", 0);
	set("coor/x", -19151);
	set("coor/y", -6821);
	set("coor/z", 49);
	setup();
        replace_program(ROOM);
}