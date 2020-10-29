#include <armor.h>
#include <ansi.h>

inherit NECK;

void create()
{
   set_name(HIY"黄金项链"NOR, ({ "necklace"}) );
   set_weight(1000);
   /*if( clonep() )
     set_default_object(__FILE__);
   else*/ {
     set("long","这是一串名贵的黄金项链。\n");
     set("material", "黄金");
     set("unit", "串");
     set("value", 1000);
     set("armor_prop/armor",10);
     set("armor_prop/dodge",2);
     set("armor_prop/per",5);
   }
   setup();
}