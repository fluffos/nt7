#include <ansi.h>
inherit ITEM;

string shop_id(){return "fz_shop";}
string shop_name(){return HIW "腾龙斋" NOR;}
string shop_string(){return "tenglongzhai fangqi";}

void create()
{
        set_name(HIW "「" + shop_name() + HIW "房契」" NOR, ({ shop_string() }));        

        set_weight(1);
        if (clonep())
                destruct(this_object());
        else {
                set("unit", "份");
                set("long", HIY "这是一份" + shop_name() + HIY "的房契，请妥善保管。\n"
                            HIM        "使用 deed register 可成为" + shop_name() + HIM "的所有者。\n"
                            HIM "使用 deed hide 可将房契隐藏。\n" NOR);
                set("no_sell", "这个东西如此贵重，我看你还是另找买家吧！\n");
                set("material", "paper");
                set("can_paimai", 1);
        }
}

void init()
{
        add_action("do_deed", "deed");
}

int do_deed(string arg)
{
        object me;

        me = this_player();

        if (! arg)return notify_fail("你要用房契做什么？\n");

        if (arg == "hide")
        {
                write("你把" + shop_name() + "房契隐藏了起来。\n");
                destruct(this_object());
                
                return 1;
        }        
        else if (arg == "register")
        {
                if (SHOP_D->is_shop_owner(shop_id(), me->query("id")))
                        return notify_fail("你不已经是" + shop_name() + "的主人了吗？\n");

                write(HIC "你在" + shop_name() + HIC"的房契上签上了你的大名：" + me->name() + "\n" NOR);
                write(HIG "恭喜你成为" + shop_name() + HIG "的主人。\n" NOR);

                SHOP_D->change_owner(me, shop_id(), me->query("id"));
                log_file("shop", me->query("id") + " at " + ctime(time()) + " 成为"+ shop_id() + "的主人。\n");

                return 1;
        }
        
        else
                return notify_fail("你要用房契做什么？\n");

}



