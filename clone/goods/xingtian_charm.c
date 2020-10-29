// This program is a part of NT MudLIB 
 
#include <ansi.h>
#include <armor.h>
inherit CHARM;
 
void create()
{
        set_name(HBGRN "刑天护符" NOR, ({ "xingtian charm", "charm" }) );
        set_weight(500);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/
        {
                set("unit", "个");
                set("long", HIY "这便是刑天戴过的护符，通体血光滔天。\n" NOR);
                set("value", 3000); 
                set("no_sell", "这样东西不能卖。\n");
                set("rigidity",8000);   
                set("material", "tian jing");
                set("no_pawn", 1);
                set("armor_prop/armor", 10);
        }
        
        set("mod_mark", "A2032");
        set("mod_level", "M2030");
        set("mod_name", HBRED "刑天套装" NOR);
        set("quality_level", 3);

        setup();
}

