// gui2-1.c
// Modified by haiyan

#include <ansi.h>
inherit NPC;

string comeon = HIW"突然你感到一股十分强烈的怨气直冲云霄。\n"NOR;

string *stya = ({ 
HIB"一阵刺耳的长啸传来，$N感到心神不宁，异常难受。\n"NOR, 
HIB"$N听到一声凄惨的长叹，顿感胸闷异常，忍不住喷出一口"HIR"鲜血"HIB"。\n"NOR
}); 

string *styb = ({
HIC"$N对$n喝道：“本道爷今日超渡于你，早日投胎转世，勿再害人！”\n"NOR,
HIY"$N挥动手中的"HIM"桃木剑"HIY"，霎时天地间清风徐徐，怨气渐消。\n"NOR
});

void check_time();

void create()
{
    set_name("冤魂", ({ "wrong ghost", "ghost" }));
    set("gender", "女性");
    set("race", "妖魔");
    set("age", 200);
    set("per", 20);
    set("long",
        "一个含冤而死的人死后即变成冤魂，很难制服，常常攻击无辜的生灵。\n");
    set("combat_exp", 100000);
    set("shen_type", -1);
    set("attitude", "peaceful");
    set("limbs", ({ "牙齿", "手爪" }) );
    set("verbs", ({ "bite", "claw" }) );
    set("env/invisible", 1);
    set("water", 200);
    set("food", 200);
    set("apply/attack", 250);
    set("apply/defense", 250);
    set_skill("parry", 250);
    set_skill("dodge", 300);

    set("chat_chance", 80);
    set("chat_msg", ({ (: check_time :) })); 
    setup();
    keep_heart_beat();
}

#include "ghoster.h"
