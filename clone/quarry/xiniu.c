#include <ansi.h>
inherit QUARRY;

void create()
{
        set_name(HIR "犀牛" NOR, ({ "xi niu", "xi", "niu" }));
        set("long", HIG "这是一头凶猛的犀牛，凶猛无比。\n" NOR);

        set("age", 3);
        set("str", 1000);
        set("con", 100);
        set("dex", 50);
        set("max_qi", 32000);
        set("max_jing", 32000);
        set("neili", 15000);
        set("max_neili", 15000);
        set("combat_exp", 9000000);

        set_skill("unarmed", 700);
        set_skill("dodge", 600);
        set_skill("parry", 800);
        set_skill("force", 600);
        
        set("item1", __DIR__"item/niurou");
           set("item2", __DIR__"item/niujiao");

        set_temp("apply/attack", 1350);
        set_temp("apply/defense", 2350);
        set_temp("apply/unarmed_damage", 800);
        set_temp("apply/armor", 800);

        set("power", 80);
        setup();
}