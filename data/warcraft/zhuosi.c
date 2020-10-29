// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;36m小萤火虫[2;37;0m[2;37;0m", ({"firebug"}));        
        set("gender", "男性");                
        set("long", "莹莹之火，可以燎原！[2;37;0m
它是卓小航的魔幻兽。
");
        set("race_type", "玄武");
        set("magic/type", "water");
        set("owner", "zhuosi");
        set("owner_name", "卓小航");
        set_temp("owner", "zhuosi");
        set_temp("owner_name", "卓小航");
        ::setup();
}
