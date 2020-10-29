// xbkai.c 冰山
// Modify By River@SJ 99.06
#include <ansi.h>
inherit ROOM;
void create()
{
	set("short", HIW"小冰块"NOR);
        set("long", @LONG
这是一块小浮基，能用手划(hua)动它，不远之处就是一块岩石(
yanshi)，从那里可以登上陆地。
LONG );
        set("no_fight", 1);
        set("no_get_from", 1); 
        set("no_sleep_room", 1); 
	set("outdoors","极北");
	setup();
}

void init()
{
        object me, ob, *obj;
        int i;
        me = this_player();
        ob = this_object();
        obj = all_inventory(ob);
        if(!this_player()->query_condition("cold_wind") && !wizardp(me))
        this_player()->apply_condition("cold_wind", 1);
        for(i= 0;i< sizeof(obj);i++){
             if(obj[i]==me ) continue;
             if(obj[i]->is_character()){
                 message_vision(HIR"只见小冰块猛得一震，沉下海去！\n"NOR, ob);
                 obj[i]->unconcious();
                 obj[i]->move(__DIR__"dbshan");
                 me->unconcious();
                 me->move(__DIR__"dbshan");
                 message("vision", "一个昏迷不醒的人被海水冲了上来。\n",environment(me), ({me}) );
             }
        }
        delete("hua_trigger");
	add_action("do_pa","pa");
	add_action("do_hua","hua");
}

int do_hua()
{
      object ob=this_player();
      if(ob->is_busy()) return notify_fail("你正忙着呢。\n");
      if(ob->query_temp("marks/划1")) return notify_fail("你已经划到岩石边了。\n");
      message_vision("$N手脚划动，吃力的向北边的岩石划去。\n",ob);
      ob->start_busy(1);      
      if((int)query("hua_trigger")>=7){
            message_vision("浮冰终于被$N划到达岩石的旁边。\n", ob);
	    delete("hua_trigger");
	    ob->set_temp("marks/划1",1);
            }
      else add("hua_trigger", 1);
      return 1;
}

int do_pa(string arg)
{
	object ob;
	ob=this_player();	
	if (!ob->query_temp("marks/划1"))
		return notify_fail("你现在离岩石还很远呢。\n");
        if (!arg  || arg !="yanshi")
		return notify_fail("你要爬到那里？\n");
	message("vision", ob->name() + "坚难的爬上了岩石。\n", environment(ob), ({ob}));
        ob->move(__DIR__"yanshi");
        message("vision", ob->name() + "从浮冰上爬了上来，浑身上水。\n",environment(ob), ({ob}) );
        EMOTE_D->do_emote(ob,"cold", ob->query("id"));
        EMOTE_D->do_emote(ob,"cold");
        ob->delete_temp("marks/划1");
        ob->start_busy(2);
        return 1;
}
