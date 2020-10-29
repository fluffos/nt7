// person used in quest

#include <ansi.h>

inherit NPC;

void random_move();
int  is_stay_in_room()  { return 1; }

void create()
{
        set_name(HIC "襄阳守军" NOR, ({"xiangyang shoujun", "shoujun" }));
        set("gender", "男性");
        set("age", 20 + random(20));
        set("long", "这是一位襄阳的士兵，长年与蒙古人作战！");
        set("chat_chance", 120);
        set("chat_msg", ({ (: random_move :) }));
        
        set("no_get", 1);

        // 襄阳士兵标志
        set("xybing", 1);

        set_temp("apply/armor", 1000);
        set_temp("apply/damage", 3000);
        set_temp("apply/attack", 100000); // 高命中

        set("str", 50);
        set("int", 10 + random(14));
        set("dex", 15);
        set("con", 15);

        set("max_qi", 20000);
        set("eff_qi", 20000);
        set("qi", 20000);
        set("max_neili",20000);
        set("neili", 20000);
        set("max_jingli", 20000);
        set("jingli", 20000);
        
        set_skill("dodge", 200);
        set_skill("force", 200);
        set_skill("unarmed", 200);
        set_skill("blade", 250);
                
        set_temp("born_time", time());

        set_temp("dest_now", 0); // 撤退标记 0 为不撤退继续战斗

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

void die()
{
        // 正常死亡
        XYWAR_D->soldier_die("xiangyang");
        ::die();

        return;
}

void heart_beat()
{
        object env;
        string route;
        
        // 接受调动
        if (XYWAR_D->is_moved())
        {
                env = environment(this_object());
                
                if (! objectp(env))return ::heart_beat();
                
                // 已经到了则不调动
                if (base_name(env) == XYWAR_D->xy_soldier_poision("env"))
                        return ::heart_beat();
                        
                route = XYWAR_D->xy_soldier_poision("poision");
                route = XYWAR_D->re_poision(route);
                
                set("route", route);
                this_object()->move(XYWAR_D->xy_soldier_poision("env"));                
        }

        return ::heart_beat();
}

void uncoucious()
{
        die();
}

void random_move()
{
        string dir;
        string route;
        object env;

        if (query_temp("dest_now"))
        {
                XYWAR_D->soldier_die("xiangyang");
                destruct(this_object());
                return;
        }

        // 检查襄阳保卫战是否结束
        if (XYWAR_D->dest_status() == 1)
        {
                set_temp("dest_now", 1);
        }
/*
        // 郭靖死亡，撤退
        if (XYWAR_D->is_guojing_die())
        {
                set_temp("dest_now", 1);
        }
*/
        // 守护方位
        route = query("route");
        
        if (stringp(route))command("guard " + route);
}

void init()
{
        object me = this_player();

        if (! living(me) || me->query_temp("apply/invisible"))
                 return;

        // 襄阳兵不相互战斗
        if (! me->query("mgbing"))return;                        

        if (playerp(me))return;

        // 延迟一定时间攻击
        // 为了设置fighting标记也更真实
        call_out("do_kill", 1 + random(3), me);
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

        if (! "/cmds/std/kill"->main(this_object(), me->query("id")))
                 kill_ob(me);
}
