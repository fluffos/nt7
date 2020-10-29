// This program is a part of NT MudLIB

inherit RIVER;

void create()
{
        set("short", "汉水南岸");
        set("long", @LONG
面前是一条波涛翻滚的大江 (river)。浊流滚滚，万舟竞发。两岸
渡船来来往往，江边一长溜摆满了鱼摊，渔家就将船泊在岸边，几个破
箩筐支一块木板，板上摆满了活蹦乱跳的汉江鲤鱼。过去不远，是有名
的老河口，不少过江客都在这里等待渡船摆渡。
LONG );
        set("outdoors", "nanyang");
        set("region", "nanyang_zone");
        set("to",__DIR__"hanshui2");

        set("exits", ([
                "south" : __DIR__"yidao2",
        ]));

        set("objects", ([
                __DIR__"npc/chuanfu1" : 1,
        ]));

        set("resource/fish", ({ "/clone/fish/liyu",
                                "/clone/fish/jiyu",
                                "/clone/fish/qingyu",
                                "/clone/fish/caoyu", }));

        set("no_clean_up", 0);

        set("coor/x", 0);
	set("coor/y", 70);
	set("coor/z", 0);
	setup();
        replace_program(RIVER);
}
