#include <ansi.h>
inherit QUARRY;

void create()
{
        set_name(HIW "天蚕" NOR, ({ "tian can", "tian", "can"}));
        set("long", HIG "一只天蚕，大个头，周身雪白。\n" NOR);

        set("age", 3);
        set("str", 1);
        set("con", 1);
        set("dex", 1);
        set("max_qi", 12000);
        set("max_jing", 12000);
        set("neili", 15000);
        set("max_neili", 15000);
        set("combat_exp", 9000000);

        set_skill("unarmed", 100);
        set_skill("dodge", 100);
        set_skill("parry", 100);
        set_skill("force", 100);
        
        set("item1", __DIR__"item/cansi2");

        set_temp("apply/attack", 1350);
        set_temp("apply/defense", 2350);
        set_temp("apply/unarmed_damage", 800);
        set_temp("apply/armor", 1800);

        set("power", 50);
        setup();
}