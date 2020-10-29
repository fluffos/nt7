// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[37m万年陆龟[2;37;0m[2;37;0m", ({"turtle"}));        
        set("gender", "男性");                
        set("long", "这是一只万年陆龟，打它不涨经验。[2;37;0m
它是慕容逵的魔幻兽。
");
        set("race_type", "玄武");
        set("magic/type", "water");
        set("owner", "null");
        set("owner_name", "慕容逵");
        set_temp("owner", "null");
        set_temp("owner_name", "慕容逵");
        ::setup();
}
