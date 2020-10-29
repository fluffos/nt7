// toukui.c 头盔
 
#include <armor.h>
#include <ansi.h>

inherit HEAD;
 
void create()
{
        set_name(HIY "家康头带" NOR, ({ "jiakang toudai", "jiakang", "toudai" }) );
        set_weight(1000);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/
        {
                set("material", "steel");
                set("unit", "顶");
                set("long", HIY "这是德川家康所特有的头带，上绣有「德川·家康」字样。\n" NOR);
                set("value", 350000);
                set("armor_prop/int", 5);
        }
        setup();
}

int query_autoload()
{
        return 1;
}