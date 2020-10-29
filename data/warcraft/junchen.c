// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("快车[2;37;0m[2;37;0m", ({"kkkkk"}));        
        set("gender", "男性");                
        set("long", "快车[2;37;0m
它是俊俊的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "junchen");
        set("owner_name", "俊俊");
        set_temp("owner", "junchen");
        set_temp("owner_name", "俊俊");
        ::setup();
}
