// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;37m啸天犬[2;37;0m[2;37;0m", ({"jingquan"}));        
        set("gender", "男性");                
        set("long", "啸天犬[2;37;0m
它是江小鱼的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "xiaoyu");
        set("owner_name", "江小鱼");
        set_temp("owner", "xiaoyu");
        set_temp("owner_name", "江小鱼");
        ::setup();
}
