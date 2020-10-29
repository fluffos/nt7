// This program is a part of NT MudLIB

inherit ROOM;

void create ()
{
        set ("short", "大厅");
        set ("long", @LONG
这是万家为庆祝老爷子五十大寿布置的大厅，前来拜寿的客人已陆
续就座，几个丫鬟仆人正忙着端茶送水，大厅上一个身形魁梧的老者正
在和众宾客周旋。
LONG);
        set("region", "jingzhou");
        set("exits", ([
                "south"  : __DIR__"wan_damen",
                "north"  : __DIR__"wan_zoulang",
                "east"   : __DIR__"wan_donglou",
                "west"   : __DIR__"wan_xilou",
        ]));
        set("objects", ([
                __DIR__"npc/wanzhenshan" : 1,
                __DIR__"npc/lvtong"      : 1,
                __DIR__"npc/lukun"       : 1,
                __DIR__"npc/zhouqi"      : 1,
        ]));

        set("coor/x", -7110);
	set("coor/y", -2030);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}