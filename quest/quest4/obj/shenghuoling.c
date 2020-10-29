#include <ansi.h>
#include <weapon.h>
inherit SWORD;

void create()
{
        set_name(RED"圣火令"NOR, ({ "shenghuo ling", "ling" }));
        set_weight(20000);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("unit", "枚");
                set("long", 
                BLK"这是一枚圣火令，看起来黑黑的毫不起眼，上面密密麻麻刻满了波斯文字。\n"NOR);
                set("rigidity", 100); 
                set("value", 100);
                set("material", "steel");
                set("wield_msg", "$N从怀里掏出一枚$n握在手中。\n");
                set("unwield_msg", "$N将手中的$n收回怀中。\n");
        }
        init_sword(40);
        setup();
}
