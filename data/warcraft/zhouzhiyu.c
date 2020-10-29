// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;37m天雷[2;37;0m[2;37;0m", ({"zzy"}));        
        set("gender", "男性");                
        set("long", "青天白日定乾坤，一遇天雷变作龙[2;37;0m
它是笑天刀的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "zhouzhiyu");
        set("owner_name", "笑天刀");
        set_temp("owner", "zhouzhiyu");
        set_temp("owner_name", "笑天刀");
        ::setup();
}
