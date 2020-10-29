// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("凤凰[2;37;0m[2;37;0m", ({"zhuque"}));        
        set("gender", "女性");                
        set("long", "quit[2;37;0m
它是蝶舞的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "raindrop");
        set("owner_name", "蝶舞");
        set_temp("owner", "raindrop");
        set_temp("owner_name", "蝶舞");
        ::setup();
}
