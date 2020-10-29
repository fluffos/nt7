#include <weapon.h>
#include <ansi.h>
inherit TASK;
void create()
{
        set_name(MAG"阉刀"NOR, ({ "yan dao", "dao" }) );
        set_weight(4000);
        if( clonep() )
            destruct(this_object());
        else {
                set("unit", "柄");
                set("jungle",1);
                set("material", "iron");
                set("long", "这是一把专门阉割太监的阉刀。\n");
                set("wield_msg", "$N抽出一把黑油油的$n握在手中。\n");
                set("unequip_msg", "$N将手中的$n插入腰间。\n");
        }
        set("owner", "海公公");
        setup();
} 
