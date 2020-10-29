// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m魔剑[2;37;0m[2;37;0m", ({"mojian"}));        
        set("gender", "男性");                
        set("long", "这把剑已经成为一只魔兽！[2;37;0m
它是剑痴的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "jianchi");
        set("owner_name", "剑痴");
        set_temp("owner", "jianchi");
        set_temp("owner_name", "剑痴");
        ::setup();
}
