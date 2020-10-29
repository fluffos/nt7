// foubing2.c 冰山
// Modify By River@SJ 99.06
#include <ansi.h>
inherit ROOM;
void create()
{
	set("short",HIW"冰山"NOR);
        set("long", @LONG
这是一块很大浮动冰山，是由万年玄冰组成。由于前面的冰山受
到火山之热，不断的熔化，这时反而随着冰山熔化成暖水一冲又向南
飘，这时你看到不远之处有一块小基块(bing)，可能可以当船用，向
岛划动。
LONG );
        set("no_fight", 1);
        set("no_get_from", 1); 
        set("no_sleep_room", 1); 
        set("outdoors","极北");
	setup();
}

void init()
{
    if(interactive(this_player())){
         remove_call_out("run");
         call_out("run", 20+random(30));
    }
    add_action("do_jump","jump");
}

int do_jump(string arg)
{
	object me=this_player();
	if (!arg) return 0;
	if (arg=="bing" || arg== "小冰块"){
            message("vision", me->name() + "张手抱向小冰块， 扑通一声跳入海中。\n",environment(me), ({me}) );
       	    me->move(__DIR__"xbkai");
            message("vision", me->name() + "狼狼狈狈的跳了过来，双手抱向小冰块。\n",environment(me), ({me}) );
            return 1;
        }
        return 0;
}

void run()
{
     object *obj;
     int i;
     obj = all_inventory(this_object());
     for(i=0; i<sizeof(obj); i++){ 
        tell_object(obj[i],HIW"\n冰山随着海水暖流向南飘离。\n\n"NOR);
       	obj[i]->move(__DIR__"dbshan");
     }
}
