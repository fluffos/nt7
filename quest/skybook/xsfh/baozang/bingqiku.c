
#include <ansi.h>
#include <room.h>
inherit ROOM;
#define QUESTDIR5 "quest/雪山飞狐/宝藏/"
#define JADE    "/d/zhiye/obj/othermaterial" //玉

void create()
{
        set("short",YEL"兵器库"NOR);
        set("long", @long
这里应该是一个练武场或者兵器室，地上散满了乱七八糟的兵器，十之八
九都是古剑，或长逾七尺，或短仅数寸，只是大多铁口斑驳。
long);
        set("exits", ([
                "east" : __DIR__"tiantan",
                "south" : __DIR__"midong3",
                "west" : __DIR__"midong3",
                "north" : __DIR__"midong3",
        ]));
        set("quest", 1);
        set("baozang",1);
        setup();
}
void init()
{
        add_action("do_search", "search"); 
        add_action("do_search", "xunzhao"); 
        add_action("do_search", "dig"); 
}
int do_search(string arg)
{
	object me,obj;
  me = this_player();
	if (me->is_busy() || me->is_fighting())
		      return notify_fail("你正忙着哪！\n");
  message_vision(HIY"$N蹲在地上，四处寻找。\n"NOR, me);
  if(!wizardp(me)) me->start_busy(1);
  if(me->query(QUESTDIR5+"bingqiku")>=2||random(2))
  {
         tell_room(environment(me), me->name() + "找了半天，一不小心踩到了一坨蝙蝠粪便，摔了个仰八叉。\n", ({ me }));
       return notify_fail("你找了半天，什么也没找到。\n");
  }
    me->add(QUESTDIR5+"bingqiku",1);
  obj = new(JADE);
  obj->set_level(3+random(3));
        obj->move(me);
        message_vision(WHT"$N发现一块"+obj->name()+WHT"。\n"NOR, me);
  log_file("quest/FEIHU", sprintf("%s(%s)找到兵器库的宝物%s。经验%d。\n", me->name(1),me->query("id"),obj->query("name"), me->query("combat_exp")) );
  me->start_busy(2);
	return 1;
}
