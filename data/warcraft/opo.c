// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("阿斯顿[2;37;0m[2;37;0m", ({"opod"}));        
        set("gender", "男性");                
        set("long", "阿斯顿[2;37;0m
它是聊天的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "opo");
        set("owner_name", "聊天");
        set_temp("owner", "opo");
        set_temp("owner_name", "聊天");
        ::setup();
}
