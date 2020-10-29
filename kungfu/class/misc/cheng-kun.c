// This program is a part of NT MudLIB

#include <ansi.h>
#include <combat.h>
#include <command.h> 

void smart_fight();
void random_move();
void death_msg();

inherit BOSS;
inherit F_SSERVER;

void create()
{
        set_name("成昆", ({ "cheng kun", "cheng" }) );
        set("long", sort_msg("谢逊之师，和前明教教主阳顶天夫人私通被发现，阳顶天因此走火而亡，夫人自杀，"
                             "他深深不忿，仇恨无所宣泄，展开了庞大漫长的复仇计划，通过谢逊来扰乱明教。后"
                             "拜空见神僧为师，学得少林九阳功，又阴谋设局使空见被谢逊所杀。以高德大僧身份，"
                             "结党营私，图谋不轨。暗地里策动六大派围攻光明顶...\n"));
        set("title", HIR"混元霹雳手"NOR);
        set("gender", "男性");
        set("class", "bonze");
        set("age", 55);
        set("attitude", "peaceful");
        set("str", 36);
        set("con", 33);
        set("dex", 30);
        set("int", 28);

        set("qi", 60000000);
        set("max_qi", 60000000);
        set("jing", 50000000);
        set("max_jing", 50000000);
        set("neili", 80000000);
        set("max_neili", 80000000);
        set("jiali", 30000);
        set("combat_exp", 2000000000);
        set("level", 70);
        set("score", 5000);
        set("jiali", 620);
        set("shen_type", -1);

        set_skill("finger", 1200);
        set_skill("force", 1200);
        set_skill("parry", 1200);
        set_skill("dodge", 1200);
        set_skill("shaolin-shenfa", 1200);
        set_skill("huanyin-zhi", 1200);
        set_skill("hunyuan-yiqi", 1200);
        set_skill("literate", 1200);
        set_skill("martial-cognize", 1200);

        map_skill("force", "hunyuan-yiqi");
        map_skill("parry", "poyang-jian");
        map_skill("finger", "huanyin-zhi");
        map_skill("dodge", "shaolin-shenfa");

        prepare_skill("finger", "huanyin-zhi");

        create_family("少林派", 36, "弟子");

        set("chat_chance", 30);
        set("chat_msg", ({ 
                (: random_move :),
                "师妹，自你去后，可知我是如何渡过的，不管有多苦，为你，我愿成魔...\n ",
        }));
        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "finger.huanyin" :),
                (: exert_function, "powerup" :),
                (: smart_fight() :),
        }));

        set_temp("apply/attack", 1000);
        set_temp("apply/defense", 2000);
        set_temp("apply/damage", 1000);
        set_temp("apply/unarmed_damage", 1000);
        set_temp("apply/armor", 5000);
        set_temp("apply/reduce_damage", 90);
        set_temp("apply/reduce_busy", 36);
        set_temp("apply/add_busy", 15);

        set("death_msg", (: death_msg :));
        set("rewards", ([
                "exp"   : 100000,
                "pot"   : 50000,
                "mar"   : 10000,
                "score" : 300,
                "gold"  : 5,
        ]));

        set("drops", ([
                "RA&RANDOM60"    :       50,   // 低级普通装备
                "RA&RANDOM70"    :       30,   // 低级普通装备
                "FI&/clone/tessera/rune21" :   30,
                "FI&/clone/goods/enchant-scroll" :   40,
                "FI&/clone/goods/sun"   :   50,
                "FI&/clone/goods/sun"   :   50,
                "FI&/clone/goods/moon"  :   50,
                "FI&/clone/goods/moon"  :   50,
                "FI&/clone/tessera/rune12"  :   1,
                "FI&/clone/tongren/tongren" + (1+random(2)):              1,
        ]));

        setup();

        carry_object("/kungfu/class/songshan/obj/yellow-cloth")->wear();
        set_temp("born_time", time());
        if (clonep()) keep_heart_beat();
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
        //me->receive_wound("qi", 500 + random(600), ob);
        return HIY "$N" HIY "怒喝一声，奋力反抗，竟逼得$n" HIY "手忙脚乱。\n" NOR;
}

void heart_beat()
{
        if (query("neili") < 1 && random(10) == 1)
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

                CHANNEL_D->channel_broadcast("news", HIG "听说" + HIW + env->short() + "(" + LOOK_CMD->locate(base_name(env)) + ")" HIG "一带出现的" +
                        HIR + this_object()->short() + HIR "消失了。\n" NOR);

                destruct(this_object());
                return;
        }
        //::random_move();
}

void death_msg()
{
        command("mess 我还不能死，我要亲手覆灭明教，师妹，大仇得报的时候，我就去见你...");
}

void smart_fight()
{
        object me;
        object target;
        string msg;
        int damage;
        
        target = select_opponent();
        me = this_object();
        
        damage = damage_power(me, "finger");
        damage *= 120;
        
        msg = HIR "$N低垂的眼帘往上扬起，露出一对深邃难测，阴狠冰冷的目光，接著灰色的僧袍往下凹陷，紧贴全身，一指点出。"
                  "动作行云流水，又若羚羊挂角，玄机暗含。一指汇集了全身的内力，瞬时全身衣衫再次鼓胀，双目放出惊人的光芒，"
                  "在$n尚自吃惊之际，$N的一指已如流星闪电般袭至，同时伴随的还有刺骨的寒气和无尽的阴毒之风，$n只觉的周"
                  "围的空气似乎都在霎那间凝固了，浑身似乎有冰蚕在血脉中爬行，甚至发出咝咝的轻声...\n" NOR;
         
        msg += COMBAT_D->do_damage(me, target, SPECIAL_ATTACK, damage, 500, 
                HIR"\n$n被$N的冰寒指力点中，真气瞬间涣散无法凝聚，全身冰冷入骨，脸色发青，不由得吐出一大口鲜血，飞出倒地！\n" NOR); 
        
        message_combatd(sort_msg(msg), me, target); 

        return;
}

