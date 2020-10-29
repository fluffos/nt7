//HSQTAN1.C

inherit ROOM;

void create()
{
        set("short", "深潭");
        set("long", @LONG
这里是瀑布下的寒潭，水中幽暗无比，四周似乎有几处出口，但
实在看不清是通向何处。水中冰冷刺骨，令人难以忍受，你只觉得气
力在一点一点消失。
LONG );
        set("exits", ([
                "east" : __DIR__"hsqtan1",
                "west" : __DIR__"hsqtan1",
                "south" :__DIR__"hsqtan1",
                "north" :__DIR__"hsqtan2",
        ]));
        set("no_clean_up", 0);
        setup();
}

void init()
{
        object me;
        int meqi,meneili,decqi,mq;
        me=this_player();
        meqi=query("qi", me);
        meneili=query("neili", me);
        mq=query("max_qi", me);
        decqi=(int)(mq/(random(4)+5+meneili/200));
        meqi=meqi-decqi;
        set("neili", 0, me);
        if( meqi>0)set("qi", meqi, me);
        else me->die();
}
