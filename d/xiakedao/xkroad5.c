inherit ROOM;

void create()
{
        set("short", "渔村晒网场");
        set("long", @LONG
小村不大，却有个好大的晒网场。几个小孩在场中无忧地玩耍，
声音喧闹。靠南海边上，有个渔夫面向大海，悠然垂钓。
LONG );
        set("outdoors", "nanhai");
        set("exits", ([
                "north"   : __DIR__"xkroad6",
		"south"   : __DIR__"xkroad5-south",
		"east"    : __DIR__"xkroad5-east",
                "west"    : __DIR__"xkroad4",
        ]));
        set("objects", ([
                __DIR__"npc/boy": 1,
                __DIR__"npc/girl": 1,
                __DIR__"npc/yufu": 1,
                CLASS_D("misc/haigui") : 1,
        ]));
        set("no_pk", 1);
        set("coor/x", -1390);
        set("coor/y", -9000);
        set("coor/z", 0);
        setup();
}

void init()
{
        MYGIFT_D->check_mygift(this_player(), "newbie_mygift/haigui");
}

int valid_leave(object me, string dir)
{
        if (dir == "east" || dir == "south")
        {
                if (! userp(me))
                        return 0;
        }

        return 1;
}

