inherit ROOM;

void create()
{
        set("short", "草棚");
        set("long", @LONG
这是峨嵋山脚下一个简单的草棚，地上堆著些上货。很多上山的
游客都在这里买些上山用品。草棚后有个口井，西面是间简陋的马厩。
LONG );
        set("outdoors", "emei");
        set("objects", ([
                __DIR__"npc/xiao-fan": 1,
        ]));
        set("exits", ([
                "west" : __DIR__"majiu1",
                "east" : __DIR__"qsjie2",
        ]));
        set("coor/x", -380);
        set("coor/y", -200);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}