// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m门可罗雀[2;37;0m[2;37;0m", ({"woa"}));        
        set("gender", "男性");                
        set("long", "门可罗雀啊！！！[2;37;0m
它是夜一的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "wowoa");
        set("owner_name", "夜一");
        set_temp("owner", "wowoa");
        set_temp("owner_name", "夜一");
        ::setup();
}
