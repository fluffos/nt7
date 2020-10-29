#include <armor.h>
#include <ansi.h>

inherit CLOTH;

void create()
{
        set_name(HIY "金丝木棉袈裟" NOR, ({ "jia sha", "cloth","jiasha" }) );
        set_weight(8000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", "这是一件用金丝镶边的灰色木棉袈裟。\n");
                set("unit", "件");
                set("material", "cloth");
                set("armor_prop/armor", 40);
                set("wear_msg","‘哗’的一声，眼前金光一闪，$N披上一件$n，古色斑斓，金丝盘绣。\n");
                set("remove_msg","$N把$n从身上脱了下来。\n");
                set("tianlongsi",1);
        }
        setup();
}
