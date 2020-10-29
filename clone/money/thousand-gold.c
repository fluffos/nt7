// thousand.c

#include <ansi.h>

inherit MONEY;

void create()
{
        set_name(YEL "一千两金票" NOR, ({"thousand-gold", "thousand-gold_money"}));
        /*if( clonep() )
                set_default_object(__FILE__);
        else*/ {
                set("money_id", "thousand-gold");
                set("long", "一张面额值一千两金子的金票。\n");
                set("unit", "叠");
                set("base_value", 10000000);
                set("base_unit", "张");
                set("base_weight", 6);
        }
        set_amount(1);
}