// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("跟屁虫[1;35m[2;37;0m[2;37;0m", ({"ddddd"}));        
        set("gender", "女性");                
        set("long", "看！灰机[2;37;0m
它是焱馨的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "sssss");
        set("owner_name", "焱馨");
        set_temp("owner", "sssss");
        set_temp("owner_name", "焱馨");
        ::setup();
}
