#include <ansi.h>
inherit TASK;
void create()
{
        set_name(HIR "春宫图" NOR,({ "chungong tu" }) );
        set_weight(100);
        if( clonep() )
                destruct(this_object());
        else {
                set("unit", "本");
                set("material", "paper");
                set("long", "这是一本宫廷流传出来的春宫图。\n");
        }
        set("owner", "韦春芳");
        setup();
}
