#include <ansi.h>
inherit ITEM;
void create()
{
        set_name(HIY "麒麟内丹" NOR, ({"qilinneidan"}));
        set_weight(1);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {  
        	set("long", HIC "传说麒麟内丹乃修炼千年火麒麟的内丹，拥有无边的力量。\n" + 
        	                "服食(fushi qilinneidan 技能id)后可永久提升非知识类技能1级。\n" HIC
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
	string skid;
	
	me = this_player();

	if (! arg )
		return notify_fail("你要服食什么？\n");

	if (! sscanf(arg, "qilinneidan %s", skid))
		return notify_fail("指令格式：fuyong qilinneidan 技能ID\n");

	arg = "qilinneidan";

	if (! objectp(ob = present(arg, me)))
		return notify_fail("你身上没有这个东西！\n");
/*
	if( query("owner", ob) != query("id", me) )
		return notify_fail(ob->name() + NOR "已经于其他玩家绑定！\n");
*/	
	if (! me->query_skill(skid, 1))
		return notify_fail("你没有这个技能，请确认输入是否正确！\n");
	
	if (skid == "zuoyou-hubo")
		return notify_fail("左右互博不能提升！\n");

	if (("/kungfu/skill/" + skid)->type() == "knowledge")
		return notify_fail("知识类技能不能提升！\n");

	if (("/kungfu/skill/" + skid)->type() != "martial")
		return notify_fail("这项技能未定义类型不能提升！\n");

   me->add_skill(skid, 1);

	tell_object(me, HIG "恭喜！你服下" + ob->name() + HIG "后，" + to_chinese(skid) + "提升1级！\n");
	

	me->save();
	
	destruct(ob);
	
	return 1;
}