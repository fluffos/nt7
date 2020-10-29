 // This program is a part of NT MudLIB
// redl 2015/10
// /u/redl/teleport/yuanjiang/npc/xiao.c
#include <ansi.h>
inherit BOSS;

#define SKLV 400000
#define APPL 6000
#define BONUS_EXP 5000000

void create()
{
        set_name(CYN "晓月禅师" NOR, ({ "xiaoyue chanshi", "chanshi", "xiaoyue" }) );
        set("title", HIG "蜀山" HIC "弃徒" NOR);
        set("long", HIR "这是传说中的长眉第三徒灭尘子，\n此时才刚夺掌教之位失败，投奔哈哈老祖之前。\n" NOR);
        set("gender", "男性");
        set("family/family_name", "魔教");
        set("age", 58);
        set("str", 180);
        set("int", 180);
        set("con", 180);
        set("dex", 180);
        set("shen", -18000000);
        set_temp("apply/attack", APPL);
        set_temp("apply/unarmed_damage", APPL);
        set_temp("apply/damage", APPL);
        set_temp("apply/armor", APPL * 3);
        set("max_qi", 10000000000000000);
        set("eff_qi", 10000000000000000);
        set("qi", 10000000000000000);
        set("max_jing", 10000000000000000);
        set("jing", 10000000000000000);
        set("eff_jing", 10000000000000000);
        set("max_jingli", 2000000000);
        set("jingli", 2000000000);
        set("max_neili", 2000000000);
        set("neili", 2000000000);
        set("jiali", APPL);
        set("combat_exp", 2000000000000);
        set("level", 400 + random(101));
        
        set_skill("finger", SKLV);
        set_skill("canhe-zhi", SKLV);
        map_skill("finger", "canhe-zhi");
        prepare_skill("finger", "canhe-zhi");
        
        set_skill("blade", SKLV);
        set_skill("moon-blade", SKLV);
        map_skill("blade", "moon-blade");
        
        set_skill("parry", SKLV);
        set_skill("moshen-zhenshen", SKLV);
        map_skill("parry", "moshen-zhenshen");
        
        set_skill("force", SKLV);
        set_skill("chiyou-kuangzhanjue", SKLV);
        map_skill("force", "chiyou-kuangzhanjue");
        
        set_skill("dodge", SKLV);
        set_skill("jiutian-xiaoyaobu", SKLV);
        map_skill("dodge", "jiutian-xiaoyaobu");

        set_skill("taoism", 3000);
        set_skill("xuanli-daogang", 80000);
        map_skill("taoism", "xuanli-daogang");
        
        set_skill("medical", 3000);
        set_skill("mojiao-medical", 5000);
        map_skill("medical", "mojiao-medical");
        
        set_skill("martial-cognize", SKLV / 10);
        set_skill("force-cognize", SKLV / 10);
        set_skill("sword-cognize", SKLV / 10);
        set_skill("motun-tianxia", 3000);
        set_skill("huitong-tianxia", 3000);
        set_skill("lunhui", 3000);
                
        set_skill("mahayana", 60000);
        set_skill("buddhism", 60000);
        set_skill("literate", 60000);
        set_skill("zuoyou-hubo", 1000);
        set_skill("array", 1000);
        

        //set("auto_perform", 1);
//         set("can_perform/yitian-jian/zhen", 30000);
        set("chat_chance_combat", 70);
        set("chat_msg_combat", ({
              (: command("perform blade.ting") :),
              //(: command("perform blade.dao") :),
        }));

//         set("rewards", ([
//                 "exp"   : 3000000,
//                 "pot"   : 1500000,
//                 "mar"   : 300000,
//                 "weiwang" : 50000,
//                 "score" : 50000,
//                 "gold"  : 10000,
//         ]));

        set_temp("apply/reduce_damage", 80);
        set_temp("apply/reduce_busy", 80);
        set_heart_beat(2);
        set("death_msg", NOR "\n$N" + (random(2)? "尖叫" : "嘶吼") + (random(2)? "一声" : "一头") + "栽倒，" + (random(2)? "化作脓血" : "散作青烟") + (random(2)? "。。" : "。。。") + "\n" NOR);
        setup();

        carry_object("/kungfu/class/quanzhen/obj/yellowrobe")->wear();
        carry_object("/clone/weapon/jiedao")->wield();
        carry_object("/clone/weapon/jiedao")->wield();
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

varargs void die()
{
        object ob;
        object killer;

        if(random(50) && //x% can call_die
         objectp(ob = previous_object(0)) &&
            sscanf(base_name(ob), "/kungfu/skill/%*s") ) {
                this_object()->full_self();
                return;
        }
       
        killer = query_last_damage_from();
        if (!killer || !objectp(killer)) {
                killer = query_temp("last_opponent", this_object());
        }
        if (!killer || !objectp(killer)) {
                killer = query("enemy_player", this_object());
        }
        
                message_vision(append_color(query("death_msg"),CYN), this_object());
                        if (!query("is_shadow", this_object())) {
                                if (killer && objectp(killer) && environment(killer)==environment(this_object())) GIFT_D->delay_bonus(killer, 
                                        ([ "exp" : BONUS_EXP, "pot" : BONUS_EXP/3, "mar" : BONUS_EXP/6, "prompt" : "你在广成金船击败" + name() + "之后"]));
                        }
                                        
                destruct(this_object());
                return;
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
        if (environment() && query("no_fight", environment())) return;
        if (!(__DIR__"obj/door"->is_attacker(ob))) return;
        tell_object(ob, NOR CYN + query("name", me) + NOR + CYN "恚怒道：就凭你也想和洒家争夺广成金船？\n" NOR);
        me->kill_ob(ob);
}

void heart_beat()
{
        if (!environment()) return;
        
        if (!random(5))
        {
                this_object()->clear_condition("no_perform");
                this_object()->clear_condition("no_exert");
                delete_temp("no_perform");
                delete_temp("no_exert");
                this_object()->stop_busy();
                if (!query_temp("weapon")) {
                        new("/clone/weapon/jiedao")->move(this_object());
                        command("wield all");
                }
                set("neili", query("max_neili"));
        }
        if (this_object()->is_fighting()) {
                                addn("jiali", APPL / 5);
                                addn_temp("apply/attack", APPL * 2);
                                addn_temp("apply/unarmed_damage", APPL * 2);
                                addn_temp("apply/damage", APPL * 2);
                                addn_temp("count_sp", 1);
                        if (query("chat_chance_combat")<120) 
                                addn("chat_chance_combat", 1);
                                if (query_temp("count_sp") > 60 + (random(30))) {
                                set("chat_msg_combat", ({
                                      (: command("perform blade.ting") :),
                                  (: command("perform blade.dao") :),
                        }));
                                }
        } else {
                if (query_temp("count_sp")) {
                        delete_temp("count_sp");
                        set("chat_chance_combat", 70);
                        set("chat_msg_combat", ({
                        (: command("perform blade.ting") :),
                        //(: command("perform blade.dao") :),
                }));
            }
                set("jiali", APPL);
            set_temp("apply/attack", APPL);
                set_temp("apply/unarmed_damage", APPL);
                set_temp("apply/damage", APPL);
        }
        return ::heart_beat();
}

int deploy2()
{
        command("go down");
        return 1;
}

int deploy()
{
        object room = get_object("/u/redl/teleport/yuanjiang/jiaban");
        if (!room) return 0;
        message_vision(append_color(NOR + CYN + "$N" + CYN + "纵身跳上了元江宝船。\n" + NOR, CYN), this_object());
        this_object()->move(room);
        message_vision(append_color(NOR + CYN + "$N" + CYN + "纵身跳了上来。\n" + NOR, CYN), this_object());
    set("chat_chance", random(10) + 60);
        set("chat_msg", ({
                                (: random_move :),
                                (: random_move :),
                                (: exert_function, "powerup" :),
                                (: exert_function, "shield" :),
                                (: exert_function, "huaxue" :),
                                (: command("perform parry.wu") :),
        }));
    //call_out("deploy2", 20);
        return 1;
}
