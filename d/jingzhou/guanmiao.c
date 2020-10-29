inherit ROOM;

void create()
{
        set("short", "关圣庙");
        set("long", @LONG
相传关老爷子旧年曾在这里和周仓争关庙首席之位。周仓说提议
谁先跑到庙里，谁就为大。关公答应后，待周仓跑到门口大叫：别占
我的门旮。周仓本是你说不，我偏要之人，往门旮旮一站，关公也就
到前面去了。这些不表，且看这庙里，香火缭绕，长年不断，来进香
的人络绎不绝，也可知关二爷在当地人心中是多英雄的人物。
LONG );
        set("exits", ([
                "south" : __DIR__"xidajie2",
                "north" :__DIR__"houdian",
        ]));
        set("objects", ([
                "/d/beijing/npc/xiangke" : 1,
        ]));
        set("coor/x", -7120);
	set("coor/y", -2040);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}