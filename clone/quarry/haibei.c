#include <ansi.h>
inherit QUARRY;

void create()
{
        set_name(HIC "海贝" NOR, ({ "hai bei", "hai", "bei" }));
        set("long", HIC "一只巨大的海贝，看起来很凶猛。\n" NOR);

        set("age", 3);
        set("str", 10);
        set("con", 100);
        set("dex", 50);
        set("max_qi", 5000);
        set("max_jing", 32000);
        set("neili", 15000);
        set("max_neili", 15000);
        set("combat_exp", 9000000);

        set_skill("unarmed", 300);
        set_skill("dodge", 300);
        set_skill("parry", 300);
        set_skill("force", 500);

        set("item1", __DIR__"item/beike");
                set("item2", __DIR__"item/zhenzhu");
                set("item3", __DIR__"item/lan-baoshikuang");

        set_temp("apply/attack", 350);
        set_temp("apply/defense", 6350);
        set_temp("apply/unarmed_damage", 300);
        set_temp("apply/armor", 1200);

        set("power", 40);
        setup();
}