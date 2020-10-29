// Room Of Mxj
// have a good day

#include <weapon.h>
#include <ansi.h>
inherit SWORD;

void create()
{
        set_name(HIG "青铜箫" NOR,({ "tong xiao", "xiao" }) );
        set_weight(5000);
        /*if( clonep() )
                set_default_object(__FILE__);
        else*/ {
                set("unit", "支");
                set("value", 400);
                set("material", "steel");
                set("shape", "flute");
                set("long", "一柄青铜打造的洞箫，通体铜绿斑斓，看起来有些年头了。\n");
                set("wield_msg", "$N从怀里掏出一支$n，握在手中。\n" NOR);
                set("unwield_msg", "$N小心翼翼的将$n放入怀里。\n" NOR);
        }
        init_sword(40);
        setup();

}

#include "music.h"
