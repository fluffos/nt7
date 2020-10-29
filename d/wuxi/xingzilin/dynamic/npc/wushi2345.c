// This program is a part of NITAN MudLIB 
// redl 2012/11/1 
#include <ansi.h>
#include "../../cnpc.h"

inherit NPC;


#define N_JINGQI_INCREASE 0.25  //每提升一品的增加百分比
#define N_NEILI_INCREASE 0.25
#define N_GIFT_EXP_INCREASE 0.2


mapping wushi_names = ([
        1 : "五品",
        2 : "四品",
        3 : "三品",
        4 : "二品",
]);


void create()
{
        object ob; 
        int lv, ntmp;
        
        lv = random(1000);
        if (lv < 1) lv = 4;
                else if (lv < 10) lv = 3;
                else if (lv < 100) lv = 2;
                else lv = 1;
        
     
        set_name(HIR + wushi_names[lv] + "武士" NOR, ({ "wu shi", "wu"}));
        set("nickname", HIY "西夏一品堂" NOR);
        set("long", 
"西夏国有个讲武馆，叫做一品堂，是该国国王所立，堂中招聘武功高强之士，优礼供养。\n"
"这是一品堂中的高级" + wushi_names[lv] + "武士，据说受赫连大将军带领，此来不知道对中原有什么图谋......\n"
        );
        
        set("age", 32);
        set("str", 40);
        set("dex", 35);
        set("con", 35);
        set("int", 25);
        ntmp = to_int(WU2345_QI_BASE * (1 + lv * N_JINGQI_INCREASE));
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
        
        set("level", WU2345_LEVEL + WU2345_LEVEL_INCREASE * (lv-1));
        set("combat_exp", 800000000);
                set("jiali", 4000 + 1000 * lv);

        set_temp("apply/parry", 100 * lv);
        set_temp("apply/dodge", 100 * lv);
        set_temp("apply/dex", 100 * lv);
        set_temp("apply/attack", 100 * lv);
        set_temp("apply/defense", 100 * lv);
        set_temp("apply/unarmed_damage", 100 * lv);
        set_temp("apply/damage", 100 * lv);
        set_temp("apply/armor", 100 * lv);

                //二三品高手1/10获得优化技能，而不是等级提高。+趣味和偶然
                ntmp = to_int(WU2345_SKILL_LV + (lv-1) * WU2345_SKILL_INCREASE);
        
        if (!random(3))
        {
                set_skill("count", ntmp / 10 * 6);
                set_skill("martial-cognize", ntmp / 10 * 9);
        }
        else
        {
                //set_skill("count", ntmp / 10 * 1);
                set_skill("martial-cognize", ntmp / 10 * 5);
        }
        
        set_skill("strike", ntmp);
        set_skill("parry", ntmp);
                if (lv >= 3 && random(10) == 0)
                {
                        set_skill("tie-zhang", ntmp);
                map_skill("strike", "tie-zhang");
                        prepare_skill("strike", "tie-zhang"); 
                        map_skill("parry", "tie-zhang");
                }
                else if (random(2))
                {
                        set_skill("kuaihuo-strike", ntmp);        
                map_skill("strike", "kuaihuo-strike");
                        prepare_skill("strike", "kuaihuo-strike"); 
                        map_skill("parry", "kuaihuo-strike");
                }
                else
                {
                        set_skill("songyang-strike", ntmp);        
                map_skill("strike", "songyang-strike");
                        prepare_skill("strike", "songyang-strike"); 
                        map_skill("parry", "songyang-strike");
                }
        
        set_skill("force", ntmp);
                if (lv >= 3 && random(10) == 0)
                {
                        set_skill("xixing-dafa", ntmp);
                map_skill("force", "xixing-dafa");
                }
                else if (random(2))
                {
                        set_skill("biyun-xinfa", ntmp);        
                map_skill("force", "biyun-xinfa");
                }
                else
                {
                        set_skill("riyue-xinfa", ntmp);        
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
 
                ntmp = to_int(WU2345_GIFT_EXP * (1 + (lv - 1) * N_GIFT_EXP_INCREASE));
        set("gift/exp", ntmp);
        set("gift/pot", ntmp / 5);
        setup();
        
      
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



        object me,ob;
        me = this_object();
        if(random(3) && //66%不能call die?
         objectp(ob = previous_object(0)) &&
            sscanf(base_name(ob), "/kungfu/skill/%*s") ) {
                me->full_self();
                return;
        }



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
                if (query_temp("xzz/ntrip2", dob)>-1) addn_temp("xzz/ntrip2", -1, dob);
                addn_temp("xzz/nkill2", 1, dob);


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

                                exp = invert_reborngiftd(dob, exp);
                                pot = exp / 4;

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
                                                                   addn("xingzilin/wushi2345",1,tob);addn("xingzilin/exp",exp,tob);GIFT_D->delay_bonus(tob,
                                                                          ([ "exp"      : exp + ((tob == dob) ? exp / 10 : 0),
                                                                                 "pot"      : pot + ((tob == dob) ? pot / 10 : 0),
                                                                                 "prompt"   : "你的队伍杀死" + name() + "之后"]));

                                                 }
                                        }
                                }
                                else
                                {
                                                                   addn("xingzilin/wushi2345",1,dob);addn("xingzilin/exp",exp,dob);GIFT_D->delay_bonus(dob,
                                                                          ([ "exp"      : exp,
                                                                                 "pot"      : pot,
                                                                                 "prompt"   : "你在杀死" + name() + "之后"]));
                                }

        }

                destruct(this_object());

        return;
}
