inherit ROOM;

void create()
{
        set("short", "衡阳西街");
        set("long", @LONG
你走在碎石铺就的狭小街道上。只见街上时常有人持剑疾行，似
乎这里出了啥事了。南边是一家小店，北面一座大宇巍峨，重檐叠瓦，
 门口彩灯高悬，管家家丁好象都是武林中人。
LONG );
        set("outdoors", "hengyang");

        set("exits", ([
               "east"   : __DIR__"hengyang",
               "west"   : __DIR__"hengyang11",
               "south"  : __DIR__"shop",
               "north"  : __DIR__"liufugate",
        ]));

        set("no_clean_up", 0);

	set("coor/x", -6900);
	set("coor/y", -5700);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
