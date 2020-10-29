inherit ROOM;

void create()
{
        set("short", "庭院");
        set("long", @LONG
这是一个不大的庭院，庭院的中央有一条碎石铺成的小路，
四周种着几株小树。西面是一间宽大的正厅，南面是出售
药材及成药的南厅，北面是药铺帐房的北厅。
LONG );

        set("no_fight", 1);
        set("exits", ([
                "north" : __DIR__"beiting",
                "south" : __DIR__"nanting",
                "west" : __DIR__"zhengting",
                "east" : __DIR__"huichun",
        ]));
        set("objects", ([
                __DIR__"npc/zhanggui" : 1,
        ]));
        set("outdoors", "yaowang");
        setup();
        replace_program(ROOM);
}
