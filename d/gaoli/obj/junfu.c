#include <armor.h>

inherit CLOTH;

void create()
{
   set_name("军服", ({ "junfu","cloth"}) );
   set_weight(6000);
   /*if( clonep() )
     set_default_object(__FILE__);
   else*/ {
     set("material", "cloth");
     set("unit", "件");
     set("value", 60);
     set("armor_prop/armor", 20);
   }
   setup();
}