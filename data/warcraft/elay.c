// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("我的兽王[2;37;0m[2;37;0m", ({"esw"}));        
        set("gender", "男性");                
        set("long", "我的兽王[2;37;0m
它是逆刃的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "elay");
        set("owner_name", "逆刃");
        set_temp("owner", "elay");
        set_temp("owner_name", "逆刃");
        ::setup();
}
