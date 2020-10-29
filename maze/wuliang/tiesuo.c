// Room: tiesuo.c
// By River 98/12
#include <ansi.h>
inherit ROOM;
void create()
{
        set("short", "铁索桥");
        set("long", @LONG
铁索桥共是四条铁索，两条在下，上铺木板，以供行走，两条在旁作为扶
手。一踏上桥，几条铁索便即幌动，行到江心，铁索晃得更加厉害，一瞥眼间，
但见江水荡荡，激起无数泡沫，如快马奔腾般从脚底飞过，只要一个失足，卷
入江水，任你多好的水性也难活命。 
LONG
        );
        set("exits", ([
            "north" : __DIR__"hslin",
            "south" : __DIR__"jiangan",
        ]));       
        set("outdoors", "大理");
        set("coor/x",-280);
  set("coor/y",-280);
   set("coor/z",-20);
   setup(); 
}

void init()
{
        object me=this_player();
        if ( me->query_skill("dodge", 1) < random(50)){
        me->start_busy(2);
        set_temp("last_damage_from", "坠入江中淹", me);
        message_vision(HIR"$N脚下一个不稳，把持不住，摔入滚滚翻腾的澜沧江内。\n"NOR,me);
        me->unconcious();
//        me->move("/d/death/relax");
        me->die();
        }       
}