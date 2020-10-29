// Modify By River 98/12
#include <ansi.h>
#include <room.h>
inherit ROOM;

void create()
{
	set("short", "斜坡");
	set("long", @LONG
这里是个斜坡,你小心翼翼的走着,斜坡不算很深,可掉下去决不是闹着玩的,
这里杂草丛生,十分荒凉,地上散着几块骨骸.
LONG
	);
        set("outdoors", "大理");

	set("exits", ([
           "south" : __DIR__"shanlu10",
           "north" : __DIR__"shanlu10",
           "west" : __DIR__"shanlu9",
           "east" : __DIR__"shanlu12",
	]));

	set("coor/x",-290);
  set("coor/y",-260);
   set("coor/z",-20);
   setup();
}

void init()
{
       object me = this_player();
       if( random(query("kar", me))<15
        && me->query_skill("dodge", 1)<100){
         message_vision(HIR"这里是个斜坡，$N不小心，从坡上滑了下来。\n"NOR, me);
         }
       if((int)me->query_skill("dodge", 1) >= 20){
         set_temp("last_damage_from", "从斜坡掉下摔", me);
         me->receive_damage("qi", 35);
         me->receive_wound("qi",  35);
         }
         else {
         set_temp("last_damage_from", "从斜坡掉下摔", me);
         me->die();
         }
}