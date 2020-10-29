//qingshe.c 冰蚕

#include <ansi.h>

inherit POISON_INSECT;

void create()
{
        set_name("冰蚕", ({ "bing can", "can" }) );
        set_weight(100);
        set("race", "野兽");
        set("age", 2);
        set("long", "一只浑身上下透体通明的蚕。\n");
        set("attitude", "peaceful");
        set("str", 20);
        set("con", 20);
        set("unit", "只");
        set("limbs", ({ "头部", "身体", "尾巴" }) );
        set("verbs", ({ "bite" }) );

        set("insect_poison", ([
                "level"  : 400,
                "maximum": 400,
        ]));

        set("combat_exp", 100);

        setup();
}