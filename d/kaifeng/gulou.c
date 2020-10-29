inherit ROOM;

void create()
{
        set("short", "鼓楼");
        set("long", @LONG
一座木结构的小亭阁楼，上层摆了个大鼓，是寺庙内每天晨钟暮
鼓时所用。有一条小楼梯通向下层。阁楼的四角挂着铁马，随风摆摇
着，分外动听。
LONG );
        set("no_clean_up", 0);
        set("exits", ([
                  "west" : __DIR__"qianyuan",
        ]));

	set("coor/x", -5030);
	set("coor/y", 2180);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}
