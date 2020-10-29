inherit ROOM;

void create()
{
        set("short", "御马监");
        set("long", @LONG
这里是汴梁城皇宫内的御马监，饲养着各地进贡来的名马，几个
太监在忙着给马梳洗，清理草料。
LONG );
        set("indo0rs", "city2");
        set("no_fly",1);

        set("exits", ([
                "east" : __DIR__"hgdadao6",
        ]));

        set("objects", ([
                __DIR__"npc/zyma" :    1,
        ]));
                       
        setup();
}       

void init()
{
        object me = this_player();
        object ma;
        if (interactive(me) && me == WAR_D->query_marshal())
        {
                if (! objectp(ma = present("shizi ma", me))
                &&  ! objectp(ma = present("shizi ma", environment(me))))
                {
                        ma = new("/maze/battle3/npc/zyma");
                        ma->move(environment(me));
                }
        }
}
