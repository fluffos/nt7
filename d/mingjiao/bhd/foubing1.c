// foubing1.c 冰山
// Modify By River@SJ 99.06
#include <ansi.h>
inherit ROOM;
void create()
{
	set("short",HIW"冰山"NOR);
        set("long", @LONG
这是一块很大浮动冰山，是由万年玄冰组成。由于前面的冰山受
到火山之热，不断的熔化，而产生吸力，把许多浮基不断的吸进，所
以冰山是不断的靠近火山。
LONG );
        set("no_fight", 1);
        set("no_get_from", 1); 
        set("no_sleep_room", 1); 
	set("outdoors","极北");
	setup();
}

void run(object ob)
{
       if(objectp(present(ob, this_object()))){
  	  write(HIW"\n冰山缓缓的向北飘去。\n\n"NOR);
       	  ob->move(__DIR__"foubing2");
       }
}

void init()
{
    if(interactive(this_player())){
          remove_call_out("run");
          call_out("run", 20+random(30), this_player());
    }
}
