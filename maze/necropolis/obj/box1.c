#include <ansi.h>
inherit ITEM; 

void create()
{
        object good;
        set_name(HIC"宝箱"NOR, ({"box"}) );
        set_weight(300);
        set("no_get", 1);
        set_max_encumbrance(80000000);
        set("unit", "个");
        set("long", "一个散发着神秘光芒的宝箱。\n");
        set("closed", 1);
        set("value", 2000);

        good = new("/clone/money/gold");
        good->set_amount(10+random(10));
        good->move(this_object());
        if (!random(3)) {
                for (int i = 0; i < 7; i++) 
                {
                        good = new("/clone/tessera/rune1" + random(8));
                            good->move(this_object());
                }                  
          }
        setup();
} 
int is_container() {return 1;} 
void init()
{
        add_action("do_open","open");

}
int is_closed()
{
        return (query("closed", this_object()));
} 

int do_open(string arg)
{
        object me, ob;
        me = this_player();
        if(!arg)
                    return 0;
        ob = present(arg,environment(this_object()));
        if (ob!=this_object())
                 return 0;
                                 
        if (!is_closed())
        {
                return notify_fail("宝箱已经打开了。 \n");
        }
        message_vision("$N将宝箱打开。 \n", me);
        set("closed", 0, this_object());
        //me->move(environment(this_object()));
        return 1;
} 