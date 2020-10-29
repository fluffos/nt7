#include <ansi.h>
inherit BOSS;

void create()
{
        set_name(HIM"贼盗王"NOR, ({"zeidao wang", "wang", "boss"}) );
        set("title", HIC "绿林霸主" NOR);
        set("gender", "男性" );
        set("age", random(30)+20);
        set("long", "迷雾森林的贼盗首领，有着一身不凡的武艺，穷凶恶极手下罕有十合之将。\n");
        set("attitude", "aggressive");
        set("class", "lvlin");
        set("str", 30);
        set("con", 30);
        set("int", 30);
        set("dex", 30);
        set("max_qi", 5000000);
        set("eff_qi", 5000000);
        set("qi", 50000000);
        set("max_jing", 2100000);
        set("eff_jing", 2100000);
        set("jing", 21000000);
        set("neili", 5000000);
        set("max_neili", 500000);
        set("jingli", 100000);
        set("max_jingli", 100000);
        set("no_suck",1);
        set("jiali", 200);
        set("shen", 0);
        set("end_boss", 1);
        set_temp("apply/attack",  50);
        set_temp("apply/defense", 30);
        set("combat_exp", 100000000);
        set_skill("force", 2000);
        set_skill("unarmed", 2000);
        set_skill("dodge", 2000);
        set_skill("parry", 2000);
        set_skill("blade", 2000);
        set_skill("douzhuan-xingyi", 2000);
        set_skill("guiyuan-tunafa", 2000);
        set_skill("tie-zhang", 1500+random(1500));
        set_skill("wuming-jianfa", 1500+random(1500));
        set_skill("wuhu-duanmendao", 1500+random(1500));
        set_skill("shaolin-shenfa", 2000);
        set_skill("martial-cognize", 2000);
        map_skill("force", "guiyuan-tunafa");
        map_skill("unarmed","tie-zhang");
        map_skill("parry", "wuhu-duanmendao");
        map_skill("blade", "wuhu-duanmendao");
        map_skill("dodge", "shaolin-shenfa");
        create_family("绿林暴风盟", 3, "首领");

        set("auto_perform", 1);
        set("clear_fuben", 1); 
        set("drops", ([
                "RA&RANDOM30" : 50,
                "RA&RANDOM30" : 50,
                "RA&RANDOM30" : 50,
                "RA&RANDOM20" : 100,
                "RA&RANDOM20" : 100,
                "RA&RANDOM20" : 100,
                "FI&/clone/goods/sun" : 30,
                "FI&/clone/goods/moon" : 30,
                "FI&/clone/tessera/cruby" : 30,
                "FI&/clone/tessera/ctopaz" : 30,
                "FI&/clone/tessera/csapphire" : 30,
                "FI&/clone/tessera/cemerald" : 30,
                "FI&/clone/tessera/cdiamond" : 30,
                "FI&/clone/goods/enchant-scroll" : 30,
                "FI&/clone/goods/resolve-scroll" : 50,
        ]));
        set("rewards", ([
                "exp"  : 15000,
                "pot"  : 5000,
                "mar"  : 300,
        ]));
        /*
        set_temp("apply/attack", 2000+random(1000));
        set_temp("apply/damage",2000+random(1000));
        set_temp("apply/unarmed_damage",2000+random(1000));
        set_temp("apply/armor", 2000+random(1000));
        set_temp("apply/add_weak", 50);
        set_temp("apply/add_busy",15);
        set_temp("apply/reduce_busy", 30);
        */
        set_temp("apply/reduce_damage", 50);
        setup();

        carry_object("/clone/weapon/gangjian")->wield();
        carry_object("/clone/weapon/blade")->wield();

        carry_object("/clone/misc/cloth")->wear();
        add_money("gold", random(300));
}

void init()
{
        object ob, me;

        me = this_player();
        ob = this_object();

        ::init();
        if( interactive(me) && visible(me) &&
            !is_fighting()) {
                kill_ob(me);
        }
}
