inherit ROOM;
 
void create()
{
        set("short", "草地");
        set("long", @LONG
你走在一片草地。草地西边似乎香气四溢，东边好象是一个小花
园。
LONG );
        set("exits", ([
            "west"   : __DIR__"chufang1",
            "east"   : __DIR__"hua1",
             "north" :__DIR__"dating1",
             "south" :__DIR__"grass1",
        ]));
        set("objects", ([
                __DIR__"npc/shinu" : 1,
        ]));
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}