// Room: /tangmen/edajie.c
 

inherit ROOM;

void create()
{
        set("short", "东大街");
        set("long",
"这是一条宽阔的青石板街道，北边是一个铺子，里面的老板是唐门的\n"
"中人，买一些个杂物。南边是一个银号，据说是蜀中最老的钱庄了，而且\n"
"信誉不一般啊，很多中原来的商人都把钱存在这儿。\n"
);
        set("outdoors", "tangmen");
        set("no_clean_up", 0);
        set("exits", ([
                "west" : __DIR__"zhongxin",
                "south" : __DIR__"tsqianz",
                "north" : __DIR__"tjpuzi",
        ]));

        setup();
        replace_program(ROOM);
}
