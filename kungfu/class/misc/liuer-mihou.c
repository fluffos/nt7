 // ouyangfeng.c

#include <ansi.h>

#define MAX_POINT     300
#define MEMBER_D      "/adm/daemons/memberd"

// X小时后更新
#define UPDATE_TIME          3 * 3600
// 出现地点
#define UPDATE_PLACE         "/d/penglai/fanchendao"
// BOSS文件
#define BOSS_FILE            "/kungfu/class/misc/liuer-mihou"

// 经验过高后无任何奖励
#define MAX_EXP              10000000

inherit NPC;

void create()
{
        set_name(HIC "六耳猕猴" NOR, ({ "liuer mihou", "liuer", "mihou" }));
        set("long", HIC "这是一只相貌奇特的猕猴，已经修炼成人形，有六耳，看起来不容易对付。\n" NOR);

        set("gender", "男性");
        set("age", 1200);
        set("nickname", HIR "已修炼成人的" NOR);
        set("shen_type", 0);
        set("attitude", "peaceful");

        set("str", 120);
        set("int", 60);
        set("con", 60);
        set("dex", 160);

        set("qi", 9000000);
        set("max_qi", 9000000);

        set("jing", 2000000);
        set("max_jing", 2000000);
        set("jingli", 2000000); 
        set("max_jingli", 2000000); 

        set("neili", 50000); 
        set("max_neili", 50000); 
        set("jiali", 600); 
        set("combat_exp", 8000000);

        set_skill("force", 400);
        set_skill("unarmed", 400);
        set_skill("dodge", 400);
        set_skill("parry", 400);
        set_skill("cuff", 400);
        set_skill("finger", 400);
        set_skill("training", 400);          

        set_skill("jiuyin-hamagong", 400); 
        set_skill("baituo-xinfa", 400);          
 
        set_skill("staff", 400);
        //set_skill("training", 340);
        set_skill("poison", 400);

        set_skill("shedu-qiqiao", 400);
        set_skill("hamagong", 400);
        set_skill("baituo-xinfa", 400);
        set_skill("chanchu-bufa", 400);
        set_skill("lingshe-quan", 400);
        set_skill("lingshe-zhangfa", 400);
        set_skill("baibian-daxue", 400);
        set_skill("guzheng-jifa", 400);
        set_skill("xiyu-tiezheng", 400);
        set_skill("wushe-qu", 400);
        set_skill("literate", 400);
        set_skill("medical", 400);
        set_skill("baituo-michuan", 400);
        set_skill("martial-cognize", 400);

        map_skill("dodge", "chanchu-bufa");
        map_skill("force", "jiuyin-hamagong"); 
        map_skill("unarmed", "jiuyin-hamagong"); 
        map_skill("cuff", "lingshe-quan");
        map_skill("parry", "lingshe-zhangfa");
        map_skill("staff", "lingshe-zhangfa");
        map_skill("finger", "shedu-qiqiao");
        map_skill("poison", "shedu-qiqiao");
        map_skill("medical", "baituo-michuan");
        map_skill("guzheng-jifa", "xiyu-tiezheng");

        prepare_skill("unarmed", "jiuyin-hamagong"); 

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "staff.qian" :),
                (: perform_action, "staff.bite" :),  
                (: perform_action, "unarmed.puji" :),  
                (: perform_action, "unarmed.zhen" :), 
                (: perform_action, "unarmed.puji" :), 
                (: exert_function, "yijin" :), 
        }));

        set_temp("apply/damage", 200);
        set_temp("apply/unarmed_damage", 200);
        set_temp("apply/armor", 2000);

        setup();
        
        carry_object("/clone/weapon/taomuzhang")->wield(); 
        carry_object("/clone/cloth/jinduan")->wear();
        carry_object("/clone/cloth/xianlv")->wear();
} 

int accept_fight(object ob)
{
        kill_ob(ob);
        return -1;
}

int accept_kill(object ob)
{
        return 1;
}

int accept_hit(object ob)
{
        kill_ob(ob);
        return -1;	
        return 1;
}

mixed hit_ob(object me, object ob, int damage_bouns)
{
	ob->start_busy(5 + random(6));
	me->receive_wound("qi", 900 + random(900), ob);
        return HIY "$N" HIY "大喝一声，拼死反抗，竟逼得$n" HIY "手忙脚乱。\n" NOR;
}

void heart_beat()
{
	if (query("neili") < 1 && random(50) == 1)						
		set("neili", query("max_neili"));

	::heart_beat();
}

void unconcious()
{/*
	// 防止直接call_die()
	if (query("qi") > 60000)
	{
		revive();
		return;
	}
	*/
        die(query_last_damage_from());
}

void die(object killer)
{
        object dob;             // 打晕这个NPC的人
        int n;                  // 可以奖励的人的数目
        int exp;                // 需要瓜分的经验
        int pot;                // 需要瓜分的潜能
        int weiwang;            // 需要瓜分的威望
        int gongxian;           // 贡献
        int tihui;              // 体会
        int score;              // 需要瓜分的阅历
        object *t;              // 杀死我的人的队伍列表
        object tob;
        int ysg;
        int i;

        // 定义奖励物品列表
	// 几率  MAX_POINT 分之 X
	mixed oblist = ([
			"/clone/money/gold"                     :        	200,
			"/clone/money/yuanbao"                  :        	100,			
			"/clone/fam/pill/renshen4"               :        	30,
			"/clone/armor/zijinhua-erhuan2"          :        	30,
			"/clone/armor/yecha3"                    :              220,
			"/clone/fam/max/naobaijin"               :              20,
		]);

		object gift_ob;
		string s_gift, *key_s_gift;
		int gift_point;
/*
	        // 防止直接call_die()
		if (query("qi") > 60000)
		{
			revive();
			return;
		}
*/
                // 找到杀了我(NPC)或是打晕我的人
                if (! objectp(dob = killer))
                dob = query_last_damage_from();

		if (! dob)
		{
			//MAP_D->update_boss(BOSS_FILE,UPDATE_PLACE,UPDATE_TIME);
			destruct(this_object());
			return;
		}

                t = dob->query_team();

	        if (objectp(dob) && environment(dob) == environment(this_object()))
	        {
	                exp = 90000 + random(80000);
	                pot = 200000 + random(80001);
	                gongxian = 8400 + random(8200);
	                tihui = 9100 + random(9800);
			n = 0;
	                n = sizeof(t);
	                
	                if (! n || n < 3)
	                {
	                       exp /= 3;
	                       pot /= 3;
	                       weiwang /= 3;
	                       score /= 3;
	                       tihui = 0;	                       
	                }

			if (n >= 3)
			{
				exp /= n;
				pot /= n;			
			}
	
			if (n)
			{				
				foreach(tob in t)
				{
					
					if (objectp(tob) && living(tob))
					{
						if (tob->query("combat_exp") >= MAX_EXP)continue;
						if (environment(tob) == environment(dob))
							GIFT_D->delay_bonus(tob,
								([ "exp"      : exp + ((tob == dob) ? 3000 : 0),
								   "pot"      : pot + ((tob == dob) ? 3000 : 0),
								   "mar"      : tihui + ((tob == dob) ? 1000 : 0),
								   "gongxian" : tob->query("family/family_name") == "昆仑派" ? gongxian : 0,
								   "prompt"   : "你的队伍打败" + name() + "之后"]), 999);
	
					}
				}
			}
			else
			{
				if (dob->query("combat_exp") < MAX_EXP)
					GIFT_D->delay_bonus(dob,
						 ([ "exp"      : exp,
					    	    "pot"      : pot,
					    	    "prompt"   : "你在打败" + name() + "之后"]), 999);
			}
	
	        }
		
	        // 一定几率掉物品在杀我的人身上dob
		if (objectp(dob) && environment(dob) == environment(this_object()) && 
		    dob->query("combat_exp") < MAX_EXP)
		{
			key_s_gift = keys(oblist);
			s_gift = key_s_gift[random(sizeof(key_s_gift))];
			gift_point = oblist[s_gift];

			// 判断几率
			if (MEMBER_D->is_valib_member(dob->query("id")) 
			    && random(MAX_POINT / ITEM_D->gift_point()) < gift_point)
			{
				// 获得物品--爆出物品直接放在dob身上
				gift_ob = new(s_gift);
				if (objectp(gift_ob))
				{
					message_vision(HIR "叮~~一声，从$N" HIR "掉出一样东西，$n" HIR 
						       "赶紧拣了起来。\n" NOR, this_object(), dob);
					tell_object(dob, BLINK + HIG "你得到了" + gift_ob->name() + BLINK + HIG "。\n" NOR);
					gift_ob->move(dob, 1);
				}
				else // 纪录之 
				{
					log_file("killed-gift-none", s_gift + "\n");
				}
			}
		}
	
	        // 消失
	        if (1)
	        {
	        	command("chat* sigh");
	        	command("chat 看来，我还是应该再回到南山中修炼一千年再说...");			
		}/*
		else
		{
			message_vision(HIG "猛然间，$N " HIG " 向后一跳，随手仍出一颗黑色小丸，顿时腾起一片烟雾 ...\n" NOR, 
			               this_object());
			command("chat 哼，雕虫小技，不陪你们玩了，告辞！");
			CHANNEL_D->do_channel(this_object(), "rumor", "听说" + name() + HIM "从古墓中盗得珍宝后，夺路而逃。" NOR);
		}
*/
		// 设置更新
		//MAP_D->update_boss(BOSS_FILE,UPDATE_PLACE,UPDATE_TIME);

		// 1/500几率掉出无名铜人
		if (random(500) < 1)
		{
			object ob_tongren;
			ob_tongren = new("/clone/tongren/tongren1");			
			message_vision(HIR "当~~一声，从$N" HIR "身上掉出" + ob_tongren->name() + HIR "，落在地上。\n" NOR, this_object());
			ob_tongren->set("who_get/id", "NONE");
			ob_tongren->set("who_get/time", time() + 30); // 30秒内都不能捡取		
			ob_tongren->move(environment(this_object()));
		}

		destruct(this_object());
	
	        return;
}

void remove()
{
	if (GIFT_D->is_open_pld())MAP_D->update_boss(BOSS_FILE,UPDATE_PLACE,UPDATE_TIME);
	return ::remove();
}
