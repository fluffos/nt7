#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIG "册马石" NOR, ({ "cema shi", "cema", "shi", "stone" }) );
        set_weight(100);

        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("long", HIG "一块光滑如玉的石头，隐约可见其中镶有一匹骏马，乃天然形成。\n"
                            "使用 loghorse 命令可使你增加一条骑马记录点。\n" 
                            "如果暂时不使用，最好将册马石存入仓库，以免丢失。\n" NOR);
                set("value", 1);
                set("no_sell", 1);
                set("unit", "块");
        }

        setup();
}

void init()
{
        if (this_player() == environment())
        {
                add_action("do_changing", "loghorse");
        }
}

int do_changing(string arg)
{
        object me;
        me = this_player();

        me->add("horse/stone", 1);
        write(HIM "册马石使用成功，你的骑马记录点增加了！\n" NOR);
        me->save();
        destruct(this_object());

        return 1;
}

int query_autoload()
{
         return 1;
}