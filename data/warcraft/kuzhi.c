// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[31m默契[2;37;0m[2;37;0m", ({"moqi"}));        
        set("gender", "男性");                
        set("long", "你我的默契[2;37;0m
它是枯枝的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "kuzhi");
        set("owner_name", "枯枝");
        set_temp("owner", "kuzhi");
        set_temp("owner_name", "枯枝");
        ::setup();
}
