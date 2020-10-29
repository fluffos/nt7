// This program is a part of NT MudLIB 
 
#include <ansi.h>
#include <armor.h>
inherit CHARM;
 
void create()
{
        set_name(BMAG "幸运女神护符" NOR, ({ "luck charm", "charm" }) );
        set_weight(500);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/
        {
                set("unit", "个");
                set("long", HIY "这便是幸运女神戴过的护符，神光浮现。\n" NOR);
                set("value", 3000); 
                set("no_sell", "这样东西不能卖。\n");
                set("rigidity",8000);   
                set("material", "tian jing");
                set("no_pawn", 1);
                set("armor_prop/armor", 10);
        }
        
        set("mod_mark", "A3021");
        set("mod_level", "M3002");
        set("mod_name", HBRED "幸运女神之眷念" NOR);
        set("quality_level", 4);

        setup();
}

