// Room: /tangmen/bdajie2.c

inherit ROOM;

void create()
{
        set("short", "北大街");
        set("long",
"一条笔直的大理石街道，直通北门，两边没有什么店铺，只有你孤独\n"
"的影子伴随着你。此处一走就可闯荡江湖了，没有牵挂的你会一路平安吗！\n"
"你要自己多多小心了。一路保重！\n"
);
        set("outdoors", "tangmen");
        set("no_clean_up", 0);
        set("exits", ([
                "north" : "/d/xuedao/sroad1",
                "south" : __DIR__"bdajie1",
        ]));

        setup();
        replace_program(ROOM);
}
