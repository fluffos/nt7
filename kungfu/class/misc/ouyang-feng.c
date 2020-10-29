// This program is a part of NT MudLIB

#include <ansi.h>
#include <command.h>

inherit BOSS;

void random_move();
void death_msg();
int checking(object me, object ob);
int hurting();

void create()
{
        set_name("欧阳锋", ({ "ouyang feng", "ouyang", "feng" }));
        set("long", "他是白驼山庄主，号称“西毒”的欧阳锋。\n"
                    "由于习练「九阴真经」走火入魔，已变得精\n"
                    "神错乱，整日披头散发。\n");
        set("title", "老毒物");
        set("gender", "男性");
        set("age", 53);
        set("nickname", HIR "西毒" NOR);
        set("shen_type",-1);
        set("attitude", "peaceful");
        set("str", 100);
        set("int", 70);
        set("con", 50);
        set("dex", 100);

        set("qi", 60000000);
        set("max_qi", 60000000);
        set("jing", 50000000);
        set("max_jing", 50000000);
        set("neili", 80000000);
        set("max_neili", 80000000);
        set("jiali", 30000);

        set("combat_exp", 4000000000);
        set("level", 70);
        set("fight_boss", 1);
        set("score", 5000);

        set_skill("force", 2000);
        set_skill("unarmed", 2000);
        set_skill("dodge", 2000);
        set_skill("parry", 2000);
        set_skill("cuff", 2000);
        set_skill("finger", 2000);
        set_skill("strike", 2000);
        set_skill("staff", 2000);
        set_skill("training", 2000);
        set_skill("poison", 2000);
        set_skill("shedu-qiqiao", 2000);
        set_skill("hamagong", 2000);
        set_skill("chanchu-bufa", 2000);
        set_skill("lingshe-quan", 2000);
        set_skill("lingshe-zhangfa", 2000);
        set_skill("baibian-daxue", 2000);
        set_skill("guzheng-jifa", 2000);
        set_skill("xiyu-tiezheng", 2000);
        set_skill("wushe-qu", 2000);
        set_skill("literate", 280);
        set_skill("medical", 360);
        set_skill("baituo-michuan", 2000);
        set_skill("martial-cognize", 2000);

        map_skill("force", "hamagong");
        map_skill("dodge", "chanchu-bufa");
        map_skill("strike", "hamagong");
        map_skill("cuff", "lingshe-quan");
        map_skill("parry", "lingshe-zhangfa");
        map_skill("staff", "lingshe-zhangfa");
        map_skill("finger", "shedu-qiqiao");
        map_skill("poison", "shedu-qiqiao");
        map_skill("medical", "baituo-michuan");
        map_skill("guzheng-jifa", "xiyu-tiezheng");

        prepare_skill("strike", "hamagong");
        prepare_skill("finger", "shedu-qiqiao");
        prepare_skill("cuff", "lingshe-quan");

        create_family("欧阳世家", 5, "掌门");

/*
        set("chat_chance", 30);
        set("chat_msg", ({ (: random_move :) }));
*/
        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "strike.puji" :),
                (: perform_action, "strike.zhen" :),
                (: perform_action, "staff.chan" :),
                (: perform_action, "staff.qianshe" :),
                (: perform_action, "staff.wuji" :),
                (: perform_action, "cuff.rou" :),
                (: exert_function, "powerup" :),
                (: exert_function, "recover" :),
        }));

        set_temp("apply/attack", 1000);
        set_temp("apply/defense", 2000);
        set_temp("apply/damage", 1000);
        set_temp("apply/unarmed_damage", 1000);
        set_temp("apply/armor", 5000);
        set_temp("apply/reduce_damage", 90);
        set_temp("apply/reduce_busy", 36);
        set_temp("apply/add_busy", 15);
        set_temp("apply/add_poison", 80);

        //set("clear_fuben", 1);
        set("auto_perform", 1);
        //set("end_time", 600);
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
                "FI&/clone/fam/pill/renshen4"               :           30,
                "FI&/clone/tessera/rune12"  :   1,
                "FI&/clone/armor/zijinhua-erhuan2"          :           30,
                "FI&/clone/armor/yecha3"                    :           100,
                "FI&/clone/tongren/tongren" + (1+random(2)):              1,
                "FI&/clone/misc/baoxiang" : 100,
        ]));
        setup();
        carry_object("/clone/misc/cloth")->wear();
        carry_object(WEAPON_DIR"treasure/lingshezhang")->wield();
        carry_object("d/baituo/obj/tiezheng");
        add_money("silver", 50);
        set_temp("born_time", time());
        //if (clonep()) keep_heart_beat();
}

void heart_beat()
{
        if (query("neili") < 1 && random(50) == 1)
                set("neili", query("max_neili"));

        ::heart_beat();
}

varargs void start_busy(mixed new_busy, mixed new_interrupt)
{
        return;
}

int accept_fight(object ob)
{
        kill_ob(ob);
        return -1;
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
        call_out("hurting", random(3)+1);
        return ::kill_ob(me);
}

int checking(object me, object ob)
{
        object weapon;

        remove_call_out("checking");
        if( !objectp(me) || !objectp(ob) )
                return 0;

        if( !query_temp("weapon", me) )
        {
                weapon = new(WEAPON_DIR"treasure/lingshezhang");
                weapon->move(me);
                weapon->wield();
        }

        call_out("checking", 1, me, ob);
        return 1;
}

int hurting()
{
        int i;
        int dam;
        object *inv;

        remove_call_out("hurting");
        message_vision( HIR "\n\n$N手中灵蛇杖吐出一股炽可焚金的火焰．．整个天地似乎都被燃烧着！！！\n\n",this_object());
        inv = all_inventory(environment(this_object()));
        for(i=sizeof(inv)-1; i>=0; i--)
        if( living(inv[i]))
        if( inv[i] != this_object())
        {
                dam = 3000+random(2000);
                inv[i]->receive_wound("qi",dam, this_object());
                inv[i]->receive_wound("jing",dam/2, this_object());

                inv[i]->affect_by("poison",
                                  ([ "level" : 1000,
                                     "id":query("id", this_object()),
                                     "name" : "火毒",
                                     "duration" : 200 ]));
                tell_object(inv[i], HIG "你中了灵蛇杖的火毒。\n");
                COMBAT_D->report_status(inv[i],1);
        }
        call_out("hurting", random(5)+5);
        return 1;
}

mixed hit_ob(object me, object ob, int damage_bouns)
{
        int damage;

        damage = 10000 + random(10000);
        damage += damage_bouns;
        ob->receive_damage("qi", damage, me);
        ob->receive_wound("qi", damage, me);
        set("neili",query("max_neili",  me), me);
        return HIB "$N" HIB "大吼一声，手中"HIR"灵蛇杖"HIB"砸向$n"
               HIB "，$n顿时感到五雷轰顶，伤及五脏内腹。\n" NOR;
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
        //command("chat* yi");
        command("mess* sigh 九阴真经不是天下无敌么...？");
}
