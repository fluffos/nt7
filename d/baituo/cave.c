inherit ROOM;

void create()
{
        set("short", "岩洞");
        set("long", @LONG
这里是一个大岩洞，在白驼山特殊的地质条件下经过漫长的年代
形成的。洞内蜿蜒曲折，也不知延伸到了何处。
LONG );
        set("exits", ([
                "enter"     : __DIR__"cave1",
                "southdown" : __DIR__"zhulin",
        ]));
        set("objects", ([
                "/clone/beast/mangshe" : 1,
        ]));
        set("outdoors", "baituo");
        set("coor/x", -50000);
        set("coor/y", 20050);
        set("coor/z", 40);
        setup();
}

int valid_leave(object me, string dir)
{
        if (dir == "enter"
           && objectp(present("mang she", environment(me))))
                        return notify_fail("蟒蛇盘在岩洞口，将路封了个严实。\n");

        return ::valid_leave(me, dir);
}