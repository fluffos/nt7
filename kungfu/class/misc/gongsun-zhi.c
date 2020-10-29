// This program is a part of NT MudLIB

#include <ansi.h>
#include <command.h>

#define HEIJIAN "/clone/lonely/heijian"
#define JUCHI   "/clone/lonely/juchidao"

inherit BOSS;

void random_move();
void death_msg();

void create()
{
        object ob1,ob2;
        set_name("公孙止", ({ "gongsun zhi", "gongsun", "zhi" }));
        set("nickname", HIR "阴阳刃" NOR);
        set("gender", "男性");
        set("attitude", "peaceful");
        set("shen_type", 0);
        set("age", 40);
        set("str", 35);
        set("con", 35);
        set("int", 25);
        set("dex", 35);
        set("max_qi", 10000000);
        set("max_jing", 10000000);
        set("max_jingli", 10000000);
        set("jingli", 10000000);
        set("qi", 10000000);
        set("neili", 50000);
        set("max_neili", 50000);
        set("jiali", 600);
        set("combat_exp", 30000000);
        set("level", 50);

        set_skill("force", 900);
        set_skill("jueqing-xinfa", 900);
        set_skill("fenxin-jue", 900);
        set_skill("dodge", 900);
        set_skill("jueqing-shenfa", 900);
        set_skill("strike", 900);
        set_skill("jueqing-zhang", 900);
        set_skill("guhong-zhang", 900);
        set_skill("cuff", 900);
        set_skill("pokong-quan", 900);
        set_skill("medical", 900);
        set_skill("jueqing-yaoli", 900);
        set_skill("sword", 900);
        set_skill("yinyang-ren", 900);
        set_skill("zilei-jian", 900);
        set_skill("guxing-jian", 900);
        set_skill("blade", 900);
        set_skill("tianjue-dao", 900);
        set_skill("luoyun-dao", 900);
        set_skill("poguang-dao", 900);
        set_skill("parry", 900);
        set_skill("literate", 900);
        set_skill("medical", 900);
        set_skill("jueqing-yaoli", 900);
        set_skill("martial-cognize", 900);

        map_skill("strike", "jueqing-zhang");
        map_skill("sword", "yinyang-ren");
        map_skill("blade", "yinyang-ren");
        map_skill("force", "fenxin-jue");
        map_skill("dodge", "jueqing-shenfa");
        map_skill("parry", "yinyang-ren");
        map_skill("parry", "jueqing-yaoli");

        prepare_skill("strike", "jueqing-zhang");

        create_family("绝情谷", 4, "谷主");

/*
        set("chat_chance", 30);
        set("chat_msg", ({ (: random_move :) }));
*/
        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "sword.huan" :),
                (: perform_action, "sword.heng" :),
                (: perform_action, "strike.hun" :),
                (: perform_action, "strike.wan" :),
                (: exert_function, "recover" :),
                (: exert_function, "powerup" :),
        }));

        set_temp("apply/attack", 1000);
        set_temp("apply/damage", 1000);
        set_temp("apply/unarmed_damage", 1000);
        set_temp("apply/armor", 5000);

        //set("end_time", 300);
        set("death_msg", (: death_msg :));

        set("rewards", ([
                "exp"   : 100000,
                "pot"   : 50000,
                "mar"   : 10000,
                "score" : 300,
                "gold"  : 50,
        ]));

        set("drops", ([
                "RA&RANDOM40"    :       100,   // 低级普通装备
                "RA&RANDOM50"    :       40,    // 低级普通装备
                "FI&/clone/goods/enchant-scroll" :   20,
                "FI&/clone/goods/sun"    :   20,
                "FI&/clone/goods/moon"   :   20,
                "FI&/clone/fam/item/stone3"                 :           30,
                "FI&/clone/tessera/rune09"  :   1,
                "FI&/clone/armor/zijinhua-erhuan3"          :           30,
                "FI&/clone/tuteng/diwang-suipian44"         :           20,
                "FI&/clone/tongren/tongren"+(1+random(2))   :           1,
                "FI&/clone/misc/baoxiang" : 100,
        ]));
        setup();

        if (clonep())
        {
                ob1 = find_object(HEIJIAN);
                if (! ob1) ob1 = load_object(HEIJIAN);
                if (! environment(ob1))
                {
                        ob1->move(this_object());
                        set_temp("handing", ob1);
                } else
                {
                        ob1 = new("/clone/weapon/changjian");
                        ob1->move(this_object());
                        set_temp("handing", ob1);
                }

                ob2 = find_object(JUCHI);
                if (! ob2) ob2 = load_object(JUCHI);
                if (! environment(ob2))
                {
                        ob2->move(this_object());
                        ob2->wield();
                }else
                {
                        ob2 = new("/clone/weapon/gangdao");
                        ob2->move(this_object());
                        ob2->wield();
                }
        }
        carry_object("/clone/cloth/cloth")->wear();
        set_temp("born_time", time());
        //if (clonep()) keep_heart_beat();
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
}

mixed hit_ob(object me, object ob, int damage_bouns)
{
        ob->start_busy(5 + random(6));
        me->receive_wound("qi", 3500 + random(3500), ob);
        return HIY "$N" HIY "大喝一声，拼死反抗，竟逼得$n" HIY "手忙脚乱。\n" NOR;
}

void heart_beat()
{
        if (query("neili") < 1 && random(50) == 1)
                set("neili", query("max_neili"));

        ::heart_beat();
}

void random_move()
{
        object env;

        if (time() - query_temp("born_time") > 1800)
        {
                env = environment(this_object());
                message_vision("$N急急忙忙的走了。\n", this_object());

                CHANNEL_D->channel_broadcast("news", HIG "听说" + HIW + env->short() + "(" + LOOK_CMD->locate(base_name(env)) + ")" HIG "一带出现的" +
                        HIR + this_object()->short() + HIG "消失了。\n" NOR);

                destruct(this_object());
                return;
        }
        //::random_move();
}

void death_msg()
{
        //command("chat* heng");
        command("mess* tnnd 敢来我绝情山庄撒野，走着瞧！");
}

void die(object killer)
{
        object ob;

        if( objectp(ob = previous_object(0)) && sscanf(base_name(ob), "/kungfu/skill/%*s") )
        {
                full_self();
                return;
        }

        if( time() < query_temp("end_time") ) // 时间没有到，死亡不了
        {
                addn("jing", query("max_jing") / 10);
                if( query("jing") > query("max_jing") ) set("jing", query("max_jing"));
                addn("eff_jing", query("max_jing") / 10);
                if( query("eff_jing") > query("max_jing") ) set("eff_jing", query("max_jing"));
                addn("qi", query("max_qi") / 10);
                if( query("qi") > query("max_qi") ) set("qi", query("max_qi"));
                addn("eff_qi", query("max_qi") / 10);
                if( query("eff_qi") > query("max_qi") ) set("eff_qi", query("max_qi"));
                message_vision(HIR "\n$N" HIR "大喝一声，运用秘法，气血有所回升！\n\n" NOR, this_object());
                return;
        }

        if (! objectp(killer))
                killer = query_last_damage_from();

        // 战胜金轮获取小龙女线索
        if (query("can_perform/surge-force/quest/step", killer) == 2)
        {
                tell_object(killer, HIM "\n正在这时，你收到杨过托人带来的口信：龙儿已与我会面，但\n"
                                    "身中情花剧毒，请尽快找到解毒灵药！\n\n" NOR);
                set("can_perform/surge-force/quest/step", 3, killer);
                killer->save();
        }

        if (random(10) == 1 || wizardp(killer))
        {
                object dan;
                dan = new("/clone/fam/quest/jueqing-dan");

                message_vision(HIR "叮~~一声，从$N" HIR "掉出一颗绝情丹，$n" HIR
                                   "赶紧拣了起来。\n" NOR, this_object(), killer);
                tell_object(killer, BLINK + HIG "你得到了" + dan->name() + BLINK + HIG "。\n" NOR);
                dan->move(killer, 1);
                set("can_perform/surge-force/quest/jueqing-dan", 1, killer);
        }

        return ::die();
}

varargs void unconcious(object defeater)
{
        object ob;

        //if( query("end_boss") || query("fight_boss") )
        if( objectp(ob = previous_object(0)) && sscanf(base_name(ob), "/kungfu/skill/%*s") ) {
                full_self();
                return;
        }
        die(defeater);
        return;
}
