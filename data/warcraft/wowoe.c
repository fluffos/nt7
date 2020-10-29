// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;35m怡堂燕雀[2;37;0m[2;37;0m", ({"woe"}));        
        set("gender", "女性");                
        set("long", "怡堂燕雀!!![2;37;0m
它是夜五的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "wowoe");
        set("owner_name", "夜五");
        set_temp("owner", "wowoe");
        set_temp("owner_name", "夜五");
        ::setup();
}
