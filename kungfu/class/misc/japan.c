// donghai.c

#include <ansi.h>

inherit NPC;

void create()
{
        set_name(HIR "东瀛" HIW "巨犬" NOR, ({ "dongying qinshou", "dongying", "qinshou" }) );
        set("title", HIY "来自远方的禽兽" NOR);
        set("gender", "变态");
        set("age", 99);
        set("long", HIY "一只巨大的禽兽，长相无比丑陋，据说来自远方的东瀛国。\n" NOR);

        set("combat_exp", 10000000);
        set("attitude", "heroism");
        set("max_neili", 1000000);
        set("neili", 1000000);
        set("max_jing", 1000000);
        set("jing", 1000000);
        set("max_qi", 1000000);
		set("eff_qi", 1000000);
        set("qi", 1000000);
        set("jingli", 1000000);
        set("max_jingli", 1000000);

		set_skill("unarmed", 1);
		set_skill("dodge", 1);
		set_skill("parry", 1);
		set_skill("sword", 1);
		set_skill("force", 1);

        set("str", 1);
        set("int", 1);
        set("con", 1);
        set("dex", 1);

        setup();

}

void unconcious()
{
        set("max_neili", 9000000);
        set("neili", 9000000);
        set("max_jing", 9000000);
        set("jing", 9000000);
        set("max_qi", 9000000);
		set("eff_qi", 9000000);
        set("qi", 9000000);
        set("jingli", 9000000);
        set("max_jingli", 9000000);
		revive();
}

void die()
{
        set("max_neili", 9000000);
        set("neili", 9000000);
        set("max_jing", 9000000);
        set("jing", 9000000);
        set("max_qi", 9000000);
		set("eff_qi", 9000000);
        set("qi", 9000000);
        set("jingli", 9000000);
        set("max_jingli", 9000000);
		revive();
}

int receive_damage(string type, int damage, object who)
{
	object money, ob, weapon, armor, armor2;
	int amount;

	string *gift = ({
		"/clone/fam/pill/puti1",
		"/clone/fam/pill/puti2",
		"/clone/fam/pill/puti3",
		"/clone/fam/pill/lingzhi1",
		"/clone/fam/pill/lingzhi2",
		"/clone/fam/pill/lingzhi3",
		"/clone/fam/pill/linghui1",
		"/clone/fam/pill/linghui2",
		"/clone/fam/pill/linghui3",
		"/clone/fam/pill/sheli1",
		"/clone/fam/pill/sheli2",
		"/clone/fam/pill/sheli3",
		"/clone/fam/pill/renshen4",
		"/clone/fam/pill/lingzhi4",
		"/clone/fam/pill/xuelian4",
		"/clone/fam/pill/xuelian3",
		"/clone/fam/pill/yulu",
		"/clone/fam/pill/dimai",
		"puti4",
	});
	
	string *gift2 = ({
		"/clone/fam/armor/heitie-kai",
		"/clone/fam/armor/longshen-toukui",
		"/clone/fam/armor/wuzhe-huwan",	
		"/clone/fam/item/longxue",
		"/clone/armor/yin-erhuan",
		"/clone/armor/zijinhua-erhuan",
	});

	string *gift3 = ({
		"/clone/weapon/qinggang-jian",
		"/clone/weapon/ningyue-dao",
		"/clone/weapon/qingtong-zhang",
		"/clone/weapon/tiemu-gun",
		"/clone/weapon/longwei-bian",		
		"/clone/weapon/pangu-gong",

		"/clone/armor/feima-xue",
	    "/clone/armor/wushi-pifeng",

		"/clone/fam/gift/con3",
		"/clone/fam/gift/dex3",
		"/clone/fam/gift/int3",
		"/clone/fam/gift/str3",

		"/clone/armor/jinsi-beixin",
		"/clone/armor/heitie-kai",
		"/clone/armor/shangu-zhixing",
		
	});

	string *gift4 = ({
		"/clone/armor/jinsi-shoutao",
		"/clone/armor/shengling-yaodai",
		"/clone/armor/chiyou-zhanpao",
		"/clone/armor/shendiao-yumao",
		"/clone/armor/yinyang-erhuan",		
		"/clone/armor/biyu-chai",
	});

	if (! objectp(who))return ::receive_damage(type, damage, who);

	if (1)
	{
		who->add("combat_exp", 1 + random(3));
		who->add("potential", 1 + random(2));
		who->add("experience", random(1));

		// 获得钱
		if (random(100) == 1)money = new("/clone/money/gold");
		else if (random(50) == 1)money = new("/clone/money/silver");
		else if (random(30) == 1)money = new("/clone/money/coin");	
		if (objectp(money))
		{
			if (money->query("id") == "gold")amount = 1 + random(3);
			if (money->query("id") == "silver")amount = 10 + random(20);
			if (money->query("id") == "coin")amount = 200 + random(400);
			money->set_amount(amount);
			money->move(who, 1);
			tell_object(who, HIG "你从" + name() + HIG "身上获得了" + sprintf("%d", amount) + 
                                         money->query("base_unit") + money->name() + "。\n" NOR);
		}

		// 随机获得物品
		if (random(10000) == 1 && random(3) == 1)
		{
			ob = new(gift[random(sizeof(gift))]);

			if (objectp(ob))
			{
				ob->move(who, 1);
				tell_object(who, HIR "你从" + name() + HIG "身上获得了一" +                                         					ob->query("base_unit") + ob->name() + "。\n" NOR);				
			}
		}
		if (random(80000) == 1 && random(5) == 1)
		{
			weapon = new(gift2[random(sizeof(gift2))]);

			if (objectp(weapon))
			{
				weapon->move(who, 1);
				tell_object(who, HIR "你从" + name() + HIG "身上获得了一" +   
					weapon->query("base_unit") + weapon->name() + "。\n" NOR);				
			}
		}
		if (random(200000) == 1 && random(6) == 1)
		{
			armor = new(gift3[random(sizeof(gift3))]);

			if (objectp(armor))
			{
				armor->move(who, 1);
				tell_object(who, HIR "你从" + name() + HIG "身上获得了一" +          
					armor->query("base_unit") + armor->name() + "。\n" NOR);				
			}
		}
		if (random(400000) == 1 && random(7) == 1)
		{
			armor2 = new(gift4[random(sizeof(gift4))]);

			if (objectp(armor2))
			{
				armor2->move(who, 1);
				tell_object(who, HIR "你从" + name() + HIG "身上获得了一" +           
					armor2->query("base_unit") + armor2->name() + "。\n" NOR);				
			}
		}
	}	


	return ::receive_damage(type, damage, who);
}
