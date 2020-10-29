// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[31m小鸟[2;37;0m[2;37;0m", ({"xiaobai"}));        
        set("gender", "男性");                
        set("long", "一只小小鸟[2;37;0m
它是风飞二扬的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "seeflyb");
        set("owner_name", "风飞二扬");
        set_temp("owner", "seeflyb");
        set_temp("owner_name", "风飞二扬");
        ::setup();
}
