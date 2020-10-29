// dream_npc.c

#include <ansi.h>

#define MAX_POINT     180000

inherit NPC;

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

void fight_ob(object ob)
{
        if( is_fighting() || !query("end_time") )
                return ::fight_ob(ob);

        set_temp("end_time", time() + query("end_time"));
        return ::fight_ob(ob);
}

varargs void unconcious(object defeater)
{
        object ob;

/*
        //if( query("end_boss") || query("fight_boss") )
        if( objectp(ob = previous_object(0)) && sscanf(base_name(ob), "/kungfu/skill/%*s") ) {
                full_self();
                return;
        }
*/
        die(defeater);
        return;
}

void init()
{
        // 随机攻击玩家
        if( userp(this_player()) && random(4) == 1 && !query_temp("apply/invisible", this_player()) )
        {
                kill_ob(this_player());
        }

        set("env/combatd", 4, this_player());
}

void die(object killer)
{
        object dob;             // 打晕这个NPC的人
        int n;                  // 可以奖励的人的数目
        int exp;                // 需要瓜分的经验
        int pot;                // 需要瓜分的潜能
        int exp2, pot2;
        object *t;              // 杀死我的人的队伍列表
        object tob;
        int i, mar;
        object *inv, objenv;

        object gift_ob;
        string s_gift, *key_s_gift;
        int gift_point;

        // 定义奖励物品列表
        mixed oblist;

        object env;
        object ob;
        int level;
        int percent;
        int gold;

/*
        //if( query("end_boss") || query("fight_boss") )
        if( objectp(ob = previous_object(0)) && sscanf(base_name(ob), "/kungfu/skill/%*s") ) {
                full_self();
                return;
        }
*/

        if( time() < query_temp("end_time", this_object()) ) // 时间没有到，死亡不了
        {
                addn("jing", query("max_jing") / 10);
                if( query("jing") > query("max_jing") ) set("jing", query("max_jing"));
                addn("eff_jing", query("max_jing") / 10);
                if( query("eff_jing") > query("max_jing") ) set("eff_jing", query("max_jing"));
                addn("qi", query("max_qi") / 10);
                if( query("qi") > query("max_qi") ) set("qi", query("max_qi"));
                addn("eff_qi", query("max_qi") / 10);
                if( query("eff_qi") > query("max_qi") ) set("eff_qi", query("max_qi"));
                message_vision(HIR "\n$N" HIR "全身泛起一道红光，奇迹般的活了下来！\n\n" NOR, this_object());
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

        // 帝王符图
        // 编号22-30
        if( query("quest_tuteng/start", dob) )
        {
                int n_tt;
                object ob_tt;

                if (random(10000) == 1)
                {
                        n_tt = 22 + random(14);
                        if (n_tt == 28 && random(10) > 1)n_tt = 25;
                        ob_tt = new("/clone/tuteng/diwang-suipian" + sprintf("%d", n_tt));
                        if (ob_tt)
                        {
                                write(HIG "你获得了一张帝王符图碎片。\n" NOR);
                                ob_tt->move(dob, 1);
                        }
                }
        }

        t = dob->query_team();

        if (objectp(dob) && environment(dob) == environment(this_object()))
        {
                exp = query("gift/exp");
                pot = query("gift/pot");
                mar = query("gift/mar");
                gold = query("gift/gold");
                level = query("gift/lvl");

                n = 0;
                n = sizeof(t);


                if (n > 1)
                {
                        exp /= n;
                        pot /= n;
                        mar /= n;
                        gold /= n;
                }

                if (n)
                {
                        foreach(tob in t)
                        {
                                if (! objectp(tob))continue;

                                exp2 = exp;
                                pot2 = pot;

                                // 佩带斩妖勋章增加10%
                                if( tob->query_all_buff("zhanyao") )
                                {
                                        exp2 = exp2 + exp2 / 10;
                                        pot2 = pot2 + pot2 / 10;
                                }
                                // 佩带十周年纪念勋章增加5%
                                if( tob->query_all_buff("year10") )
                                {
                                        exp2 = exp2 + exp2 / 20;
                                        pot2 = pot2 + pot2 / 20;
                                }

                                if (objectp(tob) && living(tob))
                                {
                                        if (environment(tob) == environment(dob))
                                        {
                                                if( level && query("level", tob) > level ) percent = 50;
                                                else percent = 100;
                                                GIFT_D->event_bonus(tob,
                                                        ([ "exp"      : exp2 + ((tob == dob) ? exp2 / 10 : 0),
                                                           "pot"      : pot2 + ((tob == dob) ? pot2 / 10 : 0),
                                                           "mar"      : mar + ((tob == dob) ? mar / 10 : 0),
                                                           "gold"     : gold,
                                                           "percent"  : percent,
                                                           "prompt"   : "你的队伍杀死" + name() + "之后"]));
                                        }
                                }
                        }
                }
                else
                {
                        // 佩带斩妖勋章增加10%
                        if( dob->query_all_buff("zhanyao") )
                        {
                                exp = exp + exp / 10;
                                pot = pot + pot / 10;
                        }
                        // 佩带十周年纪念勋章增加5%
                        if( dob->query_all_buff("year10") )
                        {
                                exp = exp + exp / 20;
                                pot = pot + pot / 20;
                        }
                        if( level && query("level", dob) > level ) percent = 50;
                        else percent = 100;

                        GIFT_D->event_bonus(dob,
                                ([ "exp"      : exp,
                                   "pot"      : pot,
                                   "mar"      : mar,
                                   "gold"     : gold,
                                   "percent"  : percent,
                                   "prompt"   : "你在杀死" + name() + "之后"]));
                }
        }

        // 一定几率掉物品在杀我的人身上dob
        if (objectp(dob) && environment(dob) == environment(this_object()))
        {
                key_s_gift = keys(oblist);
                s_gift = key_s_gift[random(sizeof(key_s_gift))];
                gift_point = oblist[s_gift];

                // 判断几率
                if( random(10) == 1
                        && random(MAX_POINT / ITEM_D->gift_point()) < gift_point )
                {
                        // 获得物品--爆出物品
                        gift_ob = new(s_gift);
                        if (objectp(gift_ob))
                        {
                                message_vision(HIR "叮~~一声，从$N" HIR "身上掉出一样东西。\n" NOR, this_object(), dob);
                                set("who_get/id", query("id", dob), gift_ob);
                                set("who_get/time", time()+60, gift_ob);//一分钟内只能自己捡取
                                gift_ob->move(environment(this_object()));
                        }
                }
        }

        // 掉出金钱及其他物品
        if (random(5) == 1)
        {
                inv = all_inventory(this_object());
                inv -= ({ 0 });
                i = sizeof(inv);
                while (i--)
                {
                        if (objectp(dob))
                        {
                                set("who_get/id", query("id", dob), inv[i]);
                                set("who_get/time", time()+60, inv[i]);
                        }
                        inv[i]->move(environment(this_object()));
                }
        }

        // 1/550000几率掉出无名铜人
        if (random(550000) == 1 && objectp(dob))
        {
                object ob_tongren;

                if( random(2) )
                        ob_tongren = new("/clone/tongren/tongren1");
                else
                        ob_tongren = new("/clone/tongren/tongren2");
                ob_tongren->move(dob, 1);
                write(HIR "你得到一个" + ob_tongren->name() + HIR "。\n");
        }

        //1/5000几率掉出蓬莱仙果
        if (random(5000) == 1 && objectp(dob))
        {
                object ob_xianguo;

                ob_xianguo = new("/clone/fam/item/penglai-xianguo");
                ob_xianguo->move(dob, 1);
                write(HIR "你得到一颗" + ob_xianguo->name() + HIR "。\n");
        }

        // 在九头蛇领地杀死九头蛇可获取少量体会
        objenv = environment(this_object());
        if( objectp(objenv) && query("short", objenv) == "九头蛇领地" )
        {
                mar = 50;
/*
                if( query("experience", dob) >= 2000000000) mar=0;
                if( query("experience", dob)-query("learned_experience", dob) >= 10000000) mar=0;
*/
                addn("experience", mar, dob);
        }

        destruct(this_object());

        return;
}
