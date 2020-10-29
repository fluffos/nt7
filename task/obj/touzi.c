#include <ansi.h>
inherit TASK;
void create()
{
        set_name(HIW "玲珑骰子" NOR,({ "linglong touzi" }) );
        set_weight(100);
        if( clonep() )
                destruct(this_object());
        else {
                set("unit", "个");
                set("material", "stone");
                set("long", "这是一个玲珑骰子。\n");
        }
        set("owner", "庄家");
        setup();
}

