// This program is a part of NT MudLIB
// yangkang.c 杨康

#include <ansi.h>
#include <command.h>

inherit BOSS;

void random_move();
void death_msg();

void create()
{
        set_name("杨康", ({"yang kang", "yang"}));
        set("gender", "男性");
        set("title", HIY "小王爷" NOR);
        set("age", 26);
        set("class", "taoist");
        set("long",
                "他就是大辽的小王爷杨康，实乃杨家将后人杨铁心之子。\n"
                "他相貌端正，但眉宇间似乎隐藏着一丝狡猾的神色。\n");
        set("attitude", "friendly");
        set("shen", 0);
        set("str", 25);
        set("int", 26);
        set("con", 26);
        set("dex", 25);

        set("chat_chance_combat", 100);
        set("chat_msg_combat", ({
                (: exert_function, "recover" :),
                (: perform_action, "strike.ju" :),
                (: perform_action, "sword.ding" :),
        }));

        set("qi", 1500);
        set("max_qi", 1500);
        set("jing", 800);
        set("max_jing", 800);
        set("neili", 30000000);
        set("max_neili", 3000000);
        set("jiali", 2000);

        set("combat_exp", 120000000);
        set("level", 30);
        set("fight_boss", 1);

        set_skill("force", 400);
        set_skill("quanzhen-xinfa", 400);
        set_skill("sword", 400);
        set_skill("quanzhen-jian", 400);
        set_skill("dodge", 400);
        set_skill("jinyan-gong", 400);
        set_skill("parry", 400);
        set_skill("unarmed", 400);
        set_skill("finger", 400);
        set_skill("zhongnan-zhi", 400);
        set_skill("literate", 400);
        set_skill("taoism", 400);

        map_skill("force", "quanzhen-xinfa");
        map_skill("sword", "quanzhen-jian");
        map_skill("dodge", "jinyan-gong");
        map_skill("parry", "quanzhen-jian");
        map_skill("finger", "zhongnan-zhi");
        prepare_skill("finger", "zhongnan-zhi");

        create_family("全真教", 3, "弟子");

        set_temp("apply/attack", 400);
        set_temp("apply/defense", 400);
        set_temp("apply/damage", 500);
        set_temp("apply/armor", 500);
        set_temp("apply/reduce_damage", 30);
        set_temp("apply/reduce_busy", 10);
        set_temp("apply/add_busy", 3);

/*
        set("chat_chance", 30);
        set("chat_msg", ({ (: random_move :) }));
*/
        set("clear_fuben", 1);
        set("auto_perform", 1);
        //set("end_time", 300);
        //set("death_msg", (: death_msg :));

        set("rewards", ([
                "exp"   : 50000,
                "pot"   : 25000,
                "mar"   : 5000,
                "score" : 300,
                "gold"  : 50,
        ]));
        set("drops", ([
                "RA&RANDOM30"    :       100,   // 低级普通装备
                "RA&RANDOM40"    :       40,    // 低级普通装备
                "FI&/clone/goods/enchant-scroll" :   20,
                "FI&/clone/goods/sun"   :   20,
                "FI&/clone/goods/moon"  :   20,
                "FI&/clone/tongren/tongren"+(1+random(2)) : 1,
                "FI&/clone/misc/baoxiang" : 100,
        ]));
        setup();

        carry_object("/clone/weapon/changjian")->wield();
        carry_object("/kungfu/class/quanzhen/obj/greyrobe")->wear();
        set_temp("born_time", time());
        //if (clonep()) keep_heart_beat();
}

int accept_fight(object ob)
{
        command("say 我可没兴趣陪你玩，快给我滚开。");
        return 0;
}

int accept_hit(object ob)
{
        message_vision(HIW "$N" HIW "脸色一变，闪过一道杀气。怒"
                       "喝道：好一个" + RANK_D->query_rude(ob) +
                       "，来吧！\n" NOR, this_object());
        kill_ob(ob);
        return 1;
}

int accept_kill(object ob)
{
        if( !living(this_object()) )
                return 1;

        return accept_hit(ob);
}

int accept_ansuan(object ob)
{
        return notify_fail("那人警惕性好高，你难以下手。\n");
}

int accept_touxi(object ob)
{
        return notify_fail("那人警惕性好高，你难以下手。\n");
}

mixed hit_ob(object me, object ob, int damage_bouns)
{
	ob->start_busy(3 + random(6));
	me->receive_wound("qi", 100 + random(100), ob);
        return HIY "$N" HIY "大喝一声，拼命反抗，竟逼得$n" HIY "手忙脚乱。\n" NOR;
}

void heart_beat()
{
	if (query("neili") < 1 && random(100) == 1)
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

                CHANNEL_D->channel_broadcast("news", HIG "听说" + HIW +
                        env->short() + "(" + LOOK_CMD->locate(base_name(env)) + ")" HIG "一带出现的" +
                        HIR + this_object()->short() + HIR "消失了。\n" NOR);

                destruct(this_object());
                return;
        }
        //::random_move();
}

void death_msg()
{
        //command("chat 我乃是金国小王爷，想杀我，我要灭你九族 ...");
        CHANNEL_D->channel_broadcast("mess", "听说杨康被江湖人士追杀，最后被金兵给救走了。" NOR); 
}
