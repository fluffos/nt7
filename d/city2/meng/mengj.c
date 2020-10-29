#include <ansi.h>
inherit NPC;

int do_kill(string arg);
int is_stay_in_room() { return 1; }

void create()
{
        int skill, nl, lvl;
        int exp;

        set_name("蒙古卫队",({ "menggu weidui", "weidui" }) );
        set("gender", "男性" );
        set("long", "这就是此次领兵南侵的负责防卫的蒙古卫队。\n");

        set("int", 30);
        set("str", 30 + random(20));
        set("con", 20 + random(20));
        set("dex", 20 + random(20));
        set("age", 20 + random(30));  
        set("per", 15 + random(15));                                         
        set("no_get", 1);  
        set("env/auto_war", 1);
        
        exp = UPDATE_D->query_max_exp();
        skill = to_int(pow(to_float(exp / 100), 1.0 / 3)) * 10;
        skill += 200;
        nl = skill * 10 + (exp / 10000);
        
        set("combat_exp", exp);
        set("max_neili", nl);
        set("neili", query("max_neili") * 3 / 2); 
        set("max_jingli", nl);
        set("jingli", query("max_jingli"));
        set("max_qi", nl * 10);
        set("qi",  query("max_qi"));
        set("eff_qi", query("max_qi"));
        set("max_jing", nl);
        set("eff_jing", query("max_jing"));
        set("jiali", skill / 2); 

        set_skill("longxiang-gong", skill);
        set_skill("xuedao-daofa", skill);
        set_skill("shenkong-xing", skill);
        set_skill("dashou-yin", skill);
        set_skill("hand", skill);
        set_skill("force", skill);
        set_skill("dodge", skill);
        set_skill("blade", skill);
        set_skill("parry", skill);
        set_skill("arrow", skill*2/3);

        map_skill("force", "longxiang-gong");
        map_skill("dodge", "shenkong-xing");
        map_skill("hand", "dashou-yin");
        map_skill("parry", "xuedao-daofa");
        map_skill("blade", "xuedao-daofa");   

        prepare_skill("hand", "dashou-yin");   
        set_temp("warquest/party", "meng"); 
           
        addn_temp("apply/armor", 400);
        addn_temp("apply/damage", 100);
        setup();

        lvl = (query("str") + skill / 10) / 10 - 1;
        if (lvl > 8) lvl = 8;
        lvl = lvl - 2;
        if (lvl < 3) lvl = 3;
        carry_object("/clone/weapon/bow"+lvl);
        carry_object(__DIR__"obj/wandao");
        carry_object("/clone/weapon/bow"+lvl);
        carry_object(__DIR__"obj/wandao");    
        carry_object("/clone/weapon/bow"+lvl);
        carry_object(__DIR__"obj/wandao");    
        carry_object("/clone/weapon/bow"+lvl);
        carry_object(__DIR__"obj/wandao");    
        carry_object(__DIR__"obj/wandao")->wield();
        carry_object(__DIR__"obj/tiejia")->wear();   
        carry_object(__DIR__"obj/pifeng")->wear();  
}

void init()
{
        ::init();
        
        add_action("do_kill",
                ({ "team kill", "array kill", "touxi", "kill",
                   "hit", "fight", "steal", "beg", "persuade",
                   "perform", "yong", "exert", "yun", "throw",
                   "conjure", "recall" }));
}

int do_kill(string arg)
{
        string what, who;

        if (! arg) return 0;

        if (this_object()->id(arg))
        {
                write("有没有搞错，那是蒙古兵耶，还不快跑？！\n");
                return 1;
        } else
        if ((sscanf(arg, "%s from %s",what, who) == 2 ||
             sscanf(arg, "%s at %s", what, who) == 2 ||
             sscanf(arg, "%s on %s", what, who) == 2 ||
             sscanf(arg, "%s %s", what, who) == 2) &&
             this_object()->id(who)) {
                write("有没有搞错，那是蒙古兵耶，还不快跑？！\n");
                return 1;
        } else
        if (arg == "roar" || arg == "hou")
        {
                write("有没有搞错，那是蒙古兵耶，还不快跑？！\n");
                return 1;
        }

        return 0;
}

varargs void die(object killer)
{
        if( !killer ) killer = query_last_damage_from(); 
        if (objectp(killer) && playerp(killer)) 
        {
                addn_temp("warquest/reward", 200, killer);
                GIFT_D->delay_war_bonus(killer, ([ "prompt" : "因歼灭蒙古卫队", "exp" : 200000, "pot" : 80000, "mar" : 8000, "gold" : 800 ])); 
        }

        message_vision("$N率领的蒙古卫队在几经顽抗后，终于被彻底" +
                        HIR "消灭了" NOR "！\n",
                        this_object());
        
        return ::die();
}
