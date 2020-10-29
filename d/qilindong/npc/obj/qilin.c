//Cracked by Yuchang
#include <ansi.h>

inherit ITEM; 
void create()
{
        set_name( RED"麒麟臂"NOR, ({ "qilin bi", "qilin", "bi", "arm" }) );
        set_weight(10000);
        /*if( clonep() )
                set_default_object(__FILE__);
        else*/
        {
                set("long", "这是一根手臂，相传是于岳少年时赤膊搏斗火麒麟，左臂被麒麟血所溅而成。\n");
                set("unit", "根");
                set("value", 150);
                set("no_sell", 1);
        }
        setup();
}


int query_autoload()
{
       return 1;
}
