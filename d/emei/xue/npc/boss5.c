// This program is a part of NT MudLIB
// redl 2014
// 郑隐

#include <ansi.h>

inherit BOSS;

void check_weapon();


void create()
{
        set_name(HIC "郑隐" NOR, ({ "zheng yin", "yin", "boss" }) );
        set("title", HIR "血神子" NOR);
        set("long", HIR "这是个英俊豪爽，风度翩翩的中年美男子。\n" NOR);
        set("gender", "男性");
        set("age", 37);

        set("str", 80);
        set("int", 100);
        set("con", 300);
        set("dex", 500);
        set("shen", -1000000000);
        set_temp("apply/attack", 1800000);
        set_temp("apply/unarmed_damage", 200000);
        set_temp("apply/damage", 200000);
        set_temp("apply/armor", 90000);
        set("max_qi", 60000000000000);
        set("eff_qi", 60000000000000);
        set("qi", 60000000000000);
        set("max_jing", 30000000000000);
        set("eff_jing", 30000000000000);
        set("jing", 30000000000000);
        set("max_jingli", 8000000000);
        set("jingli", 8000000000);
        set("max_neili", 8000000000);
        set("neili", 8000000000);
        set("jiali", 100000);
        set("combat_exp", 500000000000);
        set("level", 500);

        set_skill("unarmed", 20000);
        set_skill("finger", 20000);
        set_skill("claw", 20000);
        set_skill("strike", 20000);
        set_skill("hand", 20000);
        set_skill("cuff", 20000);
        set_skill("parry", 20000);
        set_skill("dodge", 20000);
        set_skill("force", 20000);
        set_skill("sword", 20000);
        set_skill("blade", 20000);

        set_skill("zuoyou-hubo", 2500);
        set_skill("martial-cognize", 150000 + random(9999));
        set_skill("count", 50000 + random(9999));
        set_skill("shenzhaojing", 300000 + random(9999));
        set_skill("xueying-shenfa", 300000 + random(9999));//
        set_skill("literate", 10000);
        set_skill("jingluo-xue", 5000);

        set("no_nuoyi", 1); // 不被挪移影响
        set("yuanshen", 1); 

        map_skill("parry", "shenzhaojing");
        map_skill("force", "shenzhaojing");
        map_skill("dodge", "xueying-shenfa");
        map_skill("unarmed", "shenzhaojing");
        prepare_skill("unarmed", "shenzhaojing");

        set("can_perform/qiankun-danuoyi/yi", 1);
        set("can_perform/lonely-sword/yi", 1);
        set("can_perform/lonely-sword/po", 1);
        set("can_perform/lonely-sword/jian", 1);
        set("can_perform/lonely-sword/qi", 1);
        set("can_perform/tanzhi-shentong/ding", 1);
        set("can_perform/tanzhi-shentong/dian", 1);

         set("chat_chance", 3);
         set("chat_msg", ({
                (: command("say 墓园主人原本是我这里的一只小蝙蝠，也敢称血魔？") :),
                (: command("say 小丁不堪重用，收集来的气血还不如在这摄取来的。") :),
         }));

        // yun perform
        set("chat_chance_combat", 90);
        set("chat_msg_combat", ({
              (: command("perform unarmed.wu and unarmed.ying") :),
              (: command("perform unarmed.wu and unarmed.wu") :),
              (: command("perform unarmed.ying and unarmed.ying") :),
              (: exert_function, "shield" :),
              //(: exert_function, "roar" :),
              (: exert_function, "recover" :),
        }));

        set("my_life", 4); // 当气血低于10%的时候补满一次，设置该参数为0

        //set("auto_perform", 1);
        set("end_time", 60);  // 必须战斗不少于60秒后死亡
        set("rewards", ([
                "exp"   : 2500000,
                "pot"   : 1000000,
                "mar"   : 100000,
                "weiwang" : 10000,
                "score" : 10000,
        ]));

        set("drops", ([
                "FI&/clone/tessera/fdiamond"   : 25,
                "FI&/clone/tessera/femerald"   : 25,
                "FI&/clone/tessera/fsapphire"   : 25,
                "FI&/clone/tessera/fruby"   : 25,
                "FI&/clone/tessera/ftopaz"   : 25,
                "FI&/clone/medal/vip_xunzhang"   : 1,
                "RA&MYTH60" : 6, 
        ]));

        set_temp("apply/reduce_damage", 88);
        //set_temp("apply/reduce_busy", 25);
        set_temp("apply/add_busy", 10);
        set_temp("apply/add_poison", 99);

        setup();

        carry_object("/kungfu/class/quanzhen/obj/whiterobe")->wear();

//        set("startroom", "/d/jianzhong/maigu");
}

void heart_beat()
{
        // 解除不能perform yun的限制
        if (random(2) == 1)
        {
                delete_temp("no_perform");
                delete_temp("no_exert");
        }
        if (random(5) == 1) check_weapon();
                if (!this_object()->is_fighting()) {
                        this_object()->stop_busy();
                        command("halt");
                        command("yun powerup");
                        full_self(); // 补满气血
                }
        return ::heart_beat();
}

// 检查武器
void check_weapon()
{
        object me;
        me = this_object();
        if (me->is_busy()) me->interrupt_busy(me, 1000);
        if (me->is_busy()) me->interrupt_me(me);
        if (me->is_busy()) me->stop_busy();
        if (me->is_busy()) me->interrupt_busy(me);
        return;
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

void new_life()
{
        object ob;
    full_self(); // 补满气血
        filter_array(all_inventory(environment(this_object())), (: $1->is_character() :))->start_busy(3);
    delete_temp("no_perform");
    delete_temp("no_exert");
    addn("my_life", -1);
    message_vision(HIY "\n$N" HIY "背后的血光一分再一闪，一道血红色的影子慢慢出现在他身边。\n" NOR, this_object());//分身为二
        ob = new(__FILE__);
        set("my_life", query("my_life") + ((random(16)) ? 0 : 1), ob); 
        set("chat_chance", 0, ob);
        ob->move(environment());
}

int receive_damage(string type, int damage, object who)
{
        object *ppl;

        if( !who ) who = this_object()->query_last_damage_from();
        if( !who ) return;
        ppl = query_temp("damage_from");
        if( !arrayp(ppl) || !sizeof(ppl) ) ppl = ({});
        if( userp(who) && member_array(who, ppl) == -1 )
        {
                ppl += ({ who });
                set_temp("damage_from", ppl);
        }

        if (query("my_life") && query("qi") < query("max_qi") / 10)
        {
                new_life(); // 重生一次
                return 0;
        }

        return ::receive_damage(type, damage, who);
}

void die(object killer)
{
        string prop, name;
        mapping data;
        object ob, where;
/*        string *apply = ({ "reduce_busy", "avoid_busy", "def_damage", "avoid_weak",
                "add_locked", "reduce_damage", "add_busy", "add_weak", "avoid_locked",
                "add_damage", "add_skill" });*/

        if( objectp(ob = previous_object(0)) && sscanf(base_name(ob), "/kungfu/skill/%*s") )
        {
                full_self();
                return;
        }

        if( !objectp(killer) ) killer = this_object()->query_last_damage_from();
        if( !objectp(killer) ) killer = query_temp("last_damage_from");

        // 如果还未重生，则重生一次
        if (query("my_life"))
        {
                new_life();
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
                //message_vision(HIR "\n$N" HIR "大喝一声，运用秘法，气血有所回升！\n\n" NOR, this_object());
                return;
        }

        where = environment();

        return ::die(killer);
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

// 不会被busy
/*varargs void start_busy(mixed new_busy, mixed new_interrupt)
{
        return;
}*/

void delay_kill(object me, object ob)
{
        me->kill_ob(ob);
}

void init()
{
        object me, ob;
        string basename;

        me = this_object();
        ob = this_player();
        
        if (!ob->is_character()) return;
        if (query("env/invisible", ob)) return;
        basename = base_name(ob);
        if (strsrch(basename, __DIR__) != -1) return;
        /*if (0 && environment()==environment(ob)) {
                tell_object(ob, query("name", me) + NOR CYN "瞥了你一眼说道：“精血太枯，先去墓园副本锻炼过，再来供奉我吧...”\n他长袖一挥之间，你已经被拂到了洞外。\n\n" NOR);
                ob->move("/d/emei/jldongnei");
                return;
        }*/
        call_out("delay_kill", 4, me, ob);
        if (playerp(ob)) set("enemy_player", ob);
}


