#include <ansi.h>
inherit ITEM;
void create()
{
        set_name(HIY "元神五行丹" NOR, ({"yuanshenwuxingdan"}));
        set_weight(1);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {  
        	set("long", HIY "使用（changewx 五行）元神五行丹后可指定更换元神五行属性一次。\n" + HIC
        			"拥有者：拥有者ID\n" NOR);
                set("unit", "颗");
                set("owner", "拥有者ID"); // 绑定拥有者
	        set("no_drop", 1);set("no_give", 1);set("no_store", 1);set("no_sell", 1);
        }
        setup();
}

void init()
{
        add_action("do_use", "changewx");       
}

int do_use(string arg)
{
	object ob, me;
	string wuxing;
	
	mapping wx = ([
	   "金" : 0,
	   "木" : 1,
	   "水" : 2,
	   "火" : 3,
	   "土" : 4,
	]);

	me = this_player();

	if (! arg )
		return notify_fail("指令格式：changewx [五行]\n");

	if (arg != "金" && arg != "木" && arg != "水" &&
	    arg != "土" && arg !="火")
	    	return notify_fail("五行输入错误，范围：金木水火土！\n");

	wuxing = arg;
	
	arg = "yuanshenwuxingdan";

	if (me->query("yuanshen/wuxing") == wx[wuxing])
		return notify_fail("你五行已经是" + wuxing + "属性了！\n");

	if (! objectp(ob = present(arg, me)))
		return notify_fail("你身上没有这个东西！\n");


	if (ob->query("owner") != me->query("id"))
		return notify_fail(ob->name() + NOR "已经于其他玩家绑定！\n");
	

	tell_object(me, HIG "恭喜！你服下" + ob->name() + HIG "后，元神五行变更为：" HIC + wuxing + HIG "！\n");
	
	log_file("super/"+ filter_color(query("name")) , me->query("id") + " at " + ctime(time()) + " 使用" + ob->name() + 
	                                                "元神五行变更为：" + wuxing + "！\n");

	me->set("yuanshen/wuxing", wx[wuxing]);
	me->set("yuanshen/last_change_wuxing", time());

	me->save();
	
	destruct(ob);
	
	return 1;
}

int query_autoload()
{
	return 1;
}