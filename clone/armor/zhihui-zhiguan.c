#include <armor.h>
#include <ansi.h>

inherit HEAD;
 
void create()
{
        set_name(HIR "智慧之冠" NOR, ({ "zhihui guan", "zhihui", "guan" }) );
        set_weight(1000);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/
        {
                set("material", "gold");
                set("unit", "顶");
                set("long", HIR "这是一顶充满智慧之光的头冠，佩带后可使冥思奖励加倍。\n" NOR);
                set("value", 350000);
                set("armor_prop/int", 6);
                set("armor_prop/reflect2", 1);
        }
        setup();
}

int query_autoload()
{
        return 1;
}