#include <ansi.h>
inherit TASK;
void create()
{
        set_name(HIW "尚方宝剑" NOR,({ "shangfang baojian" }) );
        set_weight(100);
        if( clonep() )
                destruct(this_object());
        else {
                set("unit", "个");
                set("material", "stone");
                set("long", "这是一个尚方宝剑。\n");
        }
        set("owner", "段正淳");
        setup();
}

