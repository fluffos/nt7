#include <ansi.h>
#include <armor.h>

inherit BOOTS;

void create()
{
        set_name( HIG "七" HIW "彩" HIM "琉璃" HIY "靴" NOR, ({ "qicai xue", "qicai", "xue" }) );
        set_weight(10);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/
        {
                set("unit", "双");
                set("long", HIC "这是一双泛着七彩光芒的宝靴，据说并非产自东土。\n");
                set("value", 2000000);
                
                set("armor_prop/dex", 60); //后天身法+60
                set("armor_prop/int", 10); //
                set("armor_prop/damage", 1000); 
                set("material", "boots");
                set("limit", ([
                        "exp"  :  100000000,
                        "dex"  :  80,
                ]));
        }
        setup();
}

int query_autoload()
{
        return 1;
}