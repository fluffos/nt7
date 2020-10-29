
// This program is a part of NT MudLIB 
 
#include <ansi.h>
#include <weapon.h>
inherit BLADE;
 
void create()
{
        set_name(HIY "神" HIW "之" HIM "祝福" NOR HIC "宝刀" NOR, ({ "zhufu blade", "blade", "dao" }) );
        set_weight(500);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/
        {
                set("unit", "柄");
                set("long", HIY "这便是神之祝福宝刀，三尺来长的单刀。\n" NOR);
                set("value", 3000); 
                set("no_sell", "这样东西不能卖。\n");
                set("rigidity",8000);   
                set("material", "tian jing");
                set("no_pawn", 1);
        }
        
        set("quality_level", 2); 
        init_blade(500);
        setup();
}


