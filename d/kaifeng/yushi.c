inherit ROOM;

void create()
{
        set("short", "浴室");
        set("long", @LONG
每年的五月初五日，寺中都会用清水清洗那些佛像。称为洗佛。
用洗佛的残水从人的头顶浇灌而下，称沐佛恩。虽然水很脏，但大家
都抢了来淋水。当然达官贵人是不会当众狼狈的所以里面辟有专门的
小浴室供他们使用。
LONG );
        set("objects", ([
                __DIR__"npc/zhangzao" : 1,
        ]));
        set("no_clean_up", 0);
        set("exits", ([
                "east" : __DIR__"zhongyuan",
                "west" : __DIR__"yushi2",
        ]));

	set("coor/x", -5050);
	set("coor/y", 2200);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}