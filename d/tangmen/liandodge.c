//liandodge.c                唐门练武场

inherit ROOM;

void init();
int do_lian(string);

void create ()
{
        set ("short", "练武场");
        set ("long", @LONG
这是一个宽敞的练武场。你的面前的场子上立满了一根根木桩，
几个唐门弟子正在上面施展轻功身法，飞快的四处游走，但不时也
有几个摔了下来，弄的鼻青脸肿。你要不怕就也上去练练 (yue)基
本的轻功身法吧。
LONG);

        set("exits", ([
                "north" : __DIR__"nzlange3",
        ]));
        set("outdoors", "tangmen");
        setup();
}

void init()
{
        add_action("do_lian", "yue");
}

int do_lian(string arg)
{
        object me;
        int jingli_cost;

        me = this_player();

        if ( !arg || ( arg != "zhuang" ) )
                return notify_fail("你想干什么？\n");

        jingli_cost = (-1) * (5 + random(15));

        if( query("jingli", me) <= (-jingli_cost) )
                return notify_fail("你太疲劳了，没有精力练功了。\n");

        if ( (int)me->query_skill("dodge", 1) < 51 )  
        {
                write("你气运丹田，轻轻一纵身跳上一根较矮的木桩，但是脚下一晃摔了下来！\n不过你对轻功身法有了一点了解。\n");
                addn("jingli", jingli_cost, me);
                me->improve_skill("dodge",(15+random(query("int", me)/2)));
        }
        else
                if ( (int)me->query_skill("dodge", 1) < 101 )  
                {
                        write("你气随心升，一晃身跃上一根木桩，只是感到内息略有阻滞！\n你对轻功身法有了一些认识。\n");
                        addn("jingli", jingli_cost, me);
                        me->improve_skill("dodge",(20+random(query("int", me)/2)));
                }
                else
                        write("你随意的在木桩上飞奔跳跃，感到已经没有困难。\n你在这里已经学不到什么了！\n");
        return 1;
}