// gui4-2.c
// Modified by haiyan

#include <ansi.h>
inherit NPC;

string comeon = HIB"天空中突然阴风大作，一朵黑云遮住了太阳。顷刻间飞沙走石，天昏地暗。\n"NOR; 

string *stya = ({ 
HIB"一股黑雾从树林深处弥漫开来，一个半男半女的沙哑嗓音在其中阴碜碜的冷笑着。\n"NOR, 
HIB"一阵鬼哭狼嚎般的叫声从四面八方涌过来，$N只觉得头疼欲裂，眼冒金星！\n"NOR, 
HIB"地上突然裂开一条长长的口子，从里边飞出几根粗大的藤条，牢牢的抓住你的四肢。拼命往裂缝里拖。\n"NOR, 
HIB"$n浑身爆发出一股强烈的妖气，从身上射出一股黑流，直击$N的全身！\n"NOR
}); 

string *styb = ({ 
HIC"$N破开掌心，用气血将手中神符定在"HIM"桃木剑"HIC"上，大吼一声，疾刺而出！\n"NOR,
HIC"$N一声长啸，正气直冲霄汉。$n凛冽的惨嗥顿时弥漫在天地之间。\n"NOR,
HIY"$N挥动手中桃木剑，化做一条八丈神龙，口吐金光，将$n牢牢罩住。\n"NOR
});

void check_time();

void create()
{
    set_name("千年树精", ({ "tree ghost", "ghost" }));
    set("gender", "男性");
    set("race", "妖魔");
    set("age", 200);
    set("per", 22);
    set("long",
        "一种千年老树修炼而成的妖魔，十分强悍。\n");
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
