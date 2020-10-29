#include <ansi.h>

#define MEMBER_D "/adm/daemons/memberd"
#define MAX_POINT 200

inherit NPC;

string slong();

void check_weapon();
void check_environment();
void die_gift();
void check_time();
void random_move();

void create()
{
        set_name(HIR "九头蛇精" NOR, ({ "jiutou shejing", "jiutou", "shejing" }) );
        set("title", HIY "千年" NOR);
        set("gender", "女性");
        set("age", 999);

        set("str", 60);
        set("int", 80);
        set("con", 60);
        set("dex", 70);

        set_temp("apply/attack", 5000);
        set_temp("apply/unarmed_damage", 5000);
        set_temp("apply/damage", 5000);
        set_temp("apply/armor", 5000);

        set("max_qi", 9000000000);
        set("eff_qi", 9000000000);
        set("qi", 9000000000);

        set("max_jing", 9000000000);
        set("jing", 9000000000);
        set("eff_jing", 9000000000);
        set("max_jingli", 9000000000);
        set("jingli", 9000000000);

        set("neili", 2000000000);
        set("max_neili", 20000000);
        set("jiali", 4000);
        set("combat_exp", 2100000000);

        set_skill("unarmed", 1500);
        set_skill("finger", 1500);
        set_skill("claw", 1500);
        set_skill("strike", 1500);
        set_skill("hand", 1500);
        set_skill("cuff", 1500);
        set_skill("parry", 1500);
        set_skill("dodge", 1500);
        set_skill("force", 1500);
        set_skill("sword", 1500);
        set_skill("pixie-jian",1500);
        set_skill("blade", 1500);
        set_skill("zuoyou-hubo", 1500);

        set_skill("badao", 1500);
        set_skill("jiuyin-shengong", 1500);
        set_skill("martial-cognize", 1600);
        set_skill("literate", 1500);

        set("no_nuoyi", 1); // 不被挪移影响

        map_skill("parry", "jiuyin-shengong");
        map_skill("force", "jiuyin-shengong");
        map_skill("dodge", "jiuyin-shengong");
        map_skill("unarmed", "jiuyin-shengong");
        map_skill("finger", "jiuyin-shengong");
        map_skill("strike", "jiuyin-shengong");
        map_skill("hand", "jiuyin-shengong");
        map_skill("cuff", "jiuyin-shengong");
        map_skill("claw", "jiuyin-shengong");
        map_skill("sword", "pixie-jian");
        map_skill("blade", "badao");

        prepare_skill("claw", "jiuyin-shengong");
        prepare_skill("cuff", "jiuyin-shengong");

        // 生命
        set("life", 9);

        // yun perform
        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                // 霸刀
                (: command("perform blade.san and blade.juan") :),
                (: command("perform blade.gui and blade.xiong") :),
                (: command("perform blade.gui twice") :),
                (: command("perform blade.xiong twice") :),
                (: command("perform blade.xiong and balde.juan") :),
                (: command("perform blade.gui and blade.juan") :),
                (: command("perform blade.dasha and blade.san") :),
                (: command("perform blade.san twice") :),
                (: command("perform blade.san twice") :),
                (: command("perform blade.san twice") :),
                (: command("perform blade.san twice") :),
                // 九阴神功
                (: command("perform claw.zhua twice") :),
                (: command("perform claw.xin twice") :),
                (: command("perform shou twice") :),
                (: command("perform quan twice") :),

                (: exert_function, "roar" :),
                (: exert_function, "powerup" :),
                (: exert_function, "shield" :),
                (: exert_function, "roar" :),
                (: exert_function, "recover" :),
                (: check_weapon :),
                (: check_environment :),
                (: check_time :),
        }));

        set("long", HIR "这是一条存活千年的蛇精，经过千年的修炼，已化为人形，与常人无异。\n"
                    HIM "她美若天仙，清丽绝俗，风姿动人，难以用人间任何语言形容。\n"
                    HIM "她面色苍白，没有一丝血色，似乎毫无情感，从不动容。\n" NOR + slong());

        setup();

        // 衣服需要更改，不穿衣服？
        //carry_object("/clone/cloth/cloth")->wear();

        // 武器
        carry_object("/clone/weapon/haoyue-wandao")->wield();

        // 设置地点
        set("startroom", "/d/shenlong/shejingdong");

}

void heart_beat()
{
        keep_heart_beat();

        if( !environment(this_object()) )
        {
                set_heart_beat(0);
                return;
        }

        check_time();
        check_environment();

        if( !objectp(this_object()) ) return;
        if( !environment(this_object()) )
                return;
        return ::heart_beat();
}

// 检查时间 6 小时后消失
// 未战斗状态下消失
void check_time()
{
        int t;
        object env;

        // 同时补充内力
        set("neili", 20000000);

        t = time() - query("life_time");

        if (t > 60 && ! is_fighting())
        {
                env = environment(this_object());
                env->move_all_player_out(1);
                destruct(this_object());
                return;
        }

        if (t > 2 * 3600)
        {
                message_vision(BLINK + HIG "\n此次对抗蛇精已经超过2小时，挑战失败！\n" NOR, this_object());
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

        if( !query_temp("weapon", me) )
        {
                ob = new("/clone/weapon/haoyue-wandao");
                ob->move(me);
                "/cmds/std/wield"->main(me, "haoyue wandao");
        }

        // 同时补充内力
        set("neili", 20000000);

        if (random(10) == 1)
        {
                //log_file("shejing", "成功删除BUSY，NO_PERFORM等状态数据。。\n");
                delete_temp("no_perform", me);
                delete_temp("no_exert", me);
                me->interrupt_me(me);

                addn_temp("apply/damage", 50000, me);
                command("perform blade.san twice");
                addn_temp("apply/damage", -50000, me);

                if (random(2))
                {
                        delete_temp("eff/jiuyin-shengong/xin", me);
                }
        }

        if (me->is_busy()) me->interrupt_busy(this_object(),1000);

        // 很小几率恢复气血
        if (random(20) == 1)
        {
                //log_file("shejing", "成功恢复气血。\n");
                if( query("eff_qi", me)<query("max_qi", me)/3)addn("eff_qi",query("max_qi",  me)/5, me);
                if( query("qi", me)<query("max_qi", me)/3)addn("qi",query("max_qi",  me)/5, me);
        }

        return;
}

// 返回描述
string slong()
{
        string msg;

        msg = HIG "只见蛇精肩膀还有 " + chinese_number(query("life")) + " 个头。\n" NOR;

        return msg;
}

void init()
{
        object me;

        me = this_player();

        if (! wizardp(me))
                this_object()->kill_ob(me);
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

int receive_damage(string type, int damage, object who)
{
        object ob;

        if (! objectp(who))
                return ::receive_damage(type, damage, who);

        if( random(10000) == 1 && time()-query_temp("last_get_shejing_linpian", who)>1800 )
        {
                ob = new("/d/shenlong/npc/obj/linpian");
                ob->move(who, 1);
                set("last_get_shejing_linpian", time(), ob);
                tell_object(who, HIG "\n你从" + name() + HIG "身上获得了" + ob->name() + HIG "。\n" NOR);
        }

        if (random(100000) == 1)
        {
                check_weapon();
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
        if (query("life") <= 1)
        {
                message_vision(HIR "\n$N" HIR "长啸一声，身体慢慢变得透明，消失了！\n" NOR, this_object());

                message_vision(BLINK + HIY "\n此次对抗蛇精已经结束，2分钟后清场，请抓紧时间。\n\n" NOR, this_object());

                env = environment(this_object());
                env->move_all_player_out(120);
                set("doing", 1, env);
                destruct(this_object());
        }
        else
        {
                // 减少生命

                message_vision(HIR "\n喀嚓~一声，一颗头颅从$N" HIR "肩膀上掉了下来，化作一滩血污 …… 一股刺鼻的血腥味"
                             "扑鼻而来！\n" NOR, this_object());

                set("str", 60);
                set("int", 80);
                set("con", 60);
                set("dex", 60);

                set("max_qi", 90000000);
                set("eff_qi", 90000000);
                set("qi", 90000000);

                set("max_jing", 90000000);
                set("jing", 90000000);
                set("eff_jing", 90000000);
                set("max_jingli", 90000000);
                set("jingli", 90000000);

                set("neili", 20000000);
                set("max_neili", 150000);
                set("jiali", 400);
                set("combat_exp", 2100000000);
                revive();

                addn("life", -1);

                // 最后一个头加强威力
                if (query("life") == 1)
                {
                        set_skill("unarmed", 2000);
                        set_skill("finger", 2000);
                        set_skill("claw", 2000);
                        set_skill("strike", 2000);
                        set_skill("hand", 2000);
                        set_skill("cuff", 2000);
                        set_skill("parry", 2000);
                        set_skill("dodge", 2000);
                        set_skill("force", 2000);
                        set_skill("sword", 2000);
                        set_skill("pixie-jian",2000);
                        set_skill("blade", 2000);
                        set_skill("zuoyou-hubo", 2000);

                        set_skill("badao", 2000);
                        set_skill("jiuyin-shengong", 2000);
                        set_skill("martial-cognize", 2000);
                }

                set("long", HIR "这是一条存活千年的蛇精，经过千年的修炼，已化为人形，与常人无异。\n"
                               HIM "她美若天仙，清丽绝俗，风姿动人，难以用人间任何语言形容。\n"
                            HIM "她面色苍白，没有一丝血色，似乎毫无情感，从不动容。\n" NOR + slong());

                set("neili", 2000000);
                return;
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
        object ob_yuanbao;      // 金元宝
        string prop, name;
        mapping data;
        object ob, where;
        string *apply = ({ "reduce_busy", "avoid_busy", "def_damage", "avoid_weak",
                "add_forget", "reduce_damage", "add_busy", "add_weak", "avoid_forget",
                "add_damage", "add_skill" });


        // 定义奖励物品列表
        // 几率  X / 百分之
        mixed oblist = ([
                "/clone/armor/fenghuang-chai3"           :                20,
                "/clone/armor/haizhi-xin3"               :                20,
                "/clone/armor/hong-feihun3"              :                15,
                "/clone/armor/lan-feihun3"               :                10,
                "/clone/armor/zi-feihun3"                :                10,
                "/clone/armor/moling-zhiyi3"             :                15,
                "/clone/armor/tiankong-zhiyi3"           :                10,
                "/clone/armor/piaoxue3"                  :                10,
                "/clone/armor/suomai3"                   :                15,
                "/clone/armor/tianming3"                 :                15,
                "/clone/armor/wuwei3"                    :                15,
                "/clone/armor/fenghuang-chai3"           :                20,
                "/clone/armor/haizhi-xin3"               :                20,
                "/clone/armor/hong-feihun3"              :                15,
                "/clone/armor/lan-feihun3"               :                10,
                "/clone/armor/zi-feihun3"                :                10,
                "/clone/armor/moling-zhiyi3"             :                15,
                "/clone/armor/tiankong-zhiyi3"           :                10,
                "/clone/armor/piaoxue3"                  :                10,
                "/clone/armor/suomai3"                   :                15,
                "/clone/armor/tianming3"                 :                15,
                "/clone/armor/wuwei3"                    :                15,
                "/clone/armor/fenghuang-chai3"           :                20,
                "/clone/armor/haizhi-xin3"               :                20,
                "/clone/armor/hong-feihun3"              :                15,
                "/clone/armor/lan-feihun3"               :                10,
                "/clone/armor/zi-feihun3"                :                10,
                "/clone/armor/moling-zhiyi3"             :                15,
                "/clone/armor/tiankong-zhiyi3"           :                10,
                "/clone/armor/piaoxue3"                  :                10,
                "/clone/armor/suomai3"                   :                15,
                "/clone/armor/tianming3"                 :                15,
                "/clone/armor/wuwei3"                    :                15,
                "/clone/armor/fenghuang-chai3"           :                20,
                "/clone/armor/haizhi-xin3"               :                20,
                "/clone/armor/hong-feihun3"              :                15,
                "/clone/armor/lan-feihun3"               :                10,
                "/clone/armor/zi-feihun3"                :                10,
                "/clone/armor/moling-zhiyi3"             :                15,
                "/clone/armor/tiankong-zhiyi3"           :                10,
                "/clone/armor/piaoxue3"                  :                10,
                "/clone/armor/suomai3"                   :                15,
                "/clone/armor/tianming3"                 :                15,
                "/clone/armor/wuwei3"                    :                15,
                "/clone/armor/zhanhun-xue3"              :                15,
                "/clone/armor/fenghuang-chai3"           :                10,
                "/clone/armor/feima-xue3"                :              20,
                "/clone/armor/shengling-yaodai3"         :              30,
                "/clone/armor/shangu-zhixing3"           :              20,
                "/clone/book/xuedao-book1"               :              35,
                "/clone/book/xuanxudao-book"             :              35,
                "/clone/armor/tiankong-zhiyi3"           :                10,
                "/clone/armor/piaoxue3"                  :                10,
                "/clone/armor/suomai3"                   :                15,
                "/clone/armor/tianming3"                 :                15,
                "/clone/armor/wuwei3"                    :                15,
                "/clone/armor/fenghuang-chai3"           :                20,
                "/clone/armor/haizhi-xin3"               :                20,
                "/clone/armor/hong-feihun3"              :                15,
                "/clone/armor/lan-feihun3"               :                10,
                "/clone/armor/zi-feihun3"                :                10,
                "/clone/armor/moling-zhiyi3"             :                15,
                "/clone/armor/tiankong-zhiyi3"           :                10,
                "/clone/armor/piaoxue3"                  :                10,
                "/clone/armor/suomai3"                   :                15,
                "/clone/armor/tianming3"                 :                15,
                "/clone/armor/wuwei3"                    :                15,
                "/clone/armor/fenghuang-chai3"           :                20,
                "/clone/armor/haizhi-xin3"               :                20,
                "/clone/armor/hong-feihun3"              :                15,
                "/clone/armor/lan-feihun3"               :                10,
                "/clone/armor/zi-feihun3"                :                10,
                "/clone/armor/moling-zhiyi3"             :                15,
                "/clone/armor/tiankong-zhiyi3"           :                10,
                "/clone/armor/piaoxue3"                  :                10,
                "/clone/armor/suomai3"                   :                15,
                "/clone/armor/tianming3"                 :                15,
                "/clone/armor/wuwei3"                    :                15,
                "/clone/armor/zhanhun-xue3"              :                15,
                "/clone/armor/fenghuang-chai3"           :                10,
                "/clone/armor/feima-xue3"                :              20,
                "/clone/armor/shengling-yaodai3"         :              30,
                "/clone/armor/shangu-zhixing3"           :              20,
                "/clone/book/xuedao-book1"               :              35,
                "/clone/book/xuanxudao-book"             :              35,

                "/clone/armor/shuijing-guan"             :              5,
                "/clone/armor/shuijing-guan2"            :              3,
                "/clone/armor/shuijing-guan3"            :              1,
                "/clone/horse/chaoying"                  :              2,
                "/clone/tuteng/diwang-suipian43"         :              5,
                "/clone/tuteng/diwang-suipian44"         :              5,
                "/clone/tuteng/diwang-suipian45"         :              5,
                "/clone/tuteng/diwang-suipian46"         :              5,
                "/clone/tuteng/diwang-suipian11"         :              5,
                "/clone/tuteng/diwang-suipian12"         :              5,
                "/clone/tuteng/diwang-suipian13"         :              5,
                "/clone/tuteng/diwang-suipian14"         :              5,
                "/clone/armor/sheyao-ring"               :              15,
                "/clone/armor/sheyao-ring2"              :              10,
                "/clone/armor/sheyao-ring3"              :              5,

                "/clone/armor/fenghuang-chai3"           :                20,
                "/clone/armor/haizhi-xin3"               :                20,
                "/clone/armor/hong-feihun3"              :                15,
                "/clone/armor/lan-feihun3"               :                10,
                "/clone/armor/zi-feihun3"                :                10,
                "/clone/armor/moling-zhiyi3"             :                15,
                "/clone/armor/tiankong-zhiyi3"           :                10,
                "/clone/armor/piaoxue3"                  :                10,
                "/clone/armor/suomai3"                   :                15,
                "/clone/armor/tianming3"                 :                15,
                "/clone/armor/wuwei3"                    :                15,
                "/clone/armor/fenghuang-chai3"           :                20,
                "/clone/armor/haizhi-xin3"               :                20,
                "/clone/armor/hong-feihun3"              :                15,
                "/clone/armor/lan-feihun3"               :                10,
                "/clone/armor/zi-feihun3"                :                10,
                "/clone/armor/moling-zhiyi3"             :                15,
                "/clone/armor/fenghuang-chai3"           :                20,
                "/clone/armor/haizhi-xin3"               :                20,
                "/clone/armor/hong-feihun3"              :                15,
                "/clone/armor/lan-feihun3"               :                10,
                "/clone/armor/zi-feihun3"                :                10,
                "/clone/armor/moling-zhiyi3"             :                15,
                "/clone/armor/tiankong-zhiyi3"           :                10,
                "/clone/armor/piaoxue3"                  :                10,
                "/clone/armor/suomai3"                   :                15,
                "/clone/armor/tianming3"                 :                15,
                "/clone/armor/wuwei3"                    :                15,
                "/clone/armor/fenghuang-chai3"           :                20,
                "/clone/armor/haizhi-xin3"               :                20,
                "/clone/armor/hong-feihun3"              :                15,
                "/clone/armor/lan-feihun3"               :                10,
                "/clone/armor/zi-feihun3"                :                10,
                "/clone/armor/moling-zhiyi3"             :                15,
                "/clone/armor/fenghuang-chai3"           :                20,
                "/clone/armor/haizhi-xin3"               :                20,
                "/clone/armor/hong-feihun3"              :                15,
                "/clone/armor/lan-feihun3"               :                10,
                "/clone/armor/zi-feihun3"                :                10,
                "/clone/armor/moling-zhiyi3"             :                15,
                "/clone/armor/tiankong-zhiyi3"           :                10,
                "/clone/armor/piaoxue3"                  :                10,
                "/clone/armor/suomai3"                   :                15,
                "/clone/armor/tianming3"                 :                15,
                "/clone/armor/wuwei3"                    :                15,
                "/clone/armor/fenghuang-chai3"           :                20,
                "/clone/armor/haizhi-xin3"               :                20,
                "/clone/armor/hong-feihun3"              :                15,
                "/clone/armor/lan-feihun3"               :                10,
                "/clone/armor/zi-feihun3"                :                10,
                "/clone/armor/moling-zhiyi3"             :                15,
        ]);

        object gift_ob;
        string s_gift, *key_s_gift;
        int gift_point;

        if( objectp(ob = previous_object(0)) && sscanf(base_name(ob), "/kungfu/skill/%*s") )
        {
                full_self();
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

              // 帝王符图
        // 编号43-46, 11-14
        if( MEMBER_D->is_valid_member(dob) && query("quest_tuteng/start", dob) )
        {
                int n_tt;
                object ob_tt;

                if (random(1000) == 1)
                {
                        n_tt = 43 + random(4);
                        if (random(3) == 1)n_tt = 11 + random(4);
                        ob_tt = new("/clone/tuteng/diwang-suipian" + sprintf("%d", n_tt));
                        if (ob_tt)
                        {
                                write(HIG "你获得了一张帝王符图碎片。\n" NOR);
                                ob_tt->move(dob, 1);
                        }
                }
        }

        if (objectp(dob) && environment(dob) == environment(this_object()))
        {
                exp = 1000000 + random(500000);
                pot = 500000 + random(200000);
                weiwang = 30000 + random(50000);
                score = 40000 + random(40000);
                mar = 10000 + random(30000);
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

                // 调整后提高30%奖励
                exp = exp + exp * 3 / 10;
                pot = pot + pot * 3 / 10;
                weiwang = weiwang + weiwang * 3 / 10;
                score = score + score * 3 / 10;
                mar = mar + mar * 3 / 10;

                if (n)
                {
                        foreach(tob in t)
                        {
                                if (objectp(tob) && living(tob))
                                {
                                        // 会员奖励再提高30%
                                        /*
                                        if( MEMBER_D->is_valid_member(query("id", tob)) )
                                        {
                                                if (environment(tob) == environment(dob))
                                                        GIFT_D->delay_boss_bonus(tob,
                                                                     ([ "exp"      : exp + exp * 3 / 10 + ((tob == dob) ? 50000 : 0),
                                                                   "pot"      : pot + pot * 3 / 10 / 10 + ((tob == dob) ? 50000 : 0),
                                                                     "weiwang"  : weiwang + weiwang * 3 / 10 + ((tob == dob) ? 50000 : 0),
                                                                   "score"    : score + score * 3 / 10 + ((tob == dob) ? 50000 : 0),
                                                                   "mar"      : mar + mar * 3 / 10 + ((tob == dob) ? 50000 : 0),
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

        // 一定几率掉物品在杀我的人身上dob
        if (objectp(dob) && environment(dob) == environment(this_object()))
        {
                key_s_gift = keys(oblist);
                s_gift = key_s_gift[random(sizeof(key_s_gift))];
                gift_point = oblist[s_gift];

                // 判断几率
                if( MEMBER_D->is_valid_member(query("id", dob) )
                    && random(MAX_POINT / ITEM_D->gift_point()) < gift_point)
                {
                        // 获得物品--爆出物品直接放在dob身上
                        gift_ob = new(s_gift);
                        if (objectp(gift_ob))
                        {
                                message_vision(HIW "叮~~一声，从$N" HIW "身上掉出" + gift_ob->name() + HIW "，$n" HIR
                                                   "赶紧拣了起来。\n" NOR, this_object(), dob);
                                tell_object(dob, BLINK + HIG "\n你得到了" + BLINK + gift_ob->name() + BLINK + HIG "。\n" NOR);
                                gift_ob->move(dob, 1);
                        }
                        else // 纪录之
                        {
                                log_file("shejing-gift-none", s_gift + "\n");
                        }
                }
        }

        // 一定几率掉物品在地上
        if (1)
        {
                key_s_gift = keys(oblist);
                s_gift = key_s_gift[random(sizeof(key_s_gift))];
                gift_point = oblist[s_gift];

                // 判断几率
                if (random(MAX_POINT / ITEM_D->gift_point()) < gift_point)
                {
                        gift_ob = new(s_gift);
                        if (objectp(gift_ob))
                        {
                                message_vision(HIC "当~~一声，从$N" HIC "身上掉出" + gift_ob->name() + HIC "，落在地上。\n" NOR, this_object());

                                gift_ob->move(environment(this_object()));
                        }
                        else // 纪录之
                        {
                                log_file("shejing-gift-none", s_gift + "\n");
                        }
                }
        }

        // 每杀死一个头掉出50到100个金元宝
        ob_yuanbao = new("/clone/money/yuanbao");
        ob_yuanbao->set_amount(50 + random(101));
        ob_yuanbao->move(environment(this_object()));
        set("who_get/id", "NONE", ob_yuanbao);
        set("who_get/time", time()+5, ob_yuanbao);//5秒钟内都不能捡取

        // 最终死亡再连续爆三件物品在地上
        if( query("life", this_object()) == 1 )
        {
                die_gift();
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
// 最终死亡再连续爆三件物品在地上
void die_gift()
{
        object gift_ob;
        string s_gift, *key_s_gift;
        int gift_point;
        object ob_xz;
        int i;

        // 定义奖励物品列表
        // 几率  X / 百分之
        mapping oblist = ([
                "/clone/armor/fenghuang-chai3"           :                20,
                "/clone/armor/haizhi-xin3"               :                20,
                "/clone/armor/hong-feihun3"              :                15,
                "/clone/armor/lan-feihun3"               :                10,
                "/clone/armor/zi-feihun3"                :                10,
                "/clone/armor/moling-zhiyi3"             :                15,
                "/clone/armor/tiankong-zhiyi3"           :                10,
                "/clone/armor/piaoxue3"                  :                10,
                "/clone/armor/suomai3"                   :                15,
                "/clone/armor/tianming3"                 :                15,
                "/clone/armor/wuwei3"                    :                15,
                "/clone/armor/fenghuang-chai3"           :                20,
                "/clone/armor/haizhi-xin3"               :                20,
                "/clone/armor/hong-feihun3"              :                15,
                "/clone/armor/lan-feihun3"               :                10,
                "/clone/armor/zi-feihun3"                :                10,
                "/clone/armor/moling-zhiyi3"             :                15,
                "/clone/armor/tiankong-zhiyi3"           :                10,
                "/clone/armor/piaoxue3"                  :                10,
                "/clone/armor/suomai3"                   :                15,
                "/clone/armor/tianming3"                 :                15,
                "/clone/armor/wuwei3"                    :                15,
                "/clone/armor/fenghuang-chai3"           :                20,
                "/clone/armor/haizhi-xin3"               :                20,
                "/clone/armor/hong-feihun3"              :                15,
                "/clone/armor/lan-feihun3"               :                10,
                "/clone/armor/zi-feihun3"                :                10,
                "/clone/armor/moling-zhiyi3"             :                15,
                "/clone/armor/tiankong-zhiyi3"           :                10,
                "/clone/armor/piaoxue3"                  :                10,
                "/clone/armor/suomai3"                   :                15,
                "/clone/armor/tianming3"                 :                15,
                "/clone/armor/wuwei3"                    :                15,
                "/clone/armor/fenghuang-chai3"           :                20,
                "/clone/armor/haizhi-xin3"               :                20,
                "/clone/armor/hong-feihun3"              :                15,
                "/clone/armor/lan-feihun3"               :                10,
                "/clone/armor/zi-feihun3"                :                10,
                "/clone/armor/moling-zhiyi3"             :                15,
                "/clone/armor/tiankong-zhiyi3"           :                10,
                "/clone/armor/piaoxue3"                  :                10,
                "/clone/armor/suomai3"                   :                15,
                "/clone/armor/tianming3"                 :                15,
                "/clone/armor/wuwei3"                    :                15,
                "/clone/armor/zhanhun-xue3"              :                15,
                "/clone/armor/fenghuang-chai3"           :                10,
                "/clone/armor/feima-xue3"                :              20,
                "/clone/armor/shengling-yaodai3"         :              30,
                "/clone/armor/shangu-zhixing3"           :              20,
                "/clone/horse/chaoying"                  :              2,
                "/clone/book/xuedao-book1"               :              35,
                "/clone/book/xuanxudao-book"             :              35,
                "/clone/armor/tiankong-zhiyi3"           :                10,
                "/clone/armor/piaoxue3"                  :                10,
                "/clone/armor/suomai3"                   :                15,
                "/clone/armor/tianming3"                 :                15,
                "/clone/armor/wuwei3"                    :                15,
                "/clone/armor/fenghuang-chai3"           :                20,
                "/clone/armor/haizhi-xin3"               :                20,
                "/clone/armor/hong-feihun3"              :                15,
                "/clone/armor/lan-feihun3"               :                10,
                "/clone/armor/zi-feihun3"                :                10,
                "/clone/armor/moling-zhiyi3"             :                15,
                "/clone/armor/tiankong-zhiyi3"           :                10,
                "/clone/armor/piaoxue3"                  :                10,
                "/clone/armor/suomai3"                   :                15,
                "/clone/armor/tianming3"                 :                15,
                "/clone/armor/wuwei3"                    :                15,
                "/clone/armor/fenghuang-chai3"           :                20,
                "/clone/armor/haizhi-xin3"               :                20,
                "/clone/armor/hong-feihun3"              :                15,
                "/clone/armor/lan-feihun3"               :                10,
                "/clone/armor/zi-feihun3"                :                10,
                "/clone/armor/moling-zhiyi3"             :                15,
                "/clone/armor/tiankong-zhiyi3"           :                10,
                "/clone/armor/piaoxue3"                  :                10,
                "/clone/armor/suomai3"                   :                15,
                "/clone/armor/tianming3"                 :                15,
                "/clone/armor/wuwei3"                    :                15,
                "/clone/armor/zhanhun-xue3"              :                15,
                "/clone/armor/fenghuang-chai3"           :                10,
                "/clone/armor/feima-xue3"                :              20,
                "/clone/armor/shengling-yaodai3"         :              30,
                "/clone/armor/shangu-zhixing3"           :              20,
                "/clone/book/xuedao-book1"               :              35,
                "/clone/book/xuanxudao-book"             :              35,

                "/clone/fam/max/naobaijin"               :                5,
                "/clone/armor/shuijing-guan"             :              5,
                "/clone/armor/shuijing-guan2"            :              3,
                "/clone/armor/shuijing-guan3"            :              1,
                "/clone/horse/chaoying"                  :              2,
                "/clone/tuteng/diwang-suipian43"         :              5,
                "/clone/tuteng/diwang-suipian44"         :              5,
                "/clone/tuteng/diwang-suipian45"         :              5,
                "/clone/tuteng/diwang-suipian46"         :              5,
                "/clone/tuteng/diwang-suipian11"         :              5,
                "/clone/tuteng/diwang-suipian12"         :              5,
                "/clone/tuteng/diwang-suipian13"         :              5,
                "/clone/tuteng/diwang-suipian14"         :              5,
                "/clone/armor/sheyao-ring"               :              15,
                "/clone/armor/sheyao-ring2"              :              10,
                "/clone/armor/sheyao-ring3"              :              5,

                "/clone/armor/fenghuang-chai3"           :                20,
                "/clone/armor/haizhi-xin3"               :                20,
                "/clone/armor/hong-feihun3"              :                15,
                "/clone/armor/lan-feihun3"               :                10,
                "/clone/armor/zi-feihun3"                :                10,
                "/clone/armor/moling-zhiyi3"             :                15,
                "/clone/armor/tiankong-zhiyi3"           :                10,
                "/clone/armor/piaoxue3"                  :                10,
                "/clone/armor/suomai3"                   :                15,
                "/clone/armor/tianming3"                 :                15,
                "/clone/armor/wuwei3"                    :                15,
                "/clone/armor/fenghuang-chai3"           :                20,
                "/clone/armor/haizhi-xin3"               :                20,
                "/clone/armor/hong-feihun3"              :                15,
                "/clone/armor/lan-feihun3"               :                10,
                "/clone/armor/zi-feihun3"                :                10,
                "/clone/armor/moling-zhiyi3"             :                15,
                "/clone/armor/fenghuang-chai3"           :                20,
                "/clone/armor/haizhi-xin3"               :                20,
                "/clone/armor/hong-feihun3"              :                15,
                "/clone/armor/lan-feihun3"               :                10,
                "/clone/armor/zi-feihun3"                :                10,
                "/clone/armor/moling-zhiyi3"             :                15,
                "/clone/armor/tiankong-zhiyi3"           :                10,
                "/clone/armor/piaoxue3"                  :                10,
                "/clone/armor/suomai3"                   :                15,
                "/clone/armor/tianming3"                 :                15,
                "/clone/armor/wuwei3"                    :                15,
                "/clone/armor/fenghuang-chai3"           :                20,
                "/clone/armor/haizhi-xin3"               :                20,
                "/clone/armor/hong-feihun3"              :                15,
                "/clone/armor/lan-feihun3"               :                10,
                "/clone/armor/zi-feihun3"                :                10,
                "/clone/armor/moling-zhiyi3"             :                15,
                "/clone/armor/fenghuang-chai3"           :                20,
                "/clone/armor/haizhi-xin3"               :                20,
                "/clone/armor/hong-feihun3"              :                15,
                "/clone/armor/lan-feihun3"               :                10,
                "/clone/armor/zi-feihun3"                :                10,
                "/clone/armor/moling-zhiyi3"             :                15,
                "/clone/armor/tiankong-zhiyi3"           :                10,
                "/clone/armor/piaoxue3"                  :                10,
                "/clone/armor/suomai3"                   :                15,
                "/clone/armor/tianming3"                 :                15,
                "/clone/armor/wuwei3"                    :                15,
                "/clone/armor/fenghuang-chai3"           :                20,
                "/clone/armor/haizhi-xin3"               :                20,
                "/clone/armor/hong-feihun3"              :                15,
                "/clone/armor/lan-feihun3"               :                10,
                "/clone/armor/zi-feihun3"                :                10,
                "/clone/armor/moling-zhiyi3"             :                15,
        ]);

        for (i = 0; i < 3; i ++)
        {
                key_s_gift = keys(oblist);
                s_gift = key_s_gift[random(sizeof(key_s_gift))];
                gift_point = oblist[s_gift];
                // 判断几率
                if (random(MAX_POINT / ITEM_D->gift_point()) < gift_point || 1)
                {
                        gift_ob = new(s_gift);
                        if (objectp(gift_ob))
                        {
                                message_vision(HIC "当~~一声，从$N" HIC "身上掉出" + gift_ob->name() + HIC "，落在地上。\n" NOR, this_object());
                                gift_ob->move(environment(this_object()));
                        }
                        else // 纪录之
                        {
                                log_file("shejing-gift-none", s_gift + "\n");
                        }
                }
        }

        // 50%几率爆出斩妖勋章
        if (random(2) == 1)
        {
                ob_xz = new("/clone/armor/zhanyao-xunzhang");
                ob_xz->move(environment(this_object()));
                message_vision(HIR "哐当~~一声，从$N" HIR "身上掉出一枚" + ob_xz->name() + HIR "，落在地上。\n" NOR, this_object());
                set("who_get/id", "NONE", ob_xz);
                set("who_get/time", time()+5, ob_xz);//5秒内都不能捡取
        }

        // 5/100几率掉出无名铜人
        if (random(100) < 5)
        {
                object ob_tongren;
                if( random(2) )
                        ob_tongren = new("/clone/tongren/tongren1");
                else
                        ob_tongren = new("/clone/tongren/tongren2");
                message_vision(HIR "当~~一声，从$N" HIR "身上掉出" + ob_tongren->name() + HIR "，落在地上。\n" NOR, this_object());
                set("who_get/id", "NONE", ob_tongren);
                set("who_get/time", time()+30, ob_tongren);//30秒内都不能捡取
                ob_tongren->move(environment(this_object()));
        }
}
