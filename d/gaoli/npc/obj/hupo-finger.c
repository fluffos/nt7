#include <armor.h>
#include <ansi.h>

inherit FINGER;

void create()
{
   set_name(HIG"琥珀戒指"NOR, ({ "finger"}) );
   set_weight(500);
   /*if( clonep() )
     set_default_object(__FILE__);
   else*/ {
     set("long","这是一枚名贵的琥珀戒指。\n");
     set("material", "琥珀");
     set("unit", "枚");
     set("value", 800);
     set("armor_prop/armor",3);
     set("armor_prop/dodge",2);
     set("armor_prop/per",1);
   }
   setup();
}