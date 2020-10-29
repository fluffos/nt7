// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;37m沧海明月[2;37;0m[2;37;0m", ({"mingyue"}));        
        set("gender", "女性");                
        set("long", "如一轮皎洁的海上明月一般从天边飞来[2;37;0m
它是孤月的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "moon");
        set("owner_name", "孤月");
        set_temp("owner", "moon");
        set_temp("owner_name", "孤月");
        ::setup();
}
