#include <ansi.h>
#include <weapon.h>
inherit SWORD;

void create()
{
        set_name(HIW"绣花针"NOR, ({ "xiuhua zhen", "zhen" }));
        set_weight(5000);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("unit", "枚");
                set("long", "这是一枚绣花针，千金小姐们手中的寻常之物。\n");
                set("value", 100);
                set("rigidity", 100); 
                set("material", "steel");
                set("wield_msg", "$N妩媚的从随身荷包中取出一枚$n捏在手指间。\n");
                set("unwield_msg", "$N将手中的$n收回腰间荷包中。\n");
        }
        init_sword(40);
        setup();
}                
