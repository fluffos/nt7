#include <ansi.h>
inherit ITEM;
void create()
{
        set_name(WHT"猴脑"NOR, ({"hou nao"}));
        set_weight(100);
        /*if( clonep() )
                set_default_object(__FILE__);
        else*/ {
                set("long", "一块猴脑!\n");
                set("unit", "块"); 
                set("no_get",1);
                set("no_put",1);
                set("no_give",1);   
                set("value",500);
                set("yaoxing",500000);
        }
    setup();
}
void init()
{
    if (environment()==this_player())
        add_action("do_eat", "eat");
}
int do_eat(string arg)
{
  object me = this_player();
  int maxneili,neili;
    neili=query("neili", me);
    maxneili=query("max_neili", me);
    
  if(!id(arg)) return 0;
  if(me->is_busy()) return notify_fail("你上一个动作还没有完成。\n");
  
if( query("max_neili", me)>me->query_skill("force",1)*50 )
{
 addn("max_neili", random(20), me);
} else {
addn("max_neili", 10+random(40), me);
}
    
  message_vision(HIY"$N拿起猴脑吃了下去,感觉内力最大值增加了数点。\n"NOR,me);
       destruct(this_object());
       return 1;
}