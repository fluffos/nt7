// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("漫画书[2;37;0m[2;37;0m", ({"sleepbag"}));        
        set("gender", "女性");                
        set("long", "一本蜡笔小新一本蜡笔小新[2;37;0m
它是书中仙的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "book");
        set("owner_name", "书中仙");
        set_temp("owner", "book");
        set_temp("owner_name", "书中仙");
        ::setup();
}
