inherit ITEM;
#include <ansi.h>

void create()
{
        set_name("小钩子", ({ "hook" , "gou zi"}) );
        set_weight(100);
        /*if( clonep() )
                set_default_object(__FILE__);
        else*/ {
                set("unit", "个");
                set("long", "一个小小的钩子，看起来很象用来钓鱼的钩子，也许你可以用
它来做一个钓鱼杆。(make) \n");
                set("value", 10);
        }
}

void init()
{
   if(this_player()==environment())
   add_action("do_make", "make");
}

int do_make(string arg)
{
   int i,xxan=0,taozhi1=0;
   object fpole, me, xan, taozhi, *inv;

   me = this_player();
   inv = all_inventory(me);
   for(i=0; i<sizeof(inv); i++)
   {
      if( query("name", inv[i]) == "细麻线"){xxan=1;xan=inv[i];}
      if( query("name", inv[i]) == "桃枝"){taozhi1=1;taozhi=inv[i];}
   }
   if ( xxan && taozhi1)
   {
      destruct(xan);
      destruct(taozhi);
      fpole = new(__DIR__"fpole");
      fpole->move(me);
      message_vision("$N用灵巧的双手造成了一个别致的小鱼杆。\n", me);
      destruct(this_object());
   }
   else
      message_vision("$N摆弄着手里的细麻线。\n", me);
   return 1;
}
