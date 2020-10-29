// hua1.c
#include <ansi.h>;
#include <armor.h>;
inherit HEAD;

void create()
{
        set_name(HIW"三生有约"NOR, ({"sansheng youyue", "youyue",}));
        /*if( clonep() )
                set_default_object(__FILE__);
        else*/ {
                set("unit", "朵");
                set("long", "一朵洁白的百合花，冠上那么隆重的名字倒有些造作了。\n");
                set("value", 10000);
                set("material", "plant");
                set_weight(10);
                set("armor_prop/armor", 0);
                set("armor_prop/per", 3);
                set("wear_msg", "$N轻轻地把一朵$n插在鬓间，微微一笑。\n");
                set("unequip_msg", "$N幽幽长叹，轻轻地把$n从头上摘了下来。\n");
        }
        setup();
}