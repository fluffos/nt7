// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("书架[2;37;0m[2;37;0m", ({"sleepbag"}));        
        set("gender", "男性");                
        set("long", "书架[2;37;0m
它是书痴的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "books");
        set("owner_name", "书痴");
        set_temp("owner", "books");
        set_temp("owner_name", "书痴");
        ::setup();
}
