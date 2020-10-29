inherit ROOM;

void create()
{
        set("short", "明廊");
        set("long", @LONG
硫璃瓦铺的一条明廊，地面的地板离开地面三尺，擦洗得很干净。
每隔一段的廊槛上都镂刻了精致的佛像。明廊至此中断，东面过去就
是菜园，南边的空地上也种了几棵菜。北面是个小柴房。
LONG );
        set("no_clean_up", 0);
        set("exits", ([
                  "west" : __DIR__"zoulang",
                  "east" : __DIR__"caidi",
                  "south" : __DIR__"caidi2",
                  "north" : __DIR__"caifang",
        ]));
        set("outdoors", "xiangguosi");

	set("coor/x", -5010);
	set("coor/y", 2210);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}
