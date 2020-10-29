#include <ansi.h>
inherit ITEM;
void create()
{
        set_name(HIG "百龙丹" NOR, ({"bailong dan"}));
        set_weight(1);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {  
        	set("long", HIC "百龙丹乃使用数百条龙血炼化而成！\n" + 
        	                "服食(fushi bailongdan)后可永久提升读书写字1级。\n" HIR
        	                "拥有者：拥有者ID\n" NOR);
                set("unit", "颗");
                set("owner", "拥有者ID"); // 绑定拥有者
	        set("no_drop", 1);set("no_give", 1);set("no_store", 1);set("no_sell", 1);
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

	if (ob->query("owner") != me->query("id"))
		return notify_fail(ob->name() + NOR "已经于其他玩家绑定！\n");
	
	me->set_skill("literate", me->query_skill("literate", 1) + 1);

	tell_object(me, HIG "恭喜！你服下" + ob->name() + HIG "后，读书写字提升1级！\n");
	
	log_file("super/"+ filter_color(query("name")) , me->query("id") + " at " + ctime(time()) + " 使用" + ob->name() + "。\n");
	
	me->save();
	
	destruct(ob);
	
	return 1;
}
int query_autoload()
{
	return 1;
}