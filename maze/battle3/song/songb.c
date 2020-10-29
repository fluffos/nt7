#include <ansi.h>
inherit NPC;

int do_kill(string arg);
int is_stay_in_room() { return 1; }

void create()
{
        int skill, nl, lvl;
        int exp;

        NPC_D->generate_cn_name(this_object());
        set("gender", "男性");
        set("long", "这是一名大宋将军，正威风凛凛地巡视着自己的队伍。\n");

        set("int", 30);
        set("str", 30 + random(20));
        set("con", 20 + random(20));
        set("dex", 20 + random(20));
        set("age", 20 + random(30));
        set("per", 15 + random(15)); 
        set("age", 20 + random(30));
        set("per", 15 + random(15));                                         
        set("no_get",1);
        
        exp = UPDATE_D->query_max_exp();
        if (exp > 500000000)
                exp = 500000000;
        exp /= 3;
        skill = to_int(pow(to_float(exp / 100), 1.0 / 3)) * 10;
        if (skill < 100) skill = 100; 
        nl = skill * 10 + (exp /10000);
        
        set("combat_exp", exp);
        set("max_neili", nl);
        set("neili", query("max_neili") * 3 / 2); 
        set("max_jingli", nl);
        set("jingli", query("max_jingli"));
        set("max_qi", nl * 5);
        set("qi",  query("max_qi"));
        set("eff_qi", query("max_qi"));
        set("max_jing", nl);
        set("eff_jing", query("max_jing"));
        set("jiali", skill / 2); 

        set_skill("taiji-shengong", skill);
        set_skill("wuhu-duanmendao", skill);
        set_skill("tiyunzong", skill);
        set_skill("taiji-quan", skill);
        set_skill("cuff", skill);
        set_skill("force", skill);
        set_skill("dodge", skill);
        set_skill("blade", skill);
        set_skill("parry", skill);
        set_skill("arrow", skill*2/3);

        map_skill("force", "taiji-shengong");
        map_skill("dodge", "tiyunzong");
        map_skill("cuff", "taiji-quan");
        map_skill("parry", "taiji-quan");
        map_skill("blade", "wuhu-duanmendao");   
        prepare_skill("cuff", "taiji-quan");
  
        set_temp("warquest/party", "song"); 
        addn_temp("apply/armor", 400);
        addn_temp("apply/damage", 100);
        setup();
        
        lvl = (query("str") + skill / 10) / 10 - 1;
        if (lvl > 8) lvl = 8;
        lvl = lvl - 2;
        if (lvl < 3) lvl = 3;
        carry_object("/clone/weapon/bow" + lvl);
        carry_object("/clone/weapon/bow" + lvl);
        carry_object("/clone/weapon/bow" + lvl);
        carry_object("/clone/weapon/bow" + lvl);
        carry_object(__DIR__"obj/wandao");
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
                write("有没有搞错，那是军队耶，还不快跑？！\n");
                return 1;
        } else
        if ((sscanf(arg, "%s from %s",what, who) == 2 ||
             sscanf(arg, "%s at %s", what, who) == 2 ||
             sscanf(arg, "%s on %s", what, who) == 2 ||
             sscanf(arg, "%s %s", what, who) == 2) &&
             this_object()->id(who)) {
                write("有没有搞错，那是军队耶，还不快跑？！\n");
                return 1;
        } else
        if (arg == "roar" || arg == "hou")
        {
                write("有没有搞错，那是军队耶，还不快跑？！\n");
                return 1;
        }

        return 0;
}

void die()
{
        message_vision("$N率领的宋军将士寡不敌众，不幸" +
                     HIR "全军覆没" NOR "！\n", this_object());

        return ::die();
}