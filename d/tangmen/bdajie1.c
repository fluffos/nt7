// Room: /tangmen/bdajie1.c

inherit ROOM;

void create()
{
        set("short", "北大街");
        set("long",
"一条笔直的大理石街道，两边的店铺可是好地方。东边不时地传来小\n"
"二吆喝声：买了、买了、快来买了。让你忍不住想进去看看。西边只不停\n"
"的传来马嘶声，你想那边会是什么啊？对了，就是驿站了！能去很多的地\n"
"方啊。\n"
);
        set("outdoors", "tangmen");
        set("no_clean_up", 0);
        set("exits", ([
                "east"  : __DIR__"kedian",
                "south" : __DIR__"zhongxin",
                "west"  : __DIR__"tmyizhan",
                "north" : __DIR__"bdajie2",
        ]));

        setup();
        replace_program(ROOM);
}
