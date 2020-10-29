// dizhangshi.c  地藏之石  武器原料，只能被 wizard 使用
// Written by Doing Lu 1998/11/3

inherit ITEM;

#include <ansi.h>

// 打造武器粗坯时需要的一种原料
// 根据 material_ attrib = x 为判断标志，其有效点数为:power_point
// 地藏之石的有效点数是 1000

void create()
{
        set_name(MAG "魔法丝带" NOR, ({"magic silk", "silk"}));
        set_weight(4000);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/
        {
                set("long", "这是一条魔法丝带，闪耀着诡异的光芒，传说可以用它制成" MAG "勋章挂带。\n" NOR);
                set("unit", "块");
                //set("material_attrib", "x");
                set("power_point", 1000);
                set("value", 10000000);
                set("no_sell", 1);
        }
}

int query_autoload() { return 1; } 
