// mu2.c
// 墓

inherit ROOM;
#include <ansi.h>
void create()
{
	set("short", "墓室");
	set("long",@long
这里是郭襄墓下的墓室。墓室不大，正面是一具白玉石棺，旁边放着一盏
长明灯。石棺一尘不染，看来经常有人进来打扫。
long);
	set("exits", ([
		"up" : __DIR__"mu",
	]));
	setup();
	set("count", 1);
}

void init()
{
	add_action("do_na", "na");
	add_action("do_move", "move");
	add_action("do_move", "open");
}

int do_move(string arg)
{
	object me, tmp;
	int dex;
	me = this_player();

	if (arg != "coffin" || !arg) 
		return notify_fail("你要干什么？\n");

	if (me->is_busy() || me->is_fighting()) 
		return notify_fail("你正忙着哪！\n");

	if ( me->query("combat_exp") < 1000000 ) return 0;
	if ( !me->query("quest/jiuyin2/emeijump")) return 0;

	message_vision("$N运足气，双手用力去搬白玉石棺盖。\n", me);
	message_vision(HIR"忽然间几支短箭从棺后一个机关里射出来，直射向$N的面门！\n"NOR, me);

	dex = me->query_dex(1) + me->query("kar");

	if( random(dex) < 18 && !me->query("hanshui_food") && random(2) ) {
		message_vision(HIW"$N连忙躲闪，结果没能躲过去。\n"NOR, me);
		me->add("quest/jiuyin2/fail", 1);
		me->set("quest/jiuyin2/time", time());
		log_file("quest/jiuyin",sprintf("%-18s想从郭襄墓中掀开棺盖，娥眉九阴部分失败%s次。\n",
       			me->name(1)+"("+capitalize(getuid(me))+")",chinese_number(me->query("quest/jiuyin2/fail"))), me);
		me->unconcious(); 
		me->set_temp("last_damage_from","身中巨毒毒发");
       		me->die();
		if (tmp = present("corpse", this_object())) {
			object *ob = deep_inventory(tmp);
			int i = sizeof(ob);
			while (i--) if (userp(ob[i])) ob[i]->move(this_object());
			destruct(tmp);
			if (me) tell_room(this_object(), me->name()+"的尸骨都找不到了。\n");
		}
		return 1;
	}
	else {
		message_vision(HIW"$N头一低，避开短箭，掀开棺盖。\n"NOR, me);
		me->set_temp("marks/掀", 1);
		log_file("quest/jiuyin",sprintf("%-18s在娥眉九阴部分失败%s次后成功在郭襄墓中掀开棺盖，身：%d，福：%d。\n",
       			me->name(1)+"("+capitalize(getuid(me))+")",chinese_number(me->query("quest/jiuyin2/fail")),
       			me->query_dex(), me->query("kar")), me);
		return 1;
	}
}

int do_na(string arg)
{
	object me, ob;

	me = this_player();
	ob = this_object();

	if (me->is_busy() || me->is_fighting()) return notify_fail("你正忙着哪！\n");


	if (arg != "all from coffin") return notify_fail("你要干什么？\n");

	if (!me->query_temp("marks/掀")) 
		return notify_fail("你不打开石棺的盖子，怎么能拿里面的东西？\n");

	if( random(30) > 5 ) {
		write("你在石棺里摸了半天，什么也没有拿到。\n", me);
		write("只听见啪的一声，棺盖不知怎么又合上了。\n", me);
		log_file("quest/jiuyin",sprintf("%-18s在失败%s次后，在郭襄墓中掀开棺盖，但未得到任何东西。\n",
       			me->name(1)+"("+capitalize(getuid(me))+")",chinese_number(me->query("quest/jiuyin2/fail"))), me);
		me->delete_temp("marks/掀");
		return 1;
	}
	if (ob->query("count") > 0) {
		switch(random(2)) {
			case 0: { 
				new("/d/emei/obj/yangpi")->move(me);
				me->set("quest/jiuyin2/emei", 1);
				log_file("quest/jiuyin",sprintf("%-18s在娥眉九阴部分失败%s次后成功在郭襄墓中得到山羊皮。\n",
       					me->name(1)+"("+capitalize(getuid(me))+")",chinese_number(me->query("quest/jiuyin2/fail"))), me);
				write("你从石棺中拿出一块山羊皮。\n", me);
				break;
			}
			case 1: {
				new("/d/emei/obj/yuzhuo")->move(me);
				write("你从石棺拿出支黑玉镯。\n", me);
				log_file("quest/jiuyin",sprintf("%-18s在娥眉九阴部分失败%s次后，在郭襄墓中掀开棺盖，但未得到山羊皮。\n",
       					me->name(1)+"("+capitalize(getuid(me))+")",chinese_number(me->query("quest/jiuyin2/fail"))), me);
				break;
			}
		}
		write("只听见啪的一声，棺盖不知怎么又合上了。\n", me);
		me->delete_temp("marks/掀");
		ob->add("count", -1);
	}
	return 1;
}
