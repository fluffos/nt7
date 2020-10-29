// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m火毒玄牛[2;37;0m[2;37;0m", ({"meccdpet"}));        
        set("gender", "女性");                
        set("long", "火毒玄牛[2;37;0m
它是阿兰夕月的魔幻兽。
");
        set("race_type", "玄武");
        set("magic/type", "water");
        set("owner", "meccd");
        set("owner_name", "阿兰夕月");
        set_temp("owner", "meccd");
        set_temp("owner_name", "阿兰夕月");
        ::setup();
}
