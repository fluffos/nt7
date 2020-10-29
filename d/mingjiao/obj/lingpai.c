#include <ansi.h>
inherit ITEM;
void create()
{
       set_name("巡逻令", ({ "xunluo ling", "ling" }) );
       set_weight(1000);
       /*if( clonep() )
               set_default_object(__FILE__);
       else*/ {
               set("unit", "片");
               set("long", "这是一片用竹片所制的令牌，是明教巡逻弟子的身份证明。\n");
               set("value", 20);
               set("material", "bamboo");          
       }
       setup();
}