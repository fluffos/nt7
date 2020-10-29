#include <armor.h>
#include <ansi.h>
inherit BOOTS;

void create()
{
   set_name(HIC"安南战靴"NOR, ({ "boot"}) );
   set_weight(100);
   /*if( clonep() )
     set_default_object(__FILE__);
   else*/ {
     set("material", "皮革");
     set("unit", "双");
     set("value",3000);
     set("armor_prop/armor",100);
     set("armor_prop/dodge",6);
   }
   setup();
}