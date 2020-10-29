// gui3-1.c
// Modified by haiyan

#include <ansi.h>
inherit NPC;

string comeon = HIB"你突然听到一声厉啸，仿佛感到一个长发怪物一闪而过。\n"NOR; 

string *stya = ({ 
HIB"$N感到长发从脸上扫过，顿时一阵火辣辣的疼痛。\n"NOR, 
HIB"$N忽觉嘴唇被紧紧吸住，一股"HIR"鲜血"HIB"从口内急泻而出。\n"NOR, 
HIR"$n张开正滴着血的大口，在$N身上一阵乱咬。\n"NOR, 
HIB"$N突然觉得身上被紧紧抓住，大惊失色，连忙后退数步。\n"NOR
}); 

string *styb = ({ 
HIC"$N举起手中的"HIY"符纸"HIC"，看清$n来势，疾拍而出。\n"NOR,
HIY"$N挥动"HIM"桃木剑"HIY"，幻化出无数金光剑影，手腕一抖，向$n刺出。\n"NOR
});

void check_time();

void create()
{
    set_name("吸血鬼", ({ "leech ghost", "ghost" }));
    set("gender", "女性");
    set("race", "妖魔");
    set("age", 200);
    set("per", 25);
    set("long",
        "一种专门吸食人血的鬼魂。常常变成美丽的女子迷惑多情的男人，吸干他的血。\n");
    set("combat_exp", 100000);
    set("shen_type", -1);
    set("attitude", "peaceful");
    set("limbs", ({ "牙齿", "手爪" }) );
    set("verbs", ({ "bite", "claw" }) );
    set("env/invisible", 1);
    set("water", 200);
    set("food", 200);
    set("apply/attack", 350);
    set("apply/defense", 350);
    set_skill("parry", 350);
    set_skill("dodge", 400);

    set("chat_chance", 80);
    set("chat_msg", ({ (: check_time :) })); 
    setup();
    keep_heart_beat();
}

#include "ghoster.h"
