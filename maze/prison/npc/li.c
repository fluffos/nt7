#include <ansi.h>

inherit BOSS;

void create()
{
        object ob;
        set_name(HIW "李莲英" NOR, ({ "li lianying", "li", "lianying" }));
        set("long", "他就是大内太监总管。\n");
        set("title", HIB "太监总管" NOR);
        set("gender", "无性");
        set("age", 50);
        set("shen_type", -1);
        set("str", 91);
        set("int", 39);
        set("con", 50);
        set("dex", 62);
        
        set("max_qi", 10000000);
        set("max_jing", 10000000);
        set("max_jingli", 10000000);
        set("jingli", 10000000);
        set("max_neili", 12000000);
        set("neili", 12000000);
        set("jiali", 55000);
        set("combat_exp", 2000000000);
        set("score", 1200000);

        set_skill("force", 2000);
        set_skill("parry", 2000);
        set_skill("dodge", 2000);
        set_skill("sword", 2000);
        set_skill("unarmed", 2000);
        set_skill("pixie-jian", 2000);        
        set_skill("literate", 2000);
        set_skill("martial-cognize", 2000);
        set_skill("kuihua-mogong", 2000);

        map_skill("force", "kuihua-mogong");
        map_skill("dodge", "kuihua-mogong");
        map_skill("unarmed", "kuihua-mogong");
        map_skill("sword", "kuihua-mogong");
        map_skill("parry", "kuihua-mogong");

        prepare_skill("unarmed", "kuihua-mogong");


        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "dodge.sheng" :),
                (: perform_action, "sword.bian" :),
                (: perform_action, "sword.tian" :),
                (: perform_action, "sword.qiong" :),
                (: perform_action, "sword.zhenwu" :),
                (: perform_action, "dodge.sheng" :),
                (: perform_action, "unarmed.bian" :),
                (: perform_action, "unarmed.tian" :),
                (: perform_action, "unarmed.qiong" :),
                (: exert_function, "recover" :),
                (: exert_function, "powerup" :),
                (: exert_function, "shield" :),
                (: exert_function, "roar" :),
        }) );
        
        set_temp("apply/attack", 5000); 
        set_temp("apply/armor", 10000); 
        set_temp("apply/damage", 5000); 
        set_temp("apply/unarmed_damage", 5000); 
        set_temp("apply/add_xuruo", 90); 
        set_temp("apply/reduce_xuruo", 100);
        set_temp("apply/add_damage", 100);
        set_temp("apply/reduce_damage", 90); 
        set_temp("apply/reduce_busy", 30); 
        set_temp("apply/add_busy", 10); 

        set("auto_perform", 1); 
        set("rewards", ([
                "exp" : 30000,
                "pot" : 10000,
                "mar" : 3000,
        ]));

        set("drops", 
                ([
                "RA&RANDOM50"                                    :       10000,  // 低级普通装备
                "RA&RANDOM60"                                    :       300,    // 中级普通装备
                "FI&/clone/enchase/rune23"   :   300,
                "FI&/clone/enchase/rune24"   :   300,
                "FI&/clone/enchase/rune25"   :   300,
                "MO&A3000"       :       300,
                "MO&A3001"       :       300,
                "MO&A3002"       :       300,
                "MO&A3003"       :       300,
                "MO&A3004"       :       300,
                "MO&A3005"       :       300,
                "MO&A3006"       :       300,
        ]));         
        set("no_corpse", 1);

        setup();

        carry_object("/d/fuzhou/obj/xiuhua")->wield();
        carry_object("/d/wanjiegu/npc/obj/qi-dress")->wear();
}
