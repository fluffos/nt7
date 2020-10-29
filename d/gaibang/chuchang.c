// chuchang shi

inherit ROOM;

void create()
{
        set("short", "储藏室");
        set("long", @LONG
这里是丐帮的储藏室，你可以看见一个个锁着的箱子。周围还悬
挂着一些武器和装备。这时有一位丐帮五袋弟子正闭目养神，看守着
这里。
LONG );
        set("exits", ([
                "west" : __DIR__"mishi",
                "east" : __DIR__"undertre",
        ]));
        set("objects", ([
                "/d/gaibang/npc/5dai" : 1,
                "/d/gaibang/npc/obj/staff" : 3,
                "/clone/weapon/gangdao" : 2,
        ]));
        set("no_clean_up", 0);
        set("coor/x", 10);
        set("coor/y", -10);
        set("coor/z", -30);
        setup();
        replace_program(ROOM);
}