#include <armor.h>
#include <ansi.h>
inherit HEAD;

void create()
{
   set_name(HIB"藤盔"NOR, ({ "tengkui"}) );
   set_weight(1000);
   /*if( clonep() )
     set_default_object(__FILE__);
   else*/ {
     set("material", "铁");
     set("unit", "件");
     set("value",1500);
     set("armor_prop/armor",30);
     set("armor_prop/dodge",11);
   }
   setup();
}