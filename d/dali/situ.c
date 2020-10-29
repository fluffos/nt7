//Room: /d/dali/situ.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","司徒堂");
        set("long", @LONG
这里是大理国司徒堂。大理君臣勤政爱民，三公劳作自不带言。
堂内无余物，奇怪的是地上角落还摆了些铁铲，孔明灯之类的物事。
LONG );
        set("objects", ([
            CLASS_D("dali")+"/huahegen" : 1,
        ]));
        set("exits",([ /* sizeof() == 1 */
            "east"  : "/d/dali/zonglichu",
        ]));
	set("coor/x", -19131);
	set("coor/y", -6851);
	set("coor/z", -1);
	setup();
        replace_program(ROOM);
}