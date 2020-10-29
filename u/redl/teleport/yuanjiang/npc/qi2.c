// This program is a part of NT MudLIB
// redl 2015/10
// /u/redl/teleport/yuanjiang/npc/qi.c
#include <ansi.h>
inherit BOSS;

void create()
{
        set_name(CYN "齐霞儿" NOR, ({ "qi xiaer", "qi" }) );
        set("title", HIG "蜀山" HIC "剑侠" NOR);
        set("long", HIR "这是传说中的蜀山第三代精英弟子，此来是为了元江金船夺宝。\n" NOR);
        set("gender", "女性");
        set("family/family_name", "峨嵋派");
        set("age", 35);
        set("str", 80);
        set("int", 80);
        set("con", 80);
        set("dex", 80);
        set("shen", 9000000);
        set_temp("apply/attack", 10000000);
        set_temp("apply/unarmed_damage", 1500000);
        set_temp("apply/damage", 1500000);
        set_temp("apply/armor", 8000000);
        set("max_qi", 8000000000000);
        set("eff_qi", 8000000000000);
        set("qi", 8000000000000);
        set("max_jing", 1500000000000);
        set("jing", 1500000000000);
        set("eff_jing", 1500000000000);
        set("max_jingli", 5000000000);
        set("jingli", 5000000000);
        set("max_neili", 25000000000);
        set("neili", 25000000000);
        set("jiali", 2000000);
        set("combat_exp", 380000000000);
        set("level", 300 + random(101));
        set_skill("strike", 58555);
        set_skill("piaoxue-zhang", 58555);
        set_skill("claw", 58555);
        set_skill("jiuyin-baiguzhao", 58555);
        set_skill("finger", 58555);
        set_skill("tiangang-zhi", 58555);
        set_skill("sword", 58555);
        set_skill("yitian-jian", 58555);
        set_skill("parry", 58555);
        set_skill("force", 58555);
        set_skill("linji-zhuang", 58555);
        set_skill("emei-jiuyang", 58555);
        set_skill("dodge", 58555);
        set_skill("zhutian-bu", 58555);
        set_skill("martial-cognize", 58555);
        set_skill("force-cognize", 58555);
        set_skill("jingxin", 2000);
        set_skill("mahayana", 6000);
        set_skill("literate", 18800);
        set_skill("zuoyou-hubo", 1000);
        set_skill("array", 1000);
        set_skill("taoism", 1000);
        set_skill("baijin-jianqi", 30000);
        map_skill("taoism", "baijin-jianqi");
        map_skill("strike", "piaoxue-zhang");
        map_skill("parry", "piaoxue-zhang");
        map_skill("claw", "jiuyin-baiguzhao");
        map_skill("finger", "tiangang-zhi");
        map_skill("force", "linji-zhuang");
        map_skill("dodge", "zhutian-bu");
        map_skill("sword", "yitian-jian");
        prepare_skill("strike", "piaoxue-zhang");
        set_skill("mingyu-gong", 46666);
        set_skill("fumo-jian", 46666);
        set_skill("wushen-jian", 46666);
        set_skill("yuenv-jian", 46666);
        set_skill("kuihua-mogong", 46666);
        set_skill("huifeng-jian", 46666);
        set_skill("never-defeated", 46666);
        set_skill("tianjian", 46666);
        set_skill("tangshi-jian", 46666);
        set_skill("sword-cognize", 31999);
        set("tianyishenjiu_time", 500);

        set("chat_chance", random(20) + 100);
        set("chat_msg", ({
//                              (: random_move :),
//                              (: random_move :),
//                              (: random_move :),
                (: command("guard qi lingyun") :),
                (: command("eat guiyuan dan") :),
                                (: exert_function, "powerup" :),
                                (: exert_function, "zhixin" :),
                                (: exert_function, "fengyun" :),
                                (: exert_function, "niepan" :),
        }));

        //set("auto_perform", 1);
        set("can_perform/yitian-jian/zhen", 30000);
        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
              (: command("eat guiyuan dan") :),
              (: command("perform finger.ling") :),
              (: command("perform finger.ling") :),
              (: command("perform finger.ling and zhao") :),
              (: command("perform sword.zhen") :),
        }));

        set("rewards", ([
                "exp"   : 1500000,
                "pot"   : 750000,
                "mar"   : 150000,
                "weiwang" : 30000,
                "score" : 30000,
                "gold"  : 10000,
        ]));

        set_temp("apply/reduce_damage", 92);
        set_temp("apply/reduce_busy", 75);
        setup();

        carry_object("/kungfu/class/quanzhen/obj/magrobe")->wear();
        carry_object(__DIR__"obj/tianlongjian")->wield();
        carry_object("/clone/medicine/guiyuan");
}

int accept_hit(object me)
{
        this_object()->kill_ob(me);
        return 1;
}

int accept_fight(object me)
{
        this_object()->kill_ob(me);
        return 1;
}

int accept_kill(object me)
{
        this_object()->kill_ob(me);
        return 1;
}

varargs void unconcious(object defeater)
{
        die(defeater);
        return;
}

void init()
{
        object me, ob;
        me = this_object();
        ob = this_player();
        
        if (!ob->is_character()) return;
        if (query("id", ob)=="qi lingyun") {
                me->set_leader(ob);
                if (!query_temp("guardfor", me)) command("guard qi lingyun");
        }
//      if (environment() && query("no_fight", environment())) return;
//      if (!(__DIR__"obj/door"->is_attacker(ob))) return;
//      tell_object(ob, NOR CYN + query("name", me) + NOR + CYN "嗔怒道：就凭你也想和我峨眉争夺广成金船？\n" NOR);
//      me->kill_ob(ob);
}

