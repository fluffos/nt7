inherit ROOM;
#include <ansi.h> 
void create()
{
        set("short", "龙潭入口");
        set("long",
"[1;32m前方就是龙潭，进去前请三思。如果到此止步，还来得及。\n"
"如要回头，请键入back。在西面，有一个向下的通道，看来似乎相当深。\n"
);

        set("exits", ([ 
              "north" : __DIR__"dragoncave", 
              "westdown" : __DIR__"spirit7", 
           ]));

        set("no_magic", 1);
        setup();
}

void init()
{
        add_action("do_back", "back");
}

int do_back(object me)
{
        me=this_player();
        message_vision(HIC"$N的身影消失在一阵光芒中。\n"NOR,me); 
        set_temp("mark/diary", 0, me);
        set_temp("m_success/初级", 0, me);
        set_temp("m_success/幻影", 0, me);
        set_temp("m_success/孽龙", 0, me);
        me->move("/d/city/wumiao");
        return 1;
}
