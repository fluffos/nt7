#include <ansi.h>
inherit ITEM;
void create()
{
        set_name(HIR "火灵芝" NOR, ({"huolingzhi"}));
        set_weight(1);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {  
        	set("long", HIC "火灵芝生长于新疆最酷热的地下深处，吸收了大地之气！\n" + 
        	                "服食(fushi huolingzhi)后可永久提升内力上限10点。\n" HIC
        	                /*"拥有者：拥有者ID*/"\n" NOR);
                set("unit", "颗");
                set("owner", "拥有者ID"); // 绑定拥有者
	        set("no_drop", 1);set("no_store", 1);set("no_sell", 1);
        }
        setup();
}

void init()
{
        add_action("do_use", "fushi");       
}

int do_use(string arg)
{
	object ob, me;
	
	me = this_player();

	if (! arg || arg != query("id"))
		return notify_fail("你要服食什么？\n");

	if (! objectp(ob = present(arg, me)))
		return notify_fail("你身上没有这个东西！\n");
/*
	if( query("owner", ob) != query("id", me) )
		return notify_fail(ob->name() + NOR "已经于其他玩家绑定！\n");
*/	
  addn("drug/neili", 10, me);

	tell_object(me, HIG "恭喜！你服下" + ob->name() + HIG "后，提升内力上限10点！\n");
	
	me->save();
	
	destruct(ob);
	
	return 1;
}