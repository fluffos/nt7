#include <ansi.h>
inherit ROOM;
void create()
{
        set("short", "七曲九回廊");
        set("long",
"这里是七、八十道长廊，相互接连，连绵不绝，直是无穷无尽。每个\n"
"长廊转弯处都有一盏宛如鬼火般摇晃不定的黄灯。廊边的潭水在灯光照射\n"
"下发出墨绿的异光。\n"
);
        set("no_magic", "1");

        setup();
}
int valid_leave(object me, string dir)
{
     if( random(query("kar", me))<15 )
message_vision(GRN"“叮”的一声轻响...一蓬牛毛细针向$N射来。\n"NOR,me);
     if(random(me->query_skill("dodge") / 100) > 10 ) {
     message_vision(RED"只听$N一声惨嚎，细针深深地钉在了$N的身上！\n"NOR,me);
     me->receive_wound("qi",random(me->query_skill("dodge") / 10));
     }
     else
     message_vision(GRN"$N轻松的躲了开去。\n"NOR,me);
     return ::valid_leave(me, dir);
}

