// This program is a part of NITAN MudLIB 
// redl 2013/10
#include <ansi.h>

inherit ITEM;
inherit F_CLEAN_UP;

string load_name();
void create()
{
        set_name(HIK "洞天仙府令" NOR, ({ "dongtian ling", "ling"}));
        set_weight(100);
                set("unit", "枚");
                set("value", 20000000);
                set("dt_value", 2);
                set("weight", 2000);
        setup();
        set("dt_name", load_name());
}        

string load_name()
{
        return __DIR__"guangchang.c"->load_name();
}

string long()
{
        if (!query("dt_name") || !query("dt_time") || query("dt_time") < time()) {
                set("dt_name", load_name());
                set("dt_time", time() + 60);
        }
        return "这是一枚银质令牌，有金篆文刻字『" + query("dt_name") + "』。\n";
}

