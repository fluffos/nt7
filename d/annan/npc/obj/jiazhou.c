#include <armor.h>
#include <ansi.h>
inherit ARMOR;

void create()
{
   set_name(HIB"安南军藤甲"NOR, ({ "armor"}) );
   set_weight(4000);
   /*if( clonep() )
     set_default_object(__FILE__);
   else*/ {
     set("material", "铁");
     set("unit", "件");
     set("value",2000);
     set("armor_prop/armor",65);
     set("armor_prop/dodge",12);
   }
   setup();
}