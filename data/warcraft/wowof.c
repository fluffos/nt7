// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[35m隋珠弹雀[2;37;0m[2;37;0m", ({"wof"}));        
        set("gender", "女性");                
        set("long", "隋珠弹雀!!![2;37;0m
它是夜六的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "wowof");
        set("owner_name", "夜六");
        set_temp("owner", "wowof");
        set_temp("owner_name", "夜六");
        ::setup();
}
