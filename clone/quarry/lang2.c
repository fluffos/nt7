#include <ansi.h>
inherit QUARRY;

void create()
{
        set_name(WHT "野狼" NOR, ({ "wolf", "lang", "ye lang" }) );
        set("long", WHT "这是一只凶残饥饿的野狼。\n" NOR);

        set("age", 1);
        set("str", 35);
        set("dex", 40);
        set("max_qi", 1500);
        set("max_jing", 1500);
        set("combat_exp", 80000);

        set("power", 30);
        set("item1", __DIR__"item/langrou");
        set("item2", __DIR__"item/langpi");

        set_temp("apply/parry", 100);
        set_temp("apply/dodge", 100);
        set_temp("apply/attack", 100);
        set_temp("apply/defense", 100);
        set_temp("apply/unarmed_damage", 100);
        set_temp("apply/armor", 100);

        setup();
}