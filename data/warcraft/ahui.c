// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("白虎[2;37;0m[2;37;0m", ({"baihu"}));        
        set("gender", "女性");                
        set("long", "啊[2;37;0m
它是阿慧的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "ahui");
        set("owner_name", "阿慧");
        set_temp("owner", "ahui");
        set_temp("owner_name", "阿慧");
        ::setup();
}
