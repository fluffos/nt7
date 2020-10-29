//didao4.c                四川唐门—地道

inherit ROOM;

void create()
{
        set("short", "地道");
        set("long",
"这是一条地道。但是它却并不是一条普通的地道，这里极宽敞足可以\n"
"有几十人在这里舞龙戏狮。这里亮如白昼，但是你却无法找到这光亮的来\n"
"源，地道向前延伸不知通向何处。你的心中升起一股莫名的恐惧，还是离\n"
"开的好。\n"
);
        set("exits", ([
                        "northup" : __DIR__"didao3",
                        "south" : __DIR__"andao1",
        ]));
        set("area", "tangmen");
        setup();
}

void init()
{
        object me, killer;
        me = this_player();

        if ( wizardp(me) )
                return;

        if( (query("family/family_name", me) == "唐门世家") && query("family/master_id", me) == "tanglyz" )
                return;
        else
        {
                if ( userp(me) )
                {
                        message_vision("突然从石壁中传来一声大喝:“擅闯禁地者，死！！！\n", me);
                        message_vision("光滑的石壁上出现了一个石门，一名唐门死士跃了出来，向$N发动进攻！！！\n", me);
                        killer = new("/d/tangmen/npc/killer");
                        killer->move(environment(me));
                        killer->kill_ob(me);
                        me->fight_ob(killer);
                }
        }
        return;
}

int valid_leave(object me, string dir)
{
        me = this_player();

        if ( ((dir == "southdown")||(dir == "northup")) && objectp(present("killer", environment(me))) )
        {
                message_vision("死士一闪身将你拦了下来：想走？没那么容易！！！\n", me);
                return notify_fail("\n");
        }
        return ::valid_leave(me, dir);
}