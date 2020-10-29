inherit ROOM;

void create()
{
        set("short", "中央广场");
        set("long", @LONG
这里是汴梁城中央广场了了，北面就是皇宫正门了，一般的寻常
百姓都不敢到那里去，不过在这里还是相当的热闹，街头卖艺的，唱
戏的都云集于此，形成一大景光。
LONG );
        set("outdoors", "city2");
        set("no_fly",1);

        set("exits", ([
                "north" : __DIR__"ydmen",
                "south" : __DIR__"nandajie2",
        ]));

        set("objects", ([
//                "/d/city2/npc/flowerg" :    1,   
        ]));

        setup();
        replace_program(ROOM);
}
