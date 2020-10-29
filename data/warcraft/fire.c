// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;33m灵书妙探[2;37;0m[2;37;0m", ({"castle"}));        
        set("gender", "男性");                
        set("long", "灵书妙探[2;37;0m
它是冰火之歌的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "fire");
        set("owner_name", "冰火之歌");
        set_temp("owner", "fire");
        set_temp("owner_name", "冰火之歌");
        ::setup();
}
