#include <armor.h>
#include <ansi.h>

inherit FINGER;

void create()
{
   set_name(HIW"白玉戒指"NOR, ({ "finger"}) );
   set_weight(500);
   /*if( clonep() )
     set_default_object(__FILE__);
   else*/ {
     set("long","这是一枚名贵的白玉戒指。\n");
     set("material", "白玉");
     set("unit", "枚");
     set("value", 800);
     set("armor_prop/armor",3);
     set("armor_prop/dodge",2);
     set("armor_prop/per",1);
   }
   setup();
}