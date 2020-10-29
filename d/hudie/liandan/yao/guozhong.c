#include <ansi.h>
inherit ITEM;
void create()
{
        set_name(NOR"果树种籽"NOR, ({ "shu zhong"}));
        set_weight(100);
        /*if( clonep() )
                set_default_object(__FILE__);
        else*/ {
                set("long", "普通的果树种籽，不知道会结出什么样的果实。\n");
                set("unit", "粒"); 
                set("no_get",1);
                set("no_put",1);
                set("no_give",1);   
                set("value",50000);
        }
    setup();
}