// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[30m黑甲龟[2;37;0m[2;37;0m", ({"sleepbag"}));        
        set("gender", "女性");                
        set("long", "厚无形，黑无色。[2;37;0m
它是空劫的魔幻兽。
");
        set("race_type", "玄武");
        set("magic/type", "water");
        set("owner", "zyz");
        set("owner_name", "空劫");
        set_temp("owner", "zyz");
        set_temp("owner_name", "空劫");
        ::setup();
}
