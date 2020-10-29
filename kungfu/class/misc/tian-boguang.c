// This program is a part of NT MudLIB
// boguang.c 田伯光

#include <ansi.h>
#include <command.h>
inherit BOSS;

void death_msg();
void random_move();
int  checking(object me, object ob);
int  fast_attack(object me, object ob);
int  is_stay_in_room()  { return 1; }

void create()
{
        set_name("田伯光", ({ "tian boguang", "tian", "boguang" }));
        set("nickname", HIM "万里独行" NOR);
        set("long", "田伯光为江湖中臭名昭彰的采花贼，一手快刀绝技，天下无双。轻功在武林中也是一等的。\n");
        set("gender", "男性");
        set("age", 35);
        set("attitude", "peaceful");
        set("shen_type", 1);
        set("str", 38);
        set("int", 30);
        set("con", 25);
        set("dex", 30);
        set("shen", 0);

        set("max_qi", 2000000);
        set("max_jing", 1000000);
        set("neili", 2000000);
        set("max_neili", 2000000);
        set("jiali", 1500);
        set("no_suck", 1);
        set("combat_exp", 30000000);
        set("level", 30);
        set("fight_level", 30);
        //set("fight_boss", 1);
        set("score", 5000);

        set_skill("unarmed", 300);
        set_skill("force", 300);
        set_skill("dodge", 300);
        set_skill("parry", 300);
        set_skill("kuangfeng-blade", 300);
        set_skill("blade", 300);
        set_skill("unarmed", 300);
        set_skill("literate", 250);
        set_skill("ding-dodge", 300);
        set_skill("ding-force", 300);
        set_skill("martial-cognize", 400);

        map_skill("dodge", "ding-dodge");
        map_skill("force", "ding-force");
        map_skill("parry", "kuangfeng-blade");
        map_skill("blade", "kuangfeng-blade");

        set_temp("apply/attack", 200);
        set_temp("apply/defense", 200);
        set_temp("apply/damage", 600);
        set_temp("apply/armor", 500);
        set_temp("apply/reduce_damage", 40);
        set_temp("apply/reduce_busy", 6);
        set_temp("apply/add_busy", 3);

/*
        set("chat_chance", 30);
        set("chat_msg", ({ (: random_move :) }));
*/
        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "blade.kuang" :),
        }));

        set("clear_fuben", 1);
        //set("auto_perform", 1);
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
                "FI&/clone/book/kuangfeng-book"  :   20,
                "FI&/clone/goods/sun"    :   20,
                "FI&/clone/goods/moon"   :   20,
                "FI&/clone/book/kuangfeng-dao1"  :   10,
                "FI&/clone/book/kuangfeng-dao2"  :   10,
                "FI&/clone/tessera/rune05"  :   1,
                "FI&/clone/tongren/tongren"+(1+random(2)) : 1,
                "FI&/clone/misc/baoxiang" : 100,
        ]));
        //set("end_time", 300);
        //set("death_msg", (: death_msg :));
        setup();
        set("startroom", "d/huashan/path1");
        carry_object("/clone/weapon/gangdao")->wield();
        carry_object("/clone/cloth/cloth")->wear();
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

void kill_ob(object me)
{
        remove_call_out("checking");
        call_out("checking", 1, this_object(), me);
        return ::kill_ob(me);
}

int checking(object me, object ob)
{
        object weapon;

        if( !objectp(me) || !objectp(ob) )
                return 0;

        if (query("neili") < 1 && random(50) == 1)
                set("neili", query("max_neili"));

        if( !query_temp("weapon", me) )
        {
                weapon = new("/clone/weapon/gangdao");
                weapon->move(me);
                weapon->wield();
        }

        if( me->is_fighting() )
        {
                if( !query_temp("attack_pending", me )
                 && objectp(weapon=query_temp("weapon", me)) )
                {
                        set_temp("attack_pending", 1, me);
                        remove_call_out("fast_attack");
                        call_out("fast_attack", 3, me, ob);
                }

                return 1;
        } else
        if( query("attack_pending", me) == 1 )
        {
                delete_temp("attack_pending", me);
                remove_call_out("fast_attack");
                return 1;
        }

        return 1;
}

int fast_attack(object me, object ob)
{
        int i, num;

        remove_call_out("fast_attack");
        delete_temp("attack_pending", me);
        num = random(3) + 5;

        message_vision("田伯光大喊一声，使出其快刀绝技疯狂般向$N连劈了" + chinese_number(num) + "刀。\n", ob);

        for (i = 1; i < num + 1; i++)
        {
                if( !me->is_fighting(ob) ) break;
                COMBAT_D->do_attack(me,ob,query_temp("weapon", me));
        }

        return 1;
}

mixed hit_ob(object me, object ob, int damage_bouns)
{
        ob->start_busy(5 + random(6));
        me->receive_wound("qi", 200 + random(100), ob);
        return HIY "$N" HIY "大喝一声，拼死反抗，竟逼得$n" HIY "手忙脚乱。\n" NOR;
}

void death_msg()
{
        command("chat* heng");
       	command("chat 今日真是冤家路窄，你爷爷我还有事，不奉陪了 ……");
	CHANNEL_D->channel_broadcast("rumor", "听说" + name() + HIM "被江湖人"
			                     "士追杀，但却奋力拼杀，突出重围，死里逃生。" NOR);
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
