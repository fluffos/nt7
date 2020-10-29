inherit ROOM;

void create()
{
        set("short", "素斋厅");
        set("long", @LONG
这是寺庙中的大小僧人用餐的地方，当然方丈的素斋是专门有人
送过去的，平时相国寺的僧人听钟吃饭，等他们吃完了也经常把剩下
的素斋舍给穷人吃。逢塑望，十五也经常作些斋席请大施主，高官富
贵们品尝，所以素斋厨的僧人是最忙的。
LONG );
        set("exits", ([
                  "north" : __DIR__"chufang2",
                  "west" : __DIR__"zhongyuan",
        ]));

        set("no_clean_up", 0);
        set("objects", ([
                  __DIR__"npc/liucaizhu" : 1,
                  __DIR__"npc/kong" : 1,
        ]));

	set("coor/x", -5030);
	set("coor/y", 2200);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}