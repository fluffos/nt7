// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;33m王八龟[2;37;0m[2;37;0m", ({"bie"}));        
        set("gender", "男性");                
        set("long", "王八龟[2;37;0m
它是名字好怪的魔幻兽。
");
        set("race_type", "玄武");
        set("magic/type", "water");
        set("owner", "simmmmer");
        set("owner_name", "名字好怪");
        set_temp("owner", "simmmmer");
        set_temp("owner_name", "名字好怪");
        ::setup();
}
