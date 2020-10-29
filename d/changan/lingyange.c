//Room: lingyange.c

inherit ROOM;

void create()
{
        set("short", "凌烟阁");
        set("long", @LONG
窄窄的门，窄窄的楼梯，布置清雅的房间，窗户都很宽大从窗内
看出去，满城秋色俱在眼前。
LONG );
        set("exits", ([ /* sizeof() == 1 */
                "west" : "/d/changan/fengxu4",
        ]));

        set("coor/x", -10690);
	set("coor/y", 1920);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}