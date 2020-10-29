// Room: /testmud/d/changan/gudi.c
// This is a room made by Wsl.

inherit ROOM;
int do_break(string arg);
int do_jump(string arg);
int do_enter(string arg);
void create()
{
        set("short", "谷底");
        set("long", @LONG
头顶几道阳光照在地上，脚下是一片很厚的草地，走在上面软绵
绵的，很是恰意，四周看上去高不可攀，怪石嶙峋，你心中不由一惊，
要不是这片厚厚的草堆垫着，在好的轻功也会摔得变成一堆肉泥。
LONG );
        set("item_desc", ([
        "怪石" : "在嶙峋的怪石中，有块岩石十分光滑，与其他岩石不同。\n", 
])); 

        setup();
}
void init()
{
    add_action("do_break", "break");
    add_action("do_jump", "jump");
    add_action("do_enter", "enter");
}
int do_break(string arg)
{
    int n;
    object me = this_player();
    if( !query_temp("killer", this_player()))return 0;
    if( !arg || arg!="岩石" )
    {
        write("你要震碎什么！\n");
        return 1;
    }
    if (query("break"))
        return notify_fail("岩石已被打破了。\n");
    n=query("neili", me);
    if (n >= 40000)
    {
        message_vision("$N气运丹田，双掌直向前方打出一道劲力。\n", this_player());
        message_vision("只见被$N打碎的岩石四出飞溅，中间的一块巨岩承受不了震动，\n", this_player());
        message_vision("掉落在草地上，发出巨大的响声。你惊喜的发现在岩石上方出现了一个洞。\n", this_player());
        set("break",1);
        set("neili", n-5000, this_player());
        remove_call_out("close");
        call_out("close", 5, me);
    }
    else
    {
        message_vision("结果只听一声闷哼，$N被自己的内力震得眼前一黑....\n", this_player());
        set("neili", 0, this_player());
        this_player()->unconcious();
    }
    return 1;
}
int do_jump(string arg)
{
        object me;
        me = this_player();
        if(!query("break")) return 0;
        if( query_temp("climb", me) )
                return notify_fail("你已经站在岩石上了。\n");
        if( !arg || arg!="碎岩" )
        {
        write("你想爬到什么地方去？\n");
        return 1;
        }
        if ((int)me->query_skill("dodge",1) > 800 ) {
                message_vision("$N一个纵身，跳上了岩石。\n", me);
                set_temp("climb", 1, me);
        }else{
                message_vision("$N施展轻功，向上跳去，但却怎么也跳不上去。\n", me);
        }
        return 1;
}
int do_enter(string arg)
{
        object me;
        me = this_player();
        if( !query_temp("climb", me))return 0;
        if( !arg || arg!="岩洞" )
        {
        write("你想去那啊？\n");
        return 1;
        }
        message_vision("$N躬了躬身体，钻进了岩洞里。\n", me);
        me->move("/d/qinhuang/mudong0.c");
        message_vision("“隆隆”，洞口已经封死了。\n", me);
        return 1;
}

void close(object me)
{
    if (me)
        delete_temp("climb", me);
    message("vision","上面几块岩石掉了下来，把洞口又封住了。\n", this_object());
    delete("break");
}
