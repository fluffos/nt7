#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIG "蛇精鳞片" NOR, ({"shejing linpian", "shejing", "linpian"}));
        set_weight(300);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("long", HIG "一片从蛇精身上获取的鳞片，是勇者的象征。\n" NOR);
                set("unit", "片");
        }
}

int query_autoload()
{
        return 1;
}
