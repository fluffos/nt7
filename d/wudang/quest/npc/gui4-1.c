// gui4-1.c
// Modified by haiyan

#include <ansi.h>
inherit NPC;

string comeon = HIB"突然一阵腥臭的浓雾笼罩了四周，眼前顿时漆黑一团。\n"NOR; 

string *stya = ({ 
HIB"忽然一道"HIW"白光"HIB"向$N疾射而来，手臂一麻，已被$n咬中。\n"NOR, 
HIB"$N身体被$n缠住，越裹越紧，几乎透不过气来。\n"NOR, 
HIB"$N背部一阵剧痛，被$n蛇尾击中。\n"NOR
}); 

string *styb = ({ 
HIC"$N一声暴喝，急挥手中"HIY"符纸"HIC"，向$n拍出。\n"NOR,
HIY"$N挥动手中的"HIM"桃木剑"HIY"，直刺$n七寸。\n"NOR
});

void check_time();

void create()
{
    set_name("百年蛇妖", ({ "snake ghost", "ghost" }));
    set("gender", "女性");
    set("race", "妖魔");
    set("age", 200);
    set("per", 20);
    set("long",
        "一种毒蛇经过百年修炼而成的妖魔。\n");
    set("combat_exp", 500000);
    set("shen_type", -1);
    set("attitude", "peaceful");
    set("limbs", ({ "牙齿", "手爪" }) );
    set("verbs", ({ "bite", "claw" }) );
    set("env/invisible", 1);
    set("water", 200);
    set("food", 200);
    set("apply/attack", 450);
    set("apply/defense", 450);
    set_skill("parry", 450);
    set_skill("dodge", 500);

    set("chat_chance", 80);
    set("chat_msg", ({ (: check_time :) })); 
    setup();
    keep_heart_beat();
}

#include "ghoster.h"
