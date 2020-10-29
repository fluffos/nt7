// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.

#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIG "寒玉萧" NOR, ({"hanyu xiao", "xiao"}));
        set_weight(4500);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("long", HIG "这根寒玉萧是鬼三的传家宝。\n" NOR);
                set("unit", "把");
                set("value", 5000);
                set("item_origin", 1);
                set("material_attrib", "hanyu");
                set("material_name", HIG "寒玉" NOR);
        }
}