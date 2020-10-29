// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;37m[41;1m日本充气娃娃[1;37m[41;1m[2;37;0m[2;37;0m", ({"niao"}));        
        set("gender", "男性");                
        set("long", "她肤如凝脂，眉目如画，风情万种，楚楚动人。当真是我见犹怜！	[2;37;0m
它是血海飘香的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "dupengc");
        set("owner_name", "血海飘香");
        set_temp("owner", "dupengc");
        set_temp("owner_name", "血海飘香");
        ::setup();
}
