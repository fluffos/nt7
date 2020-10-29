// Budai.c
// Creator : Numa@Sj 00-6-3

#include <ansi.h>
inherit ITEM;

#define SHU "/d/city/obj/whdmd-book"

void create()
{
        set_name("布袋", ({"bu dai", "dai"}));
        set_weight(2000);
        set_max_encumbrance(3000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", "这是一个破旧的布袋。\n");
                set("unit", "个");
                set("no_get", 1);
                set("no_steal", 1);
                set("no_give", 1);
                set("fill_lime", 1);
        }
        setup();
}

int is_container() { return 1; }

void init()
{
	add_action("do_sa","sa");
	add_action("do_put","put");
}

int do_put(string arg)
{
        string str;

        if (!arg) return 0;
        if (sscanf(arg,"%s in dai",str) == 1 || sscanf(arg,"%s in bu dai",str) == 1) {
                if (str != "shihui")
                        return notify_fail("这样东西放不进去。\n");
        }
        return 0;
}

int do_sa(string arg)
{
	object me = this_player();
	object ob = this_object();
	object ob1, ob2, ob3;
	string msg;
	
	if (!(ob1 = present("shihui", ob)))
		return notify_fail("袋里又没石灰，你撒啥？！\n");

	if (!arg)
		return notify_fail("你想要用石灰粉干什么?\n");

	if (arg = "shi song"
	 && ob2 = present("shi song",environment(me))
	 && ob3 = present("mao shiba",environment(me))) {
		if (!me->query_temp("mao18/passed4"))
			return notify_fail("人家打架呢，你瞎搀和啥！\n");
		msg = HIW"$N趁$n不备，从布袋中掏出石灰粉，猛的撒向$n的眼睛！\n"NOR;
		destruct(ob1);
		call_out("do_attack", 1, me, ob2, ob3, msg);
		return 1;
	}
	else
		return notify_fail("石灰粉如何能够去攻击人家？！\n");
}

int do_attack(object me, object ob2, object ob3, string msg)
{
          ob2 = present("shi song",environment(me));
	if (random(me->query_str()) > 20 && !me->query("fail")) {
		msg += RED"$n募地白影晃动，无数粉末冲进眼里，鼻里，口里，一时气为之窒，跟着双\n"+
			"眼剧痛，犹似万枚钢针同时刺一般，待欲张口大叫，满嘴粉末，连喉头嗌住了，\n"+
			"再也叫不出声来。\n"NOR;
		msg += CYN"$N随手捡起地上单刀，顺手插入了$n肚中。\n"NOR;
		message_vision(msg, me, ob2);
		ob2->die();
		me->delete_temp("mao18/passed4");
		me->set("mao18/pass",1);
		remove_call_out("do_finish");
		call_out("do_finish", 2, me, ob3);
		return 1;
	}
	else {
		log_file("quest/wuhu",sprintf("%8s%-18s从茅十八处学得五虎断门刀，失败，福：%d。\n",
			me->name(1), "("+capitalize(me->query("id"))+")", me->query("kar") ), me);
		me->set("mao18/fail", 1);
		msg += HIR"谁知却撒了个空，自己也摔了一交。\n"NOR;
		message_vision(msg, me, ob2);
		return 1;
	}
}

int do_finish(object me, object ob)
{
	object ob1;
	
	tell_object(me,HIY"茅十八道：“你为什么用石灰撒在那史松的眼里？”声音严厉，神态更是凶恶。\n\n"+
			"    你心中十分害怕，当下茅十八便将撒石灰、下蒙汗药等这些江湖人所不齿的卑鄙手段\n"+
			"告诉了你。随后又说：“我这里有一本我派刀法的秘籍，你拿去自行好好钻研。只要你能\n"+
			"勤学苦练，将来未始不能练成一身好武艺。咱们后会有期了！”说完转身离去了。\n"NOR);
	ob1 = new(SHU);
	ob1->move(me);
	ob1->set_temp("mao18/book",me->query("id"));
	log_file("quest/wuhu",sprintf("%8s%-18s从茅十八处学得五虎断门刀，福：%d。\n",
		me->name(1), "("+capitalize(me->query("id"))+")", me->query("kar") ), me);
	if (ob) destruct(ob);
	return 1;
}
