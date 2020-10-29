// This program is a part of NT MudLIB

#include <ansi.h>
#include <command.h>

inherit BOSS;

void random_move();
void death_msg();

void create()
{
        set_name(HIM "盗墓飞贼" NOR, ({ "daomu feizei", "daomu", "feizei" }) );
        set("title", HIC "「神秘人」" NOR);
        set("gender", random(2) == 1 ? "男性" : "女性");
        set("age", 25);
        set("long", @LONG
这是一名盗墓的飞贼，一身黑色蒙面装束，看起来身形矫健。
LONG);
        set("combat_exp", 3000000);
        set("shen_type", 0);
        set("max_neili", 13000);
        set("neili", 13000);
        set("max_jing", 22000);
        set("jing", 22000);
        set("max_qi", 600000);
        set("eff_qi", 600000);
        set("qi", 600000);
        set("jingli", 22000);
        set("max_jingli", 22000);
        set("level", 20);

        set("no_clean_up", 1);

        //set("no_nuoyi", 1); // 不被挪移影响

        set("str", 28);
        set("int", 25);
        set("con", 25);
        set("dex", 30);

        set_skill("martial-cognize", 200);
        set_skill("unarmed", 200);
        set_skill("sword", 200);
        set_skill("blade", 200);
        set_skill("parry", 200);
        set_skill("dodge", 240);
        set_skill("force", 200);
        set_skill("strike", 220);

        set_skill("xiaoyao-xinfa", 200);
        set_skill("chilian-shenzhang", 220);
        set_skill("lingbo-weibu", 240);


        map_skill("strike", "chilian-shenzhang");
        map_skill("dodge", "lingbo-weibu");
        map_skill("parry", "chilian-shenzhang");
        map_skill("force", "xiaoyao-xinfa");

        prepare_skill("strike", "chilian-shenzhang");

/*
        set("chat_chance", 30);
        set("chat_msg", ({ (: random_move :) }));
*/
        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "strike.lian" :),
                (: perform_action, "dodge.ling" :),
                (: exert_function, "recover" :)
        }) );

        set("jiali", 50);

        //set("end_time", 300);
        //set("death_msg", (: death_msg :));

        set("rewards", ([
                "exp"   : 50000,
                "pot"   : 25000,
                "mar"   : 5000,
                "score" : 30,
                "gold"  : 5,
        ]));

        set("drops", ([
                "RA&RANDOM10"    :       100,   // 低级普通装备
                "RA&RANDOM20"    :       40,    // 低级普通装备
                "FI&/clone/goods/enchant-scroll" :   20,
                "FI&/clone/goods/sun"    :   20,
                "FI&/clone/goods/moon"   :   20,
                "FI&/clone/armor/shenwu-xiangquan"      :       30,
                "FI&/clone/armor/yexing-yi"             :       60,
                "FI&/clone/tessera/rune04"  :   1,
                "FI&/clone/misc/baoxiang"  :   100,
        ]));
        setup();

        carry_object("/clone/armor/yexing-yi")->wear();
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
        me->receive_wound("qi", 300 + random(300), ob);
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
                        HIR + this_object()->short() + HIR "消失了。\n" NOR);

                destruct(this_object());
                return;
        }
        //::random_move();
}

void death_msg()
{
        if (random(2) == 1)
        {
                command("mess* grin");
                //command("chat 想抓我没那么容易，后会无期...！");
                CHANNEL_D->do_channel(this_object(), "mess", "听说" + name() + HIW "从古墓中盗得珍宝后，夺路而逃。" NOR);
        }
        else
        {
                message_vision(HIG "猛然间，$N " HIG " 向后一跳，随手仍出一颗黑色小丸，顿时腾起一片烟雾 ...\n" NOR,
                               this_object());
                //command("chat 哼，雕虫小技，不陪你们玩了，告辞！");
                CHANNEL_D->do_channel(this_object(), "mess", "听说" + name() + HIW "从古墓中盗得珍宝后，夺路而逃。" NOR);
        }
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

        if( objectp(killer) && query("family/family_name", killer) == "古墓派")
                set("rewards/gongxian", 300);

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
