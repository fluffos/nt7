//Room: /d/dali/yanchi2.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","沿池堤岸");
        set("long", @LONG
滇池风景怡人，沿堤岸漫步，遵堤行湖中，堤南北皆碧水。盖其
碧波即草海之余，南连于滇池，北抵黄土坡，西濒与赤鼻山之簏。东
行湖中，遥顾四周山色，掩映重波间，青蒲偃水，高柳潆堤，天然绝
胜。
LONG );
        set("outdoors", "dalic");
        set("exits",([ /* sizeof() == 1 */
            "westdown" : "/d/dali/yanchi1",
            "east"     : "/d/dali/yanchi3",
        ]));
        set("no_clean_up", 0);
	set("coor/x", -19090);
	set("coor/y", -6860);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}