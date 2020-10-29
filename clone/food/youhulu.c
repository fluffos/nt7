// 神话世界·西游记·版本４．５０
/* <SecCrypt CPL V3R05> */
 
// hulu.c 

inherit ITEM;
inherit F_LIQUID;

void create()
{
  set_name("油葫芦", ({"you hulu", "youhulu", "hulu", "hu"}));
  set_weight(700);
  /*if (clonep())
    set_default_object(__FILE__);
  else*/ {
    set("long", "一个装满菜油的葫芦。\n");
    set("unit", "个");
    set("value", 100);
    set("max_liquid", 20);
    set("liquid", ([
      "type" : "oil",
      "name" : "菜油",
      "remaining" : 12,
   ]));
  }
}