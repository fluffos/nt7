// xiaoyuanbao.c 小金元宝

#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(YEL "小金元宝" NOR, ({ "xiao yuanbao", "xiao", "yuanbao" }));
        set_weight(2000);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("long", "一只黄澄澄的金元宝。\n");
                set("value", 1200000);
                set("unit", "只");
        }
}

int query_autoload() { return 1; }