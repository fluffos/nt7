// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("丁恁碧[2;37;0m[2;37;0m", ({"dnb"}));        
        set("gender", "男性");                
        set("long", "丁恁碧[2;37;0m
它是段大妹的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "cescji");
        set("owner_name", "段大妹");
        set_temp("owner", "cescji");
        set_temp("owner_name", "段大妹");
        ::setup();
}
