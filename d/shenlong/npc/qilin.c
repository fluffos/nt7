#include <ansi.h>

#define MEMBER_D "/adm/daemons/memberd"
#define MAX_POINT 100

inherit NPC;

void check_weapon();
void check_environment();
void check_time();

void create()
{
        set_name(HIR "火麒麟" NOR, ({ "huo qilin", "huo", "qilin" }) );
        set("title", HIY "上古神兽" NOR);
        set("long", HIR "这是一只传说中的上古神兽—火麒麟，只见它浑身似火，散射着令人窒息的炽热。\n"
                        "仔细一看，这只火麒麟经过千万年修炼，已经化为人形，威风无比，令人敬畏。\n" NOR);

        set("gender", "男性");
        set("age", 999);

        set("str", 120);
        set("int", 120);
        set("con", 120);
        set("dex", 120);

        set("shen", 8000000);

        set_temp("apply/attack", 30000);
        set_temp("apply/unarmed_damage", 20000);
        set_temp("apply/damage", 20000);
        set_temp("apply/armor", 20000);
        set_temp("apply/qy", 20);  // 气运
        set_temp("apply/fy", 20);  // 福缘

        set("scborn/ok", 1);

        set("max_qi", 15000000000);
        set("eff_qi", 15000000000);
        set("qi", 15000000000);

        set("max_jing", 10000000000);
        set("jing", 10000000000);
        set("eff_jing", 10000000000);
        set("max_jingli", 10000000000);
        set("jingli", 10000000000);

        set("neili", 2000000000);
        set("max_neili", 30000000);
        set("jiali", 20000);
        set("combat_exp", 2100000000);

        set_skill("unarmed", 2500);
        set_skill("finger", 2500);
        set_skill("claw", 2500);
        set_skill("strike", 2500);
        set_skill("hand", 2500);
        set_skill("cuff", 2500);
        set_skill("parry", 2500);
        set_skill("dodge", 2500);
        set_skill("force", 2500);
        set_skill("sword", 2500);
        set_skill("blade", 2500);
        set_skill("zuoyou-hubo", 2500);

        set_skill("badao", 2500);
        set_skill("jiuyang-shengong", 2500);
        set_skill("taiji-jian", 2500);
        set_skill("liumai-shenjian", 2500);
        set_skill("martial-cognize", 2500);
        set_skill("literate", 2500);
        set_skill("tianwei-zhengqi", 500);

        set_skill("jingluo-xue", 2000);

         set("no_nuoyi", 1); // 不被挪移影响

        map_skill("parry", "jiuyang-shengong");
        map_skill("force", "jiuyang-shengong");
        map_skill("dodge", "jiuyang-shengong");
        map_skill("unarmed", "jiuyang-shengong");
        map_skill("finger", "liumai-shenjian");
        map_skill("strike", "jiuyang-shengong");
        map_skill("hand", "jiuyang-shengong");
        map_skill("cuff", "jiuyang-shengong");
        map_skill("claw", "jiuyang-shengong");
        map_skill("sword", "taiji-jian");

        prepare_skill("claw", "jiuyin-shengong");
        prepare_skill("cuff", "jiuyin-shengong");
        prepare_skill("finger", "liumai-shenjian");

        // yun perform
        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
              // 太极剑
              (: command("perform sword.sui and sword.chan") :),
              (: command("perform sword.jian and sword.zhuan") :),
              (: command("perform sword.zhenwu and sword.jian") :),
              (: command("perform sword.jian twice") :),
              (: command("perform sword.jian and finger.tian") :),
              // 六脉神剑
              (: command("perform finger.six twice") :),
              (: command("perform finger.qi twice") :),
              (: command("perform finger.zong and finger.tian") :),
              (: command("perform finger.tian twice") :),

              (: exert_function, "roar" :),
              (: exert_function, "powerup" :),
              (: exert_function, "shield" :),
              (: exert_function, "roar" :),
              (: exert_function, "recover" :),
              (: exert_function, "recover" :),
              (: exert_function, "dispel" :),
              (: check_weapon :),
              (: check_time :),
        }));

        set("my_life", 1); // 当气血低于10%的时候补满一次，设置该参数为0

        setup();

        // 衣服需要更改，不穿衣服？
        //carry_object("/clone/cloth/cloth")->wear();

        // 武器
        carry_object("/clone/weapon/chi-jian")->wield();

        // 设置地点
        set("startroom", "/d/shenlong/huodong1");

}

void heart_beat()
{
        keep_heart_beat();

        if( !environment(this_object()) )
                return ::heart_beat();

        // 检查出现时间
        if (random(2))check_time();

        if( !objectp(this_object()) ) return;
        if( !environment(this_object()) )
                return ::heart_beat();
        if (random(5) == 1)check_weapon();

        return ::heart_beat();
}

// 检查时间 6 小时后消失
// 未战斗状态下消失
void check_time()
{
        int t;
        object env;

        t = time() - query("life_time");

        if (t > 60 && ! is_fighting())
        {
                env = environment(this_object());
                env->move_all_player_out(1);
                destruct(this_object());
                return;
        }

        if (t > 6 * 3600)
        {
                message_vision(BLINK + HIG "\n此次对抗火麒麟已经超过6小时，挑战失败！\n" NOR, this_object());
                env = environment(this_object());
                env->move_all_player_out(1);
                destruct(this_object());
                return;
        }

        return;
}

// 检查地点
void check_environment()
{        /*
        if (! environment(this_object()))return;

        if (base_name(environment(this_object())) != query("startroom"))
        {
                command("say 咦？我怎么会在这里，有人作弊，有人作弊，巫师快出来！");
                destruct(this_object());
        }
        */

}

// 检查武器
void check_weapon()
{
        object me, ob;

        me = this_object();

        // 同时补充内力
        set("neili", query("max_neili"));

        if (me->is_busy())me->interrupt_busy(me, 1000);

        if (me->is_busy())me->interrupt_me(me);

        if( !query_temp("weapon", me) )
        {
                ob = new("/clone/weapon/chi-jian");
                ob->move(me);
                "/cmds/std/wield"->main(me, "chi jian");
        }

        if (random(5) == 1)
        {
                delete_temp("no_perform", me);
                delete_temp("no_exert", me);

                addn_temp("apply/damage", 20000, me);
                if (random(10) == 1)
                        command("perform sword.jian twice");
                else
                        command("perform sword.jian and finger.tian");
                addn_temp("apply/damage", -20000, me);

                if (random(2))
                {
                        delete_temp("eff/jiuyin-shengong/xin", me);
                }
        }

        if (random(20) == 1)
        {
                me->clear_condition();
        }

        // 很小几率恢复气血
        if (random(50) == 1)
        {
                //log_file("qilin", "成功恢复气血。\n");
                if( query("eff_qi", me)<query("max_qi", me)/3)addn("eff_qi",query("max_qi",  me)/5, me);
                if( query("qi", me)<query("max_qi", me)/3)addn("qi",query("max_qi",  me)/5, me);
        }

        if (me->is_busy())me->interrupt_busy(me);

        if (! me->is_fighting() || random(5) == 1)
        {
                command("yun roar");
        }

        return;
}

void init()
{
        object me;

        me = this_player();

        if (! wizardp(me))this_object()->kill_ob(me);
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

void new_life()
{
        object me = this_object();

        // 补满气血
        set("eff_qi",query("max_qi", me), me);
        set("qi",query("max_qi", me), me);
        set("eff_jing",query("max_jing", me), me);
        set("jing",query("max_jing", me), me);
        set("jingli",query("max_jingli", me), me);

        me->clear_condition();

        me->interrupt_me(this_object());

        delete_temp("no_perform", me);
        delete_temp("no_exert", me);

        set_temp("apply/attack", 30000, me);
        set_temp("apply/unarmed_damage", 20000, me);
        set_temp("apply/damage", 20000, me);
        set_temp("apply/armor", 20000, me);
        set_temp("apply/qy", 30, me);//气运
        set_temp("apply/kar", 30, me);//福缘

        delete("my_life", me);

        message_vision(HIG "\n$N" HIG "大叫一声，浑身散发着火红的金光，刹那间，如获重生！\n\n" NOR, me);

        return;
}

int receive_damage(string type, int damage, object who)
{
        object ob;

        object me = this_object();

        if( !query("my_life", me))return ::receive_damage(type,damage,who);

        if( query("qi", me)<query("max_qi", me)/10 )
        {
                new_life(); // 重生一次
                return 0;
        }

        return ::receive_damage(type, damage, who);
}

void unconcious()
{
        object ob;

        if( objectp(ob = previous_object(0)) && sscanf(base_name(ob), "/kungfu/skill/%*s") )
        {
                full_self();
                return;
        }

        die(query_last_damage_from());
}

// 检查生命
void check_life()
{
        object env;

        // 如果life<=1则死亡
        if (1)
        {
                message_vision(HIR "\n$N" HIR "长啸一声，身体化作一团火球，消失了！\n" NOR, this_object());

                message_vision(BLINK + HIY "\n此次对抗火麒麟已经结束，2分钟后清场，请抓紧时间。\n\n" NOR, this_object());

                env = environment(this_object());
                env->move_all_player_out(120);
                set("doing", 1, env);
                destruct(this_object());
        }
}

void die(object killer)
{
        object dob;             // 打晕这个NPC的人
        int n;                  // 可以奖励的人的数目
        int exp;                // 需要瓜分的经验
        int pot;                // 需要瓜分的潜能
        int weiwang;            // 需要瓜分的威望
        int score;              // 需要瓜分的阅历
        object *t;              // 杀死我的人的队伍列表
        object tob;
        int mar;                //  需要瓜分的体会
        int i;
        string prop, name;
        mapping data;
        object ob, where;
        string *apply = ({ "reduce_busy", "avoid_busy", "def_damage", "avoid_weak",
                "add_forget", "reduce_damage", "add_busy", "add_weak", "avoid_forget",
                "add_metal", "reduce_metal", "add_wood", "reduce_wood", "add_water", "reduce_water",
                "add_fire", "reduce_fire", "add_earth", "reduce_earth",
                "add_damage", "add_skill" });


        // 定义奖励物品列表
        // 几率  X / 百分之
        mixed oblist = ([
                "/clone/armor/qilin/jixing"              :              20,
                "/clone/armor/qilin/jinghua"             :              20,
                "/clone/armor/qilin/yaoyan"              :              20,
                "/clone/armor/qilin/jinlinyi"            :              20,
                "/clone/armor/qilin/yanmie"              :              20,
        ]);

        object gift_ob, gift_huoyan;
        string s_gift, *key_s_gift;
        string huoyan = "/clone/armor/qilin/jiezhi";
        int gift_point;

        if( objectp(ob = previous_object(0)) && sscanf(base_name(ob), "/kungfu/skill/%*s") )
        {
                full_self();
                return;
        }

        // 如果还未重生，则重生一次
        if (query("my_life"))
        {
                new_life();
                return;
        }

        // 找到杀了我(NPC)或是打晕我的人
        if (! objectp(dob = killer))
                dob = query_last_damage_from();

        if (! dob)
        {
                // 调用生命检查函数
                check_life();
                return;
        }

        t = dob->query_team();

        if (objectp(dob) && environment(dob) == environment(this_object()))
        {
                exp = 800000 + random(400000);
                pot = 400000 + random(200000);
                weiwang = 6000 + random(9000);
                score = 6000 + random(6000);
                mar = 6000 + random(6000);
                n = 0;

                n = sizeof(t);
                if (! n || n < 3)
                {
                       exp /= 5;
                       pot /= 5;
                       weiwang /= 3;
                       score /= 3;
                       mar /= 5;
                }

                if (n >= 3)
                {
                        exp /= n;
                        pot /= n;
                        weiwang /= n;
                        score /= n;
                        mar /= n;
                }

                if (n)
                {
                        foreach(tob in t)
                        {
                                if (objectp(tob) && living(tob))
                                {
                                        // 会员奖励再提高10%
                                        /*
                                        if( MEMBER_D->is_valid_member(query("id", tob)) )
                                        {
                                                if (environment(tob) == environment(dob))
                                                        GIFT_D->delay_boss_bonus(tob,
                                                                     ([ "exp"      : exp + exp * 1 / 10 + ((tob == dob) ? 50000 : 0),
                                                                   "pot"      : pot + pot * 1 / 10 / 10 + ((tob == dob) ? 50000 : 0),
                                                                     "weiwang"  : weiwang + weiwang * 1 / 10 + ((tob == dob) ? 50000 : 0),
                                                                   "score"    : score + score * 1 / 10 + ((tob == dob) ? 50000 : 0),
                                                                   "mar"      : mar + mar * 1 / 10 + ((tob == dob) ? 50000 : 0),
                                                                   "prompt"   : "你的队伍杀死" + name() + HIG "之后"]), 999);
                                        }
                                        else */
                                        {
                                                if (environment(tob) == environment(dob))
                                                        GIFT_D->delay_boss_bonus(tob,
                                                                     ([ "exp"      : exp + ((tob == dob) ? 50000 : 0),
                                                                   "pot"      : pot + ((tob == dob) ? 50000 : 0),
                                                                   "weiwang"  : weiwang + ((tob == dob) ? 50000 : 0),
                                                                   "score"    : score + ((tob == dob) ? 50000 : 0),
                                                                   "mar"      : mar + ((tob == dob) ? 50000 : 0),
                                                                   "prompt"   : "你的队伍杀死" + name() + HIG "之后"]), 100);
                                        }

                                }
                        }
                }
                else
                {
                        /*
                        if( MEMBER_D->is_valid_member(query("id", dob)) )
                        {
                                GIFT_D->delay_boss_bonus(dob,
                                        ([ "exp"      : exp + exp * 3 / 10,
                                           "pot"      : pot + pot * 3 / 10,
                                           "weiwang"  : weiwang + weiwang * 3 / 10,
                                           "score"    : score + score * 3 / 10,
                                           "mar"      : mar + mar * 3 / 10,
                                           "prompt"   : "你在杀死" + name() + HIG "之后"]), 999);
                        }

                        else */
                        {
                                GIFT_D->delay_boss_bonus(dob,
                                        ([ "exp"      : exp,
                                           "pot"      : pot,
                                           "weiwang"  : weiwang,
                                           "score"    : score,
                                           "mar"      : mar,
                                           "prompt"   : "你在杀死" + name() + HIG "之后"]), 100);
                       }
                }
        }

        // 100%掉一件物品
        if (1)
        {
                key_s_gift = keys(oblist);
                s_gift = key_s_gift[random(sizeof(key_s_gift))];
                gift_point = oblist[s_gift];

                gift_ob = new(s_gift);
                if (objectp(gift_ob))
                {
                        message_vision(HIC "当~~一声，从$N" HIC "身上掉出" + gift_ob->name() + HIC "，落在地上。\n" NOR, this_object());
                        set("who_get/id", "NONE", gift_ob);
                        set("who_get/time", time()+30, gift_ob);//30秒内都不能捡取
                        gift_ob->move(environment(this_object()));
                }
                else // 纪录之
                {
                        //log_file("qilin-gift-none", s_gift + "\n");
                }
        }

        // 20%几率掉出火眼之戒
        if (random(10) < 2)
        {
                gift_huoyan = new(huoyan);
                set("who_get/id", "NONE", gift_huoyan);
                set("who_get/time", time()+30, gift_huoyan);//30秒内都不能捡取
                gift_huoyan->move(environment(this_object()));
                message_vision(HIW "叮~~一声，从$N" HIW "身上掉出" + gift_huoyan->name() +
                               HIW "，落在地上。\n" NOR, this_object());

                //log_file("qilin_gift", "火麒麟于 " + ctime(time()) + " 掉出火眼之戒。\n");
        }

        where = environment();

        prop = apply[random(sizeof(apply))];
        name = EQUIPMENT_D->chinese(prop)+"元素";

        data = ([]);
        data["element"] = prop;
        data["name"] = name;
        ob = TEMPLATE_D->create_object("/inherit/template/element/element", prop, data);
        ob->set_name(name, ({prop, "element"}));
        ob->move(where);
        message_vision(HIC "叮~~一声，从$N" HIC "身上掉出" + ob->name() + NOR + HIC "，落在地上。\n" NOR, this_object());
        // 检查生命
        check_life();

        return ;
}
