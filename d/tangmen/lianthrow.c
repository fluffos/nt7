//lianthrow.c                唐门练武场

inherit ROOM;

void init();
int do_lian(string);

void create ()
{
        set ("short", "练武场");
        set ("long", @LONG
这是一个宽敞的练武场。你的身边摆着几个木架，每一个上面又
分成十数个小格，每一格中都放着不同的暗器。你的对面，也就是广
场的那边有几个木人模型，头、脸、耳、鼻都清晰可见，你可以用它
来练习(zhi)唐家称霸江湖的暗器手法。
LONG);
        set("exits", ([
                "south" : __DIR__"nzlange3",
        ]));
        set("outdoors", "tangmen");
        setup();
}

void init()
{
        add_action("do_lian", "zhi");
}

int do_lian(string arg)
{
        object me;
        int jingli_cost;

        me = this_player();

        if ( !arg || ( arg != "biao" ) )
                return notify_fail("你想干什么？\n");

        jingli_cost = (-1) * (5 + random(15));

        if( query("jingli", me) <= (-jingli_cost) )
                return notify_fail("你太疲劳了，没有精力练功了。\n");

        if ( (int)me->query_skill("throwing", 1) < 51 )  
        {
                write("你从木架上拿起一枚暗器，摆好架势向木人掷去，“咄”的一声打歪了！\n但是你对暗器手法又有了一点认识。\n");
                addn("jingli", jingli_cost, me);
                me->improve_skill("throwing",(15+random(query("int", me)/2)));
        }
        else
                if ( (int)me->query_skill("throwing", 1) < 101 )  
                {
                        write("你从木架上捻起一枚暗器，甩手向木人掷去，“咄”的一声打中了！\n你对暗器手法有了一些认识。\n");
                        addn("jingli", jingli_cost, me);
                        me->improve_skill("throwing",(20+random(query("int", me)/2)));
                }
                else
                        write("你随手捻起一枚暗器向木人掷去，“咄”的一声正中眉心！\n你在这里已经学不到什么了！\n");
        return 1;
}