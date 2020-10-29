// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m红莲老猪[2;37;0m[2;37;0m", ({"redi"}));        
        set("gender", "男性");                
        set("long", "。。。。[2;37;0m
它是绿莲老猪的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "rcdl");
        set("owner_name", "绿莲老猪");
        set_temp("owner", "rcdl");
        set_temp("owner_name", "绿莲老猪");
        ::setup();
}
