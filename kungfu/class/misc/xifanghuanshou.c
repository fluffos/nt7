// nanhai.c

#include <ansi.h>

#define MAX_POINT     1000
#define MEMBER_D      "/adm/daemons/memberd"

inherit NPC;

void create()
{
	set_name(HIY "七彩" HIM "琉璃兽" NOR, ({ "qicai liulishou", "qicai", "liulishou" }) );
	set("title", HIW "圣诞" HIR "怪兽" NOR);
	set("gender", "男性");
	set("age", 8888);
	set("long", @LONG
这是一只长相奇特怪兽，全身幻出七彩之色，头大身小，一对浑圆的眼
珠闪烁出摄人的光芒。
LONG );
	set("combat_exp", 2000000000);
	set("shen_type", 0);
	set("attitude", "heroism");
        set("max_neili", 5000000);
        set("neili", 5000000);
        set("max_jing", 5000000);
        set("jing", 5000000);
        set("max_qi", 900000000);
	set("eff_qi", 900000000);
        set("qi", 900000000);
        set("jingli", 5000000);
        set("max_jingli", 5000000);

	set("no_nuoyi", 1); // 不被挪移影响

        set("str", 200);
        set("int", 100);
        set("con", 100);
        set("dex", 300);

	set_skill("unarmed", 4000);
	set_skill("sword", 4000);
	set_skill("parry", 4000);
	set_skill("dodge", 4000);
	set_skill("force", 4000);

        set("jiali", 1000);

        set_temp("apply/attack", 150000);
        set_temp("apply/unarmed_damage", 100000);
	set_temp("apply/damage", 100000);
        set_temp("apply/armor", 10000);

        if (clonep(this_object()))
        {
                set("chat_chance", 30);
                set("chat_msg", ({ (: random_move :) }));
                set("born_time", time());
                keep_heart_beat();
        }

		setup();
}

int accept_fight(object ob)
{
        message_vision("$N一声巨吼，扑了过来。\n",
                       this_object(), ob);
        kill_ob(ob);
        return -1;
}

int accept_kill(object ob)
{
        return 1;
}

int accept_hit(object ob)
{
        return 1;
}

mixed hit_ob(object me, object ob, int damage_bouns)
{
		ob->start_busy(20 + random(10));
		me->receive_wound("qi", 5000 + random(3000), ob);
        return HIY "$N" HIY "周围雾气缭绕，直逼得$n" HIY "头晕目眩。\n" NOR;
}

void heart_beat()
{
		if (query("neili") < 1)
			set("neili", query("max_neili"));

		::heart_beat();
}

void unconcious()
{
	    // 防止直接call_die()
		if (query("qi") > 500000)
		{
			revive();
			return;
		}
	
        die(query_last_damage_from());
}

void die(object killer)
{
        object dob;             // 打晕这个NPC的人
        int n;                  // 可以奖励的人的数目
        int exp;                // 需要瓜分的经验
        int pot;                // 需要瓜分的潜能
        int tihui;              // 需要瓜分的体会
        int weiwang;            // 需要瓜分的威望
        int score;              // 需要瓜分的阅历
        object *t;              // 杀死我的人的队伍列表
        object tob;
        int i;

        // 定义奖励物品列表
		// 几率  X / 万分之一
		mixed oblist = ([

		]);

		object gift_ob;
		string s_gift, *key_s_gift;
		int gift_point;
		
	    // 防止直接call_die()
		if (query("qi") > 100000)
		{
			revive();
			return;
		}

        // 找到杀了我(NPC)或是打晕我的人
        if (! objectp(dob = killer))
                dob = query_last_damage_from();

		if (! dob)
		{
				destruct(this_object());
				return;
		}

        t = dob->query_team();

        if (objectp(dob) && environment(dob) == environment(this_object()))
        {
                exp = 1000000 + random(1500000);
                pot = 1000000 + random(1000000);
                tihui = 150000 + random(70000);
                //weiwang = 100000 + random(300000);
                //score = 200000 + random(200000);
		n = 0;
                n = sizeof(t);
                
                if (! n || n < 3)
                {
                       exp /= 5;
                       pot /= 5;
                       tihui /= 5;
                       //weiwang /= 3;
                       //score /= 3;
                }

		if (n >= 3)
		{
			exp /= n;
			pot /= n;
			tihui /= n;
			//weiwang /= n;
			//score /= n;
		}

		if (n)
		{				
			foreach(tob in t)
			{
				  if (objectp(tob) && living(tob))
				 {
				 		if (environment(tob) == environment(dob))
						   GIFT_D->delay_bonus(tob,
						          ([ "exp"      : exp + ((tob == dob) ? 50000 : 0),
							     "pot"      : pot + ((tob == dob) ? 50000 : 0),
						             //"weiwang"  : weiwang + ((tob == dob) ? 50000 : 0),
							     //"score"    : score + ((tob == dob) ? 50000 : 0),
							      "mar"      : tihui + ((tob == dob) ? 10000 : 0),
							     "prompt"   : "你的队伍打败" + name() + "之后"]), 999);

				 }
			}
		}
		else
		{
						   GIFT_D->delay_bonus(dob,
						          ([ "exp"      : exp,
							     "pot"      : pot,
							     //"weiwang"  : weiwang,
						             //"score"    : score,
						             "mar"      : tihui + ((tob == dob) ? 10000 : 0),
							     "prompt"   : "你在打败" + name() + "之后"]), 999);
		}

        }
        //25%几率掉出七彩琉璃靴
 	if (objectp(dob) && environment(dob) == environment(this_object()) && random(4) == 1)
	{
		gift_ob = new("/clone/armor/qicai-xue");
		message_vision(HIR "叮~~一声，从$N" HIR "掉出一样东西，$n" HIR 
			           "赶紧拣了起来。\n" NOR, this_object(), dob);
		tell_object(dob, BLINK + HIG "你得到了" + gift_ob->name() + BLINK + HIG "。\n" NOR);
		gift_ob->move(dob, 1);
	}

        // 消失
        command("chat 看来这趟东方之行实在是自讨没趣！");
	message_vision("$N长啸一声，化作一团火焰，消失在天际。\n", this_object());
        CHANNEL_D->do_channel(this_object(), "rumor",
                        "听说" + name() + HIM "被一群武林异士打败，败兴而归。" NOR);
                        
	destruct(this_object());

        return;
}

void random_move()
{
	if (time() - query("born_time") > 1800)
	{
		message_vision("$N长啸一声，化作一团火焰，消失在天际。\n", this_object());
		destruct(this_object());
		return;
	}
}
