// person used in quest

#include <ansi.h>
#define MEMBER_D  "/adm/daemons/memberd"

inherit NPC;

void random_move();
int  is_stay_in_room()  { return 1; }

void create()
{
        set_name(NOR + YEL "蒙古步兵" NOR, ({"menggu bubing", "bubing" }));
        set("gender", "男性");
        set("age", 20 + random(20));
        set("long", "这是一位蒙古步兵，看起来非常凶悍！");
        set("chat_chance", 120);
        set("chat_msg", ({ (: random_move :) }));
        set("no_get", 1);

        // 蒙古士兵标志
        set("mgbing", 1);

        set_temp("apply/armor", 1000);
        set_temp("apply/damage", 1000);
        set_temp("apply/attack", 100000); // 高命中

        set("str", 20);
        set("int", 10 + random(14));
        set("dex", 15);
        set("con", 15);

        set("max_qi", 10000);
        set("eff_qi", 10000);
        set("qi", 10000);
        set("max_neili",600);
        set("neili", 600);
        set("max_jingli", 600);
        set("jingli", 600);
        
        set_skill("dodge", 50);
        set_skill("force", 30);
        set_skill("unarmed", 30);
        set_skill("blade", 100);
                
        set_temp("born_time", time());

        set_temp("dest_now", 0); // 撤退标记 0 为不撤退继续战斗

        add_money("gold", 1 + random(2));

        // 设置奖励级别
        set("gift/level", "步兵");
        set("gift/exp", 900 + random(921));
        set("gift/pot", 820 + random(831));
        set("gift/experience", 230 + random(321));

        setup();

        carry_object(__DIR__"obj/menggucloth")->wear(); 
        carry_object("/clone/weapon/gangdao")->wield();
        
        if (clonep()) keep_heart_beat();

}

int accept_fight(object ob)
{
        command("say 我可没兴趣陪你玩，快给我滚开。");
        return 0;
}

int accept_hit(object ob)
{
        return 0;
}

int accept_ansuan(object ob)
{
        return notify_fail("那人警惕性好高，你难以下手。\n");
}

int accept_touxi(object ob)
{
        return notify_fail("那人警惕性好高，你难以下手。\n");
}

void die(object killer)
{
        object dob;             // 打晕这个NPC的人
        int n;                  // 组队中队员数目
        int exp;                // 需要瓜分的经验
        int pot;                // 需要瓜分的潜能
        int tihui;              // 需要瓜分的体会
        int weiwang;            // 需要瓜分的威望
        int score;              // 需要瓜分的阅历

        object *t;              // 杀死我的人的队伍列表
        object tob;
        int i;

        // 找到杀了我(NPC)或是打晕我的人
        if (! objectp(dob = killer))
                dob = query_defeated_by();

        if (! dob)
        {
                if (! query("no_total"))
                        XYWAR_D->soldier_die(this_object()->query("route"), 3);
                destruct(this_object());
                return;
        }

        // 战斗进行时才有奖励
        if (XYWAR_D->now_status() != 2)
        {
                if (! query("no_total"))
                        XYWAR_D->soldier_die(this_object()->query("route"), 3);
                destruct(this_object());
                return;
        }
        
        if (objectp(dob))
        {
                exp = query("gift/exp");
                pot = query("gift/pot");
                tihui = query("gift/experience");

                // 组队
                t = dob->query_team();

                if (pointerp(t))n = sizeof(t);

                // 组队后需要瓜分经验
                if (n > 1)
                {
                       exp /= n;
                       pot /= n;
                       tihui /= n;
                }

                if (exp < 1)exp = 1;
                if (pot < 1)pot = 1;
                if (tihui < 1)tihui = 1;
                                
                // 帝王符图
                // 编号47-48
                if (dob->query("scborn/ok") && MEMBER_D->is_valib_member(dob->query("id")) && dob->query("quest_tuteng/start"))
                {
                        int n_tt;
                        object ob_tt;
        
                        if (random(120) == 1)
                        {
                                n_tt = 47 + random(2);
                                ob_tt = new("/clone/tuteng/diwang-suipian" + sprintf("%d", n_tt));
                                if (ob_tt)
                                {
                                        write(HIG "你获得了一张帝王符图碎片。\n" NOR);
                                        ob_tt->move(dob, 1);
                                }
                        }
                }
                                                        
                if (pointerp(t))
                {                                                
                        /// 999 表明获得的特殊奖励不受上限限制
                        foreach(tob in t)
                        {
                                   if (objectp(tob) && living(tob))
                                   {
                                                     // 设置杀敌标志，最为最终奖励依据
                                                     tob->set("xywar/xy_" + sprintf("%d", XYWAR_D->get_ran_num()), pot);

                                                  GIFT_D->delay_bonus(tob,
                                                         ([ "exp"         : exp + ((tob == dob) ? exp : 0),
                                                              "pot"         : pot + ((tob == dob) ? pot : 0),
                                                               "mar"         : tihui + ((tob == dob) ? tihui : 0),
                                                              "prompt"      : "你的队伍击毙" + name() + "之后" ]), 999);
                                                                  
                                    }
                        }
                }
                else
                {
                        // 设置杀敌标志，最为最终奖励依据
                        dob->set("xywar/xy_" + sprintf("%d", XYWAR_D->get_ran_num()), pot);
                        
                        GIFT_D->delay_bonus(dob,
                            ([ "exp"         : exp,
                               "pot"         : pot,
                               "mar"         : tihui,
                               "prompt"      : "你在击毙" + name() + "之后" ]), 999);
                }
        }

        // 正常死亡
        if (! query("no_total"))
                XYWAR_D->soldier_die(this_object()->query("route"), 3);
        destruct(this_object());

        return;
}

void uncoucious()
{
        die(query_last_damage_from());
}

void random_move()
{
        string dir;
        string route;
        object env;
                
        if (query_temp("dest_now"))
        {
                if (! query("no_total"))
                        XYWAR_D->soldier_die(this_object()->query("route"), 3);
                destruct(this_object());
                return;
        }

        if (XYWAR_D->dest_status() == 1)
        {
                set_temp("dest_now", 1);
        }

        // 行进路径方向
        // 需要先设置
        route = query("route");

        env = environment(this_object());

        if (! objectp(env))return;
        
        // 如果到达中央广场宣告襄阳保卫战失败
        if (base_name(env) == "/d/xiangyang/guangchang")
        {                        
               XYWAR_D->arrived_center();// 保卫战失败
               return;
        }

        // 按照路由列表移动
        if (stringp(route) && XYWAR_D->now_status() == 2)command("go " + route);
}

void init()
{
        object me = this_player();

        if (! living(me) || me->query_temp("apply/invisible"))
                 return;

        // 蒙古并不相互战斗
        if (me->query("mgbing"))return;                        

        // 延迟一定时间攻击
        // 为了设置fighting标记也更真实
        if (! me->query("env/invisible"))call_out("do_kill", 1 + random(4), me);
        
        if (playerp(me))me->set("env/combatd",4);

}

void do_kill(object me)
{
        if (! objectp(me))return;
        
        if (! living(me) || me->query_temp("apply/invisible"))
                 return;

        // 并不是每个对象都攻击，这样做是为了节约系统资源和更为真实
        if (me->is_fighting() && random(3) == 1)return;

        // 只能同时攻击一个人
        if (this_object()->is_fighting())return;

        kill_ob(me);
        me->kill_ob(this_object());
}
