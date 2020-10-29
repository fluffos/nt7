#include <ansi.h>
inherit ITEM;
void create()
{
        set_name(HIW "天灵丹" NOR, ({"tianlingdan"}));
        set_weight(1);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {  
        	set("long", HIC "传说此丹乃昆仑上中仙人花费七七四十九天炼制而成。\n" + 
        	                "服食(fushi tianlingdan)后，15分钟内可额外提升汲取效率3%。\n" HIR
        	                /*"拥有者：拥有者ID*/"\n" NOR);
                set("unit", "颗");
                set("owner", "拥有者ID"); // 绑定拥有者
	        set("no_drop", 1);set("no_store", 1);set("no_sell", 1);
        }
        setup();
}

/*
void init()
{
        add_action("do_use", "fushi");       
}
*/

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

	if( !query("add_jiqu_xiaolv15", me) || 
	query("add_jiqu_xiaolv15", me)-time() <= 0 )
set("add_jiqu_xiaolv15", time()+900, 		me);
	else
	{
addn("add_jiqu_xiaolv15", 900, 		me);
	}

	tell_object(me, HIG "恭喜！你服下" + ob->name() + HIG "后，15分钟内研究次数额外提高汲取效率3%！\n");
	tell_object(me,HIG"目前该效果还剩余时间："+sprintf("%d",query("add_jiqu_xiaolv15", me))+"秒。\n");
	
	me->save();
	
	destruct(ob);
	
	return 1;
}