// This program is a part of NT MudLIB

#include <ansi.h>
#include <command.h>

inherit BOSS;

void random_move();
void death_msg();

void create()
{
        set_name("小龙女", ({ "xiao longnv",}));
        set("title", HIR "困于情花谷的" NOR);
        set("gender", "女性");
        set("age", 22);
        set("long", @LONG
她一生爱穿白衣，当真如风拂玉树，雪裹琼苞，
兼之生性清冷，实当得起“冷浸溶溶月”的形
容。
LONG);
        set("attitude", "friendly");
        set("str", 21);
        set("int", 40);
        set("con", 45);
        set("dex", 46);
        set("per", 29);
        set("shen_type", 1);

        set("qi", 5000000);
        set("max_qi", 5000000);

        set("jing", 2000000);
        set("max_jing", 2000000);
        set("jingli", 2000000);
        set("max_jingli", 2000000);

        set("neili", 30000);
        set("max_neili", 30000);
        set("jiali", 700);
        set("combat_exp", 80000000);
        set("level", 50);

        set_skill("force", 700);
        set_skill("suxin-jue", 700);
        set_skill("yunv-xinjing", 700);
        set_skill("sword", 700);
        set_skill("yunv-jian", 700);
        set_skill("suxin-jian", 700);
        set_skill("quanzhen-jian", 700);
        set_skill("whip", 700);
        set_skill("yinsuo-jinling", 700);
        set_skill("dodge", 700);
        set_skill("yunv-shenfa", 700);
        set_skill("parry", 700);
        set_skill("unarmed", 700);
        set_skill("meinv-quan", 700);
        set_skill("strike", 700);
        set_skill("tianluo-diwang", 700);
        set_skill("zuoyou-hubo", 700);
        set_skill("literate", 700);
        set_skill("throwing", 700);
        set_skill("yufeng-zhen", 700);
        set_skill("martial-cognize", 700);

        map_skill("force", "yunv-xinjing");
        map_skill("whip", "yinsuo-jinling");
        map_skill("sword", "suxin-jian");
        map_skill("dodge", "yunv-shenfa");
        map_skill("parry", "meinv-quan");
        map_skill("unarmed", "meinv-quan");
        map_skill("strike", "tianluo-diwang");
        map_skill("throwing", "yufeng-zhen");

        prepare_skill("strike", "tianluo-diwang");
        prepare_skill("unarmed", "meinv-quan");

        set_temp("apply/attack", 1500);
        set_temp("apply/defense", 1500);
        set_temp("apply/damage", 1000);
        set_temp("apply/unarmed_damage", 1000);
        set_temp("apply/armor", 200);

/*
        set("chat_chance", 30);
        set("chat_msg", ({ (: random_move :) }));
*/
        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: command("perform strike.wang and unarmed.you") :),
                (: exert_function, "recover" :),
                (: exert_function, "powerup" :),
                (: perform_action, "whip.feng twice" :),
        }) );

        //set("end_time", 300);
        set("death_msg", (: death_msg :));

        set("rewards", ([
                "exp"   : 50000,
                "pot"   : 25000,
                "mar"   : 5000,
                "score" : 30,
                "gold"  : 5,
        ]));

        set("drops", ([
                "RA&RANDOM40"    :       100,   // 低级普通装备
                "RA&RANDOM50"    :       40,    // 低级普通装备
                "FI&/clone/goods/enchant-scroll" :   20,
                "FI&/clone/goods/sun"    :   20,
                "FI&/clone/goods/moon"   :   20,
                "FI&/clone/tessera/rune07"  :   1,
                "FI&/clone/armor/zijinhua-erhuan3"          :        50,
	        "FI&/clone/book/yufeng-shu"                 :        60,
	        "FI&/clone/tongren/tongren"+(1+random(2))   :        1,
                "FI&/clone/misc/baoxiang" : 100,
        ]));
        setup();

        carry_object("/clone/weapon/changbian")->wield();
        carry_object("/clone/cloth/baipao")->wear();
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
	me->receive_wound("qi", 900 + random(900), ob);
        return HIY "$N" HIY "娇喝一声，奋力反抗，竟逼得$n" HIY "手忙脚乱。\n" NOR;
}

void heart_beat()
{
	if (query("neili") < 1 && random(50) == 1)
		set("neili", query("max_neili"));

	return ::heart_beat();
}

void random_move()
{
        object env;

        if (time() - query_temp("born_time") > 1800)
        {
                env = environment(this_object());
                message_vision("$N急急忙忙的走了。\n", this_object());

                CHANNEL_D->channel_broadcast("news", HIG "听说" + HIW +
                        env->short() + "(" + LOOK_CMD->locate(base_name(env)) + ")" HIG "一带出现的" +
                        HIR + this_object()->short() + HIG "消失了。\n" NOR);

                destruct(this_object());
                return;
        }
        //::random_move();
}

void death_msg()
{
        //command("chat* protect1");
        CHANNEL_D->channel_broadcast("mess", "听说" + name() + HIW "被神雕救走 ……" NOR);
}
