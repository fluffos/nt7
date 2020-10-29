// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("米虫[2;37;0m[2;37;0m", ({"wmbbb"}));        
        set("gender", "女性");                
        set("long", "米虫[2;37;0m
它是武米宝的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "wmb");
        set("owner_name", "武米宝");
        set_temp("owner", "wmb");
        set_temp("owner_name", "武米宝");
        ::setup();
}
