inherit ROOM;

void create()
{
        set("short", "般若台");
        set("long", @LONG
这是个普通的石台，相传当年佛祖曾降临此台传法。再往南去就
是本寺重地——牟尼堂。江湖中传言天龙寺的镇寺之宝——六脉神剑
谱就藏于此中。
LONG );
        set("exits", ([
                "south" : __DIR__"munitang",
                "north" : __DIR__"doushuai",
        ]));
        setup();
}

string long()
{
        if (! stringp(query("exits/south")))
                return query("long") + "    奇怪的是大门紧"
                       "闭，不知道里面怎么回事。\n";

        return query("long");
}

int valid_leave(object me, string dir)
{
        if (me->query_condition("killer") && dir == "south")
                return notify_fail("那里PKER不能进去。\n");

        return ::valid_leave(me, dir);
}