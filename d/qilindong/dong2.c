// Room: dong2.c

#include <ansi.h>
inherit ROOM;

void create()
{
	set("short", HIR "麒麟窟" NOR);
        set("long", HIR "\n\n" 
"这是麒麟窟。进来顿觉一股热浪扑面而来，冲得你差点晕了\n"
"过去。四周一片通红，地面上冒着丝丝白气，脚底剧烈的炙痛\n"
"使你几乎立脚不住。热风带着隆隆巨响冲击着耳鼓，令你觉得\n"
"置身洪炉之中，全身的水分都在被一滴滴地烤干。你感到生命\n" 
"正离你而去·！\n\n" NOR 
     ); 
        set("exits", ([
                "east"      : __DIR__"dong1",
                "south"     : __DIR__"dong2",
                "west"      : __DIR__"dong1",
                "north"     : __DIR__"dong3",
	]));
	setup();
}

void init()
{
        object me = this_player();

        me->set_temp("die_reason", "闯入麒麟窟，被烈炎烧死了");
        me->receive_damage("qi", 500);
        me->receive_wound("qi",  500);
        message_vision(HIR "四周烈火熊熊，烈炎袭向$N将$N遍体灼伤！\n" NOR, me);
}

