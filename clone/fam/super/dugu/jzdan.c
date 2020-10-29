#include <ansi.h>
inherit ITEM;
void create()
{
        set_name(HIR "九转丹" NOR, ({"jiuzhuandan"}));
        set_weight(1);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {  
        	set("long", HIC "九转丹乃是神农氏通过九九八十一次炼制而成。\n" + 
        	                "服食(fushi jiuzhuandan)后，15分钟内可额外提升研究效率3%。\n" HIR
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

	if( !query("add_yanjiu_xiaolv15", me) || 
	query("add_yanjiu_xiaolv15", me)-time() <= 0 )
set("add_yanjiu_xiaolv15", time()+900, 		me);
	else
	{
addn("add_yanjiu_xiaolv15", 900, 		me);
	}

	tell_object(me, HIG "恭喜！你服下" + ob->name() + HIG "后，15分钟内研究效率额外提高3%！\n");
	tell_object(me,HIG"目前该效果还剩余时间："+sprintf("%d",query("add_yanjiu_xiaolv15", me))+"秒。\n");
	
	me->save();
	
	destruct(ob);
	
	return 1;
}