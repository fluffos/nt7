#include <ansi.h>
inherit TASK;
void create()
{
        set_name(HIY "黄内裤" NOR,({ "huang neiku" }) );
        set_weight(100);
        if( clonep() )
                destruct(this_object());
        else {
                set("unit", "件");
                set("material", "cloth");
                set("long", "这是一件皇帝穿过的黄内裤。\n");
        }
        set("owner", "韦小宝");
        setup();
}

