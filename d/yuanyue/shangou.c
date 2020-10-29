// This program is a part of NITAN MudLIB

#include <ansi.h>
inherit ROOM;

int do_jump(string arg);
void create()
{
        set("short", "山沟"); 
        set("long", @LONG
这里是圆月山庄后园的一个山沟，旁边是一片密密的松木林，四
周一片寂静。
LONG);
        set("outdoors", "wansong");
        set("type","forest");
        set("exits",([
                "east":__DIR__"senling4",
        ]) );
        
        set("coor/x",-630);
        set("coor/y",250);
        set("coor/z",90);
        setup();
}   

void init() 
{ 
        if (NATURE_D->query_month() == 7 &&
            NATURE_D->query_day() == 15 || query("mojiao/715", this_player()))
        {
                add_action("do_jump", "jump");
        }
}

string long() 
{
        string msg; 
       
        msg = query("long"); 
 
        if (NATURE_D->query_month() == 7 &&
            NATURE_D->query_day() == 15)
                msg += HIW "山沟中的洪水滚滚而过，气势非凡，你见此情形顿时有想要跳入洪水中(jump hongshui)的冲动。" NOR;
        
        return sort_string(msg, 60, 4); 
}

int do_jump(string arg)
{
        object me = this_player();

        if (! arg || (arg != "hongshui" && arg != "shangou"))
                return notify_fail("你想跳入什么？\n");

        message_vision(HIW "$N" HIW "纵身跳入山沟中的滚滚洪水之中，顿时没有了身影。\n" NOR, me);        

        tell_object(me, HIW "山沟中的洪水太急，一股劲浪打来，你顿时晕了过去。\n" NOR);        
        
        me->unconcious(); 
        me->move(__DIR__"hole");
        if( !query("mojiao/715", me) ) set("mojiao/715", me);
        return 1;
}
