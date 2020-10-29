// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[35m百灵[2;37;0m[2;37;0m", ({"bird"}));        
        set("gender", "男性");                
        set("long", "朱雀[2;37;0m
它是春香的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "huac");
        set("owner_name", "春香");
        set_temp("owner", "huac");
        set_temp("owner_name", "春香");
        ::setup();
}
