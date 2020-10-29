#include <ansi.h>
inherit QUARRY;

void create()
{
        set_name(HIG "蚕" NOR, ({ "can"}));
        set("long", HIG "一只普通的蚕。\n" NOR);

        set("age", 3);
        set("str", 1);
        set("con", 1);
        set("dex", 1);
        set("max_qi", 2000);
        set("max_jing", 2000);
        set("neili", 15000);
        set("max_neili", 15000);
        set("combat_exp", 9000000);

        set_skill("unarmed", 100);
        set_skill("dodge", 100);
        set_skill("parry", 100);
        set_skill("force", 100);
        
        set("item1", __DIR__"item/cansi");
        set("item3", __DIR__"item/cansi2");

        set_temp("apply/attack", 1350);
        set_temp("apply/defense", 2350);
        set_temp("apply/unarmed_damage", 800);
        set_temp("apply/armor", 800);

        set("power", 10);
        setup();
}