// Modify By River 98/12
#include <ansi.h>
#include <room.h>
inherit ROOM;

void create()
{
	set("short", "荆棘林");
	set("long", @LONG
你信步而行，举步踏到的尽是矮树长草，这里没有路,每走一步，荆棘都
钩刺到小腿,划破你的身体。
LONG
	);
        set("outdoors", "大理");

	set("exits", ([
           "south" : __DIR__"shanlu9",
           "north" : __DIR__"shanlu12",
           "west" : __DIR__"shanlu13",
           "east" : __DIR__"shanlu14",
	]));

	set("coor/x",-300);
  set("coor/y",-270);
   set("coor/z",-20);
   setup();

}

void init()
{    
     object me = this_player();
     if( random(query("kar", me))<10
      && me->query_con() < 30){
       set_temp("last_damage_from", "在森林里筋疲力尽累", me);
       addn("qi", -50, me);
       addn("jingli", -10, me);
       me->receive_wound("jing", 20);
       }
       else{
       addn("qi", -20, me);
       }                   
}