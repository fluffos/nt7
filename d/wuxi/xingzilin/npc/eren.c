// This program is a part of NITAN MudLIB 
// redl 2012/11/1 
#include <ansi.h>
#include "../cnpc.h"

inherit NPC;


#define N_JINGQI_INCREASE 0.25  //每提升一品的增加百分比
#define N_NEILI_INCREASE 0.25
#define N_GIFT_EXP_INCREASE 0.2


mapping wushi_names = ([
        1 : "云中鹤",
        2 : "岳老三",
        3 : "叶二娘",
        4 : "段延庆",
]);

mapping id_names = ([
        1 : "yun zhonghe",
        2 : "yue laosan",
        3 : "ye erniang",
        4 : "duan yanqing",
]);

mapping nick_names = ([
        1 : "穷凶极恶",
        2 : "凶神恶煞",
        3 : "无恶不作",
        4 : "恶贯满盈",
]);

mixed es_die(object me) //超时自毁
{
        message_vision("$N"+NOR+YEL+"猛打一个激灵，鬼鬼祟祟地往路边树林里一跳，突然消失不见了...\n"NOR, me);
        destruct(me);
}

void create()
{
        object ob; 
        int lv, ntmp;
        
        lv = random(1000);
        if (lv < 1) lv = 4;
                else if (lv < 10) lv = 3;
                else if (lv < 100) lv = 2;
                else lv = 1;
//        lv = 1 + random(4);
     
        set_name(HIR + wushi_names[lv] + NOR, ({ id_names[lv], "e ren" }));
        set("nickname", HIY +nick_names[lv]+ NOR);
        set("long", 
"西夏国有个讲武馆，叫做一品堂，是该国国王所立，堂中招聘武功高强之士，优礼供养。\n"
"这是一品堂中的一品高手四大恶人之一，据说受赫连大将军带领，此来不知道对中原有什么图谋......\n"
        );
        
        set("age", 40);
        set("str", 45);
        set("dex", 45);
        set("con", 45);
        set("int", 35);
        ntmp = to_int(1.8 * WU2345_QI_BASE * (1 + lv * N_JINGQI_INCREASE));
        set("max_qi", ntmp);
        set("eff_qi", ntmp);
        set("qi", ntmp);
        set("max_jing", to_int(ntmp * HP_JING_PERCENT));
        set("eff_jing", to_int(ntmp * HP_JING_PERCENT));
        set("jing", to_int(ntmp * HP_JING_PERCENT));
        ntmp = to_int(WU2345_QI_BASE * HP_NEILI_PERCENT * (1 + lv * N_NEILI_INCREASE));
        set("max_neili", ntmp);
        set("neili", ntmp);
        set("max_jingli", ntmp);
        set("jingli", ntmp);
        
        set("level", EREN_LEVEL + WU2345_LEVEL_INCREASE * (lv-1));
        set("combat_exp", 1000000000);
                set("jiali", 6000 + 1000 * lv);

                set_temp("rename", wushi_names[lv]);
        set_temp("apply/parry", 200 + (lv*50));
        set_temp("apply/dodge", 200 + (lv*50));
        set_temp("apply/dex", 200 + (lv*50));
        set_temp("apply/attack", 200 + (lv*50));
        set_temp("apply/defense", 200 + (lv*50));
        set_temp("apply/unarmed_damage", 300 + (lv*50));
        set_temp("apply/damage", 200 + (lv*50));
        set_temp("apply/armor", 200 + (lv*50));

                //比同品武士高500级sk
                ntmp = to_int(500 + WU2345_SKILL_LV + (lv-1) * WU2345_SKILL_INCREASE);
        
        if (!random(3))
        {
                set_skill("count", ntmp / 10 * 8);
                set_skill("martial-cognize", ntmp);
        }
        else
        {
                set_skill("count", ntmp / 10 * 1);
                set_skill("martial-cognize", ntmp / 10 * 6);
        }
        
                        set_skill("force", ntmp);
                                if (lv >= 3 && random(6) == 0)
                                {
                                        set_skill("xixing-dafa", ntmp + 100);
                                map_skill("force", "xixing-dafa");
                                }
                                else if (random(2))
                                {
                                        set_skill("biyun-xinfa", ntmp + 100);        
                                map_skill("force", "biyun-xinfa");
                                }
                                else
                                {
                                        set_skill("riyue-xinfa", ntmp + 100);        
                                map_skill("force", "riyue-xinfa");
                                }
                        set_skill("dodge", ntmp);
                            switch (random(5))
                        {
                                case 0:
                                        set_skill("chanchu-bufa", ntmp);
                                        map_skill("dodge", "chanchu-bufa");
                                        break;
                                case 1:
                                        set_skill("shuishangpiao", ntmp);
                                        map_skill("dodge", "shuishangpiao");
                                        break;
                                default:
                                        set_skill("kunlun-shenfa", ntmp);
                                        map_skill("dodge", "kunlun-shenfa");
                                        break;
                        }

        switch (lv)
        {
                case 4:
                        set_skill("staff", ntmp);
                        set_skill("fumo-zhang", ntmp);
                        map_skill("staff", "fumo-zhang");
                        set_skill("parry", ntmp);
                        map_skill("parry", "fumo-zhang");
                        set("chat_chance_combat", 100);
                        set("chat_msg_combat", ({
                        (: perform_action, "staff.lun" :),
                        (: perform_action, "staff.lun" :),
                        (: perform_action, "staff.lun" :),
                        (: exert_function, "recover" :),
                    (: exert_function, "powerup" :),
                        (: exert_function, "shield" :),
                        }) );
                        break;
                case 3:
                        set_skill("finger", ntmp + 200);
                        set_skill("tougu-zhen", ntmp + 200);
                        map_skill("finger", "tougu-zhen");
                        set_skill("parry", ntmp);
                        map_skill("parry", "tougu-zhen");
                                prepare_skill("finger", "tougu-zhen"); 
                        set("chat_chance_combat", 100);
                        set("chat_msg_combat", ({
                        (: perform_action, "finger.feng" :),
                        (: perform_action, "finger.feng" :),
                        (: perform_action, "finger.feng" :),
                        (: exert_function, "recover" :),
                    (: exert_function, "powerup" :),
                        (: exert_function, "shield" :),
                        }) );
                        break;
                case 2:
                        set_skill("blade", ntmp);
                        set_skill("jinwu-blade", ntmp);
                        map_skill("blade", "jinwu-blade");
                        set_skill("parry", ntmp);
                        map_skill("parry", "jinwu-blade");
                        set("chat_chance_combat", 100);
                        set("chat_msg_combat", ({
                        (: perform_action, "blade.chi" :),
                        (: perform_action, "blade.chi" :),
                        (: perform_action, "blade.jinwu" :),
                        (: exert_function, "recover" :),
                    (: exert_function, "powerup" :),
                        (: exert_function, "shield" :),
                        }) );
                        break;
                default:
                        set_skill("strike", ntmp);
                        set_skill("yinlong-shou", ntmp);
                        map_skill("strike", "yinlong-shou");
                        set_skill("parry", ntmp);
                        map_skill("parry", "yinlong-shou");
                                prepare_skill("strike", "yinlong-shou"); 
                        set("chat_chance_combat", 100);
                        set("chat_msg_combat", ({
                        (: perform_action, "strike.duo" :),
                        (: perform_action, "strike.duo" :),
                        (: perform_action, "strike.duo" :),
                        (: exert_function, "recover" :),
                    (: exert_function, "powerup" :),
                        (: exert_function, "shield" :),
                        }) );
                        break;
        }
        
        

 
                ntmp = to_int(EREN_GIFT_EXP * (1 + (lv - 1) * N_GIFT_EXP_INCREASE));
        set("gift/exp", ntmp);
        set("gift/pot", ntmp / 5);
        setup();
        
        switch (lv)
        {
                case 4:
                                ob = new("/clone/weapon/staff/muzhang");
                                ob->move(this_object()); 
                                ob->wield(); 
                        break;
                case 2:
                                ob = new("/clone/weapon/blade/zhadao");
                                ob->move(this_object()); 
                                ob->wield(); 
                        break;
        }
        
        call_out("es_die", 120 + random(60), this_object());//避免主id抢太多大米的
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
        return 1;
}

void unconcious()
{
        die(query_last_damage_from());
}

void init()
{
        if (playerp(this_player())) kill_ob(this_player());
}

void die(object killer)
{
         int showexp;
        object dob;             // 打晕这个NPC的人
        int n;                  // 可以奖励的人的数目
        int exp;                // 需要瓜分的经验
        int pot;                // 需要瓜分的潜能
        object *t;              // 杀死我的人的队伍列表
        object tob;
        int i;
                object *inv;

                object gift_ob;
                string s_gift, *key_s_gift;
                int gift_point;

        // 定义奖励物品列表
                mixed oblist;
                
                object env;

                oblist = query("oblist");


                // 通知当前房间，以便计算刷新
                env = environment(this_object());
                env->npc_die(this_object());
        // 找到杀了我(NPC)或是打晕我的人
        if (! objectp(dob = killer))
                dob = query_last_damage_from();

                if (! dob)
                {
                                destruct(this_object());
                                return;
                }

                //移动惩罚消弱
                addn_temp("xzz/ntrip2", -1, dob);
                addn_temp("xzz/nkill2", 1, dob);

                message_vision(NOR"$N轻轻一挥手，割下$n的项上首级。\n"NOR, dob, this_object());
                new(__DIR__"obj/head")->move(dob); 

        t = dob->query_team();

        if (objectp(dob) && environment(dob) == environment(this_object()))
        {
                exp = query("gift/exp");
                pot = query("gift/pot");
       
                                if( query("level", dob) <= query("level") ) 
                                {
                                }
                                else if( query("level", dob) <= query("level")*1.5 )
                                {
                                        exp /= 2;
                                        pot /= 2;
                                }
                                else if( query("level", dob) <= query("level")*2 )
                                {
                                        exp /= 4;
                                        pot /= 4;
                                }
                                else 
                                {
                                        exp = 100;
                                        pot = 100;
                                }
                                
                exp = to_int(exp * (random(100)+950) / 1000);
                showexp = exp;                
                                
                                CHANNEL_D->channel_broadcast(CHANL_NAME, 
                                        query("name", dob) + "于无锡杏子林击杀"+HIY+"「一品堂高手」"+HIR+query_temp("rename")+NOR+YEL+"，获得"+chinese_number(get_show_giftexp(dob, showexp))+"点经验奖励。"
                                        );

                                exp = invert_reborngiftd(dob, exp);
                                pot = exp / 5;


                n = 0;
                n = sizeof(t);

                                if (n > 1)
                                {
                                        exp /= n;
                                        pot /= n;
                                }

                                if (n)
                                {                                
                                        foreach(tob in t)
                                        {
                                                   if (objectp(tob) && living(tob) && environment(tob) == environment(this_object()))
                                                {
                                                                   addn("xingzilin/eren",1,tob);addn("xingzilin/exp",exp,tob);GIFT_D->delay_bonus(tob,
                                                                          ([ "exp"      : exp + ((tob == dob) ? exp / 10 : 0),
                                                                                 "pot"      : pot + ((tob == dob) ? pot / 10 : 0),
                                                                                 "prompt"   : "你的队伍杀死" + name() + "之后"]));

                                                 }
                                        }
                                }
                                else
                                {
                                                                   addn("xingzilin/eren",1,dob);addn("xingzilin/exp",exp,dob);GIFT_D->delay_bonus(dob,
                                                                          ([ "exp"      : exp,
                                                                                 "pot"      : pot,
                                                                                 "prompt"   : "你在杀死" + name() + "之后"]));
                                }

        }

                destruct(this_object());

        return;
}



