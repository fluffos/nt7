// This program is a part of NT MudLIB 
 
#include <ansi.h>
#include <weapon.h>
inherit HAMMER;
 
void create()
{
        set_name(HIY "神" HIW "之" HIM "祝福" NOR HIC "铁锤" NOR, ({ "zhufu hammer", "hammer", "chui" }) );
        set_weight(500);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/
        {
                set("unit", "柄");
                set("long", HIY "这便是神之祝福铁锤。\n" NOR);
                set("value", 3000); 
                set("no_sell", "这样东西不能卖。\n");
                set("rigidity",8000);   
                set("material", "tian jing");
                set("no_pawn", 1);
        }
        
        set("quality_level", 2); 
        init_hammer(500);
        setup();
}



