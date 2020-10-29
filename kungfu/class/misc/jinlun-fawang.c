// This program is a part of NT MudLIB
// jinlun-fawang.c

#include <ansi.h>

#define JINLUN    "/clone/lonely/jinlun"
#define JIASHA    "/clone/lonely/jiasha"

inherit BOSS;

void create()
{
        object ob1, ob2;
        set_name("金轮法王", ({ "jinlun fawang", "jinlun", "fawang" }));
        set("long", @LONG
他便是大轮寺的护教法王。贵为蒙古国师，极
受成吉思汗重用，常年来随军队征战，扰乱中
原武林，地位显赫尊崇无比。金轮法王踏足中
原后罕逢敌手，藐视中原群雄。其武道之高深
当可谓西域第一人。
LONG);
        set("nickname", HIY "蒙古国师" NOR);
        set("gender", "男性");
        set("class", "bonze");
        set("age", 58);
        set("attitude", "peaceful");
        set("shen_type", -1);

        set("str", 70);
        set("int", 70);
        set("con", 70);
        set("dex", 70);

        set("max_jing", 30000000);
        set("max_jingli", 30000000);
        set("jingli", 30000000);
        set("qi", 8000000);
        set("max_qi", 8000000);

        set("neili", 300000);
        set("max_neili", 300000);
        set("jiali", 4200);
        set("combat_exp", 120000000);
        set("score", 500000);

        set_skill("force", 900);
        set_skill("mizong-neigong", 900);
        set_skill("unarmed", 900);
        set_skill("longxiang-gong", 900);
        set_skill("dodge", 900);
        set_skill("shenkong-xing", 900);
        set_skill("hammer", 900);
        set_skill("riyue-lun", 900);
        set_skill("dali-chu", 900);
        set_skill("xiangmo-chu", 900);
        set_skill("sword", 900);
        set_skill("mingwang-jian", 900);
        set_skill("dagger", 900);
        set_skill("finger", 900);
        set_skill("poxu-daxuefa", 900);
        set_skill("hand", 900);
        set_skill("dashou-yin", 900);
        set_skill("cuff", 900);
        set_skill("yujiamu-quan", 900);
        set_skill("parry", 900);
        set_skill("lamaism", 900);
        set_skill("literate", 900);
        set_skill("sanscrit", 900);
        set_skill("martial-cognize", 900);
        set_skill("mizong-zhenyan", 1500);

        map_skill("force", "longxiang-gong");
        map_skill("dodge", "shenkong-xing");
        map_skill("parry", "longxiang-gong");
        map_skill("unarmed", "longxiang-gong");
        map_skill("hammer", "riyue-lun");
        map_skill("dagger", "poxu-daxuefa");
        map_skill("sword", "mingwang-jian");
        map_skill("finger", "poxu-daxuefa");
        map_skill("hand", "dashou-yin");
        map_skill("cuff", "yujiamu-quan");

        prepare_skill("unarmed", "longxiang-gong");

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "hammer.po" :),
                (: perform_action, "hammer.yuan" :),
                (: perform_action, "hammer.lian" :),
                (: perform_action, "unarmed.tun" :),
                (: perform_action, "unarmed.die" :),
                (: perform_action, "unarmed.ji" :),
                (: exert_function, "recover" :),
                (: exert_function, "shield" :),
                (: exert_function, "powerup" :),
        }));

        create_family("大轮寺", 1, "住持");

        //set("end_time", 1200);  // 必须战斗不少于1200秒后死亡
        set("rewards", ([
                "exp"   : 100000,
                "pot"   : 50000,
                "mar"   : 10000,
                "weiwang" : 500,
                "score" : 500,
                "gold"  : 100,
        ]));

        set("drops", ([
                "RA&RANDOM40"    :       100,   // 低级普通装备
                "RA&RANDOM50"    :       40,    // 低级普通装备
                "FI&/clone/goods/enchant-scroll" :   20,
                "FI&/clone/goods/sun"    :   20,
                "FI&/clone/goods/moon"   :   20,
                "FI&/clone/money/gold"                     :              200,
                "FI&/clone/money/yuanbao"                  :              100,
                "FI&/clone/fam/item/stone5"                :              30,
                "FI&/clone/armor/zijinhua-erhuan3"         :              30,
                "FI&/clone/tuteng/diwang-suipian4"         :              120,
                "FI&/clone/tongren/tongren" + (1+random(2)):              1,
                "FI&/clone/tessera/rune08"  :   1,
                "FI&/clone/misc/baoxiang" : 100,
        ]));

        setup();

        set_temp("apply/damage", 1500);
        set_temp("apply/unarmed_damage", 1500);
        set_temp("apply/armor", 14000);

        set_temp("apply/reduce_damage", 70);
        set_temp("apply/reduce_busy", 36);
        set_temp("apply/add_busy", 15);

        if (clonep())
        {
                ob1 = find_object(JINLUN);
                if (! ob1) ob1 = load_object(JINLUN);
                if (! environment(ob1))
                {
                        ob1->move(this_object());
                        ob1->wield();
                }
        }

        if (clonep())
        {
                ob2 = find_object(JIASHA);
                if (! ob2) ob2 = load_object(JIASHA);
                if (! environment(ob2))
                {
                        ob2->move(this_object());
                        ob2->wear();
                } else
                {
                        ob2 = new("/d/xueshan/obj/p-jiasha");
                        ob2->move(this_object());
                        ob2->wear();
                }
        }
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
        return 1;
}

mixed hit_ob(object me, object ob, int damage_bouns)
{
        ob->start_busy(5 + random(6));
        me->receive_wound("qi", 1500 + random(1500), ob);
        return HIY "$N" HIY "大喝一声，拼死反抗，竟逼得$n" HIY "手忙脚乱。\n" NOR;
}

void heart_beat()
{
        if (query("neili") < 1 && random(50) == 1)
                set("neili", query("max_neili"));

        ::heart_beat();
}

varargs void die(object killer)
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

        if (! killer)
        {
                destruct(this_object());
                return;
        }

        // 战胜金轮获取小龙女线索
        if (query("can_perform/surge-force/quest/step", killer) == 1)
        {
                message_vision(HIR "$N" HIR "眼见$n" HIR "快要支持不住，赶紧上前一步喝道：快说，小龙女何在？"
                                   "否则，取你老命！\n$n" HIR "怒道：小龙女已经被那公孙止捉去，困于绝情山庄内，关"
                                   "我何事？\n\n正说话间，$n" HIR "已趁机杀出一条血路...\n\n" NOR, killer, this_object());

                tell_object(killer, HIM "看来，还是赶快去绝情山庄一趟吧！\n\n" NOR);
                set("can_perform/surge-force/quest/step", 2, killer);
                killer->save();
        }

        //command("chat* haha");
        command("mess 天下间竟有武功如此了得的人物，老衲甘拜下风！");

        return ::die();
}
