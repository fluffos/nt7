// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("彩云[2;37;0m[2;37;0m", ({"sleepbag"}));        
        set("gender", "女性");                
        set("long", "翱翔高空的朱雀[2;37;0m
它是马可夫的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "markov");
        set("owner_name", "马可夫");
        set_temp("owner", "markov");
        set_temp("owner_name", "马可夫");
        ::setup();
}
