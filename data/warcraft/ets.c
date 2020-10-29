// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;35m粉红朱雀[2;37;0m[2;37;0m", ({"etspet"}));        
        set("gender", "男性");                
        set("long", "一只幼小的粉红朱雀！[2;37;0m
它是外星女的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "ets");
        set("owner_name", "外星女");
        set_temp("owner", "ets");
        set_temp("owner_name", "外星女");
        ::setup();
}
