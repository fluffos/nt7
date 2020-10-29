// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m红布袋[2;37;0m[2;37;0m", ({"sleepbag"}));        
        set("gender", "男性");                
        set("long", "红布袋[2;37;0m
它是书书的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "ani");
        set("owner_name", "书书");
        set_temp("owner", "ani");
        set_temp("owner_name", "书书");
        ::setup();
}
