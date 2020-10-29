#include <armor.h>
#include <ansi.h>

inherit CLOTH;

void create()
{
        set_name(YEL"细丝木棉袈裟"NOR, ({ "jia sha", "cloth","jiasha" }) );
        set_weight(8000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", "这是一件黄色的木棉袈裟。\n");
                set("unit", "件");
                set("material", "cloth");
                set("armor_prop/armor", 20);
                set("wear_msg","$N披上一件$n。\n");
                set("remove_msg","$N把$n从身上脱了下来。\n");
                set("tianlongsi",1);
        }
        setup();
}
