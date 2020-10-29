// modified by snowman.  检查是否busy或 fighting

#include <room.h>
#include <ansi.h>
inherit ROOM;

void create()
{
	set("short", HIY"无心井"NOR);
	set("long", @LONG
这是一口千年古井，井旁是用青石砌成的井台，上面是用生铁铸
就的一个高一尺的井缘。井内深达十几米，水面上漂满了落叶。井旁
杂草丛生，井边的轱辘架也早就朽了，显然很久没人用了，奇怪的是
井边的石板居然十分光滑。
LONG);
	set("exits", ([
		"west" : __DIR__"bzqn",
	]));

        set("resource/water",1); 
	set("outdoors", "天龙寺");
	set("coor/x",-380);
  set("coor/y",-270);
   set("coor/z",30);
   setup();
}
void init()
{
        add_action("do_tiao", "tiao");  
}

int do_tiao(string arg)
{
	object me=this_player();
	object weapon = me->query_temp("weapon");

        if ( !arg || (arg != "leaf") )
		return notify_fail("你要挑什么？\n");
         
        if( me->is_busy() || me->is_fighting() ) return notify_fail("你正忙着呢。\n");
        if (!weapon || weapon->query("skill_type") != "sword" )
		return notify_fail("你要用手把树叶挑出来？\n");

        if ((int)me->query_skill("sword", 1) < 30 )
          return notify_fail("你满头大汗的挑了半天，连一片页子也没碰着，还是干脆用手拿吧。\n");

        if ((int)me->query_skill("sword", 1) >100 )
        return notify_fail("你“唰唰”几剑就把所有的落叶都挑出了井外。\n");
    
	me->receive_damage("jingli", random(40));
        write("你不断用剑把落叶挑出井外，落叶随水漂来漂去，你对剑术有了新的认识。\n");
         me->improve_skill("sword", me->query("int"));       
         return 1;
}                                     
