// This is a room made by wsl.

inherit ROOM;
int do_climb(string arg);
void create()
{
    set("short", "兵马俑");
        set("long", @LONG
来到这里似乎已经无路可走了，左面有个石台，不知是做什么用
的，石台的上方可以看到许多植物的根，盘根错节，有些已经长到了
石台上了。
LONG );
        set("exits", ([
          "south" : __DIR__"shidao5",
]));
    setup();
}
void init()
{
        add_action("do_climb", "climb");
        add_action("do_jump", "jump");
        add_action("do_pa", "爬");
}
int do_climb(string arg)
{
        object me = this_player();
        if( !arg || arg == "" ) return 0;
        if( query_temp("pa", me))return notify_fail("你已经在石台上了，还爬什么呀！\n");
        if( arg == "石台" ) {
                message_vision("$N想都不想，就爬上了去。\n",me);
        set_temp("pa", 1, me);
        return 1;
        }
}
int do_jump(string arg)
{
        object me = this_player();
        if( !query_temp("pa", me))return 0;
        if( !arg || arg == "") return notify_fail("你要跳到什么地方去呀？\n");
        if( query_temp("jump", me))return notify_fail("你已经跳下来了。\n");
        if( arg == "down" ) {
                message_vision("$N提了提气，又跳了下去。\n",me);
        set_temp("jump", 1, me);
        delete_temp("pa", me);
        return 1;
        }
}
int do_pa(string arg)
{
        object me = this_player();
        if( !query_temp("pa", me))return 0;
        if(!arg || arg == "") return notify_fail("你要往那爬？\n");
        if( arg == "根" ) {
                message_vision("$N颤悠悠地爬上了盘在石台上的树根......\n",me);
        delete_temp("pa", me);
        delete_temp("jump", me);
        call_out("go_up", 10 , me );
        return 1;
        }
}
void go_up(object me)
{
        if(!me) return;
        tell_object(me, "你顺着树根爬呀...爬呀......\n你爬了很久，终于你又见到了阳光。\n");
        me->move("/d/changan/caodi.c");
}       