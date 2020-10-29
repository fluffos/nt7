#include <ansi.h>
inherit NPC;

void create()
{
       // set_name(HIY "刀魂" NOR, ({ "daohun" }) );

        set("gender", "无性");
        set("age", 35);

        // yun perform
        set("chat_chance_combat", 120); 
        set("chat_msg_combat", ({ 
              // 霸刀
              (: command("perform blade.daosha") :), 
              (: command("perform blade.juan") :),
              (: command("perform blade.gui") :), 
              (: command("perform blade.xiong") :), 
              (: command("perform blade.san") :), 

              (: exert_function, "powerup" :), 
              (: exert_function, "shield" :), 
              (: exert_function, "recover" :),
              (: exert_function, "dispel" :),
        }));

        //setup();

}


void init_npc(object me)
{
        object env, ob;
        
        mapping map_status, hp_status, my;
        string *mname;
        int i, temp;
        int percent;

        ob = this_object();
        env = environment(me);

        // 设置出生时间
        set("start_time", time(), ob);
        // 设置出生地点
        set("start_place", env, ob);
        // 设置归属
        set("owner",query("id",  me), ob);

        set_name(HIB+me->name()+HIB"的刀魂"NOR,({query("id", me)+"-daohun"}));
        set("long", HIM "据说当霸道修炼到一定程度便能够达到刀人合一的\n"
                        "境界，能够使手中的刀富有灵气，从而幻化出刀魂。\n" NOR);

        // 设置百分比
        if (me->query_skill("badao") >= 7000)
        {
                percent = 120;
        }
        else if (me->query_skill("badao") >= 6000)
        {
                percent = 110;
        }       
        else if (me->query_skill("badao") >= 5000)
        {
                percent = 100;
        }
        else if (me->query_skill("badao") >= 4500)
        {
                percent = 98;
        }
        else if (me->query_skill("badao") >= 4200)
        {
                percent = 96;
        }
        else if (me->query_skill("badao") >= 3800)
        {
                percent = 94;
        }
        else if (me->query_skill("badao") >= 3500)
        {
                percent = 92;
        }
        else if (me->query_skill("badao") >= 3200)
        {
                percent = 90;
        }
        else if (me->query_skill("badao") >= 2600)
        {
                percent = 88;
        }
        else if (me->query_skill("badao") >= 2300)
        {
                percent = 86;
        }
        else if (me->query_skill("badao") >= 2000)
        {
                percent = 84;
        }
        else
        {
                percent = 82;
        }
        
        // 削弱修正
        percent -= 20;
        
        // 设置技能     
        if (mapp(map_status = me->query_skill_map()))
        {
                mname = keys(map_status);

                temp = sizeof(map_status);
                for (i = 0; i < temp; i++)
                {
                       // 设置基本技能
                       ob->set_skill(mname[i], me->query_skill(mname[i], 1) * percent / 100); 
                       // 设置激发技能
                       ob->set_skill(map_status[mname[i]], me->query_skill(map_status[mname[i]], 1) * percent / 100);
                       // 激发技能
                       ob->map_skill(mname[i], map_status[mname[i]]);
                }
        }

        hp_status = me->query_entire_dbase();
        my = ob->query_entire_dbase();

        my["str"] = hp_status["str"] * percent / 200;
        my["int"] = hp_status["int"] * percent / 200;
        my["con"] = hp_status["con"] * percent / 300;
        my["dex"] = hp_status["dex"] * percent / 200;

        my["max_qi"]     = hp_status["max_qi"] / 10000  * percent + 100;
        my["eff_qi"]     = hp_status["eff_qi"] / 10000  * percent + 100;
        my["qi"]         = hp_status["qi"] / 10000  * percent + 100;
        my["max_jing"]   = hp_status["max_jing"] / 1000  * percent;
        my["eff_jing"]   = hp_status["eff_jing"] / 1000  * percent;
        my["jing"]       = hp_status["jing"] / 1000  * percent;
        my["jingli"]     = hp_status["jingli"] / 1000 * percent;
        my["max_jing"]   = hp_status["max_jing"] / 1000  * percent;
        my["max_jingli"] = hp_status["max_jingli"] / 1000  * percent;
        my["max_neili"]  = hp_status["max_neili"] / 5000  * percent;
        my["neili"]      = hp_status["neili"] / 5000  * percent;
        my["jiali"]      = 0;
        my["combat_exp"] = hp_status["combat_exp"] / 500  * percent;

        set_temp("apply/attack",query_temp("apply/attack", me)/2);
        set_temp("apply/damage",query_temp("apply/damage", me)/300*percent);

        ob->reset_action();

        ::setup();

        // 衣服
        carry_object("/clone/armor/daohun-cloth")->wear();
        // 武器
        carry_object("/clone/weapon/daohun-blade")->wield();
}

void heart_beat()
{
        object ob, env, owner, obtar;
        object *obs;
        
        keep_heart_beat();
        
        // 每3次心跳检查1次
        if (time() - query("last_check_heart_beat") >= 6)
        {
                set("last_check_heart_beat", time());
                
                // 如果不在出生房间超过1次则消失
                env = environment(this_object());
                if (! objectp(env) || env != query("start_place"))
                {
                        if (query("no_in_place") > 0)
                        {
                                // 消失
                                message_vision(HIG "$N" HIG "周身白光笼罩，伴随着刺眼的光芒，$N" HIG 
                                                   "瞬间化为乌有！\n" NOR, this_object());
                                destruct(this_object());
                                return;
                        }
                        else
                        {
                                addn("no_in_place", 1);
                        }
                }
                // 如果超过时间则消失
                if (time() - query("start_time") > 5*60)
                {
                        message_vision(HIG "$N" HIG "周身白光笼罩，伴随着刺眼的光芒，$N" HIG 
                                        "瞬间化为乌有！\n" NOR, this_object()); 
                        destruct(this_object());
                        return;
                }
                
                // 三次检查OWNER不存在则消失
                owner = find_player(query("owner"));
                if (! objectp(owner))
                {
                        addn("no_find_owner", 1);
                        if (query("no_find_ower") >= 3)
                        {
                                message_vision(HIG "$N" HIG "周身白光笼罩，伴随着刺眼的光芒，$N" HIG 
                                                "瞬间化为乌有！\n" NOR, this_object()); 
                                destruct(this_object());
                                return;                         
                        }
                }
                else // 随机攻击OWNER攻击的目标
                {
                        if (owner->is_fighting() && ! this_object()->is_fighting())
                        {
                                obs = owner->query_enemy();
                                if (sizeof(obs))
                                {
                                        obtar = obs[random(sizeof(obs))];
                                        message_combatd(HIR "\n$N" HIR "对$n" HIR "发动攻击……\n\n" NOR, this_object(), obtar); 
                                        this_object()->kill_ob(obtar);
                                }
                        }
                }
        }
        return ::heart_beat();
}

void init()
{

}

int accept_hit(object me)
{
        this_object()->kill_ob(me);
        return 1;
}

int accept_fight(object me)
{
        this_object()->kill_ob(me);
        return 1;
}

int accept_kill(object me)
{
        this_object()->kill_ob(me);
        return 1;
}

void unconcious()
{
        die();
}

void die(object killer)
{
        message_vision(HIG "$N" HIG "周身白光笼罩，伴随着刺眼的光芒，$N" HIG 
                                     "瞬间化为乌有！\n" NOR, this_object());
        destruct(this_object());
        return;
}
