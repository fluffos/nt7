// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;37m花白朱雀[2;37;0m[2;37;0m", ({"slgpet"}));        
        set("gender", "女性");                
        set("long", "一只幼小的花白朱雀！[2;37;0m
它是蚊子的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "slg");
        set("owner_name", "蚊子");
        set_temp("owner", "slg");
        set_temp("owner_name", "蚊子");
        ::setup();
}
