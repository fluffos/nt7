// gui2-2.c
// Modified by haiyan

#include <ansi.h>
inherit NPC;

string comeon = HIB"一阵闷响由远及近，你急向响声发出之处看去，" +
                "但见一具棺木似乎被剧烈的撞动着，突然棺盖被一股怪力击飞。\n" +
                HIR"一股血腥之气笔直的向你扑来。\n"NOR; 

string *stya = ({ 
HIB"忽听一阵破空之声，$N不由感到一丝寒意袭来。\n"NOR, 
HIB"$N忽觉双肩噗嗤一声，被十指插入筋骨，几乎痛晕过去。\n"NOR, 
HIB"$N突然觉得身上被咬了一下，剧痛难当。\n"NOR, 
HIB"$N突然觉得身上被紧紧抓住，大惊失色，连忙后退数步。\n"NOR
}); 

string *styb = ({ 
HIC"$N对$n喝道：“本道爷今日要将你打入十八层地狱，永不得超生。”\n"NOR,
HIY"$N急挥手中的"HIM"桃木剑"HIY"，划出无数光环，将$n套在当中。\n"NOR
});

void check_time();

void create()
{
    set_name("僵尸", ({ "corpse ghost", "ghost" }));
    set("gender", "男性");
    set("race", "妖魔");
    set("age", 200);
    set("per", 12);
    set("long",
        "一个人死后变成的僵尸，异常凶猛，常吸食各种生灵的血，使之枯竭而亡。\n");
    set("combat_exp", 50000);
    set("shen_type", -1);
    set("attitude", "peaceful");
    set("limbs", ({ "牙齿", "手爪" }) );
    set("verbs", ({ "bite", "claw" }) );
    set("env/invisible", 1);
    set("water", 200);
    set("food", 200);
    set("apply/attack", 260);
    set("apply/defense", 260);
    set_skill("parry", 250);
    set_skill("dodge", 300);

    set("chat_chance", 80);
    set("chat_msg", ({ (: check_time :) })); 
    setup();
    keep_heart_beat();
}

#include "ghoster.h"
