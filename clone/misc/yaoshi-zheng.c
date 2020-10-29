#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(WHT "炼药师证" NOR, ({ "yaoshi zheng", "yaoshi", "zheng" }));
        set_weight(1);
        set("level", 1);
        set("long", WHT "这是一枚红底金边的炼药师证，等级 "+query("level")+" 品，由炼药师协会颁发。\n" NOR);
        set("unit", "枚");
        set("value", 5);
        set("material", "steal");
        set("no_sell", "这年头，你把吃饭的家伙也拿来卖钱？");
        setup();
}

void enable()
{
        set_name(HIR+chinese_number(query("level"))+"品" WHT "炼药师证" NOR, ({ "yaoshi zheng", "yaoshi", "zheng" }));
        set("long", WHT "这是一枚红底金边的炼药师证，等级 "+query("level")+" 品，由炼药师协会颁发。\n" NOR);
}