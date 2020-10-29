// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("跳蚤[2;37;0m[2;37;0m", ({"sleepbag"}));        
        set("gender", "女性");                
        set("long", "跳蚤[2;37;0m
它是黑臭虫的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "bugc");
        set("owner_name", "黑臭虫");
        set_temp("owner", "bugc");
        set_temp("owner_name", "黑臭虫");
        ::setup();
}
