#include <ansi.h>
inherit TASK;
void create()
{
        set_name(HIW "秃鹰羽氅" NOR,({ "yu chang" }) );
        set_weight(100);
        if( clonep() )
                destruct(this_object());
        else {
                set("unit", "件");
                set("material", "cloth");
                set("long", "这是一件秃鹰羽氅。\n");
        }
        set("owner", "水笙");
        setup();
}

