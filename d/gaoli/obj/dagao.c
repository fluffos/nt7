 
inherit ITEM;
inherit F_FOOD;

void create()
{
   set_name("打糕", ({"da gao","gao"}));
        set_weight(100);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("long", "这是一个高丽的打糕，看起来很好吃。\n");
                set("no_decay",1);
                set("unit", "个");
                set("value", 100);
                set("food_remaining", 30);
                set("food_supply", 50);
        }
}
/*
int is_get_of(object pal,object ob)
{
  if(pal->query("family/family_name")!="弈剑派")
  return notify_fail("只有弈剑派弟子可以捡这里的东西！！\n");
  return 1;
*/